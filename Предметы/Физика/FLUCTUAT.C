#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#define OR ||
#define AND &&
#define NOT !
void kontur();
void print_first_data();
void print_first();
void print_second_data();
void print_second();
void graph_print();
void second_values();
char chr();
void up_key();
void down_key();
void right_key();
void left_key();
void clear_sym(int,int);
void calculus();
void outnumber(float);
void meaning (int,int,float,int);
void credits();
const float Kx=0.667,PI=3.14;
const unsigned UP=72,DOWN=80,LEFT=75,RIGHT=77;
char *str;
int gd,gm,ge;
int Xat=8,Yat=8,j=1;
float C=1,L=20,R=1,q0=50,w0,q,t,w1,b,i,T0,T1,Qua,z,k[5];
unsigned w1f,T1f,Quaf;
float Wc,Wl,Wa;
char keys,*ver="V1.0";
void main(){
  FILE *fileb;
  if ((fileb=fopen ("egavga.bgi","r"))==NULL)	 {
    printf ("File EGAVGA.BGI not found!\n");
    fclose(fileb);
    return;}
  fclose(fileb);
  if ((fileb=fopen ("fluctuat.doc","r"))==NULL){
    printf ("File FLUCTUAT.DOC not found!\n");
    fclose (fileb);
    return;}
  fclose (fileb);
  k[1]=C;
  k[2]=L;
  k[3]=R;
  k[4]=q0;
  gd=EGA;
  gm=1;
  initgraph (&gd,&gm,"");
  ge=graphresult();
  if (ge==grOk)
    {
      cleardevice();
      credits();
      setfillstyle (EMPTY_FILL,7);
      setcolor(7);
      kontur();
      moveto (Xat,Yat+24+(j+8));
      outtext (">");
      print_first();
      print_second();
      calculus();
      do{
	keys=getch();
	Xat=8;
	Yat=32;
	if (keys=='\0'){
	    keys=getch();
	    if (keys==UP)
	      up_key();
	    if (keys==DOWN)
	      down_key();
	    if (keys==LEFT)
	      left_key();
	    if (keys==RIGHT)
	      right_key();}
	if (keys==13)
	  graph_print();}
      while (keys!=27);
      closegraph();
      printf ("Watching for fluctuation by Skrylev Pavel (C) 1995\n");}
}
void kontur(){
  moveto (22*8,0);
  outtext ("WATCHING FOR THE FLUCTUATION");
  line (400,10,450,10);
  line (450,0,450,20);
  line (470,0,470,20);
  line (470,10,520,10);
  line (520,10,520,40);
  ellipse (520,45,270,90,5,5);
  ellipse (520,55,270,90,5,5);
  ellipse (520,65,270,90,5,5);
  line (520,70,520,100);
  line (520,100,470,100);
  line (470,105,470,95);
  line (470,95,450,95);
  line (450,95,450,105);
  line (450,105,470,105);
  line (450,100,400,100);
  line (400,100,400,10);
  moveto (457,0);
  outtext ("C");
  moveto (471,12);
  outtext ("+q");
  moveto (434,12);
  outtext ("-q");
  moveto (457,86);
  outtext ("R");
  moveto (530,52);
  outtext ("L");}
void print_first_data(){
  Xat=32;
  Yat=40;
  setcolor (7);
  bar (Xat,Yat,Xat+47,Yat+31);
  moveto (Xat,Yat);
  outnumber (k[1]);
  outtext (" F");
  moveto (Xat,Yat+8);
  outnumber (k[2]);
  outtext (" Hn");
  moveto (Xat,Yat+16);
  outnumber (k[3]);
  outtext (" Ohm");
  moveto (Xat,Yat+24);
  outnumber (k[4]);
  outtext (" Kl");}
void print_first(){
  setcolor (7);
  moveto (Xat-4,Yat+4);
  lineto (Xat+260,Yat+4);
  lineto (Xat+260,Yat+82);
  lineto (Xat-4,Yat+82);
  lineto (Xat-4,Yat+4);
  line (Xat+92,Yat+4,Xat+92,Yat+82);
  line (Xat-4,Yat+28,Xat+260,Yat+28);
  moveto (Xat,Yat+8);
  outtext ("CHANGED");
  moveto (Xat,Yat+16);
  outtext ("VARIABLES");
  moveto (Xat+96,Yat+8);
  outtext ("CALCULATED");
  moveto (Xat+96,Yat+16);
  outtext ("VARIABLES");
  Yat=Yat+24;
  moveto (Xat+8,Yat+8);
  outtext ("C=");
  moveto (Xat+8,Yat+16);
  outtext ("L=");
  moveto (Xat+8,Yat+24);
  outtext ("R=");
  moveto (Xat+8,Yat+32);
  outtext ("q=");}
