#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
//structures
typedef struct sm{
  long val;
  void far* ptr;};
typedef struct sa{
  unsigned psw;
  void far* reg2;
  unsigned long temp;};
typedef struct pcb{
  int name;
  pcb far*nptg;
  pcb far*lptg;
  pcb far*npall;
  pcb far*lpall;
  unsigned int short stopt;
  unsigned int short blokt;
  unsigned int short lnsmc;
  unsigned int short sw;
  sm msc;
  sm msr;
  void far*fm;
  pcb far*nsw;
  sm srs;
  sm ses;
  unsigned long asize;
  void far*aaddr;
  sa isa;
  sa fsa;
  sa msa;};
typedef struct {
  unsigned long blsize;
  void far *bladdr;
  unsigned long brdsize;}xaprm;
typedef struct {
  void far *ptr;
  void far *next;
  unsigned long size;} fsb;
//variables
void far*reg2;
unsigned psw;
pcb far*running;
void far*nexttry;
unsigned short nexttrym;
pcb far*curpcb;
sm memory;
sa syssemsa;
//pcb
pcb fstpcb,scnpcb,thdpcb;
//fsb
sm fsbsem;
fsb fsbb[5];
fsb far*fsbfirst=&fsbb[0];
//parameters
xaprm params;
void xa(int);
void first(){
  // init xa_parameters
  unsigned long blsz;
  gotoxy(5,20);
  printf("Сколько процесс 0 запрашивает памяти:");
  scanf("%lx",&blsz);
  params.blsize=blsz;
  params.bladdr=NULL;
  params.brdsize=4;
  reg2=&params;
  xa(0);}
void second(){
  // init xa_parameters
  unsigned long blsz;
  gotoxy(5,20);
  printf("Сколько процесс 1 запрашивает памяти:");
  scanf("%lx",&blsz);
  params.blsize=blsz;
  params.bladdr=NULL;
  params.brdsize=4;
  reg2=&params;
  xa(1);}
void third(){
  // init xa_parameters
  unsigned long blsz;
  gotoxy(5,20);
  printf("Сколько процесс 2 запрашивает памяти:");
  scanf("%lx",&blsz);
  params.blsize=blsz;
  params.bladdr=NULL;
  params.brdsize=4;
  reg2=&params;
  xa(2);}
void pause(){
  while(getch()==0){};}
void wait(){
  while(!(!(*curpcb).stopt)&&(!(*curpcb).blokt)){};
}
void print_fsb(){
  int i;
  for (i=0;i<5;i++){
    gotoxy(3,i+3);
    printf("%p %p %p %lxh        ",&fsbb[i],fsbb[i].next,fsbb[i].ptr,fsbb[i].size);}
}
void print_rn(){
  gotoxy(65,3);
  printf("%p,%ld",memory.ptr,memory.val);
  gotoxy(65,4);
  printf("%p,%ld",fsbsem.ptr,fsbsem.val);
  gotoxy(68,5);
  printf("%p",running);
  gotoxy(68,6);
  printf("%p",nexttry);
  gotoxy(69,7);
  printf("%p",fsbfirst);}
void print_pcb(){
  gotoxy(20,11);
  printf("%d",fstpcb.name);
  gotoxy(20,12);
  printf("%p",&fstpcb);
  gotoxy(20,13);
  printf("%p",fstpcb.npall);
  gotoxy(20,14);
  printf("%p",fstpcb.lpall);
  gotoxy(20,15);
  printf("%d",fstpcb.stopt);
  gotoxy(20,16);
  printf("%d",fstpcb.blokt);
  gotoxy(20,17);
  printf("%p",fstpcb.nsw);
  gotoxy(30,11);
  printf("%d",scnpcb.name);
  gotoxy(30,12);
  printf("%p",&scnpcb);
  gotoxy(30,13);
  printf("%p",scnpcb.npall);
  gotoxy(30,14);
  printf("%p",scnpcb.lpall);
  gotoxy(30,15);
  printf("%d",scnpcb.stopt);
  gotoxy(30,16);
  printf("%d",scnpcb.blokt);
  gotoxy(30,17);
  printf("%p",scnpcb.nsw);
  gotoxy(40,11);
  printf("%d",thdpcb.name);
  gotoxy(40,12);
  printf("%p",&thdpcb);
  gotoxy(40,13);
  printf("%p",thdpcb.npall);
  gotoxy(40,14);
  printf("%p",thdpcb.lpall);
  gotoxy(40,15);
  printf("%d",thdpcb.stopt);
  gotoxy(40,16);
  printf("%d",thdpcb.blokt);
  gotoxy(40,17);
  printf("%p",thdpcb.nsw);}
