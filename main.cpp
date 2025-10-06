#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#include <vector>
#include <array>
#include <future>
#include <random>
#include <cstdlib>

using time_point = std::chrono::time_point<std::chrono::steady_clock>;

int main(int argc, const char **argv)
{
  uint32_t number_of_threads{1};
  uint32_t number_of_steps{1};

  if (argc != 3)
  {
    std::cout << "Usage: stress T S\nWhere T and S are unsigned integers representing number of threads and number of steps"
              << std::endl;
    std::cout << "Bad usage. Give me the numnber of threads to run and the "
                 "number of steps for each thread to run."
              << std::endl;
    std::exit(1);
  }

  try
  {
    number_of_threads = std::stoi(argv[1]);
    number_of_steps = std::stoi(argv[2]);
  }
  catch (std::invalid_argument e)
  {
    std::cout << "Bad number of threads or steps" << std::endl;
    std::exit(2);
  }

  std::cout << "Starting CPU stress test..." << std::endl;
  time_point start_time = std::chrono::steady_clock::now();

  std::vector<std::future<void>> futures;
  for (int i = 0; i < number_of_threads; i++)
  {
    futures.emplace_back(std::async(std::launch::async, [&]()
                                    {
      double result = 1.0;
      for (uint32_t i = 0; i < number_of_steps; ++i) {
        for (uint32_t j = 0; j < 1000000; j++) 
        {
          result = std::sqrt(result + i);
          result = std::sin(result);
          result = std::cos(result);
        }
      } }));
  }

  for (const std::future<void> &aFuture : futures)
  {
    aFuture.wait();
  }

  time_point end_time = std::chrono::steady_clock::now();

  std::cout << "CPU stress test completed." << std::endl;

  std::chrono::duration<double> diff = end_time - start_time;
  std::cout << "Elapsed time: " << diff.count() << std::endl;

  return 0;
}
