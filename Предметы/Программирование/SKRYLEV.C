#include<stdio.h>
#include<conio.h>
#include<io.h>
#include<string.h>
#include<ctype.h>

#define AND &&
#define OR ||
#define TRUE 1
#define FALSE 0


typedef struct{
char name[11];
char size[2];
char hex[11];
}instr;

void enter(void);
void look(void);
void alf(void);
void length(void);
void kb(void);
void createwin(void);

void main(void)
{
 char c;

 do
  {
   clrscr();
   window(25,5,54,12);
   textbackground(7);
   textcolor(3);
   clrscr();
   window(25,5,54,20);
   gotoxy(1,1);
   createwin();
   textcolor(0);
   window(26,6,53,13);
   gotoxy(1,3);
   cputs("  ������ � 䠩�\n\r");
   cputs("  ��ࠡ�⪠ 䠩��\n\r");
   cputs("  c���஢�� �� ��䠢���\n\r");
   cputs("  ���஢�� �� D����\n\r");
   cputs("  ��ᬮ�� 䠩��\n\r");
   cputs("  ��室\n\r");
   textbackground(0);
   window(1,1,80,25);
   gotoxy(23,1);
   textcolor(15);
   cputs("�������� ������ �� ����������������");
   gotoxy(29,24);
   cputs("(C) ����� ������� 1995");
   c=getch();
   switch (c)
    {
	 case 'c':enter();
	  break;
	 case 'g':look();
	  break;
	 case 'f':alf();
	  break;
	 case 'l':length();
	  break;
	 case 'j':kb();
	  break;
	 }
  }
 while(c!='d');
 clrscr();
 cputs("Course work for a course of Programming by Skrylev Pavel (C)1995");
}

