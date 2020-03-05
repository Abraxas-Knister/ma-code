#include "m-setup.hpp"
#include <cmath>
#include <Eigen/Eigenvalues>

bool checktwo(const m_operator_t &, const int);
m_state_t Setup::gdstate() const
{
    Eigen::SelfAdjointEigenSolver<m_operator_t> solver(H);
    for (int i=0; i<16; i++)
    {
        if (checktwo(solver.eigenvectors(),i)) return solver.eigenvectors().col(i);
    }
    MSG_1("Couldn't find groundstate with two particles.");
}

bool checktwo(const m_operator_t &m, const int col)
{
    for (int i=0; i<16; i++)
    {
        switch (i) {
            case 3:
            case 5:
            case 6:
            case 9:
            case 10:
            case 12:
                if (!areNear(std::fabs(m(i,col)),absEps)) { return true; }
        }
    }
    return false;
}

