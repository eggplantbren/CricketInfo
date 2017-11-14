#ifndef CricketInfo_ExponentialHazard
#define CricketInfo_ExponentialHazard

// Includes
#include <ostream>
#include <RNG.h>
#include <vector>

namespace CricketInfo
{

double logsumexp(const std::vector<double>& logv);

/*
* Batting stuff with an exponential hazard model
*/
class ExponentialHazard
{
    private:

        // Parameters
        double mu2, C, D;

        // Number of scores
        static constexpr size_t N = 100;
        static constexpr size_t max_score = 1000;

        // The scores
        std::vector<int> xs;

        // Log likelihood
        double logl;

        // Generate scores
        void generate_xs(InfoNest::RNG& rng);

        // Compute the log likelihood
        void compute_logl();


    public:

        // Do-nothing constructor
        ExponentialHazard();

        // Generate from the distribution
        void generate(InfoNest::RNG& rng);

        // Metropolis proposal
        double perturb(InfoNest::RNG& rng);

        // Printing to stream
        void print(std::ostream& out) const;

    public:

        // A few options to use for `distance`
        static double parameter_distance
                            (const ExponentialHazard& s1,
                             const ExponentialHazard& s2);

        static double data_distance(const ExponentialHazard& s1,
                                    const ExponentialHazard& s2);

        static double joint_distance(const ExponentialHazard& s1,
                                     const ExponentialHazard& s2);
};

} // namespace CricketInfo

#endif

