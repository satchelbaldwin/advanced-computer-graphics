#pragma once
#include <random>
#include <utility>
#include <vector>

typedef std::pair<double, double> Sample;
typedef std::vector<Sample> Samples;

class Sampler {
public:
  Sampler(int, int);
  int num_samples;
  int num_sets;
  std::vector<Samples> sets;

  void generate_jitter(int);
  int current_sample = 0;
  int current_set = 0;
  Sample next();

private:
  double random();
  std::random_device rd;
  std::mt19937 generator;
  std::uniform_real_distribution<double> dist;
};