#include <ctime>
#include <iostream>
#include <Execute.hpp>
#include "ConstantHazard.h"
#include "RNG.h"

int main()
{
    // Create random number generators
    // The first one is used to generate reference points
    // and the second is used for the Nested Sampling
    unsigned long seed0 = 0;
    unsigned long seed1 = time(0);
    InfoNest::RNG rng0(seed0);
    InfoNest::RNG rng1(seed1);

    // Define run parameters
    constexpr double depth         = 1000.0;
    constexpr size_t num_reps      = 1000;
    constexpr size_t num_particles = 10;
    constexpr size_t mcmc_steps    = 10000;

    // Do the run.
    InfoNest::execute<CricketInfo::ConstantHazard>
                        (rng0, rng1,
                         depth, num_reps, num_particles, mcmc_steps,
                         CricketInfo::ConstantHazard::parameter_distance);


    return 0;
}

