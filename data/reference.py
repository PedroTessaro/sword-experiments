# The correctly rounded sum of each input, by Python's math.fsum (Shewchuk's
# algorithm) -- an answer that does not come from any program under test.
import math, struct, sys
for path in sys.argv[1:]:
    raw = open(path, "rb").read()
    xs = struct.unpack("<%dd" % (len(raw) // 8), raw)
    s = math.fsum(xs)
    print("%s,%016x,%.17g" % (path, struct.unpack("<Q", struct.pack("<d", s))[0], s))
