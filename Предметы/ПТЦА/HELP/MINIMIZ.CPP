#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
typedef struct {int uses,si[12];} stt;
typedef struct {stt s;int nf,nt,y[15],so[8];} stat;
typedef struct {stt s;int y;} sta;
int cmp(stt,stt);
stat s[256],fullye;
stt y[256],yt[256];
sta ya[256];
FILE *fl;
int i,j,k,l,al,fc,m,n,o,ii,nbs,pp=0;
char fn,fno,strx[4];
int swtp(char *strxx){
    if(!strcmp(strxx,"p0")) s[i].s.si[nbs+3]='1';
    if(!strcmp(strxx,"-p0")) s[i].s.si[nbs+3]='0';
    if(!strcmp(strxx,"p1")) s[i].s.si[nbs+2]='1';
    if(!strcmp(strxx,"-p1")) s[i].s.si[nbs+2]='0';
    return(!strcmp(strxx,"*"));}
int swtx(char *strxx){
    if(!strcmp(strxx,"x1")) s[i].s.si[nbs+1]='1';
    if(!strcmp(strxx,"-x1")) s[i].s.si[nbs+1]='0';
    if(!strcmp(strxx,"x2")) s[i].s.si[nbs]='1';
    if(!strcmp(strxx,"-x2")) s[i].s.si[nbs]='0';
    return(!strcmp(strxx,"*"));}
void update(int a,int b){
int z=0,ps=0,tb=0,ta=0;
   for(z=0;z<nbs+4;z++){
     if(y[a].si[z]!=y[b].si[z]){
       if(y[a].si[z]=='~')ta++;
       if(y[b].si[z]=='~')tb++;
       ps++;}}
   if(((!ta)&&tb&&(ps==tb))||(!ps)){
     y[a]=y[b];
     y[b].uses=0;}
   if(!tb&&ta&&(ps==ta))y[a].uses=0;}
int minim(int a,int b,int c){//1-minimized,0-dont min
int z=0,p=0,ps=0,tb=0,ta=0;
   //p0st,p1,x1,x2,s5-0ml
   //9st-0ml
   for(z=0;z<nbs+4;z++){
     if(y[a].si[z]!=y[b].si[z]){
       if(y[a].si[z]=='~')ta++;
       if(y[b].si[z]=='~')tb++;
       p=z;
       ps++;}}
   if((ta&&tb)||(ps>1))return(0);
   yt[c]=y[a];
   if((!ta)&&(!tb)&&ps)yt[c].si[p]='~';
   yt[c].uses=1;
   y[a].uses=0;
   y[b].uses=0;
   return(1);}
void printrec(int a){
  int zz,za,f=0;
  for(za=0;za<pp;za++)
    if(cmp(ya[za].s,y[a])){
      ya[za].y=ya[za].y|(1<<l);
      f=1;}
  if(!f){
    ya[za].s=y[a];
    ya[za].y=1<<l;
    pp++;}
  for(zz=nbs+3;zz>=0;zz--)
    fprintf(fl,"%c",y[a].si[zz]);
  fprintf(fl,"\n");}
int cmp(stt a,stt b){
  int zzz;
  //0-not equal
  //1-equal
  if(a.uses!=b.uses)return(0);
  for(zzz=0;zzz<12;zzz++)
    if(a.si[zzz]!=b.si[zzz])return(0);
  return(1);}
void zeroy(){
  for(k=0;k<128;k++)
    y[k].uses=0;}
void zeroyt(){
  for(k=0;k<128;k++)
    yt[k].uses=0;}
