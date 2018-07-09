#include "math.h"
#include "stdio.h"
float const PI=3.141592654;
int a=2,b=5;
float ft(float t){
  return(sin(a*t)+sin(b*t));}
int max(int m1,int m2){
  if (m1>m2)
    return(m1);
  else
    return(m2);}
float T=2*PI;
float N=abs(max(a,b)*T/PI)+1;
float dt=T/N;
float f(int x){
  return(sin(a*dt*x)+sin(b*dt*x));}
float a1(int x){
  int i;
  float s=0;
  for(i=0;i<N;i++)
    s=s+f(i)*cos(2*PI*i*x/N);
  return(s);}
float b1(int x){
  int i;
  float s=0;
  for(i=0;i<N;i++)
    s=s+f(i)*sin(2*PI*i*x/N);
  return(s);}
float F(int k){
  return(sqrt(pow(a1(k),2)+pow(b1(k),2)));}
float fi(int k){
  return(atan(b1(k)/a1(k)));}
void main(){
  int i,z;
  float t;
  FILE *file1,*file2,*file3,*file4;
  file1=fopen("lab_n31.dat","w");
  file2=fopen("lab_n32.dat","w");
  file3=fopen("lab_n33.dat","w");
  file4=fopen("lab_n34.dat","w");
  for(i=abs(N/2)+1-N;i<abs(N/2)+1;i++){
    if (i<0)
      z=i+N;
    else
      z=i;
    fprintf(file1,"%d %e\n",i,F(z));
    fprintf(file2,"%d %e\n",i,fi(z));}
  for(z=0;z<N;z++)
    fprintf(file3,"%d %e\n",z,f(z));
  for(t=0;t<T;t=t+0.1)
    fprintf(file4,"%e %e\n",t,ft(t));
}