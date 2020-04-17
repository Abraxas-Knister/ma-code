#include "../src/fourier.hpp"

#include <cmath>
#include <iostream>
#include <fstream>

int main ()
{
    std::vector<complex> v (200);
    std::cerr << "creating a " << v.size() << " long Fourier instance.\n";
    Fourier * f = new Fourier(v.size());

    int x = 10;
    for (std::size_t i{ 0 }; i<v.size(); ++i)
          v[i] = std::sin(x*2.0*PI*i/static_cast<double>(v.size()));
    std::cerr << "Updating it with " << x << " sine periods.\n";

    f->update(v,1.0/v.size());

    std::cerr << "write to cout\n";

    std::cout << *f;
    delete f;
}
