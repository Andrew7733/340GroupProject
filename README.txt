1. How big is a cache block?
After running  hundreds of test it looks like there was a steep drop off in performance most often at a stride of 80 and we are incrementing our stride in steps of 4 so we concluded that our cache has a line size of 76 Bytes.
2. How big is the cache?
3. How long does a reference to main memory take to complete?
Our data suggested a memory reference took ~120ns to complete
4. How long does a reference that can be satisfied from cache ta
ke to complete?
Our data suggest a reference in cache took ~6ns to complete




Actual non-experimental answers for my Intel i7 4770k:
    L1 Data cache = 32 KB, 64 B/line, 8-WAY.
    L1 Instruction cache = 32 KB, 64 B/line, 8-WAY.
    L2 cache = 256 KB, 64 B/line, 8-WAY
    L3 cache = 8 MB, 64 B/line