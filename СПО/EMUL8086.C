#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "stdlib.h"
char *mem;
int h[256];
long reg[8],sreg[4],sregc,flag;
int com,i,j,p,e,ee;
int flags[8];
char *fnm,*null=NULL;
FILE *file1,*file2;
int ip=0x100,dump=0;
char k;
int verify_command(){
  return(h[i]);}
void print_error(){
    gotoxy(25,21);
    printf("Illegal command code <Exeption #6>");
    ip+=1;}
void print_memory(){
  for(j=0;j<2;i++)
    for(i=0;i<4;i++)
      printf("%D",*(mem+i+j*4+dump));}
void load_code(){
  printf("Enter code adress:");
  scanf("%D:%D",&sreg[1],&ip);}
void load_dump(){
  printf("Enter data adress:");
  scanf("%D:%D",&sreg[3],&dump);}
void load_file(){
  printf("Enter filename:");
  scanf("%s",fnm);
  file1=fopen(fnm,"r");
  while(!feof(file1))
    fscanf(file1,"%c",*(mem+i++));}
int r_m(int mode){
  int kk;
  kk=*(mem+ip+1)&7;
  switch(kk){
    case 0: return(reg[3]+reg[6]);
    case 1: return(reg[3]+reg[7]);
    case 2: return(reg[5]+reg[6]);
    case 3: return(reg[5]+reg[7]);
    case 4: return(reg[6]);
    case 5: return(reg[7]);
    case 6: if(!mode) return(*(mem+ip+2)+(*(mem+ip+3)<<8));
	      else  return(reg[5]);}
  return(reg[3]);}
int rm(int mode,int w){
//0-byte ptr
  if(!w) {switch(mode){
    case 0 : return(r_m(mode));
    case 1 : return(r_m(mode)+(*(mem+ip+2)));
    case 2 : return(r_m(mode)+(*(mem+ip+2))+(*(mem+ip+3)<<8));}
    return(reg[*(mem+ip+1)&7]);}
  else {switch(mode){
    case 0 : return(r_m(mode));
    case 1 : return(r_m(mode)+(*(mem+ip+2)));
    case 2 : return(r_m(mode)+(*(mem+ip+2))+(*(mem+ip+3)<<8));}
  return(reg[*(mem+ip+1)&7]);}}
int parity(int fzz) {
	for (i=0;i<16;i++)
	  if((1<<i)&fzz)p++;
	return(p);}
