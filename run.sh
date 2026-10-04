#!/bin/sh
# run.sh <platform> — every experiment on this machine, into results/<platform>/.
#
# Needs a C compiler with OpenMP (CC, default cc), python3, and a built Sword
# compiler (SHIELD, default ../sword/shield). Thread counts are THREADS.
set -eu
here=$(cd "$(dirname "$0")" && pwd)
platform=${1:?usage: run.sh <platform>}
CC=${CC:-cc}
SHIELD=${SHIELD:-$here/../sword/shield}
THREADS=${THREADS:-"1 2 3 4 6 8 10 16"}
SUM_N=${SUM_N:-10000000}
MC_N=${MC_N:-10000000}
MATH_N=${MATH_N:-1000000}
REPS=${REPS:-7}
# ONLY=math skips everything that needs OpenMP. NOTE is written into env.txt,
# for what a reader has to know about the machine (emulated, say).
ONLY=${ONLY:-all}
# Apple's clang has OpenMP only as a preprocessor pass over Homebrew's libomp.
if [ -z "${OMPFLAGS:-}" ] && [ "$(uname)" = Darwin ]; then
    omp=$(brew --prefix libomp 2>/dev/null || echo /opt/homebrew/opt/libomp)
    OMPFLAGS="-Xpreprocessor -fopenmp -I$omp/include -L$omp/lib -lomp"
fi
OMPFLAGS=${OMPFLAGS:--fopenmp}
NOTE=${NOTE:-}
out=$here/results/$platform
mkdir -p "$out"
build=$(mktemp -d)
trap 'rm -rf "$build"' EXIT

{
    echo "platform: $platform"
    echo "date: $(date -u +%Y-%m-%dT%H:%M:%SZ)"
    echo "uname: $(uname -srm)"
    if [ -r /proc/cpuinfo ]; then
        echo "cpu: $(grep -m1 -E 'model name|^Model|CPU part' /proc/cpuinfo | cut -d: -f2- | sed 's/^ //')"
    else
        echo "cpu: $(sysctl -n machdep.cpu.brand_string 2>/dev/null)"
    fi
    echo "cores: $(getconf _NPROCESSORS_ONLN)"
    echo "cc: $($CC --version | head -1)"
    echo "openmp: $OMPFLAGS"
    echo "shield: $($SHIELD --version)"
    echo "sword commit: ${SWORD_REV:-$(git -C "$(dirname "$SHIELD")" rev-parse --short HEAD 2>/dev/null || echo unknown)}"
    echo "python: $(python3 --version)"
    echo "threads: $THREADS"
    echo "sum_n: $SUM_N mc_n: $MC_N math_n: $MATH_N reps: $REPS"
    echo "only: $ONLY"
    [ -n "$NOTE" ] && echo "note: $NOTE"
} > "$out/env.txt"

# The inputs must be the same bytes on every machine; their hashes go into
# inputs.txt so that the analysis can refuse to compare ones that are not.
hashes() {
    (cd "$build" && python3 -c 'import hashlib, sys
for p in sys.argv[1:]:
    print(p, hashlib.sha256(open(p, "rb").read()).hexdigest())' "$@") >> "$out/inputs.txt"
}
: > "$out/inputs.txt"

$CC -O2 -o "$build/args" "$here/math/args.c" -lm
$CC -O2 -o "$build/libm" "$here/math/libm.c" -lm
$SHIELD "$here/math/num.sword" -o "$build/num_sword"

if [ "$ONLY" = all ]; then
$CC -O2 -o "$build/gen" "$here/data/gen.c" -lm
$CC -O2 $OMPFLAGS -o "$build/sum_omp" "$here/sum/sum_omp.c"
$CC -O2 $OMPFLAGS -o "$build/mc_omp" "$here/mc/mc_omp.c" -lm
$SHIELD "$here/sum/sum.sword" -o "$build/sum_sword"
$SHIELD "$here/mc/mc.sword" -o "$build/mc_sword"

# E1: summation.
(cd "$build" && ./gen "$SUM_N")
hashes uniform.bin mixed.bin
python3 "$here/data/reference.py" "$build/uniform.bin" "$build/mixed.bin" |
    sed "s|$build/||" > "$out/reference.csv"
echo "data,method,threads,bits,value,median_ns" > "$out/sum.csv"
for data in uniform mixed; do
    "$build/sum_omp" "$build/$data.bin" serial 1 "$REPS" | sed "s/^/$data,/" >> "$out/sum.csv"
    for t in $THREADS; do
        for m in omp ompkahan; do
            "$build/sum_omp" "$build/$data.bin" $m "$t" "$REPS" | sed "s/^/$data,/" >> "$out/sum.csv"
        done
        for m in plain kahan exact; do
            SWORD_THREADS=$t "$build/sum_sword" "$build/$data.bin" $m "$REPS" | sed "s/^/$data,/" >> "$out/sum.csv"
        done
    done
done

# E1b: the same configuration again and again, the thread count fixed.
REPEAT=${REPEAT:-100}
REPEAT_THREADS=${REPEAT_THREADS:-"2 4 8 16"}
echo "data,method,threads,bits,value,median_ns" > "$out/repeat.csv"
for t in $REPEAT_THREADS; do
    for r in $(seq 1 "$REPEAT"); do
        "$build/sum_omp" "$build/mixed.bin" omp "$t" 1 | sed "s/^/mixed,/" >> "$out/repeat.csv"
        SWORD_THREADS=$t "$build/sum_sword" "$build/mixed.bin" plain 1 | sed "s/^/mixed,/" >> "$out/repeat.csv"
    done
done

# E2: Monte Carlo.
echo "method,threads,bits,value,median_ns" > "$out/mc.csv"
for t in $THREADS; do
    for m in thread index philox; do
        "$build/mc_omp" $m "$MC_N" "$t" 5 >> "$out/mc.csv"
    done
    for m in plain mix exact; do
        SWORD_THREADS=$t "$build/mc_sword" $m "$MC_N" 5 >> "$out/mc.csv"
    done
done

fi

# E3: elementary functions; the result bits are kept for comparing platforms.
(cd "$build" && ./args "$MATH_N")
hashes trig.bin near.bin exp.bin unit.bin log.bin
(cd "$build" && mkdir -p out && ./libm "$platform" > libm.csv &&
    ./num_sword "$platform" > num.csv)
{ echo "fn,count,ns_per_call"; cat "$build/libm.csv" "$build/num.csv"; } > "$out/math.csv"
mkdir -p "$out/bits"
cp "$build"/out/*.bin "$out/bits/"
echo "done: $out"
