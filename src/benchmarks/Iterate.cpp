#include "Map.h"
#include "bench.h"
#include "sfc64.h"

BENCHMARK(IterateIntegers) {
    sfc64 rng(123);

    size_t const num_iters = 50000;

    uint64_t result = 0;
    Map<int, int> map;

    auto const state = rng.state();
    bench.beginMeasure("iterating");
    for (size_t n = 0; n < num_iters; ++n) {
        map[rng()] = n;
        for (auto const& keyVal : map) {
            result += keyVal.first;
        }
    }

    rng.state(state);
    for (size_t n = 0; n < num_iters; ++n) {
        map.erase(rng());
        for (auto const& keyVal : map) {
            result += keyVal.first;
        }
    }
    bench.endMeasure(UINT64_C(18439538569855951616), result);
}
