#ifndef CricketInfo_ConstantHazard
#define CricketInfo_ConstantHazard

// Includes
#include <ostream>
#include <vector>
#include <RNG.h>

namespace CricketInfo
{

/*
* Batting stuff with a constant hazard model (i.e., just a geometric
* conditional prior for scores).
*/
class ConstantHazard
{
    private:



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

