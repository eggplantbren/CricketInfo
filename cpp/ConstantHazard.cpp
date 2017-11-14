#include "ConstantHazard.h"
#include <Utils.h>

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

double ConstantHazard::perturb(InfoNest::RNG& rng)
{
    double logH = 0.0;

    // Different kinds of proposal
    int which = rng.rand_int(3);

    if(which == 0)
    {
        // Perturb mu
        mu = log(mu);
        logH -= -0.5*pow((mu - log(25.0)) / 0.75, 2);
        mu += 0.75*rng.randh();
        logH += -0.5*pow((mu - log(25.0)) / 0.75, 2);
        mu = exp(mu);
    }
    else if(which == 1)
    {
        // Regenerate some of the us
        int reps = static_cast<int>(pow(static_cast<double>(N), rng.rand()));
        for(int i=0; i<reps; ++i)
            us[rng.rand_int(N)] = rng.rand();
        compute_xs();
    }
    else
    {
        // Perturb a single u
        int i = rng.rand_int(N);
        us[i] += rng.randh();
        InfoNest::wrap(us[i], 0.0, 1.0);
        compute_xs();        
    }

    return logH;
}

void ConstantHazard::print(std::ostream& out) const
{
    out << mu << ' ';
}

double ConstantHazard::parameter_distance(const ConstantHazard& s1,
                                          const ConstantHazard& s2)
{
    return std::abs(s1.mu - s2.mu);
}

} // namespace CricketInfo

