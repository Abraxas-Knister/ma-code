#include "random.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>

bool Random::seeded = false;

void Random::seed()
{
    if(Random::seeded)
          assert(0 && "seeded twice");
    Random::seeded = true;
    std::srand(std::time(nullptr));
}
void Random::static_seed(int seed)
{
    if(Random::seeded)
          assert(0 && "seeded twice");
    Random::seeded = true;
    std::srand(seed);
}
double Random::rand()
{
    Random::check();
    static constexpr double frac { 1.0 /( 1.0 + RAND_MAX ) };
    return std::rand()*frac;
}
double Random::grand(double mean, double stddev)
{
    Random::check();
    static double n2 = 0.0;
    static bool n2_cached { false };
    if (!n2_cached)
    {
        double x, y, r;
        do
        {
            x = 2.0 * std::rand()/RAND_MAX - 1.0;
            y = 2.0 * std::rand()/RAND_MAX - 1.0;

            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);

        double d = std::sqrt( - 2.0 * std::log(r)/r );

        n2 = y*d;
        n2_cached = true;

        double n1 = x*d;
        double result = n1*stddev + mean;
        return result;
    } else {
        n2_cached = false;
        return n2*stddev + mean;
    }
}
