#include "m-setup.hpp"
#include <Eigen/Eigenvalues>

m_state_t Setup::gdstate() const
{
    Eigen::SelfAdjointEigenSolver<m_operator_t> solver(H);
    return solver.eigenvectors().col(1);
}
