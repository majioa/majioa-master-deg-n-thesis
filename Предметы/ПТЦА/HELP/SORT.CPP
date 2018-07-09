#include "stdio.h"
typedef struct {char inm[8];int a;char outm[20];int b;} tdf;
tdf mas[500];
tdf aaa;
FILE *fl,*fl1;
char kk;
int i,j,k,l,m;
void swap(int z){
  int zz;
  for(zz=0;zz<8;zz++){
    aaa.inm[zz]=mas[z].inm[zz];
    mas[z].inm[zz]=mas[z+1].inm[zz];
    mas[z+1].inm[zz]=aaa.inm[zz];}
  for(zz=0;zz<20;zz++){
    aaa.outm[zz]=mas[z].outm[zz];
    mas[z].outm[zz]=mas[z+1].outm[zz];
    mas[z+1].outm[zz]=aaa.outm[zz];}}
char inv(char a){
  return((!(a-0x30))+0x30);}
void main(){
  fl=fopen("pzu","r");
  fl1=fopen("newpzu1","w");
  for(i=0;i<500;i++){
     if(feof(fl))break;
    for(j=0;j<8;j++){
      mas[i].inm[j]=fgetc(fl);
     if(feof(fl))break;}
    kk=fgetc(fl);
    for(k=0;k<5;k++){
      for(j=0;j<4;j++){
	mas[i].outm[k*4+j]=fgetc(fl);
	if(feof(fl))break;}
      kk=fgetc(fl);
      if(feof(fl))break; }}

  for(l=0;l<i-2;l++){
    for(m=0;m<i-l-2;m++){
      for(j=0;j<8;j++){
	if(mas[m].inm[j]>mas[m+1].inm[j]){
					  swap(m);
					  break;}
	if(mas[m].inm[j]<mas[m+1].inm[j]){
					  break;}}}}
  
  for(l=0;l<i;l++){
    fputc(0xba,fl1);
    for(j=0;j<8;j++)
      fputc(mas[l].inm[j],fl1);
    fputc(0xba,fl1);
    for(k=0;k<5;k++){
      for(j=0;j<4;j++)
	fputc(inv(mas[l].outm[k*4+j]),fl1);
      fputc(0xba,fl1);}
    fputc(0xa,fl1);}
}
