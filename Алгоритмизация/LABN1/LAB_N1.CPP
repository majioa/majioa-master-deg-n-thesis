#include <stdio.h>
#include <math.h>
#include <stdlib.h>
FILE *file_;
float const PI=3.14;
void pila(int x0,int m){
  int x1,t;
  for (t=1;t<=64;t++){
    x1=x0+m;
    fprintf(file_,"%d %d\n",t,x1);
    x0=x1;}}
void fluctuation(float a1,float a2,float m,float dx){
   int t;
   float y0=m,y1=m*a1/2,y2,x,z;
   for (t=1;t<=64;t++){
     x=random(dx);
     if (dx==0||x==0) z=0;
     else z=sqrt(2*dx*log(x))*sin(x);
     y2=a1*y1+a2*y0+z;
     fprintf(file_,"%d %f\n",t,y2);
     y0=y1;
     y1=y2;}}
int main(){
  int T=50;
  float pi=3.14;
  file_=fopen ("lab_n11.dat","w");
  pila(0,1024);
  file_=fopen ("lab_n121.dat","w");
  fluctuation (0,0.7,10,0);
  file_=fopen ("lab_n122.dat","w");
  fluctuation (0,-0.7,10,0);
  file_=fopen ("lab_n123.dat","w");
  fluctuation (0,-1.1,8,0);
  file_=fopen ("lab_n124.dat","w");
  fluctuation (2*cos(2*pi/T),-1,10,0);
  file_=fopen ("lab_n131.dat","w");
  fluctuation (0,0.7,10,500);
  file_=fopen ("lab_n132.dat","w");
  fluctuation (0,-0.7,10,500);
  fcloseall();
  return(0);}