void print_second_data(){
  Xat=120;
  Yat=40;
  setcolor (7);
  bar (Xat+8,Yat,Xat+143,Yat+7);
  moveto (Xat+8,Yat);
  outnumber (w0);
  outtext (" rad/sec");
  bar (Xat,Yat+8,Xat+143,Yat+15);
  moveto (Xat,Yat+8);
  outnumber (b);
  outtext (" rad/sec");
  bar (Xat+8,Yat+16,Xat+119,Yat+23);
  moveto (Xat+8,Yat+16);
  outnumber (T0);
  outtext (" sec");
  bar (Xat+8,Yat+24,Xat+143,Yat+31);
  moveto (Xat+8,Yat+24);
  if (w1f==0){
    if (R==0)
      outtext ("w0");
    else{
      outnumber (w1);
      outtext (" rad/sec");}}
  else
    outtext ("-");
  bar (Xat,Yat+32,Xat+119,Yat+39);
  moveto (Xat,Yat+32);
  if (Quaf==0)
    outnumber (Qua);
  else
    outtext ("-");
  bar (Xat+8,Yat+40,Xat+119,Yat+47);
  moveto (Xat+8,Yat+40);
  if (T1f==0){
    if (R==0)
      outtext ("T0");
    else{
      outnumber (T1);
      outtext (" sec");}}
  else
    outtext ("-");}
void print_second(){
  Xat=104;
  Yat=40;
  moveto (Xat,Yat);
  outtext ("w0=");
  moveto (Xat,Yat+8);
  outtext ("B=");
  moveto (Xat,Yat+16);
  outtext ("T0=");
  moveto (Xat,Yat+24);
  outtext ("w1=");
  moveto (Xat,Yat+32);
  outtext ("Q=");
  moveto (Xat,Yat+40);
  outtext ("T1= 	 sec");}
void graph_print(){
  int XQ,YQ,XQo,YQo;
  float KyQ,Kyi,KyE;
  int Xi,Yi,Xio,Yio;
  int XE,YE,XEo,Yco,Ylo,Yao;
  bar (0,100,300,400);
  bar (300,150,600,290);
  setcolor (7);
  XQ=50;
  YQ=150;
  XQo=XQ;
  YQo=YQ-50;
  KyQ=q0/50;
  line (XQ-1,YQ+5,XQ-1,YQ-50);
  line (XQ-5,YQ,XQ+200,YQ);
  setcolor (1);
  moveto (XQ-4,YQ-58);
  outtext ("q");
  setcolor (7);
  outtext ("[Kl]");
  moveto (XQ+200,YQ-4);
  outtext ("t[sec]");
  Xi=300;
  Yi=232;
  Xio=Xi;
  Yio=Yi;
  Kyi=q0*w0/50;
  line (Xi-1,Yi+5,Xi-1,Yi-50);
  line (Xi-5,Yi,Xi+200,Yi);
  setcolor (5);
  moveto (Xi-4,Yi-58);
  outtext ("i");
  setcolor (7);
  outtext ("[A]");
  moveto (Xi+200,Yi-4);
  outtext ("t[sec]");
  XE=50;
  YE=315;
  XEo=XE;
  Yco=YE-100;
  Ylo=YE;
  Yao=Yco;
  KyE=pow(q0,2)/C/200;
  line (XE-1,YE+5,XE-1,YE-100);
  line (XE-5,YE,XE+200,YE);
  setcolor (4);
  moveto (XE-4,YE-108);
  outtext ("W");
  setcolor (7);
  outtext (",");
  setcolor (2);
  outtext ("Wc");
  setcolor (7);
  outtext (",");
  setcolor (3);
  outtext ("Wl");
  setcolor (7);
  outtext ("[J]");
  moveto (XE+200,YE-4);
  outtext ("t[sec]");
  meaning (XQ-8,YQ-49,KyQ*10,50);
  meaning (Xi-8,Yi-49,Kyi*10,50);
  meaning (XE-8,YE-99,KyE*10,100);
  t=0;
  while (t<=200*Kx){
      setcolor (1);
      q=q0*cos(w1*t)/exp(b*t);
      moveto (XQo,YQo);
      XQo=XQ+floor(t/Kx);
      YQo=YQ-floor(q/KyQ);
      lineto (XQo,YQo);
      setcolor (5);
      i=q0*w0*sin(w1*t)/exp(b*t);
      moveto (Xio-1,Yio);
      Xio=Xi+floor (t/Kx);
      Yio=Yi-floor (i/Kyi);
      lineto (Xio,Yio);
      setcolor(2);
      Wc=pow(q0,2)*pow(cos(w1*t),2)/exp(2*b*t)/2/C;
      moveto (XEo,Yco);
      Yco=YE-floor (Wc/KyE);
      lineto (XE+floor(t/Kx),Yco);
      setcolor(3);
      Wl=L*pow(q0,2)*pow(w0,2)*pow(sin(w1*t),2)/(2*exp(2*b*t));
      moveto (XEo,Ylo);
      Ylo=YE-floor(Wl/KyE);
      lineto (XE+floor(t/Kx),Ylo);
      setcolor(4);
      Wa=Wc+Wl;
      moveto (XEo,Yao);
      XEo=XE+floor (t/Kx);
      Yao=YE-floor(Wa/KyE);
      lineto (XEo,Yao);
      t++;}
  setcolor (7);}