void inc(int ww){
  if(!ww)reg[com&0x7]++;
  else if((*(mem+ip+1))>>6==3){
	 if((reg[*(mem+ip+1)&7]++)&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if(((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))++)&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}
void dec(int ww){
  if(!ww) reg[com&7]--;
  else if((*(mem+ip+1)>>6)==3){
	 if((reg[*(mem+ip+1)&7]--)&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if(((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))--)&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}
void add(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]+=*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x3c)>>3)]&=0xffff;}
		  else flags[0]=0;
		  if(reg[((*(mem+ip+1)&0x3c)>>3)]==0)flags[1]=1;
		  else flags[1]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]+=(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x38)>>3)]&=0xffff;}
	     else flags[0]=0;
	     if(reg[((*(mem+ip+1)&0x38)>>3)]==0)flags[1]=1;
	     else flags[1]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+=reg[((*(mem+ip+1)&0x3c)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+=reg[((*(mem+ip+1)&0x38)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
		else flags[0]=0;
		if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
		else flags[1]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]+=(*(mem+ip+1)|((*(mem+ip+2))<<8)))&0x10000){flags[0]=1;
		   reg[0]&=0xffff;}
	 else flags[0]=0;
	 if(reg[0]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=parity(reg[0]);}}
  else{if(((*(mem+ip+1))>>6)==3){
	 if((reg[*(mem+ip+1)&7]+=(*(mem+ip+2)|((*(mem+ip+3))<<8)))&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+=(*(mem+ip+2)+*(mem+ip+3)<<8))&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void or(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]|=*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x3c)>>3)]&=0xffff;}
		  else flags[0]=0;
		  if(reg[((*(mem+ip+1)&0x3c)>>3)]==0)flags[1]=1;
		  else flags[1]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]|=(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x38)>>3)]&=0xffff;}
	     else flags[0]=0;
	     if(reg[((*(mem+ip+1)&0x38)>>3)]==0)flags[1]=1;
	     else flags[1]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))|=reg[((*(mem+ip+1)&0x3c)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))|=reg[((*(mem+ip+1)&0x38)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
		else flags[0]=0;
		if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
		else flags[1]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]|=(*(mem+ip+1)|((*(mem+ip+2))<<8)))&0x10000){flags[0]=1;
		   reg[0]&=0xffff;}
	 else flags[0]=0;
	 if(reg[0]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=parity(reg[0]);}}
  else{if(((*(mem+ip+1))>>6)==3){
	 if((reg[*(mem+ip+1)&7]|=(*(mem+ip+2)|((*(mem+ip+3))<<8)))&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))|=(*(mem+ip+2)+*(mem+ip+3)<<8))&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void adc(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]+=*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1))+flags[0])&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x3c)>>3)]&=0xffff;}
		  else flags[0]=0;
		  if(reg[((*(mem+ip+1)&0x3c)>>3)]==0)flags[1]=1;
		  else flags[1]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]+=(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+flags[0])&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x38)>>3)]&=0xffff;}
	     else flags[0]=0;
	     if(reg[((*(mem+ip+1)&0x38)>>3)]==0)flags[1]=1;
	     else flags[1]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+=(reg[((*(mem+ip+1)&0x3c)>>3)])+flags[0])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+=(reg[((*(mem+ip+1)&0x38)>>3)])+flags[0])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
		else flags[0]=0;
		if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
		else flags[1]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]+=(*(mem+ip+1)|((*(mem+ip+2))<<8))+flags[0])&0x10000){flags[0]=1;
		   reg[0]&=0xffff;}
	 else flags[0]=0;
	 if(reg[0]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=parity(reg[0]);}}
  else{if(((*(mem+ip+1))>>6)==3){
	 if((reg[*(mem+ip+1)&7]+=(*(mem+ip+2)|((*(mem+ip+3))<<8))+flags[0])&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+=((*(mem+ip+2)+*(mem+ip+3)<<8))+flags[0])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void sbb(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]-=*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1))+flags[0])&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x3c)>>3)]&=0xffff;}
		  else flags[0]=0;
		  if(reg[((*(mem+ip+1)&0x3c)>>3)]==0)flags[1]=1;
		  else flags[1]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]-=(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))+flags[0])&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x38)>>3)]&=0xffff;}
	     else flags[0]=0;
	     if(reg[((*(mem+ip+1)&0x38)>>3)]==0)flags[1]=1;
	     else flags[1]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))-=(reg[((*(mem+ip+1)&0x3c)>>3)])+flags[0])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))-=(reg[((*(mem+ip+1)&0x38)>>3)])+flags[0])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
		else flags[0]=0;
		if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
		else flags[1]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]-=(*(mem+ip+1)|((*(mem+ip+2))<<8))+flags[0])&0x10000){flags[0]=1;
		   reg[0]&=0xffff;}
	 else flags[0]=0;
	 if(reg[0]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=parity(reg[0]);}}
  else{if(((*(mem+ip+1))>>6)==3){
	 if((reg[*(mem+ip+1)&7]-=(*(mem+ip+2)|((*(mem+ip+3))<<8))+flags[0])&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))-=((*(mem+ip+2)+*(mem+ip+3)<<8))+flags[0])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void and(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]&=*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x3c)>>3)]&=0xffff;}
		  else flags[0]=0;
		  if(reg[((*(mem+ip+1)&0x3c)>>3)]==0)flags[1]=1;
		  else flags[1]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]&=(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x38)>>3)]&=0xffff;}
	     else flags[0]=0;
	     if(reg[((*(mem+ip+1)&0x38)>>3)]==0)flags[1]=1;
	     else flags[1]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=reg[((*(mem+ip+1)&0x3c)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=reg[((*(mem+ip+1)&0x38)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
		else flags[0]=0;
		if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
		else flags[1]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]&=(*(mem+ip+1)|((*(mem+ip+2))<<8)))&0x10000){flags[0]=1;
		   reg[0]&=0xffff;}
	 else flags[0]=0;
	 if(reg[0]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=parity(reg[0]);}}
  else{if(((*(mem+ip+1))>>6)==3){
	 if((reg[*(mem+ip+1)&7]&=(*(mem+ip+2)|((*(mem+ip+3))<<8)))&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=(*(mem+ip+2)+*(mem+ip+3)<<8))&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void sub(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]-=*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x3c)>>3)]&=0xffff;}
		  else flags[0]=0;
		  if(reg[((*(mem+ip+1)&0x3c)>>3)]==0)flags[1]=1;
		  else flags[1]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]-=(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x38)>>3)]&=0xffff;}
	     else flags[0]=0;
	     if(reg[((*(mem+ip+1)&0x38)>>3)]==0)flags[1]=1;
	     else flags[1]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))-=reg[((*(mem+ip+1)&0x3c)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))-=reg[((*(mem+ip+1)&0x38)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
		else flags[0]=0;
		if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
		else flags[1]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]-=(*(mem+ip+1)|((*(mem+ip+2))<<8)))&0x10000){flags[0]=1;
		   reg[0]&=0xffff;}
	 else flags[0]=0;
	 if(reg[0]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=parity(reg[0]);}}
  else{if(((*(mem+ip+1))>>6)==3){
	 if((reg[*(mem+ip+1)&7]-=(*(mem+ip+2)|((*(mem+ip+3))<<8)))&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))-=(*(mem+ip+2)+*(mem+ip+3)<<8))&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void xor(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]^=*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x3c)>>3)]&=0xffff;}
		  else flags[0]=0;
		  if(reg[((*(mem+ip+1)&0x3c)>>3)]==0)flags[1]=1;
		  else flags[1]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]^=(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))&0x10000){flags[0]=1;
		    reg[((*(mem+ip+1)&0x38)>>3)]&=0xffff;}
	     else flags[0]=0;
	     if(reg[((*(mem+ip+1)&0x38)>>3)]==0)flags[1]=1;
	     else flags[1]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))^=reg[((*(mem+ip+1)&0x3c)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))^=reg[((*(mem+ip+1)&0x38)>>3)])&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
		else flags[0]=0;
		if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
		else flags[1]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]^=(*(mem+ip+1)|((*(mem+ip+2))<<8)))&0x10000){flags[0]=1;
		   reg[0]&=0xffff;}
	 else flags[0]=0;
	 if(reg[0]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=parity(reg[0]);}}
  else{if(((*(mem+ip+1))>>6)==3){
	 if((reg[*(mem+ip+1)&7]^=(*(mem+ip+2)|((*(mem+ip+3))<<8)))&0x10000){flags[0]=1;
		   reg[*(mem+ip+1)&7]&=0xffff;}
	 else flags[0]=0;
	 if(reg[*(mem+ip+1)&7]==0)flags[1]=1;
	 else flags[1]=0;
	 flags[2]=reg[*(mem+ip+1)&7];}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))^=(*(mem+ip+2)+*(mem+ip+3)<<8))&0x10000){flags[0]=1;
		    *(mem+rm((*(mem+ip+1)&0xc0)>>6,1))&=0xffff;}
	    else flags[0]=0;
	    if(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0)flags[1]=1;
	    else flags[1]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void cmp(int ww){
  if(!ww){
    if(com&7<4)
      if(com&2){
	if(com&1){if((reg[((*(mem+ip+1)&0x3c)>>3)]==*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1))))flags[1]=1;
		  else flags[1]=0;
		  flags[0]=0;
		  flags[2]=parity(reg[((*(mem+ip+1)&0x3c)>>3)]);}
	else{if(reg[((*(mem+ip+1)&0x38)>>3)]==*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)))flags[1]=1;
	     else flags[1]=0;
	     flags[0]=0;
	     flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}}
      else{if(com&2){if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==reg[((*(mem+ip+1)&0x3c)>>3)]))flags[1]=1;
	    else flags[1]=0;
	    flags[0]=0;
	    flags[2]=parity(reg[((*(mem+ip+1)&0x38)>>3)]);}
	   else{if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==reg[((*(mem+ip+1)&0x38)>>3)]))flags[1]=1;
		else flags[1]=0;
		flags[0]=0;
		flags[2]=parity(*(mem+rm((*(mem+ip+1)&0xc0)>>6,1)));}}
    else{if((reg[0]==(*(mem+ip+1)|((*(mem+ip+2))<<8))))flags[0]=1;
	 else flags[1]=0;}}
  else{if((*(mem+ip+1))>>6==3){
	 if((reg[*(mem+ip+1)&7]==(*(mem+ip+2)|((*(mem+ip+3))<<8))))flags[1]=1;
	 else flags[1]=0;}
       else if((*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==(*(mem+ip+2)+*(mem+ip+3)<<8)))flags[1]=1;
	    else flags[1]=0;
	    flags[0]=0;
	    flags[2]=*(mem+rm((*(mem+ip+1)&0xc0)>>6,1));}}
