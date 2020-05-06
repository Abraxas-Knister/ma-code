double res_model(const std::pair<double,double> &dat,
                 const dlib::matrix<double,3,1> &par)
{
    return (par(0)-1.0)*std::cos(dat.first/par(1))
           -par(0)     *std::cos(dat.first/par(2))
                                      - dat.second;
}

double guessa(const std::vector<std::pair<double,double>>&,const double);
double guessb(double,const std::vector<std::pair<double,double>>&);
double guessc(double,const std::vector<std::pair<double,double>>&,const double,const double);
#include "twosite-guess.inl"

double qpartmass(double,double,double,double);
double timestep(double,double);

void Twosite::ckparams(double &V)
{
    /* This method will change V to the hybridisation that is in agreement with
     * the data in "greensfunction" in assumption that is is sampled in
     * timesteps of tstep difference beginning at 0.
     *
     * It will try to set a new tstep.
     */

    /* the model function for the greensfunction is:
     *
     *  - i ( (a-1) cos (t/b) - a cos(t/c) )
     */

    // get imag
    std::vector<std::pair<double,double>> scale;
    {
        int ct=-1;
        for (auto i:greensfunction)
              scale.push_back( std::make_pair(++ct*tstep,i.imag()) );
    }
    // get first guess for b, then a, then c
    double a, b = guessb(0.1,scale)*tstep, c;
    if (!b) {
        a = guessa(scale,b);
        c = guessc(a*0.5,scale,a,b)*tstep;
        dlib::matrix<double,3,1> par = {a,b,c};
        dlib::solve_least_squares_lm(dlib::objective_delta_stop_strategy(1e-7),
            res_model,dlib::derivative(res_model),scale,par);
        a = par(0); b = par(1); c = par(2);
        double newV = std::sqrt(qpartmass(a,b,c,V));
        if (std::isnormal(newV))
              V = newV;
        tstep = timestep(a,b);
    } else {
        tstep *= 10.0;
    }
}

double qpartmass(double a, double b, double c, double V)
{
    /* fourier transforming the model leads to
     *    G(w)   = (
     * the self energy is
     *    S(w)   =  1/G0(w) - 1/G(w)
     * with
     *    G0(w)  =  1/(w + mu - V/w)
     * which means that
     *    dS/dw | w=0
     *           =
     * and therefore
     *    Z      = 
     */
    return 1.0;
}

double timestep(double,double);
