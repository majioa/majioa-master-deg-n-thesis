#include "math.h"
#include "stdio.h"
float const PI=3.141592654;
float al=0.7;
float fs=acos(((1-al)*(1-al)/(0.9*0.9)-al*al-1)/2/al)/2/PI,fz=fs/40,fa=0.03125;
const int range=40;
float y[2*range],x[2*range],K[2*range],H[6];
float T=1/fs;
float N=2;
float dt=T/N;
float Hf(float f){
  float t;
  t=sqrt(1+2*al*cos(2*PI*f)+al*al);
  return((1-al)/t);}
float xf(int i,float fre){
  return(cos(2*PI*fre*dt*i));}
float zf(int i){
  return(cos(2*PI*fz*dt*i)/2);}
void calcx(FILE *fl,float freq,int z){
  int i;
  for(i=0;i<N*range;i++){
    x[i]=xf(i,freq)+zf(i)*z;
    fprintf(fl,"%d %e\n",i,x[i]);}}
float yf(int i){
  return((1-al)*x[i]-al*y[i-1]);}
void calcy(FILE *fl1,FILE *fl2){
  int i,k;
  for(i=0;i<N*range;i++){
    y[i]=yf(i);
    fprintf(fl1,"%d %e\n",i,y[i]);}
  for (i=0;i<N*range;i++){
    y[i]=0;
    for (k=0;k<=i;k++)
      y[i]+=x[i-k]*K[k];
    fprintf(fl2,"%d %e\n",i,y[i]);}}
int main(){
  int i,j,k;
  float t;
  FILE *file1,*file2,*file3,*file4,*file5;
  FILE *file[15];
  file1=fopen("l5_ipx.dat","w");
  file3=fopen("l5in.dat","w");
  file4=fopen("l5out1.dat","w");
  file5=fopen("l5out2.dat","w");
  for(i=0;i<N*range;i++){
    K[i]=(1-al)*pow(-al,i);
    fprintf(file1,"%d %e\n",i,K[i]);}
  calcx(file3,fs,1);
  calcy(file4,file5);
  fcloseall();
  file2=fopen("l5_achx.dat","w");
  file[0]=fopen("l5_32i.dat","w");
  file[3]=fopen("l5_16i.dat","w");
  file[6]=fopen("l5_8i.dat","w");
  file[9]=fopen("l5_4i.dat","w");
  file[12]=fopen("l5_2i.dat","w");
  file[1]=fopen("l5_32o1.dat","w");
  file[4]=fopen("l5_16o1.dat","w");
  file[7]=fopen("l5_8o1.dat","w");
  file[10]=fopen("l5_4o1.dat","w");
  file[13]=fopen("l5_2o1.dat","w");
  file[2]=fopen("l5_32o2.dat","w");
  file[5]=fopen("l5_16o2.dat","w");
  file[8]=fopen("l5_8o2.dat","w");
  file[11]=fopen("l5_4o2.dat","w");
  file[14]=fopen("l5_2o2.dat","w");
  for(j=0;j<5;j++){
    H[j]=Hf(fa);
    fprintf(file2,"%e %e\n",fa,H[j]);
    calcx(file[j*3],fa,0);
    calcy(file[j*3+1],file[j*3+2]);
    fa*=2;}
  fcloseall();
  return(0);
}