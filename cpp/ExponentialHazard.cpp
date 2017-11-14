#include "ExponentialHazard.h"
#include <algorithm>
#include <Utils.h>
#include <iostream>

namespace CricketInfo
{

ExponentialHazard::ExponentialHazard()
:xs(N)
{

}

void ExponentialHazard::generate(InfoNest::RNG& rng)
{
    // Lognormal
    mu2 = 25.0*exp(0.75*rng.randn());

    // Beta prior
    while(true)
    {
        C = rng.rand();
        if(rng.rand() <= (1.0 - C))
            break;
    }

    // Beta prior
    while(true)
    {
        D = rng.rand();
        if(rng.rand() <= (1.0 - pow(D, 4)))
            break;
    }

    generate_xs(rng);
    compute_logl();
}

void ExponentialHazard::generate_xs(InfoNest::RNG& rng)
{
    // Derived parameters
    double mu0 = C*mu2;
    double oneOverL = 1.0/(D*mu2);

    // Calculate effective average function
    std::vector<double> mu(max_score + 1);
    for(size_t i=0; i<mu.size(); ++i)
        mu[i] = mu0 + (mu2 - mu0)*exp(-static_cast<double>(i)*oneOverL);

    // Calculate probabilities
    std::vector<double> ps(max_score+1);
    ps[0] = 1.0;
    for(size_t i=1; i<ps.size(); ++i)
        ps[i] = ps[i-1]*mu[i]/(mu[i] + 1.0);
    for(size_t i=0; i<ps.size(); ++i)
        ps[i] *= 1.0/(mu[i] + 1.0);

    // Maximum probability
    double pMax = *std::max_element(ps.begin(), ps.end());

    for(size_t i=0; i<N; ++i)
    {
        while(true)
        {
            xs[i] = rng.rand_int(max_score + 1);
            if(rng.rand() <= ps[xs[i]]/pMax)
                break;
        }
    }
}


void ExponentialHazard::compute_logl()
{
    logl = 0.0;

    // Derived parameters
    double mu0 = C*mu2;
    double oneOverL = 1.0/(D*mu2);

    // Calculate effective average function
    std::vector<double> mu(max_score + 1);
    for(size_t i=0; i<mu.size(); ++i)
        mu[i] = mu0 + (mu2 - mu0)*exp(-static_cast<double>(i)*oneOverL);

    // Calculate log-probabilities
    std::vector<double> logps(max_score+1);
    logps[0] = 0.0;
    for(size_t i=1; i<logps.size(); ++i)
        logps[i] = logps[i-1] + log(mu[i]/(mu[i] + 1.0));
    for(size_t i=0; i<logps.size(); ++i)
        logps[i] += log(1.0/(mu[i] + 1.0));

    double log_ptot = logsumexp(logps);
    for(double& logp: logps)
        logp -= log_ptot;

    for(auto x: xs)
        logl += logps[x];
}

double ExponentialHazard::perturb(InfoNest::RNG& rng)
{
    double logH = 0.0;

    logH -= logl;

    int which = rng.rand_int(3);

    if(which == 0)
    {
        // Perturb mu2
        mu2 = log(mu2);
        logH -= -0.5*pow((mu2 - log(25.0)) / 0.75, 2);
        mu2 += 0.75*rng.randh();
        logH += -0.5*pow((mu2 - log(25.0)) / 0.75, 2);
        mu2 = exp(mu2);
    }
    else if(which == 1)
    {
        logH -= log(1.0 - C);
        C += rng.randh();
        InfoNest::wrap(C, 0.0, 1.0);
        logH += log(1.0 - C);
    }
    else
    {
        logH -= 4*log(1.0 - D);
        D += rng.randh();
        InfoNest::wrap(D, 0.0, 1.0);
        logH += 4*log(1.0 - D);
    }

    compute_logl();
    logH += logl;

    return logH;
}

void ExponentialHazard::print(std::ostream& out) const
{
    out << mu2 << ' ' << C << ' ' << D << ' ';
}

double ExponentialHazard::parameter_distance(const ExponentialHazard& s1,
                                             const ExponentialHazard& s2)
{
    return std::abs(s1.mu2 - s2.mu2);
}

double logsumexp(const std::vector<double>& logv)
{
	int n = static_cast<int>(logv.size());
	//if(n<=1)
	//	cout<<"Warning in logsumexp"<<endl;
	double max = *std::max_element(logv.begin(), logv.end());
	double answer = 0;
	// log(sum(exp(logf)) 	= log(sum(exp(logf - max(logf) + max(logf)))
	//			= max(logf) + log(sum(exp(logf - max(logf)))
	for(int i=0; i<n; i++)
		answer += exp(logv[i] - max);
	answer = max + log(answer);
	return answer;
}

} // namespace CricketInfo