void jcc(){
     if(flags[(com&0xf)>>1])
       ip+=*(mem+ip+1);}
void jmp(int ww){
   if(!ww){
    switch(com){
     case 0xe9:ip+=*(mem+ip+1)+*(mem+ip+2)<<8;
     case 0xea:;{sreg[1]=*(mem+ip+3)+(*(mem+ip+4)<<8);
		ip=*(mem+ip+1)+*(mem+ip+2)<<8;}
     case 0xeb:;ip+=*(mem+ip+1);}}
    else {
      if((*(mem+ip+1)>>3)&7==4) ip=*(mem+rm(*(mem+ip+1)>>6,1));
      else {sreg[1]=*(mem+rm(*(mem+ip+1)>>6,1)+2);
	   ip=*(mem+rm(*(mem+ip+1)>>6,1));}}}
void arithm(){
    if(com<0x6) add(0);
    if(com<0xe) or(0);
    if(com<0x16) adc(0);
    if(com<0x1e) sbb(0);
    if(com<0x26) and(0);
    if(com<0x2e) sub(0);
    if(com<0x36) xor(0);
    else cmp(0);}
void nop(){}
void test(){
    if(com&1){if(reg[((*(mem+ip+1)&0x3c)>>3)]&*(mem+rm(((*(mem+ip+1)&0xc0)>>6),1))==0)flags[1]=1;
		else flags[1]=0;}
      else{if(reg[((*(mem+ip+1)&0x38)>>3)]&*(mem+rm((*(mem+ip+1)&0xc0)>>6,1))==0) flags[1]=1;
	   else flags[1]=0;}}
