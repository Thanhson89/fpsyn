#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fenv.h>
#include <gmp.h>
#include <mpfr.h>

#define REAL double

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define Absolute(a)  ((a) >= 0.0 ? (a) : -(a))

REAL randfl_uniReal(a)
REAL a;
{
    return (REAL)rand()/((REAL)RAND_MAX/a);
}

REAL randfl(a)
int a;
{
    int r = (rand() % a)-(a/2);
	REAL t = (REAL)rand()/((REAL)RAND_MAX);
    return (t - (1/2))*pow(2,r);
}
//FPSyn Function
void FPSyn_InCircle(REAL ax,REAL ay,REAL bx,REAL by,REAL cx,REAL cy,REAL dx,REAL dy,REAL* result, REAL* error_bound){
//Calculation steps for input: ;
REAL t1=cx-dx;
REAL t3=cy-dy;
REAL t4=ax-dx;
REAL t5=by-dy;
REAL t6=ay-dy;
REAL t7=bx-dx;
REAL t8=t1*t1;
REAL t9=t3*t3;
REAL t10=t8+t9;
REAL t11=t4*t5;
REAL t12=t6*t7;
REAL t14=t11-t12;
REAL t15=t10*t14;
REAL t16=t4*t4;
REAL t17=t6*t6;
REAL t18=t16+t17;
REAL t19=t3*t7;
REAL t20=t1*t5;
REAL t22=t19-t20;
REAL t23=t18*t22;
REAL t24=t5*t5;
REAL t25=t7*t7;
REAL t26=t24+t25;
REAL t27=t3*t4;
REAL t28=t1*t6;
REAL t30=t27-t28;
REAL t31=t26*t30;
REAL t33=t15+t23;
REAL t34=t33-t31;
//Calculation steps for Error-bound: ;
t19=fabs(t19);
t34=fabs(t34);
t20=fabs(t20);
t28=fabs(t28);
t27=fabs(t27);
t11=fabs(t11);
t12=fabs(t12);
REAL tem0=t11+t12;
REAL tem1=t10*tem0;
REAL tem2=t19+t20;
REAL tem3=t18*tem2;
REAL tem4=t27+t28;
REAL tem5=t26*tem4;
REAL tem6=tem1+tem3;
REAL tem7=tem5+tem6;
REAL tem8=1.11022302462516e-15*tem7;
REAL tem9=1.11022302462516e-16*t34;
REAL tem10=tem8+tem9;
*result=t34;
*error_bound=1.0000000001*tem10;
}
//Manual Function
void Manual_InCircle(REAL ax,REAL ay,REAL bx,REAL by,REAL cx,REAL cy,REAL dx,REAL dy,REAL* result, REAL* error_bound){
//Calculation steps for input: ;
 REAL adx, bdx, cdx, ady, bdy, cdy;
 REAL bdxcdy, cdxbdy, cdxady, adxcdy, adxbdy, bdxady;
 REAL alift, blift, clift;
 REAL det;
 REAL permanent;

 adx = ax - dx;
 bdx = bx - dx;
 cdx = cx - dx;
 ady = ay - dy;
 bdy = by - dy;
 cdy = cy - dy;

  bdxcdy = bdx * cdy;
  cdxbdy = cdx * bdy;
  alift = adx * adx + ady * ady;

  cdxady = cdx * ady;
  adxcdy = adx * cdy;
  blift = bdx * bdx + bdy * bdy;

  adxbdy = adx * bdy;
  bdxady = bdx * ady;
  clift = cdx * cdx + cdy * cdy;

  det = alift * (bdxcdy - cdxbdy)
      + blift * (cdxady - adxcdy)
      + clift * (adxbdy - bdxady);

  permanent = (Absolute(bdxcdy) + Absolute(cdxbdy)) * alift
            + (Absolute(cdxady) + Absolute(adxcdy)) * blift
            + (Absolute(adxbdy) + Absolute(bdxady)) * clift;
*result=det;
*error_bound = 1.1102230246251577e-15 * permanent;


}
//IA Function
void IA_InCircle(REAL ax,REAL ay,REAL bx,REAL by,REAL cx,REAL cy,REAL dx,REAL dy,REAL* result, REAL* hbound, REAL* lbound){
REAL t1=cx-dx;
REAL t3=cy-dy;
REAL t4=ax-dx;
REAL t5=by-dy;
REAL t6=ay-dy;
REAL t7=bx-dx;
REAL t8=t1*t1;
REAL t9=t3*t3;
REAL t10=t8+t9;
REAL t11=t4*t5;
REAL t12=t6*t7;
REAL t14=t11-t12;
REAL t15=t10*t14;
REAL t16=t4*t4;
REAL t17=t6*t6;
REAL t18=t16+t17;
REAL t19=t3*t7;
REAL t20=t1*t5;
REAL t22=t19-t20;
REAL t23=t18*t22;
REAL t24=t5*t5;
REAL t25=t7*t7;
REAL t26=t24+t25;
REAL t27=t3*t4;
REAL t28=t1*t6;
REAL t30=t27-t28;
REAL t31=t26*t30;
REAL t33=t15+t23;
REAL t34=t33-t31;
//Calculate bound
REAL eps=pow(2,-53);
int inferr=0;
int roundmode = fegetround();
fesetround(FE_UPWARD);
REAL t1_e_1=fabs(t1);
REAL t1_e=eps*t1_e_1;
REAL t1_h=t1+t1_e;
REAL t1_l_n=t1_e-t1;
REAL t3_e_1=fabs(t3);
REAL t3_e=eps*t3_e_1;
REAL t3_h=t3+t3_e;
REAL t3_l_n=t3_e-t3;
REAL t4_e_1=fabs(t4);
REAL t4_e=eps*t4_e_1;
REAL t4_h=t4+t4_e;
REAL t4_l_n=t4_e-t4;
REAL t5_e_1=fabs(t5);
REAL t5_e=eps*t5_e_1;
REAL t5_h=t5+t5_e;
REAL t5_l_n=t5_e-t5;
REAL t6_e_1=fabs(t6);
REAL t6_e=eps*t6_e_1;
REAL t6_h=t6+t6_e;
REAL t6_l_n=t6_e-t6;
REAL t7_e_1=fabs(t7);
REAL t7_e=eps*t7_e_1;
REAL t7_h=t7+t7_e;
REAL t7_l_n=t7_e-t7;
REAL t8_e_1=fabs(t8);
REAL t8_e=eps*t8_e_1;
REAL  t8_h, t8_l_n;
if(t1_h<=0){
if(t1_h<=0){
REAL t1_h_n=-t1_h;
REAL t8_l_n_1=t1_h_n*t1_h;
REAL t8_h_1=t1_l_n*t1_l_n;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
else if(t1_l_n>=0){
REAL t8_l_n_1=t1_l_n*t1_h;
REAL t8_h_1=t1_l_n*t1_l_n;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
else{
REAL t8_l_n_1=t1_l_n*t1_h;
REAL t1_h_n=-t1_h;
REAL t8_h_1=t1_h_n*t1_l_n;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
}
else if(t1_l_n>=0){
if(t1_h<=0){
REAL t8_l_n_1=t1_h*t1_l_n;
REAL t8_h_1=t1_l_n*t1_l_n;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
else if(t1_l_n>=0){
REAL t8_l_n_1_1=t1_l_n*t1_h;
REAL t8_l_n_1_2=t1_l_n*t1_h;
REAL t8_l_n_1=max(t8_l_n_1_1,t8_l_n_1_2);
REAL t8_h_1_1=t1_l_n*t1_l_n;
REAL t8_h_1_2=t1_h*t1_h;
REAL t8_h_1=max(t8_h_1_1,t8_h_1_2);
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
else{
REAL t8_l_n_1=t1_l_n*t1_h;
REAL t8_h_1=t1_h*t1_h;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
}
else{
if(t1_h<=0){
REAL t8_l_n_1=t1_l_n*t1_h;
REAL t1_h_n=-t1_h;
REAL t8_h_1=t1_h_n*t1_l_n;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
else if(t1_l_n>=0){
REAL t8_l_n_1=t1_l_n*t1_h;
REAL t8_h_1=t1_h*t1_h;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
else{
REAL t1_l=-t1_l_n;
REAL t8_l_n_1=t1_l*t1_l_n;
REAL t8_h_1=t1_h*t1_h;
t8_h=t8_h_1+t8_e;
t8_l_n=t8_l_n_1+t8_e;
}
}
REAL t9_e_1=fabs(t9);
REAL t9_e=eps*t9_e_1;
REAL  t9_h, t9_l_n;
if(t3_h<=0){
if(t3_h<=0){
REAL t3_h_n=-t3_h;
REAL t9_l_n_1=t3_h_n*t3_h;
REAL t9_h_1=t3_l_n*t3_l_n;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
else if(t3_l_n>=0){
REAL t9_l_n_1=t3_l_n*t3_h;
REAL t9_h_1=t3_l_n*t3_l_n;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
else{
REAL t9_l_n_1=t3_l_n*t3_h;
REAL t3_h_n=-t3_h;
REAL t9_h_1=t3_h_n*t3_l_n;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
}
else if(t3_l_n>=0){
if(t3_h<=0){
REAL t9_l_n_1=t3_h*t3_l_n;
REAL t9_h_1=t3_l_n*t3_l_n;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
else if(t3_l_n>=0){
REAL t9_l_n_1_1=t3_l_n*t3_h;
REAL t9_l_n_1_2=t3_l_n*t3_h;
REAL t9_l_n_1=max(t9_l_n_1_1,t9_l_n_1_2);
REAL t9_h_1_1=t3_l_n*t3_l_n;
REAL t9_h_1_2=t3_h*t3_h;
REAL t9_h_1=max(t9_h_1_1,t9_h_1_2);
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
else{
REAL t9_l_n_1=t3_l_n*t3_h;
REAL t9_h_1=t3_h*t3_h;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
}
else{
if(t3_h<=0){
REAL t9_l_n_1=t3_l_n*t3_h;
REAL t3_h_n=-t3_h;
REAL t9_h_1=t3_h_n*t3_l_n;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
else if(t3_l_n>=0){
REAL t9_l_n_1=t3_l_n*t3_h;
REAL t9_h_1=t3_h*t3_h;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
else{
REAL t3_l=-t3_l_n;
REAL t9_l_n_1=t3_l*t3_l_n;
REAL t9_h_1=t3_h*t3_h;
t9_h=t9_h_1+t9_e;
t9_l_n=t9_l_n_1+t9_e;
}
}
REAL t10_e_1=fabs(t10);
REAL t10_e=eps*t10_e_1;
REAL t10_h_1=t8_h+t9_h;
REAL t10_h=t10_h_1+t10_e;
REAL t10_l_n_1=t8_l_n+t9_l_n;
REAL t10_l_n=t10_l_n_1+t10_e;
REAL t11_e_1=fabs(t11);
REAL t11_e=eps*t11_e_1;
REAL  t11_h, t11_l_n;
if(t4_h<=0){
if(t5_h<=0){
REAL t4_h_n=-t4_h;
REAL t11_l_n_1=t4_h_n*t5_h;
REAL t11_h_1=t4_l_n*t5_l_n;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
else if(t5_l_n>=0){
REAL t11_l_n_1=t4_l_n*t5_h;
REAL t11_h_1=t4_l_n*t5_l_n;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
else{
REAL t11_l_n_1=t4_l_n*t5_h;
REAL t4_h_n=-t4_h;
REAL t11_h_1=t4_h_n*t5_l_n;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
}
else if(t4_l_n>=0){
if(t5_h<=0){
REAL t11_l_n_1=t4_h*t5_l_n;
REAL t11_h_1=t4_l_n*t5_l_n;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
else if(t5_l_n>=0){
REAL t11_l_n_1_1=t4_l_n*t5_h;
REAL t11_l_n_1_2=t5_l_n*t4_h;
REAL t11_l_n_1=max(t11_l_n_1_1,t11_l_n_1_2);
REAL t11_h_1_1=t4_l_n*t5_l_n;
REAL t11_h_1_2=t4_h*t5_h;
REAL t11_h_1=max(t11_h_1_1,t11_h_1_2);
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
else{
REAL t11_l_n_1=t4_l_n*t5_h;
REAL t11_h_1=t4_h*t5_h;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
}
else{
if(t5_h<=0){
REAL t11_l_n_1=t5_l_n*t4_h;
REAL t5_h_n=-t5_h;
REAL t11_h_1=t5_h_n*t4_l_n;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
else if(t5_l_n>=0){
REAL t11_l_n_1=t5_l_n*t4_h;
REAL t11_h_1=t4_h*t5_h;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
else{
REAL t4_l=-t4_l_n;
REAL t11_l_n_1=t4_l*t5_l_n;
REAL t11_h_1=t4_h*t5_h;
t11_h=t11_h_1+t11_e;
t11_l_n=t11_l_n_1+t11_e;
}
}
REAL t12_e_1=fabs(t12);
REAL t12_e=eps*t12_e_1;
REAL  t12_h, t12_l_n;
if(t6_h<=0){
if(t7_h<=0){
REAL t6_h_n=-t6_h;
REAL t12_l_n_1=t6_h_n*t7_h;
REAL t12_h_1=t6_l_n*t7_l_n;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
else if(t7_l_n>=0){
REAL t12_l_n_1=t6_l_n*t7_h;
REAL t12_h_1=t6_l_n*t7_l_n;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
else{
REAL t12_l_n_1=t6_l_n*t7_h;
REAL t6_h_n=-t6_h;
REAL t12_h_1=t6_h_n*t7_l_n;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
}
else if(t6_l_n>=0){
if(t7_h<=0){
REAL t12_l_n_1=t6_h*t7_l_n;
REAL t12_h_1=t6_l_n*t7_l_n;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
else if(t7_l_n>=0){
REAL t12_l_n_1_1=t6_l_n*t7_h;
REAL t12_l_n_1_2=t7_l_n*t6_h;
REAL t12_l_n_1=max(t12_l_n_1_1,t12_l_n_1_2);
REAL t12_h_1_1=t6_l_n*t7_l_n;
REAL t12_h_1_2=t6_h*t7_h;
REAL t12_h_1=max(t12_h_1_1,t12_h_1_2);
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
else{
REAL t12_l_n_1=t6_l_n*t7_h;
REAL t12_h_1=t6_h*t7_h;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
}
else{
if(t7_h<=0){
REAL t12_l_n_1=t7_l_n*t6_h;
REAL t7_h_n=-t7_h;
REAL t12_h_1=t7_h_n*t6_l_n;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
else if(t7_l_n>=0){
REAL t12_l_n_1=t7_l_n*t6_h;
REAL t12_h_1=t6_h*t7_h;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
else{
REAL t6_l=-t6_l_n;
REAL t12_l_n_1=t6_l*t7_l_n;
REAL t12_h_1=t6_h*t7_h;
t12_h=t12_h_1+t12_e;
t12_l_n=t12_l_n_1+t12_e;
}
}
REAL t14_e_1=fabs(t14);
REAL t14_e=eps*t14_e_1;
REAL t14_h_1=t11_h+t12_l_n;
REAL t14_h=t14_h_1+t14_e;
REAL t14_l_n_1=t12_h+t11_l_n;
REAL t14_l_n=t14_l_n_1+t14_e;
REAL t15_e_1=fabs(t15);
REAL t15_e=eps*t15_e_1;
REAL  t15_h, t15_l_n;
if(t10_h<=0){
if(t14_h<=0){
REAL t10_h_n=-t10_h;
REAL t15_l_n_1=t10_h_n*t14_h;
REAL t15_h_1=t10_l_n*t14_l_n;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
else if(t14_l_n>=0){
REAL t15_l_n_1=t10_l_n*t14_h;
REAL t15_h_1=t10_l_n*t14_l_n;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
else{
REAL t15_l_n_1=t10_l_n*t14_h;
REAL t10_h_n=-t10_h;
REAL t15_h_1=t10_h_n*t14_l_n;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
}
else if(t10_l_n>=0){
if(t14_h<=0){
REAL t15_l_n_1=t10_h*t14_l_n;
REAL t15_h_1=t10_l_n*t14_l_n;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
else if(t14_l_n>=0){
REAL t15_l_n_1_1=t10_l_n*t14_h;
REAL t15_l_n_1_2=t14_l_n*t10_h;
REAL t15_l_n_1=max(t15_l_n_1_1,t15_l_n_1_2);
REAL t15_h_1_1=t10_l_n*t14_l_n;
REAL t15_h_1_2=t10_h*t14_h;
REAL t15_h_1=max(t15_h_1_1,t15_h_1_2);
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
else{
REAL t15_l_n_1=t10_l_n*t14_h;
REAL t15_h_1=t10_h*t14_h;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
}
else{
if(t14_h<=0){
REAL t15_l_n_1=t14_l_n*t10_h;
REAL t14_h_n=-t14_h;
REAL t15_h_1=t14_h_n*t10_l_n;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
else if(t14_l_n>=0){
REAL t15_l_n_1=t14_l_n*t10_h;
REAL t15_h_1=t10_h*t14_h;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
else{
REAL t10_l=-t10_l_n;
REAL t15_l_n_1=t10_l*t14_l_n;
REAL t15_h_1=t10_h*t14_h;
t15_h=t15_h_1+t15_e;
t15_l_n=t15_l_n_1+t15_e;
}
}
REAL t16_e_1=fabs(t16);
REAL t16_e=eps*t16_e_1;
REAL  t16_h, t16_l_n;
if(t4_h<=0){
if(t4_h<=0){
REAL t4_h_n=-t4_h;
REAL t16_l_n_1=t4_h_n*t4_h;
REAL t16_h_1=t4_l_n*t4_l_n;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
else if(t4_l_n>=0){
REAL t16_l_n_1=t4_l_n*t4_h;
REAL t16_h_1=t4_l_n*t4_l_n;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
else{
REAL t16_l_n_1=t4_l_n*t4_h;
REAL t4_h_n=-t4_h;
REAL t16_h_1=t4_h_n*t4_l_n;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
}
else if(t4_l_n>=0){
if(t4_h<=0){
REAL t16_l_n_1=t4_h*t4_l_n;
REAL t16_h_1=t4_l_n*t4_l_n;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
else if(t4_l_n>=0){
REAL t16_l_n_1_1=t4_l_n*t4_h;
REAL t16_l_n_1_2=t4_l_n*t4_h;
REAL t16_l_n_1=max(t16_l_n_1_1,t16_l_n_1_2);
REAL t16_h_1_1=t4_l_n*t4_l_n;
REAL t16_h_1_2=t4_h*t4_h;
REAL t16_h_1=max(t16_h_1_1,t16_h_1_2);
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
else{
REAL t16_l_n_1=t4_l_n*t4_h;
REAL t16_h_1=t4_h*t4_h;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
}
else{
if(t4_h<=0){
REAL t16_l_n_1=t4_l_n*t4_h;
REAL t4_h_n=-t4_h;
REAL t16_h_1=t4_h_n*t4_l_n;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
else if(t4_l_n>=0){
REAL t16_l_n_1=t4_l_n*t4_h;
REAL t16_h_1=t4_h*t4_h;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
else{
REAL t4_l=-t4_l_n;
REAL t16_l_n_1=t4_l*t4_l_n;
REAL t16_h_1=t4_h*t4_h;
t16_h=t16_h_1+t16_e;
t16_l_n=t16_l_n_1+t16_e;
}
}
REAL t17_e_1=fabs(t17);
REAL t17_e=eps*t17_e_1;
REAL  t17_h, t17_l_n;
if(t6_h<=0){
if(t6_h<=0){
REAL t6_h_n=-t6_h;
REAL t17_l_n_1=t6_h_n*t6_h;
REAL t17_h_1=t6_l_n*t6_l_n;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
else if(t6_l_n>=0){
REAL t17_l_n_1=t6_l_n*t6_h;
REAL t17_h_1=t6_l_n*t6_l_n;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
else{
REAL t17_l_n_1=t6_l_n*t6_h;
REAL t6_h_n=-t6_h;
REAL t17_h_1=t6_h_n*t6_l_n;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
}
else if(t6_l_n>=0){
if(t6_h<=0){
REAL t17_l_n_1=t6_h*t6_l_n;
REAL t17_h_1=t6_l_n*t6_l_n;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
else if(t6_l_n>=0){
REAL t17_l_n_1_1=t6_l_n*t6_h;
REAL t17_l_n_1_2=t6_l_n*t6_h;
REAL t17_l_n_1=max(t17_l_n_1_1,t17_l_n_1_2);
REAL t17_h_1_1=t6_l_n*t6_l_n;
REAL t17_h_1_2=t6_h*t6_h;
REAL t17_h_1=max(t17_h_1_1,t17_h_1_2);
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
else{
REAL t17_l_n_1=t6_l_n*t6_h;
REAL t17_h_1=t6_h*t6_h;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
}
else{
if(t6_h<=0){
REAL t17_l_n_1=t6_l_n*t6_h;
REAL t6_h_n=-t6_h;
REAL t17_h_1=t6_h_n*t6_l_n;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
else if(t6_l_n>=0){
REAL t17_l_n_1=t6_l_n*t6_h;
REAL t17_h_1=t6_h*t6_h;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
else{
REAL t6_l=-t6_l_n;
REAL t17_l_n_1=t6_l*t6_l_n;
REAL t17_h_1=t6_h*t6_h;
t17_h=t17_h_1+t17_e;
t17_l_n=t17_l_n_1+t17_e;
}
}
REAL t18_e_1=fabs(t18);
REAL t18_e=eps*t18_e_1;
REAL t18_h_1=t16_h+t17_h;
REAL t18_h=t18_h_1+t18_e;
REAL t18_l_n_1=t16_l_n+t17_l_n;
REAL t18_l_n=t18_l_n_1+t18_e;
REAL t19_e_1=fabs(t19);
REAL t19_e=eps*t19_e_1;
REAL  t19_h, t19_l_n;
if(t3_h<=0){
if(t7_h<=0){
REAL t3_h_n=-t3_h;
REAL t19_l_n_1=t3_h_n*t7_h;
REAL t19_h_1=t3_l_n*t7_l_n;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
else if(t7_l_n>=0){
REAL t19_l_n_1=t3_l_n*t7_h;
REAL t19_h_1=t3_l_n*t7_l_n;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
else{
REAL t19_l_n_1=t3_l_n*t7_h;
REAL t3_h_n=-t3_h;
REAL t19_h_1=t3_h_n*t7_l_n;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
}
else if(t3_l_n>=0){
if(t7_h<=0){
REAL t19_l_n_1=t3_h*t7_l_n;
REAL t19_h_1=t3_l_n*t7_l_n;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
else if(t7_l_n>=0){
REAL t19_l_n_1_1=t3_l_n*t7_h;
REAL t19_l_n_1_2=t7_l_n*t3_h;
REAL t19_l_n_1=max(t19_l_n_1_1,t19_l_n_1_2);
REAL t19_h_1_1=t3_l_n*t7_l_n;
REAL t19_h_1_2=t3_h*t7_h;
REAL t19_h_1=max(t19_h_1_1,t19_h_1_2);
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
else{
REAL t19_l_n_1=t3_l_n*t7_h;
REAL t19_h_1=t3_h*t7_h;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
}
else{
if(t7_h<=0){
REAL t19_l_n_1=t7_l_n*t3_h;
REAL t7_h_n=-t7_h;
REAL t19_h_1=t7_h_n*t3_l_n;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
else if(t7_l_n>=0){
REAL t19_l_n_1=t7_l_n*t3_h;
REAL t19_h_1=t3_h*t7_h;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
else{
REAL t3_l=-t3_l_n;
REAL t19_l_n_1=t3_l*t7_l_n;
REAL t19_h_1=t3_h*t7_h;
t19_h=t19_h_1+t19_e;
t19_l_n=t19_l_n_1+t19_e;
}
}
REAL t20_e_1=fabs(t20);
REAL t20_e=eps*t20_e_1;
REAL  t20_h, t20_l_n;
if(t1_h<=0){
if(t5_h<=0){
REAL t1_h_n=-t1_h;
REAL t20_l_n_1=t1_h_n*t5_h;
REAL t20_h_1=t1_l_n*t5_l_n;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
else if(t5_l_n>=0){
REAL t20_l_n_1=t1_l_n*t5_h;
REAL t20_h_1=t1_l_n*t5_l_n;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
else{
REAL t20_l_n_1=t1_l_n*t5_h;
REAL t1_h_n=-t1_h;
REAL t20_h_1=t1_h_n*t5_l_n;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
}
else if(t1_l_n>=0){
if(t5_h<=0){
REAL t20_l_n_1=t1_h*t5_l_n;
REAL t20_h_1=t1_l_n*t5_l_n;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
else if(t5_l_n>=0){
REAL t20_l_n_1_1=t1_l_n*t5_h;
REAL t20_l_n_1_2=t5_l_n*t1_h;
REAL t20_l_n_1=max(t20_l_n_1_1,t20_l_n_1_2);
REAL t20_h_1_1=t1_l_n*t5_l_n;
REAL t20_h_1_2=t1_h*t5_h;
REAL t20_h_1=max(t20_h_1_1,t20_h_1_2);
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
else{
REAL t20_l_n_1=t1_l_n*t5_h;
REAL t20_h_1=t1_h*t5_h;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
}
else{
if(t5_h<=0){
REAL t20_l_n_1=t5_l_n*t1_h;
REAL t5_h_n=-t5_h;
REAL t20_h_1=t5_h_n*t1_l_n;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
else if(t5_l_n>=0){
REAL t20_l_n_1=t5_l_n*t1_h;
REAL t20_h_1=t1_h*t5_h;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
else{
REAL t1_l=-t1_l_n;
REAL t20_l_n_1=t1_l*t5_l_n;
REAL t20_h_1=t1_h*t5_h;
t20_h=t20_h_1+t20_e;
t20_l_n=t20_l_n_1+t20_e;
}
}
REAL t22_e_1=fabs(t22);
REAL t22_e=eps*t22_e_1;
REAL t22_h_1=t19_h+t20_l_n;
REAL t22_h=t22_h_1+t22_e;
REAL t22_l_n_1=t20_h+t19_l_n;
REAL t22_l_n=t22_l_n_1+t22_e;
REAL t23_e_1=fabs(t23);
REAL t23_e=eps*t23_e_1;
REAL  t23_h, t23_l_n;
if(t18_h<=0){
if(t22_h<=0){
REAL t18_h_n=-t18_h;
REAL t23_l_n_1=t18_h_n*t22_h;
REAL t23_h_1=t18_l_n*t22_l_n;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
else if(t22_l_n>=0){
REAL t23_l_n_1=t18_l_n*t22_h;
REAL t23_h_1=t18_l_n*t22_l_n;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
else{
REAL t23_l_n_1=t18_l_n*t22_h;
REAL t18_h_n=-t18_h;
REAL t23_h_1=t18_h_n*t22_l_n;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
}
else if(t18_l_n>=0){
if(t22_h<=0){
REAL t23_l_n_1=t18_h*t22_l_n;
REAL t23_h_1=t18_l_n*t22_l_n;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
else if(t22_l_n>=0){
REAL t23_l_n_1_1=t18_l_n*t22_h;
REAL t23_l_n_1_2=t22_l_n*t18_h;
REAL t23_l_n_1=max(t23_l_n_1_1,t23_l_n_1_2);
REAL t23_h_1_1=t18_l_n*t22_l_n;
REAL t23_h_1_2=t18_h*t22_h;
REAL t23_h_1=max(t23_h_1_1,t23_h_1_2);
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
else{
REAL t23_l_n_1=t18_l_n*t22_h;
REAL t23_h_1=t18_h*t22_h;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
}
else{
if(t22_h<=0){
REAL t23_l_n_1=t22_l_n*t18_h;
REAL t22_h_n=-t22_h;
REAL t23_h_1=t22_h_n*t18_l_n;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
else if(t22_l_n>=0){
REAL t23_l_n_1=t22_l_n*t18_h;
REAL t23_h_1=t18_h*t22_h;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
else{
REAL t18_l=-t18_l_n;
REAL t23_l_n_1=t18_l*t22_l_n;
REAL t23_h_1=t18_h*t22_h;
t23_h=t23_h_1+t23_e;
t23_l_n=t23_l_n_1+t23_e;
}
}
REAL t24_e_1=fabs(t24);
REAL t24_e=eps*t24_e_1;
REAL  t24_h, t24_l_n;
if(t5_h<=0){
if(t5_h<=0){
REAL t5_h_n=-t5_h;
REAL t24_l_n_1=t5_h_n*t5_h;
REAL t24_h_1=t5_l_n*t5_l_n;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
else if(t5_l_n>=0){
REAL t24_l_n_1=t5_l_n*t5_h;
REAL t24_h_1=t5_l_n*t5_l_n;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
else{
REAL t24_l_n_1=t5_l_n*t5_h;
REAL t5_h_n=-t5_h;
REAL t24_h_1=t5_h_n*t5_l_n;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
}
else if(t5_l_n>=0){
if(t5_h<=0){
REAL t24_l_n_1=t5_h*t5_l_n;
REAL t24_h_1=t5_l_n*t5_l_n;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
else if(t5_l_n>=0){
REAL t24_l_n_1_1=t5_l_n*t5_h;
REAL t24_l_n_1_2=t5_l_n*t5_h;
REAL t24_l_n_1=max(t24_l_n_1_1,t24_l_n_1_2);
REAL t24_h_1_1=t5_l_n*t5_l_n;
REAL t24_h_1_2=t5_h*t5_h;
REAL t24_h_1=max(t24_h_1_1,t24_h_1_2);
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
else{
REAL t24_l_n_1=t5_l_n*t5_h;
REAL t24_h_1=t5_h*t5_h;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
}
else{
if(t5_h<=0){
REAL t24_l_n_1=t5_l_n*t5_h;
REAL t5_h_n=-t5_h;
REAL t24_h_1=t5_h_n*t5_l_n;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
else if(t5_l_n>=0){
REAL t24_l_n_1=t5_l_n*t5_h;
REAL t24_h_1=t5_h*t5_h;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
else{
REAL t5_l=-t5_l_n;
REAL t24_l_n_1=t5_l*t5_l_n;
REAL t24_h_1=t5_h*t5_h;
t24_h=t24_h_1+t24_e;
t24_l_n=t24_l_n_1+t24_e;
}
}
REAL t25_e_1=fabs(t25);
REAL t25_e=eps*t25_e_1;
REAL  t25_h, t25_l_n;
if(t7_h<=0){
if(t7_h<=0){
REAL t7_h_n=-t7_h;
REAL t25_l_n_1=t7_h_n*t7_h;
REAL t25_h_1=t7_l_n*t7_l_n;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
else if(t7_l_n>=0){
REAL t25_l_n_1=t7_l_n*t7_h;
REAL t25_h_1=t7_l_n*t7_l_n;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
else{
REAL t25_l_n_1=t7_l_n*t7_h;
REAL t7_h_n=-t7_h;
REAL t25_h_1=t7_h_n*t7_l_n;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
}
else if(t7_l_n>=0){
if(t7_h<=0){
REAL t25_l_n_1=t7_h*t7_l_n;
REAL t25_h_1=t7_l_n*t7_l_n;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
else if(t7_l_n>=0){
REAL t25_l_n_1_1=t7_l_n*t7_h;
REAL t25_l_n_1_2=t7_l_n*t7_h;
REAL t25_l_n_1=max(t25_l_n_1_1,t25_l_n_1_2);
REAL t25_h_1_1=t7_l_n*t7_l_n;
REAL t25_h_1_2=t7_h*t7_h;
REAL t25_h_1=max(t25_h_1_1,t25_h_1_2);
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
else{
REAL t25_l_n_1=t7_l_n*t7_h;
REAL t25_h_1=t7_h*t7_h;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
}
else{
if(t7_h<=0){
REAL t25_l_n_1=t7_l_n*t7_h;
REAL t7_h_n=-t7_h;
REAL t25_h_1=t7_h_n*t7_l_n;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
else if(t7_l_n>=0){
REAL t25_l_n_1=t7_l_n*t7_h;
REAL t25_h_1=t7_h*t7_h;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
else{
REAL t7_l=-t7_l_n;
REAL t25_l_n_1=t7_l*t7_l_n;
REAL t25_h_1=t7_h*t7_h;
t25_h=t25_h_1+t25_e;
t25_l_n=t25_l_n_1+t25_e;
}
}
REAL t26_e_1=fabs(t26);
REAL t26_e=eps*t26_e_1;
REAL t26_h_1=t24_h+t25_h;
REAL t26_h=t26_h_1+t26_e;
REAL t26_l_n_1=t24_l_n+t25_l_n;
REAL t26_l_n=t26_l_n_1+t26_e;
REAL t27_e_1=fabs(t27);
REAL t27_e=eps*t27_e_1;
REAL  t27_h, t27_l_n;
if(t3_h<=0){
if(t4_h<=0){
REAL t3_h_n=-t3_h;
REAL t27_l_n_1=t3_h_n*t4_h;
REAL t27_h_1=t3_l_n*t4_l_n;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
else if(t4_l_n>=0){
REAL t27_l_n_1=t3_l_n*t4_h;
REAL t27_h_1=t3_l_n*t4_l_n;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
else{
REAL t27_l_n_1=t3_l_n*t4_h;
REAL t3_h_n=-t3_h;
REAL t27_h_1=t3_h_n*t4_l_n;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
}
else if(t3_l_n>=0){
if(t4_h<=0){
REAL t27_l_n_1=t3_h*t4_l_n;
REAL t27_h_1=t3_l_n*t4_l_n;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
else if(t4_l_n>=0){
REAL t27_l_n_1_1=t3_l_n*t4_h;
REAL t27_l_n_1_2=t4_l_n*t3_h;
REAL t27_l_n_1=max(t27_l_n_1_1,t27_l_n_1_2);
REAL t27_h_1_1=t3_l_n*t4_l_n;
REAL t27_h_1_2=t3_h*t4_h;
REAL t27_h_1=max(t27_h_1_1,t27_h_1_2);
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
else{
REAL t27_l_n_1=t3_l_n*t4_h;
REAL t27_h_1=t3_h*t4_h;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
}
else{
if(t4_h<=0){
REAL t27_l_n_1=t4_l_n*t3_h;
REAL t4_h_n=-t4_h;
REAL t27_h_1=t4_h_n*t3_l_n;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
else if(t4_l_n>=0){
REAL t27_l_n_1=t4_l_n*t3_h;
REAL t27_h_1=t3_h*t4_h;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
else{
REAL t3_l=-t3_l_n;
REAL t27_l_n_1=t3_l*t4_l_n;
REAL t27_h_1=t3_h*t4_h;
t27_h=t27_h_1+t27_e;
t27_l_n=t27_l_n_1+t27_e;
}
}
REAL t28_e_1=fabs(t28);
REAL t28_e=eps*t28_e_1;
REAL  t28_h, t28_l_n;
if(t1_h<=0){
if(t6_h<=0){
REAL t1_h_n=-t1_h;
REAL t28_l_n_1=t1_h_n*t6_h;
REAL t28_h_1=t1_l_n*t6_l_n;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
else if(t6_l_n>=0){
REAL t28_l_n_1=t1_l_n*t6_h;
REAL t28_h_1=t1_l_n*t6_l_n;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
else{
REAL t28_l_n_1=t1_l_n*t6_h;
REAL t1_h_n=-t1_h;
REAL t28_h_1=t1_h_n*t6_l_n;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
}
else if(t1_l_n>=0){
if(t6_h<=0){
REAL t28_l_n_1=t1_h*t6_l_n;
REAL t28_h_1=t1_l_n*t6_l_n;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
else if(t6_l_n>=0){
REAL t28_l_n_1_1=t1_l_n*t6_h;
REAL t28_l_n_1_2=t6_l_n*t1_h;
REAL t28_l_n_1=max(t28_l_n_1_1,t28_l_n_1_2);
REAL t28_h_1_1=t1_l_n*t6_l_n;
REAL t28_h_1_2=t1_h*t6_h;
REAL t28_h_1=max(t28_h_1_1,t28_h_1_2);
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
else{
REAL t28_l_n_1=t1_l_n*t6_h;
REAL t28_h_1=t1_h*t6_h;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
}
else{
if(t6_h<=0){
REAL t28_l_n_1=t6_l_n*t1_h;
REAL t6_h_n=-t6_h;
REAL t28_h_1=t6_h_n*t1_l_n;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
else if(t6_l_n>=0){
REAL t28_l_n_1=t6_l_n*t1_h;
REAL t28_h_1=t1_h*t6_h;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
else{
REAL t1_l=-t1_l_n;
REAL t28_l_n_1=t1_l*t6_l_n;
REAL t28_h_1=t1_h*t6_h;
t28_h=t28_h_1+t28_e;
t28_l_n=t28_l_n_1+t28_e;
}
}
REAL t30_e_1=fabs(t30);
REAL t30_e=eps*t30_e_1;
REAL t30_h_1=t27_h+t28_l_n;
REAL t30_h=t30_h_1+t30_e;
REAL t30_l_n_1=t28_h+t27_l_n;
REAL t30_l_n=t30_l_n_1+t30_e;
REAL t31_e_1=fabs(t31);
REAL t31_e=eps*t31_e_1;
REAL  t31_h, t31_l_n;
if(t26_h<=0){
if(t30_h<=0){
REAL t26_h_n=-t26_h;
REAL t31_l_n_1=t26_h_n*t30_h;
REAL t31_h_1=t26_l_n*t30_l_n;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
else if(t30_l_n>=0){
REAL t31_l_n_1=t26_l_n*t30_h;
REAL t31_h_1=t26_l_n*t30_l_n;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
else{
REAL t31_l_n_1=t26_l_n*t30_h;
REAL t26_h_n=-t26_h;
REAL t31_h_1=t26_h_n*t30_l_n;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
}
else if(t26_l_n>=0){
if(t30_h<=0){
REAL t31_l_n_1=t26_h*t30_l_n;
REAL t31_h_1=t26_l_n*t30_l_n;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
else if(t30_l_n>=0){
REAL t31_l_n_1_1=t26_l_n*t30_h;
REAL t31_l_n_1_2=t30_l_n*t26_h;
REAL t31_l_n_1=max(t31_l_n_1_1,t31_l_n_1_2);
REAL t31_h_1_1=t26_l_n*t30_l_n;
REAL t31_h_1_2=t26_h*t30_h;
REAL t31_h_1=max(t31_h_1_1,t31_h_1_2);
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
else{
REAL t31_l_n_1=t26_l_n*t30_h;
REAL t31_h_1=t26_h*t30_h;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
}
else{
if(t30_h<=0){
REAL t31_l_n_1=t30_l_n*t26_h;
REAL t30_h_n=-t30_h;
REAL t31_h_1=t30_h_n*t26_l_n;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
else if(t30_l_n>=0){
REAL t31_l_n_1=t30_l_n*t26_h;
REAL t31_h_1=t26_h*t30_h;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
else{
REAL t26_l=-t26_l_n;
REAL t31_l_n_1=t26_l*t30_l_n;
REAL t31_h_1=t26_h*t30_h;
t31_h=t31_h_1+t31_e;
t31_l_n=t31_l_n_1+t31_e;
}
}
REAL t33_e_1=fabs(t33);
REAL t33_e=eps*t33_e_1;
REAL t33_h_1=t15_h+t23_h;
REAL t33_h=t33_h_1+t33_e;
REAL t33_l_n_1=t15_l_n+t23_l_n;
REAL t33_l_n=t33_l_n_1+t33_e;
REAL t34_e_1=fabs(t34);
REAL t34_e=eps*t34_e_1;
REAL t34_h_1=t33_h+t31_l_n;
REAL t34_h=t34_h_1+t34_e;
REAL t34_l_n_1=t31_h+t33_l_n;
REAL t34_l_n=t34_l_n_1+t34_e;
fesetround(roundmode);
*result=t34;
if (inferr==0) {
*hbound=t34_h;
*lbound=-t34_l_n;
}
else{
*hbound=1/0;
*lbound=1/0;
}
}
//Main test Function

int main(){
int range=100;
int sample=100000;
REAL varlist;
REAL res, err, merr, herr,lerr;
FILE *fsave;
fsave=fopen("ProbSave.txt","w");
FILE *freport;
freport=fopen("ProbReport.txt","w");
int cIA=0;
int cFPS=0;
int cMan=0;
int cIAFPS=0;
int cIAnFPS=0;
int cFPSnIA=0;
int cManFPS=0;
int cMannFPS=0;
int cFPSnMan=0;
int bIA, bFPS, bMan;
REAL ax,ay,bx,by,cx,cy,dx,dy;
int i;
for(i=0; i<sample; i++)
{

ax=randfl(range);
ay=randfl(range);
bx=randfl(range);
by=randfl(range);
cx=randfl(range);
cy=randfl(range);
dx=randfl(range);
dy=randfl(range);


FPSyn_InCircle(ax,ay,bx,by,cx,cy,dx,dy,&res,&err);
Manual_InCircle(ax,ay,bx,by,cx,cy,dx,dy,&res,&merr);
IA_InCircle(ax,ay,bx,by,cx,cy,dx,dy,&res,&herr,&lerr);

printf("%e      %e      %e      %e      %e      %e         %f         %f\n ", res, err, merr, herr, lerr,herr-lerr, (herr-lerr)/2/err, merr/err);
fprintf(fsave, "%e      %e      %e      %e      %e      %e         %f         %f\n ", res, err, merr, herr, lerr,herr-lerr, (herr-lerr)/2/err, merr/err);

if ((0<herr)&&(0>lerr)){bIA=1;}
else { bIA=0;}

if ((res<merr)&&(res>-merr)){bMan=1;}
else { bMan=0;}

if ((res<err)&&(res>-err)){bFPS=1;}
else { bFPS=0;}

cIA = cIA + bIA;
cFPS = cFPS+ bFPS;
cMan= cMan + bMan;

cIAFPS= cIAFPS+bIA*bFPS;
if ((bIA==1)&&(bFPS==0)) {cIAnFPS=cIAnFPS+1;}
if ((bIA==0)&&(bFPS==1)) {cFPSnIA=cFPSnIA+1;}

cManFPS= cManFPS+bMan*bFPS;
if ((bMan==1)&&(bFPS==0)) {cMannFPS=cMannFPS+1;}
if ((bMan==0)&&(bFPS==1)) {cFPSnMan=cFPSnMan+1;}

}

fclose(fsave);

printf("In error IA: %d\n", cIA);
printf("In error FPSyn: %d\n", cFPS);
printf("In error Manual: %d\n", cMan);

fprintf(freport,"In error IA: %d\n", cIA);
fprintf(freport,"In error Manual: %d\n", cMan);
fprintf(freport,"In error FPSyn: %d\n", cFPS);

fprintf(freport,"In error IA & FPSyn: %d\n", cIAFPS);
fprintf(freport,"In error FPSyn not IA: %d\n", cFPSnIA);
fprintf(freport,"In error IA not FPSyn: %d\n", cIAnFPS);

fprintf(freport,"In error Manual & FPSyn: %d\n", cManFPS);
fprintf(freport,"In error FPSyn not Manual: %d\n", cFPSnMan);
fprintf(freport,"In error Manual not FPSyn: %d\n", cMannFPS);

fclose(freport);

}