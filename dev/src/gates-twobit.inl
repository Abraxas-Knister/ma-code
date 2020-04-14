/* implementing
 *  exp ( i d XX ) 
 *  ..........YY..
 *  ..........ZZ..
 * by reducing XX ... to single rotations exp (i d X)
 *
 * exp ( idX ) describes the rotation by -2d, Rig::gate(bit,X,r) needs to be
 * called with r = -2*d/PI
 */
void XX(Rig& r, int a, int b, double rarg)
{
    /* X_1 X_2
     *  = C_1_X_2 | X_1 | C_1_X_2
     */
    using namespace QC;
    r.gate(b,X,a).gate(a,X,-2.0*rarg/PI).gate(b,X,a);
}
void YY(Rig& r, int a, int b, double rarg)
{
    /* Y_1 Y_2
     *  = C_1_Y_2 | Y_1 | C_1_Y_2
     */
    using namespace QC;
    r.gate(b,Y,a).gate(a,Y,-2.0*rarg/PI).gate(b,Y,a);
}
void ZZ(Rig& r, int a, int b, double rarg)
{
    /* exp ( i d Z_1 Z_2 ):
     *
     * Z_1 Z_2
     *  = C_1_X_2 | Z_2 | C_1_X_2
     */
    using namespace QC;
    r.gate(b,X,a).gate(b,Z,-2.0*rarg/PI).gate(b,X,a);
}