void callf(){
  reg[4]-=2;
  *(mem+reg[4])=sreg[1];
  reg[4]-=2;
  *(mem+reg[4])=ip;
  sreg[1]=*(mem+ip+1)+*(mem+ip+2)<<8;
  ip=*(mem+ip+3)+*(mem+ip+4)<<8;}
void testa(){
  if(com&1)if(reg[0]&(*(mem+ip+1)+(*(mem+ip+2))<<8))flags[1]=0;
	   else flags[1]=1;
  else if((reg[0]&0xff)&(*(mem+ip+1)))flags[1]=0;
	   else flags[1]=1;}
void ret(){
  ip=*(mem+reg[4])+*(mem+reg[4]+1)<<8;
  reg[4]+=2;}
void retf(){
  ip=*(mem+reg[4])+*(mem+reg[4]+1)<<8;
  reg[4]+=2;
  sreg[1]=*(mem+reg[4])+*(mem+reg[4]+1)<<8;
  reg[4]+=2;}
void inti(){
  reg[4]-=2;
  *(mem+reg[4])=flag;
  reg[4]-=2;
  *(mem+reg[4])=sreg[1];
  reg[4]-=2;
  *(mem+reg[4])=ip;
  switch(com){
    case 0xcc:{sreg[1]=*(null+3*4+2)+*(null+3*4+3)<<8;
		ip=*(null+3*4)+*(null+3*4+1)<<8;}
    case 0xcd:{sreg[1]=*(null+*(mem+ip+1)*4+2)+*(null+*(mem+ip+1)*4+3)<<8;
		ip=*(null+*(mem+ip+1)*4)+*(null+*(mem+ip+1)*4+1)<<8;}
    case 0xce:{sreg[1]=*(null+3*4+2)+*(null+3*4+3)<<8;
		ip=*(null+3*4)+*(null+3*4+1)<<8;}}}
void iret(){
  ip=*(mem+reg[4])+*(mem+reg[4]+1)<<8;
  reg[4]+=2;
  sreg[1]=*(mem+reg[4])+*(mem+reg[4]+1)<<8;
  reg[4]+=2;
  flag=*(mem+reg[4])+*(mem+reg[4]+1)<<8;
  reg[4]+=2;}