/************************ ���� � ���� *********************************/
void enter(void)
{
 instr com;
 FILE *f;
 int i,numm;
 char filename[14],k;

 window(1,1,80,25);
 textbackground(0);
 textcolor(3);
 clrscr();
 cputs("������ �������� 䠩��, � ����� �㤥� ������ ������...");
 gets(filename);
 cputs("����쪮 �㤥� ������ ����ᥩ...");
 scanf("%d",&numm);
 gets(com.name);
 for (i=0;i<numm;i++)
  {
   clrscr();
   printf("������ ����� %d\n",i);
   cputs("  ������ �������� �������...");
   gets(com.name);
   cputs("  ������ ����� �������...");
   gets(com.size);
   cputs("  ������ ��⭠������ ��� �������...");
   gets(com.hex);
   if(access(filename,06)==-1)
     f=fopen(filename,"aw");
    else
     f=fopen(filename,"ar");
   fseek(f,0,SEEK_END);
   fwrite(&com,sizeof(com),1,f);
   fclose(f);
   }
}
/************************* �������� ����� *********************************/
void look(void)
{
 instr com;
 int i,n=0;
 char filename[14];
 FILE *f;

 window(1,1,80,25);
 textbackground(0);
 textcolor(11);
 clrscr();
 cputs("������ ��� 䠩��, ����� �㤥� ᬮ����...");
 scanf("%s",filename);
 f=fopen(filename,"r");
 fseek(f,0,SEEK_SET);
 while(!feof(f))
  {
   fread(&com,sizeof(com),1,f);
   n++;
  }
 n--;
 fseek(f,0,SEEK_SET);
 printf("��������    �����  ��設�� ���\n");
 for(i=0;i<n;i++)
  {
   fread(&com.name,sizeof(com.name),1,f);
   fread(&com.size,sizeof(com.size),1,f);
   fread(&com.hex,sizeof(com.hex),1,f);
   printf("%s",&com.name);
   gotoxy(15,wherey());
   printf("%s",&com.size);
   gotoxy(18,wherey());
   printf("%s\n",&com.hex);
  }
 fclose(f);
 getch();
}
/*************************���������� �� ��������*************************/
void alf(void)
{
 FILE *f,*f1;
 char filename[14],nameoffile[14];
 char c;
 int i,n=0,j,k,fl;
 instr smass[100],old;

 window(1,1,80,25);
 textbackground(0);
 textcolor(3);
 clrscr();
 cputs("������ ��� 䠩��-���筨�� ������...");
 scanf("%s",filename);
 cputs("������ ��� 䠩��,� ����� ���� ����ᠭ� �����...");
 scanf("%s",nameoffile);
 f=fopen(filename,"r");
 f1=fopen(nameoffile,"aw");
 fseek(f,0,SEEK_SET);
 while(!feof(f))
  {
   fread(&smass[n],sizeof(old),1,f);
   n++;
  }
 n--;
 for (i=n-1;i>0;i--)
   {
     for (j=0;j<i;j++)
       {
	 fl=TRUE;
	 k=0;
	 while ((k<10)AND(fl==TRUE))
	   {
	     if (smass[j].name[k]>smass[j+1].name[k])
		{
		  old=smass[j];
		  smass[j]=smass[j+1];
		  smass[j+1]=old;
		  fl=FALSE;
		}
	     if (smass[j].name[k]<smass[j+1].name[k])
		fl=FALSE;
	     k++;
	   }
       }
   }
 printf("��������    �����  ��設�� ���\n");
 for (i=0;i<n;i++)
   {
   fwrite (&smass[i],sizeof(old),1,f1);
   printf("%s",&smass[i].name);
   gotoxy(15,wherey());
   printf("%s",&smass[i].size);
   gotoxy(18,wherey());
   printf("%s\n",&smass[i].hex);
   }
 fcloseall();
 cputs("��ࠡ�⪠ �����襭�...");
 getch();
}
/**********************���������� �� �����***************************/
void length(void)
{
 FILE *f,*f1;
 char filename[14],nameoffile[14];
 char c;
 int i,n=0,k;
 instr com;

 window(1,1,80,25);
 textbackground(0);
 textcolor(2);
 clrscr();
 cputs("������ ��� 䠩��-���筨�� ������...");
 scanf("%s",filename);
 cputs("������ ��� 䠩��,� ����� ���� ����ᠭ� �����...");
 scanf("%s",nameoffile);
 f=fopen(filename,"r");
 f1=fopen(nameoffile,"aw");
 fseek(f,0,SEEK_SET);
 while(!feof(f))
  {
   fread(&com,sizeof(com),1,f);
   n++;
  }
 printf("��������    �����  ��設�� ���\n");
 n--;
 for(k=49;k<=57;k++)
  {
   fseek(f,0,SEEK_SET);
   for(i=0;i<n;i++)
	{
	 c=toascii(k);
	 fread(&com.name,sizeof(com.name),1,f);
	 fread(&com.size,sizeof(com.size),1,f);
	 fread(&com.hex,sizeof(com.hex),1,f);
	 if(com.size[0]==c)
            {
	    fwrite(&com,sizeof(com),1,f1);
	    printf("%s",&com.name);
	    gotoxy(15,wherey());
	    printf("%s",&com.size);
	    gotoxy(18,wherey());
	    printf("%s\n",com.hex);
            }
	}
  }
 fcloseall();
 cputs("��ࠡ�⪠ �����襭�...");
 getch();
}
/***************************��������� �����****************************/
void kb(void)
{
 instr com;
 char filename[14],nameoffile[14];
 FILE *f,*f1;
 char size[2];
 int i,n=0;

 window(1,1,80,25);
 textbackground(0);
 textcolor(3);
 clrscr();
 cputs("������ ��� 䠩��, ����� �㤥� ��ࠡ��뢠��...");
 scanf("%s",filename);
 cputs("������ ��� 䠩��, � ����� �㤥� ����ᠭ १����...");
 scanf("%s",nameoffile);
 f=fopen(filename,"r");
 f1=fopen(nameoffile,"aw");
 cputs("������ ����� �������...");
 scanf("%s",size);
 fseek(f,0,SEEK_SET);
 while(!feof(f))
  {
   fread(&com,sizeof(com),1,f);
   n++;
  }
 n--;
 fseek(f,0,SEEK_SET);
 printf("��������    �����  ��設�� ���\n");
 for(i=0;i<n;i++)
  {
   fread(&com.name,sizeof(com.name),1,f);
   fread(&com.size,sizeof(com.size),1,f);
   fread(&com.hex,sizeof(com.hex),1,f);
   if(com.size[0]==size[0])
	{
	 fwrite(&com,sizeof(com),1,f1);
	 printf("%s",&com.name);
	 gotoxy(15,wherey());
	 printf("%s",&com.size);
	 gotoxy(18,wherey());
	 printf("%s\n",&com.hex);
	 }
  }
 fcloseall();
 getch();
}
void createwin(void)
{
   cputs("����������������������������ͻ");
   cputs("�                            �");
   cputs("�                            �");
   cputs("�                            �");
   cputs("�                            �");
   cputs("�                            �");
   cputs("�                            �");
   cputs("�                            �");
   cputs("�                            �");
   cputs("����������������������������ͼ");

}

