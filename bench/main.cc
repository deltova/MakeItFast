#include <fstream>
#include <iostream>
#include <sstream>

#include <benchmark/benchmark.h>
#include <nlohmann/json.hpp>
#include <twitter.hh>

auto parseActions()
{
    std::ifstream bench("../../bench/bench.json");
    std::stringstream buffer;
    if (!bench.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        exit(0);
    }
    buffer << bench.rdbuf();
    return nlohmann::json::parse(buffer.str());
}

static void BM_WholeBench(benchmark::State& state)
{
    auto actions = parseActions();
    for (auto _ : state)
    {
        Twitter twitter = Twitter();
        for (const auto& action : actions)
        {
            if (action[0] == 0)
                twitter.follow(action[1], action[2]);
            if (action[0] == 1)
                twitter.unfollow(action[1], action[2]);
            if (action[0] == 2)
                twitter.postTweet(action[1], action[2]);
            if (action[0] == 3)
                twitter.getNewsFeed(action[1]);
        }
    }
}
// Register the function as a benchmark
BENCHMARK(BM_WholeBench)->Unit(benchmark::kMillisecond);
// Run the benchmark
BENCHMARK_MAIN();
