#include "../src/random.hpp"

#include <iostream>
#include <vector>

int main()
{
    std::cerr << "trying to reach the random samples without seeding\n";
    try { 
        std::cerr << "rand();\n";
        Random::rand();
        throw 0;
    }
    catch (int) { std::cerr << "Did not catch.\n"; }
    catch (...) { std::cerr << "Catch succeeded.\n"; }
    try { 
        std::cerr << "grand();\n";
        Random::grand(0,1);
        throw 0;
    }
    catch (int) { std::cerr << "Did not catch.\n"; }
    catch (...) { std::cerr << "Catch succeeded.\n"; }

    std::cerr << "now seeding.\n";
    Random::seed();

    std::vector<int> v(20,0);
    std::cerr << "trying uniform.\n";
    int ct = 400;
    while (ct--)
    {
        int r = static_cast<int>( Random::rand()*20);
        if (r<0) continue;
        if (r>19) continue;
        v[r]+=1;
    }
    for (auto i:v)
    {
        while (i--) std::cerr << '*';
        std::cerr << '\n';
    }
    v.assign(20,0);
    std::cerr << "trying gauss, mu = 5, sigma**2 = 4.\n";
    ct = 400;
    while (ct--)
    {
        int r = static_cast<int>( Random::grand(6,4) );
        if (r<0) continue;
        if (r>19) continue;
        v[r]+=1;
    }
    for (auto i:v)
    {
        while (i--) std::cerr << '*';
        std::cerr << '\n';
    }

    Random::static_seed(0);
    return 0;
}
