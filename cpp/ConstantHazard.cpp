#include "ConstantHazard.h"

namespace CricketInfo
{

ConstantHazard::ConstantHazard()
:us(N)
,xs(N)
{

}

void ConstantHazard::generate(InfoNest::RNG& rng)
{
    mu = 25.0*exp(0.75*rng.randn());

    for(double& u: us)
        u = rng.rand();

    compute_xs();
}

void ConstantHazard::compute_xs()
{
    double p = 1.0/(mu + 1.0);
    double val = 1.0/log(1.0 - p);

    for(size_t i=0; i<N; ++i)
        xs[i] = static_cast<int>(log(1.0 - us[i])*val);
}

} // namespace CricketInfo

