#include <stdio.h>
#include <math.h>
FILE *fi1,*fi2;
int as,ap,i;
int mas[25]={0,0,15,0,0,5,0,10,10,0,9,0,12,0,0,10,10,5,0,0,5,10,0,0,10};
int typer[5]={10,10,5,0,0};
float scal(int val,int mode1){
  float n=0;
  int i;
  for(i=0;i<5;i++)
    n=n+typer[i]*mas[val*(mode1*4+1)+i];
  return(sqrt(n));}
float norma(int val){
  float n=0;
  int i;
  for(i=0;i<5;i++)
    n=n+pow(mas[val+i],2);
  return(sqrt(n));}
int main(){
  fi1=fopen("lab_n21.dat","w");
  fi2=fopen("lab_n22.dat","w");
  for (i=0;i<5;i++)
    fprintf(fi1,"%d %.0f\n",i,scal(i,1));
  for (i=0;i<22;i++)
    fprintf(fi2,"%d %.0f\n",i,scal(i,0)*10/norma(i));
  fcloseall();
  return(0);}