void regulator(){
   do{
     print_pcb();
     print_rn();
     do{
       if (((*((*running).npall)).stopt||(*((*running).npall)).blokt)&&running!=NULL){
	 running=(*running).npall;
	 nexttry=(*running).npall;
	 if (running==NULL) wait();}
       else{
	 running=(pcb *)nexttry;
	 nexttry=(*running).npall;
	 break;}
	 }while(1);
       if (((*running).name)==0)
	 first();
       if (((*running).name)==1)
	 second();
       if (((*running).name)==2)
	 third();
       }while(1);
}
void xp(){
   sm *addrsm=(sm*) reg2;
   pcb far*pcbwait;
   long i;
   (*addrsm).val--;
   print_rn();
   pause();
   if (((*addrsm).val)<0) {
     (*running).isa=syssemsa;
     if ((*addrsm).val==-1)
       (*addrsm).ptr=running;
     else{
       (void far*)pcbwait=(*addrsm).ptr;
       for (i=-1;i>=(*addrsm).val;i--){
	 if ((*pcbwait).nsw==NULL) {
	   (*pcbwait).nsw=running;
	   break;}
	 pcbwait=(*pcbwait).nsw;}}
     print_rn();
     (*running).blokt=1;
     regulator();}}
void xv(){
   sm *addrsm=(sm*) reg2;
   (*addrsm).val++;
   print_rn();
   pause();
   if (((*addrsm).val)<=0){
     (*running).blokt=0;
     if (!nexttrym) {
       nexttry=running;
       nexttrym=1;}
     (*addrsm).ptr=(*running).nsw;
     (*running).nsw=NULL;
     (*running).blokt=0;
	  regulator();}}
void sort_fsb(){
   int i,j;
   fsb *curfsb,*nextfsb;
   unsigned long psize;
   void *pbeg;
   for (i=0;i<5;i++){
     curfsb=fsbfirst;
     for (j=0;j<5;j++){
       (void *)nextfsb=(*curfsb).next;
       if ((*curfsb).next==NULL) break;
       if ((*curfsb).size>(*nextfsb).size) {
	  psize=(*curfsb).size;
	  (*curfsb).size=(*nextfsb).size;
	  (*nextfsb).size=psize;
	  pbeg=(*curfsb).ptr;
	  (*curfsb).ptr=(*nextfsb).ptr;
	  (*nextfsb).ptr=pbeg;}
       curfsb=nextfsb;}}}
void xb(fsb far* fsbaddr,unsigned long blsize,unsigned long needsize,int n){
   int i;
   unsigned long newsize=blsize-((needsize&0xfffffffc)+4*(!(!(needsize&3))));
   unsigned long oldsize=(*fsbaddr).size-newsize;
   unsigned long addr=(unsigned long)(*fsbaddr).ptr+oldsize;
   (*fsbaddr).ptr=(void*)addr;
   (*fsbaddr).size=newsize;
   fsbaddr=fsbfirst;
   for(i=0;i<n;i++){
     (*fsbaddr).size=0;
     (void *)fsbaddr=(*fsbaddr).next;}
   sort_fsb();
   }