void loop(){
  switch(com){
    case 0xe3:if(!reg[1])ip+=*(mem+ip+1);
    case 0xe0:{reg[1]--;
	       if(reg[1])ip+=*(mem+ip+1);}
    case 0xe1:{reg[1]--;
	       if(reg[1]||!flags[1])ip+=*(mem+ip+1);}
    case 0xe2:{reg[1]--;
	      if(reg[1]||flags[1])ip+=*(mem+ip+1);}}}
void shrr(int co,int w){
  switch((*(mem+ip+1)>>3)&7){
     case 0:{if(
	     *(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))<<1;}
     case 1:{*(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))>>1;}
     case 2:{*(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))<<1;}
     case 3:{*(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))>>1;}
     case 4:{*(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))<<1;}
     case 5:{*(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))>>1;}
     case 6:{*(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))<<1;}
     case 7:{*(mem+rm(*(mem+ip+1)>>6,w))=*(mem+rm(*(mem+ip+1)>>6,w))>>1;}
void shift(int ww){
  if(!ww){
     shrr(1,!(com&1));
  else shrr(reg[1]&0xff,!(com&1));}}
void call(int ww){
  if(!ww){
  reg[4]-=2;
  *(mem+reg[4])=ip;
  ip+=*(mem+ip+1)+*(mem+ip+2)<<8;}
  else if((*(mem+ip+1)>>3)&7==4) {
     reg[4]-=2;
     *(mem+reg[4])=ip;
     ip=*(mem+rm(*(mem+ip+1)>>6,1));}
      else {
	reg[4]-=2;
	*(mem+reg[4])=sreg[1];
	reg[4]-=2;
	*(mem+reg[4])=ip;
	sreg[1]=*(mem+rm(*(mem+ip+1)>>6,1)+2);
	ip=*(mem+rm(*(mem+ip+1)>>6,1));}}
void arithm1(){
switch((*(mem+ip+1)>>3)&7){
  case 0:add(1);
  case 1:or(1);
  case 2:adc(1);
  case 3:sbb(1);
  case 4:and(1);
  case 5:sub(1);
  case 6:xor(1);
  default: cmp(1);}}
void jmpmp(){
switch((*(mem+ip+1)>>3)&7){
  case 0:inc(1);
  case 1:dec(1);
  case 2:call(1);
  case 3:call(2);
  case 4:jmp(1);
  case 5:jmp(2);}}
void execute_command(){
    com=*(mem+ip);
    if(com==0x90) nop();
    if(com<64) arithm();
    if(com<0x48) inc(0);
    if(com<0x50) dec(0);
    if(com<0x80) jcc();
    if(com<0x84) arithm1();
    if(com<0x86) test();
    if(com<0x9a) callf();
    if(com<0xae) testa();
    if(com<0xca) ret();
    if(com<0xcc) retf();
    if(com<0xcf) inti();
    if(com==0xcf) iret();
    if(com<0xe8) loop();
    if(com<0xe8) call(0);
    if(com<0xe8) jmp(0);
    else jmpmp();
    ip+=h[com];
    sregc=3;}
void print_registers(){
    for(i=0;i<3;i++)
      printf("%X",reg[i]);
    for(i=0;i<3;i++)
      printf("%X",reg[i+3]);
    for(i=0;i<4;i++)
      printf("%X:%X",sreg[i],reg[i+6]);}
void print_dump(){
    for(j=0;j<2;j++)
      for(i=0;i<4;i++)
	printf("%X",*(mem+dump));}
void print_stack(){
    for(i=0;i<2;i++)
      printf("%X",*(mem+reg[4]));}
void print_flags(){
    for(i=0;i<8;i++)
      printf("%d",flags[i]);}
main(){
    print_registers();
    print_flags();
    file2=fopen("command.tbl","r");
    if(!file2) {
       return(-1);}
    while (!feof(file2)){
      fscanf(file2,"%d,",h[i++]);}
    mem=(char *)calloc(0x20000,sizeof(char));
    if (getch()==27) return(0);
    i=0;
    do{
      gotoxy(15,21);
      printf("										     ");
      gotoxy(21,21);
      if(!verify_command())
	print_error();
      else execute_command();
      print_registers();
      print_flags();
      print_memory();
      print_stack();
      do {
	  k=getch();
	  switch(k){
	   case 0x3b: load_dump();
	   case 0x3c: load_code();
	   case 0x3d: load_file();
	   case 27: return(0);}
	  }while(k!=0x3b||k!=0x3c||k!=27||k!=0x3d);
      }while(1);
}