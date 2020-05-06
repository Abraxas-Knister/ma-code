double guessb(double thresh, const std::vector<std::pair<double,double>>& scale)
{
    double mean=0.0;
    int lidx=0,ct=0;
    bool out=true, first = true;
    for (std::size_t i=0; i<scale.size(); ++i)
    {
        if (std::abs(scale[i].second) < thresh)
        {
            if (out)
            {
                out = false;
                if (!first)
                {
                    mean += i-lidx;
                    ++ct;
                } else { first = false; }
                lidx = i;
            }
        } else {
            out = true;
        }
    }
    if (!ct) return 0.0;
    return mean/ct/PI;
}

double guessa(const std::vector<std::pair<double,double>>& scale,const double b)
{
    double curmax=0.0;
    for (const auto& m : scale)
    {
        double cur = m.second + std::cos(m.first/b);
        if ( std::abs(cur) < curmax)
              return curmax/2.0;
        else curmax = std::abs(cur);
    }
    return 0.0;
}

double guessc(double thresh, const std::vector<std::pair<double,double>>& scale,
              const double a, const double b)
{
    std::vector<std::pair<double,double>> newscale;
    for (const auto &m:scale)
    {
        double sec = m.second + std::cos(m.first/b)*(1.0-a);
        newscale.push_back(std::make_pair(m.first,sec));
        if (m.first > b*2.0*PI) break;
    }
    return guessb(thresh,newscale);
}