void xa(int n){
   int l=0;
   char kk;
   unsigned long sumsize=0;
   xaprm *addrst=(xaprm*) reg2;
   unsigned long blsize=(*addrst).blsize,needsize=0;
   void far *bladdr;
   gotoxy(5,20);

   printf ("Запрос на выделение памяти размером %lxh байт от процесса %d",(long)blsize,n);
   pause();
   fsb far*fsbaddr=fsbfirst;
   fsb far*fsbneed=fsbfirst;
   void *fbladdr;

   reg2=&fsbsem;
   gotoxy(5,20);
   printf ("P - Операция на семафоре FSBSEM                                      ");
   xp();

   do{
   if (!(*fsbaddr).size) (void far*)fsbneed=(*fsbaddr).next;
   if ((*fsbaddr).size>=blsize) {
	needsize=(*fsbaddr).size;
	bladdr=(*fsbaddr).ptr;
	break;}
   else {
	sumsize+=(*fsbaddr).size;
	if ((*fsbaddr).size)
	  l++;
	if (sumsize>=blsize){
	  needsize=sumsize;
	  bladdr=(*fsbneed).ptr;
	  break;}
	if((*fsbaddr).next==NULL) {
	  bladdr=NULL;
	  break;}
	else
	  (void far*)fsbaddr=(*fsbaddr).next;}}
     while (1);
     if ((l>1)&&bladdr!=NULL) {
       gotoxy(5,20);
       printf ("Программа хочет памяти больше чем есть в FSB , дать ей кусками?(Д/Н)     ");
       do{
       kk=getch();
       if (kk=='y') bladdr=NULL;}
       while(kk!='y'&&kk!='l');}
     if (bladdr!=NULL) {
      xb(fsbaddr,needsize,blsize,l-1);
      (*addrst).bladdr=bladdr;
      gotoxy(5,20);
      printf ("V - Операция на семафоре FSBSEM                                     ");
      xv();}
   else {
      gotoxy(5,20);
      printf ("V - Операция на семафоре FSBSEM                                     ");
      xv();
      reg2=&memory;
      gotoxy(5,20);
      printf ("P - Операция на семафоре MEMORY                                     ");
      xp();}
   print_fsb();}
void main(){
  //setup fsb
  int i;
  clrscr();
  for(i=0;i<5;i++){
    fsbb[i].ptr=(void *)((i+1)*0x10000000);
    fsbb[i].next=&fsbb[i+1];
    fsbb[i].size=0x10000000;}
  fsbb[4].next=NULL;
  //setup xapcb
  fstpcb.name=0;
  fstpcb.npall=&scnpcb;
  fstpcb.lpall=&thdpcb;
  fstpcb.stopt=0;
  fstpcb.blokt=0;
  fstpcb.nsw=NULL;
  scnpcb.name=1;
  scnpcb.npall=&thdpcb;
  scnpcb.lpall=&fstpcb;
  scnpcb.stopt=0;
  scnpcb.blokt=0;
  scnpcb.nsw=NULL;
  thdpcb.name=2;
  thdpcb.npall=&fstpcb;
  thdpcb.lpall=&scnpcb;
  thdpcb.stopt=0;
  thdpcb.blokt=0;
  thdpcb.nsw=NULL;
  //setup variables for regulator
  reg2=0;
  nexttry=&fstpcb;
  nexttrym=1;
  running=NULL;
  memory.ptr=NULL;
  memory.val=0;
  fsbsem.ptr=NULL;
  fsbsem.val=1;

  gotoxy(15,1);
  printf("Цепочка FSB");
  gotoxy(3,2);
  printf("FSBADDR   NEXTFSB   PTR       SIZE");
  gotoxy(50,3);
  printf("Семафор MEMORY=");
  gotoxy(50,4);
  printf("Семафор FSBSEM=");
  gotoxy(50,5);
  printf("Указатель RUNNING=");
  gotoxy(50,6);
  printf("Указатель NEXTTRY=");
  gotoxy(50,7);
  printf("Указатель FIRSTFSB=");
  gotoxy(20,10);
  printf("PCB");
  gotoxy(10,11);
  printf("NAME");
  gotoxy(10,12);
  printf("PCBADDR");
  gotoxy(10,13);
  printf("NPALL");
  gotoxy(10,14);
  printf("LPALL");
  gotoxy(10,15);
  printf("STOPT");
  gotoxy(10,16);
  printf("BLOKT");
  gotoxy(10,17);
  printf("NWS");
  print_fsb();
  print_pcb();
  print_rn();
  //call regulator
  regulator();
}