void second_values(){
  w0=1/(sqrt(L*C));
  b=R/2/L;
  T0=2*PI/w0;
  if (w0>=b){
      w1f=0;
      w1=sqrt(pow(w0,2)-pow(b,2));}
  else
    w1f=1;
  if (b!=0){
      Quaf=0;
      Qua=w1/2/b;}
  else
    Quaf=1;
  if ((w1!=0) AND (w1f!=1)){
      T1f=0;
      T1=2*PI/w1;
      z=b*T1;}
  else
    T1f=1;}
char chr(unsigned cod_sym){
  return (cod_sym);}
void up_key(){
  if (j==1)
    return;
  clear_sym(Xat,Yat+(j*8));
  j--;
  moveto (Xat,Yat+(j*8));
  outtext (">");}
void down_key(){
  if (j==4)
    return;
  clear_sym (Xat,Yat+(j*8));
  j++;
  setcolor (7);
  moveto (Xat,Yat+(j*8));
  outtext (">");}
void right_key(){
  if (k[j]==100)
    return;
  k[j]++;
  bar (Xat+24,Yat+(j*8),Xat+47,Yat+7+(j*8));
  calculus();}
void left_key(){
  if (((k[j]==1) AND ((k[3]!=1) OR (j!=3))) OR (k[j]==0))
    return;
  k[j]--;
  bar (Xat+24,Yat+(j*8),Xat+47,Yat+7+(j*8));
  calculus();}
void clear_sym(int left,int top){
  bar (left,top,left+7,top+7);}
void calculus(){
  C=k[1];
  L=k[2];
  R=k[3];
  q0=k[4];
  second_values();
  print_first_data();
  print_second_data();}
void outnumber(float num){
   int dec,sign;
   float numh=floor(num);
   float numl=floor((num-numh)*1000000);
   outtext(fcvt(numh,0,&dec,&sign));
   if(numl){
     outtext(".");
     outtext(fcvt(numl,0,&dec,&sign));}}
void meaning (int Xb,int Yb,float mea,int top){
  char *str;
  int dec,sign;
  float meai;
  setcolor (7);
  line (Xb,Yb,Xb+4,Yb);
  line (Xb+2,Yb,Xb+2,Yb+top-1);
  line (Xb,Yb+top-1,Xb+4,Yb+top-1);
  moveto (Xb-24,Yb+(top/2)-4);
  meai=floor (mea);
  if (meai!=0)
    str=fcvt (meai,0,&dec,&sign);
  else{
      str=fcvt (mea,1,&dec,&sign);
      outtext ("0.");
      if (mea<0.1){
	  outtext ("1");
	  moveto (Xb-32,Yb+(top/2)-4);
	  outtext ("<");}
      else
	  clear_sym (Xb-32,Yb+(top/2)-4);}
  outtext (str);}
void credits(){
  int X=450,Y=300;
  line (X,Y,X,Y+15);
  line (X+5,Y,X+5,Y+15);
  ellipse (X-1,Y+1,90,270,2,2);
  line (X,Y-1,X+7,Y-1);
  ellipse (X+3,Y+9,30,330,5,5);
  moveto (X+8,Y);
  outtext ("ABE");
  line (X+33,Y+6,X+37,Y);
  bar (X+37,Y,X+38,Y+6);
  moveto (X+8,Y+8);
  outtext ("KP	EB");
  bar (X+24,Y+8,X+25,Y+14);
  ellipse (X+26,Y+12,270,90,2,2);
  bar (X+30,Y+8,X+31,Y+14);
  line (X+33,Y+14,X+37,Y+8);
  bar (X+37,Y+8,X+38,Y+14);
  moveto (X,Y+16);
  outtext ("(C)1995");}