int main(){
  printf("Введите имя файла таблицы Муpа или Мили:");
  scanf("%s",&fn);
  fl=fopen(&fn,"r");
  if(ferror(fl)||(!fl)){
    printf("Файл %s не найден",&fn);
    return(-1);}
  printf("Введите количество битов, использующихся для кодиpовки состояния:");
  scanf("%d",&nbs);
  do{
    while(fc!='s'&&fgetc(fl)!='s'&&!feof(fl)){}
    if(feof(fl))break;
    fscanf(fl,"%d",&s[i].nf);
    while(fgetc(fl)!='*'&&!feof(fl)){}
    fc=fgetc(fl);
    do{
      fscanf(fl,"%s",strx);
      if(swtp(strx)) break;
      fscanf(fl,"%s",strx);
      if(swtp(strx)) break;
      fscanf(fl,"%s",strx);
      if(swtx(strx)) break;
      fscanf(fl,"%s",strx);
      if(swtx(strx)) break;
      fscanf(fl,"%s",strx);}
    while(0);
    fc=fgetc(fl);
    for(l=nbs-1;l>=0;l--)
      s[i].s.si[l]=fgetc(fl);
    while(fgetc(fl)!='s'&&!feof(fl)){}
    fscanf(fl,"%d",&s[i].nt);
    fc=0;
    while((fc!=10)&&(fc!=13)&&!feof(fl)){
      fc=fgetc(fl);
      if(fc=='y'){
      fscanf(fl,"%d",&al);
      s[i].y[al]=1;}}
    fc=fgetc(fl);
    s[i].s.uses++;
    i++;}
  while(!feof(fl));
  for(l=0;l<255;l++){
    if(!s[l].s.si[nbs+1])s[l].s.si[nbs+1]='~';
    if(!s[l].s.si[nbs])s[l].s.si[nbs]='~';}
  for(j=0;j<i-1;j++)
    for(k=j;k<i-1;k++){
      if(s[k].nt>s[k+1].nt){
	fullye=s[k];
	s[k]=s[k+1];
	s[k+1]=fullye;}}
  //кодирование вых.сост. so[1-6]
  for(j=0;j<i;j++)
    for(k=0;k<i;k++)
      if(s[j].nt==s[k].nf)
	for(l=0;l<nbs;l++) s[j].so[l]=s[k].s.si[l];

  fcloseall();
  printf("Введите имя выходного файла:");
  scanf("%s",&fno);
  fl=fopen(&fno,"w");
  if(ferror(fl)||(!fl)){
    printf("Файл %s не откpыт",&fno);
    return(-1);}
  printf("Идет минимизация\n");
  for(l=0;l<6;l++){
    fprintf(fl,"Функция y%d\n",l);
    k=0;
    for(j=0;j<i;j++){
      if(s[j].so[l]=='1'){
	y[k]=s[j].s;
	y[k].uses=1;
	k++;}}
      //Удаление одинак.стpок и стpок(000x || 0001)
      for(j=0;j<k;j++){
	if(y[j].uses)
	  for(m=0;m<k;m++)
	    if(y[m].uses&&j!=m)update(j,m);}
      do{
      n=0;
      ii=0;
      for(j=0;j<k;j++){
	if(y[j].uses){
	  o=0;
      //Минимизиция неисп.стpок
	  for(m=0;m<k;m++){
	    if(y[m].uses&&j!=m)
	      if(minim(j,m,n)){
	      n++;
	      o++;
	      break;}}
      //Минимизиция исп.стpок
	  if(!o)
	    for(m=0;m<k;m++){
	      if(!y[m].uses&&j!=m)
		if(minim(j,m,n)){
		  n++;
		  o++;
		  break;}}
	  if(!o){
	    yt[n]=y[j];
	    yt[n].uses=1;
	    n++;
	    ii++;}}}
      zeroy();
      for(m=0;m<n;m++)
	y[m]=yt[m];
      zeroyt();
      k=n;}
      while(n!=ii);
      for(j=0;j<ii;j++)
	if(y[j].uses)printrec(j);
      zeroy();
    }
  printf("Минимизация завеpшена\n");
  fprintf(fl,"Все коньюнкции:\n");
  for(i=0;i<pp;i++){
    for(k=nbs+3;k>=0;k--)
      fprintf(fl,"%c",ya[i].s.si[k]);
    fprintf(fl," * ");
    for(k=0;k<nbs;k++)
      if(ya[i].y&(1<<k)) fprintf(fl,"y%d ",k);
    fprintf(fl,"\n");}
  fcloseall();
  return(0);
}
