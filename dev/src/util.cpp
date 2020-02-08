#include "config.hpp"
#include "debug.hpp"

#include <algorithm>    // for std::max
#include <cmath>        // for std::abs
#include <fstream>      // for std::ofstream(::app)

bool areNear( double a, double b )
// mostly relative comparison of floating point values
{
    MSG_2("near?");
    double diff = std::abs(a-b);
    bool ret { diff <= absEps };
    if (ret) {
        MSG_1("abs near");
        return true;
    }
    ret = ( diff <= (std::max(std::abs(a), std::abs(b)) * relEps) );
    MSG_2("rel near: " + std::to_string(ret) );
    return ret;
}

std::string debugString {""};

void writeDebug(const std::string &f)
{
    std::ofstream log ("log/"+f, std::ofstream::app);
    log << debugString + " = = = = = = = = = = = = = = = = \n";
    log.close();
}

int debugMsgID()
{
    static unsigned ID{0};
    return ID++;
}
