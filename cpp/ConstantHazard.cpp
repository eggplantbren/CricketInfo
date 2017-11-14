#include "ConstantHazard.h"
#include <Utils.h>

namespace CricketInfo
{

ConstantHazard::ConstantHazard()
:xs(N)
{

}

void ConstantHazard::generate(InfoNest::RNG& rng)
{
    mu = 25.0*exp(0.75*rng.randn());

    generate_xs(rng);
    compute_logl();
}

void ConstantHazard::generate_xs(InfoNest::RNG& rng)
{
    double p = 1.0/(mu + 1.0);
    double val = 1.0/log(1.0 - p);

    for(size_t i=0; i<N; ++i)
        xs[i] = static_cast<int>(log(1.0 - rng.rand())*val);
}


void ConstantHazard::compute_logl()
{
    logl = 0.0;

    double a = log(1.0 / (mu + 1.0));
    double b = log(mu / (mu + 1.0));

    for(size_t i=0; i<N; ++i)
        logl += a + xs[i]*b;
}

double ConstantHazard::perturb(InfoNest::RNG& rng)
{
    double logH = 0.0;

    logH -= logl;

    // Perturb mu
    mu = log(mu);
    logH -= -0.5*pow((mu - log(25.0)) / 0.75, 2);
    mu += 0.75*rng.randh();
    logH += -0.5*pow((mu - log(25.0)) / 0.75, 2);
    mu = exp(mu);

    compute_logl();
    logH += logl;

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

