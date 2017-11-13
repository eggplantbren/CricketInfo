#ifndef CricketInfo_ConstantHazard
#define CricketInfo_ConstantHazard

// Includes
#include <ostream>
#include <RNG.h>
#include <vector>

namespace CricketInfo
{

/*
* Batting stuff with a constant hazard model (i.e., just a geometric
* conditional prior for scores).
*/
class ConstantHazard
{
    private:

        // Parameter
        double mu;

        // Number of scores
        static constexpr size_t N = 100;

        // The scores, and the latent us that produce them
        std::vector<double> us;
        std::vector<int> xs;

        // Compute the xs from the us
        void compute_xs();

    public:

        // Do-nothing constructor
        ConstantHazard();

        // Generate from the distribution
        void generate(InfoNest::RNG& rng);

        // Metropolis proposal
        double perturb(InfoNest::RNG& rng);

        // Printing to stream
        void print(std::ostream& out) const;

    public:

        // A few options to use for `distance`
        static double parameter_distance
                            (const ConstantHazard& s1,
                             const ConstantHazard& s2);

        static double data_distance(const ConstantHazard& s1,
                                    const ConstantHazard& s2);

        static double joint_distance(const ConstantHazard& s1,
                                     const ConstantHazard& s2);
};

} // namespace CricketInfo

#endif

