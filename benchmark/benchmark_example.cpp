#include <benchmark/benchmark.h>
#include "math_utils.h" // Include your math_utils.h header file

static void BM_AddFunction(benchmark::State &state)
{
    int a = 1, b = 2;
    // Perform the add function multiple times per iteration
    for (auto _ : state)
    {
        int sum = 0;
        for (int i = 0; i < 1000; ++i)
        { // Increase the loop count for longer execution time
            sum += add(a, b);
        }
        benchmark::DoNotOptimize(sum); // Prevent the compiler from optimizing out the computation
    }
}
// Register the function as a benchmark
BENCHMARK(BM_AddFunction);

// Main function to run the benchmark
BENCHMARK_MAIN();
