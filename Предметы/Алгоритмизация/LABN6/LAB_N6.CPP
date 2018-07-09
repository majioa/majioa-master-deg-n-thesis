#include "math.h"
#include "stdio.h"
float const PI=3.141592654;
float alf=0.9,aly=0.1;
const int b=2,c=1;
const int range=40;
const int N=4;
float nullF[b+1-c],F[N*range];
float nullY[b+1-c],Y[N*range];
float Xy[N*range],Xf[N*range],Ky[N*range],Kf[N*range];
float dt=1/N;
void calcF(FILE *fl,int z){
  int i;
  if(!z){
    F[0]=1;
    for(i=0;i<N*range;i++)
      fprintf(fl,"%d %e\n",i,F[i]);}
  else for(i=0;i<N*range;i++){
    F[i]=cos(2*PI*dt*i);
    fprintf(fl,"%d %e\n",i,F[i]);}}
void calcY(FILE *fl){
  int i;
  for(i=0;i<N*range;i++){
    Y[i]=(-(1-alf)/(1-aly))*(F[i-(b-c)]+aly*F[i-(b+1-c)])+alf*Y[i-1];
    fprintf(fl,"%d %e\n",i,Y[i]);}}
void calcXy(FILE *fl){
  int i,k;
  for (i=0;i<N*range;i++){
    Xy[i]=0;
    for (k=0;k<=i;k++)
      Xy[i]+=Y[i-c-k]*Ky[k];
    fprintf(fl,"%d %e\n",i,Xy[i]);}}
void calcXf(FILE *fl){
  int i,k;
  for (i=0;i<N*range;i++){
    Xf[i]=0;
    for (k=0;k<=i;k++)
      Xf[i]+=F[i-b-k]*Kf[k];
    fprintf(fl,"%d %e\n",i,Xf[i]);}}
int main(){
  int i,j,k;
  float t;
  FILE *file1,*file2,*file3,*file4,*file5;
  FILE *file6,*file7,*file8,*file9,*file10;
  for(i=0;i<N*range;i++){
    Kf[i]=(1-alf)*pow(alf,i);
    Ky[i]=(1-aly)*pow(-aly,i);}
  file1=fopen("f-delta.dat","w");
  file2=fopen("y-delta.dat","w");
  file3=fopen("xf-delta.dat","w");
  file4=fopen("xy-delta.dat","w");
  file5=fopen("x-delta.dat","w");
  file6=fopen("f-sin.dat","w");
  file7=fopen("y-sin.dat","w");
  file8=fopen("xf-sin.dat","w");
  file9=fopen("xy-sin.dat","w");
  file10=fopen("x-sin.dat","w");
  calcF(file1,0);
  calcY(file2);
  calcXf(file3);
  calcXy(file4);
  for (i=0;i<N*range;i++){
    fprintf(file5,"%d %e\n",i,Xy[i]+Xf[i]);}
  calcF(file6,1);
  calcY(file7);
  calcXf(file8);
  calcXy(file9);
  for (i=0;i<N*range;i++){
    fprintf(file10,"%d %e\n",i,Xy[i]+Xf[i]);}
  fcloseall();
  return(0);
}