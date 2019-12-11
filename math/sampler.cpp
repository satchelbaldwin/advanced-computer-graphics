#include "sampler.hpp"
#include <iostream>

Sampler::Sampler(int n, int s)
    : num_samples(n), num_sets(s), generator(rd()), dist(0.0, 1.0) {}

double Sampler::random() { return dist(generator); }

void Sampler::generate_jitter(int subdivisions) {
  sets.clear();
  for (int s = 0; s < num_sets; ++s) {
    Samples set;
    // generate centers of unit square centered on 0, 0
    // adjust by
    for (int i = 0; i < subdivisions; ++i) {
      for (int j = 0; j < subdivisions; ++j) {
        double part = 1.0 / (double)subdivisions;
        double x = part * i + (part / 2);
        double y = part * j + (part / 2);
        std::cout << "x " << x << "y " << y << "\n";
        //x += random() * part - (part / 2) / 8;
        //y += random() * part - (part / 2) / 8;
        set.push_back(Sample(x - 0.5, y - 0.5));
      }
    }

    sets.push_back(set);
  }
}

Sample Sampler::next() {
  current_sample++;
  if (current_sample >= num_samples) {
    current_sample = 0;
    current_set = (int)floor(random() * num_sets);
  }
  Samples set = sets[0];
  return set[current_sample];
}