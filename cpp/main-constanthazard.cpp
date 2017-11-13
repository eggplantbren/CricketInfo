#include <iostream>
#include "ConstantHazard.h"
#include "RNG.h"

int main()
{
    InfoNest::RNG rng(0);

    CricketInfo::ConstantHazard c;
    c.generate(rng);

    return 0;
}

