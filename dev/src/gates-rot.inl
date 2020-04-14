// "rotate" ie introduce phase between up and dw
std::function<unitary> QC::R(double pimul)
{
    complex phase { std::exp(IU*PI*pimul) };
    return
        [phase] (complex& up,complex&) -> void
        {
            up *= phase;
        }
    ;
}
std::function<unitary> QC::R(double by, double theta, double phi)
{
    // calculate the direction vector around which to turn
    double
        ct  {std::cos(theta)}, st  {std::sin(theta)},
        cp  {std::cos(phi)}  , sp  {std::sin(phi)};
    double
        x {st*cp}, y {st*sp}, z {ct};
    /* rotation is:
     * exp ( i*by*<v,s> )
     *  = cos(by) Id + i sin(by) <v,s>
     */
    /* <v,s> = x X + y Y + z Z
     *
     *   ( 0 x ) + ( 0 -iy ) + ( z 0  )
     * = ( x 0 ) + ( iy 0  ) + ( 0 -z )
     */
    complex
        dd {z}      , du {x-IU*y},
        ud {x+IU*y} , uu {-z};
    complex
        cos { std::cos(by*0.5*PI) }, isin { IU*std::sin(by*0.5*PI) };
    return
        [=] (complex& up, complex& dw) -> void
        {
            complex
                d = cos*dw - isin*(dd*dw+du*up),
                u = cos*up - isin*(ud*dw+uu*up);
            dw = d;
            up = u;
        }
    ;
}
std::function<unitary> QC::disturb(double degree)
{
    double
        by    { Random::grand(0,degree) },
        theta { Random::rand()*PI },
        phi   { Random::rand()*2.0*PI };
    return R(by,theta,phi);
}
