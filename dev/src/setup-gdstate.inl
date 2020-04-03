bool checktwo(const Setup::operator_t &, const int);
void Setup::setGdstate()
{
    Eigen::SelfAdjointEigenSolver<Setup::operator_t> solver(H);
    for (int i=0; i<16; i++)
    {
        if (checktwo(solver.eigenvectors(),i))
        {
            groundstate = solver.eigenvectors().col(i);
            return;
        }
    }
    throw "Couldn't find groundstate with two particles.";
}

bool checktwo(const Setup::operator_t &m, const int col)
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
                if (!areNear(std::abs(m(i,col)))) { return true; }
        }
    }
    return false;
}
