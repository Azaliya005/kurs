#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>
#include <iostream>
#include <cstdlib>  

using namespace std;
using namespace System;
using namespace System::IO;

int menu(int);
void mini(struct z*);
void text_data(char *,char *);
void first(struct z*);
void alfspis(struct z*);
void listing(struct z*);
void diagram(struct z *);
void vstavka(struct z*,char*);
void sovpadeniya(struct z *);
void vopros(struct z*);

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80

/*char dan[7][55]={
          "Какой персонаж имеет меньше всего созвездий?         ",
          "Какой персонаж был получен раньше всех?              ",
          "Список лучников c доходом выше 500 тыс.              ",
          "Алфавитный список                                    ",
          "Одинаковое количество созвездий, но разное оружие    ",
          "Диаграмма                                            ",
          "Выход                                                "
  };
  char BlankLine[ ]="                                ";
  int NC;*/

  struct z {
      char name[20];
      char element[20];
      char weapon[20];
      char year[10];
      long constellation;
	  long money;
      };
  struct sp {
	char fio[20];
	long money;
	struct sp* sled;
	struct sp* pred;

		} *spisok;

int main(array<System::String ^> ^args)
{

	int i,n;
	int NC;//объявление как локальную переменную
	FILE *in;
	char dan[7][55]={
          "Какой персонаж имеет меньше всего созвездий?         ",
          "Какой персонаж был получен раньше всех?              ",
          "Список лучников c доходом выше 500 тыс.              ",
          "Алфавитный список                                    ",
          "Одинаковое количество созвездий, но разное оружие    ",
          "Диаграмма                                            ",
          "Выход                                                "
	};
	struct z *clients;
	setlocale(LC_CTYPE,"Russian");
	setlocale(LC_CTYPE,".1251");
	SetConsoleCP (1251);
	SetConsoleOutputCP (1251);
  
	
	Console::CursorVisible::set(false);
	Console::BufferHeight=Console::WindowHeight;
	Console::BufferWidth=Console::WindowWidth;
	if((in=fopen("gns.txt","r"))==NULL)
		{
		printf("\файл не открыт!");
		getch(); exit(1);
		}

	fscanf(in, "%d", & NC);
	clients = (struct z*)malloc(NC*sizeof(struct z));

	for (i = 0; i < NC; i++)
	fscanf(in, "%s%s%s%s%ld%ld", clients[i].name,clients[i].element, clients[i].weapon, clients[i].year, &clients[i].constellation, &clients[i].money);


	for (i = 0; i < NC; i++)
	printf("\n%-15s %-10s %-15s %-11s %3ld %11ld", clients[i].name, clients[i].element, clients[i].weapon, clients[i].year, clients[i].constellation, clients[i].money);
	getch();


	while(1)
    {
	  Console::ForegroundColor=ConsoleColor::DarkRed;
      Console::BackgroundColor=ConsoleColor::Blue;
      Console::Clear();
      Console::ForegroundColor=ConsoleColor::DarkRed;
      Console::BackgroundColor=ConsoleColor::Blue;
      Console::CursorLeft=10;
      Console::CursorTop=4;
      printf(BlankLine);

      for(i=0;i<7;i++)
          {
          Console::CursorLeft=10;
          Console::CursorTop=i+5;
          printf(" %s ",dan[i]);
          }
      Console::CursorLeft=10;
      Console::CursorTop=12;
      printf(BlankLine);
      
      n = menu(7);
      switch(n)
          {
            case 1: mini(NC,clients); break;
			case 2: first(NC,clients);break;
            case 3: listing(NC,clients);break;
            case 4: alfspis(NC,clients);break;
            case 5: vopros(NC,clients);break;
            case 6: diagram(NC,clients);break;
            case 7: exit(0);
      
          }
      }  

  getch();
    return 0;
}

//выбор из меню
int menu(int n)

	char dan[7][55]={
          "Какой персонаж имеет меньше всего созвездий?         ",
          "Какой персонаж был получен раньше всех?              ",
          "Список лучников c доходом выше 500 тыс.              ",
          "Алфавитный список                                    ",
          "Одинаковое количество созвездий, но разное оружие    ",
          "Диаграмма                                            ",
          "Выход                                                "
	};
	int y1=0,y2=n-1;
	char c=1;
	while (c!=ESC)
	{
		switch(c)
		{
			case DOWN: y2=y1; y1++; break;
			case UP: y2=y1; y1--; break;
			case ENTER: return y1+1;
		}
		if(y1>n-1){y2=n-1;y1=0;}
		if(y1<0) {y2=0;y1=n-1;}
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::DarkMagenta;
		Console::CursorLeft=11;
		Console::CursorTop=y1+5;
		printf("%s",dan[y1]);
		Console::ForegroundColor=ConsoleColor::DarkRed;
		Console::BackgroundColor=ConsoleColor::Blue;
		Console::CursorLeft=11;
		Console::CursorTop=y2+5;
		printf("%s",dan[y2]);
		c=getch();
	} 

exit(0);
}

// какой персонаж имеет меньше всего созвездий
void mini(struct z* clients)
{
int i = 0; struct z best;
int NC;
strcpy(best.name, clients[i].name);
best.constellation = clients[i].constellation;
for (i = 1; i < NC; i++)
  if (clients[i].constellation < best.constellation)
    {
    strcpy(best.name, clients[i].name);
    best.constellation = clients[i].constellation;
    }

Console::ForegroundColor=ConsoleColor::DarkRed;
Console::BackgroundColor=ConsoleColor::Blue;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Имеет созвездий:%d",best.constellation);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Персонаж:%s",best.name);
getch();
}

void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
	"января","февраля","марта","апреля","мая","июня","июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}
// Какой персонаж был получен раньше всех?
void first(struct z* client)
{
int i;
char s[17];
struct z* best=client;
for(i=1;i<NC;i++)
if (strcmp(client[i].year,best->year)<0)
 best=&client[i];
text_data(s,best->year);
Console::ForegroundColor=ConsoleColor::DarkRed;
Console::BackgroundColor=ConsoleColor::Blue;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Имеет оружие: %s", best->weapon);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Персонаж: %s",best->name);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("Был получен: %s ",s);
getch();
}

//Составление алфавитного списка
void alfspis(struct z* client)
{
int i;
int NC;
struct sp* nt,*z=0;
Console::ForegroundColor=ConsoleColor::DarkRed;
Console::BackgroundColor=ConsoleColor::Blue;
Console::Clear();
if(!spisok)
	for(i=0;i<NC;i++)
		vstavka(client,client[i].name);
Console::Clear();
printf("\n Алфавитный список персонажей");
printf("\n ===============================\n");
for(nt=spisok; nt!=0; nt=nt->sled)
	printf("\n %-20s %ld",nt->fio,nt->money);
for(nt=spisok,z=0; nt!=0; z=nt,nt=nt->sled);
for(nt=z,i=0; nt!=0; nt=nt->pred,i++){
	Console::CursorLeft=35;
	Console::CursorTop=4+i;
	printf(" %-20s %ld\n", nt->fio,nt->money);}
getch();
}
//Вставка персонажей в алфавитный список
void vstavka(struct z* client,char* fio)
{
int i;
int NC;
struct sp *nov,*nt,*z=0;
for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled);
if(nt && strcmp(nt->fio,fio)==0) return;
nov=(struct sp *) malloc(sizeof(struct sp));
strcpy(nov->fio,fio);
nov->sled=nt;
nov->pred=z;
nov->money=0;
for(i=0;i<NC;i++)
	if(strcmp(client[i].name,fio)==0)
		nov->money+=client[i].money;
if(!z) spisok=nov;
if (z)
	z->sled=nov;
if(nt)
	nt->pred=nov;
return;
}
//Вывод алфавитного списка лучников
void listing(struct z* client)
{
int i;
struct z* nt;
int NC;
Console::ForegroundColor=ConsoleColor::DarkRed;
Console::BackgroundColor=ConsoleColor::Blue;
Console::Clear();
printf("\n\r Список \"лучников\"  с доходом выше 500 тыс.");
printf("\n\r=====================================================\r");
for(i=0,nt=client;i<NC;nt++,i++)
	if (nt->money>500000 && strcmp(nt->weapon,"лук")==0)
		printf("\n\r %-20s %ld",nt->name,nt->money);
getch();
}
//одно оружие, но разные созвездия
void vopros(struct z* clients)
{
int i,x,n=0;
int NC;
for(i=0;i<NC;i++){
for(x=1;x<NC;x++){
if ((clients[i].constellation==clients[x].constellation) && (strcmp(clients[i].weapon,clients[x].weapon)!=0))
{
Console::BackgroundColor=ConsoleColor::Blue;
Console::ForegroundColor=ConsoleColor::DarkRed;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("%s и %s Общее количество созвездий: %d ",clients[i].name,clients[x].name,clients[x].constellation);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("но с разными оружиями: %s и %s",clients[i].weapon,clients[x].weapon);
n=1;
break;
}
}
if(n==1)
break;
}
if(n!=1){
Console::BackgroundColor=ConsoleColor::Black;
Console::ForegroundColor=ConsoleColor::Green;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Совпадений нет!");
}

getch();
}

//Диаграмма. Процентное соотношение всех доходов.
void diagram(struct z *client)
{
struct sp *nt; 
int len,i,NColor; 
int NC;
int sum = 0 ; 
char str1[20];

char str2[20];
System::ConsoleColor Color; 

Console::ForegroundColor=ConsoleColor::DarkRed; 
Console::BackgroundColor=ConsoleColor::White; 
Console::Clear();
for(i=0;i<NC;i++) sum = sum+client[i].money ;
if(!spisok)
for(i=0;i<NC;i++)
vstavka(client,client[i].name); 

Color=ConsoleColor::Black; NColor=0;
for(nt=spisok,i=0; nt!=0; nt=nt->sled,i++)
{
sprintf(str1,"%s",nt->fio); 
sprintf(str2,"%3.1f%%",(nt->money*100./sum)); 
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor= ConsoleColor::White;
Console::CursorLeft=5; Console::CursorTop=i+1; 
printf("%s",str1);  
Console::CursorLeft=20;
printf("%s",str2);  
Console::BackgroundColor=++Color; NColor++;
Console::CursorLeft=30;
for(len=0; len<nt->money*100/sum; len++) printf(" ");
if(NColor==14) 
{ Color=ConsoleColor::Black; NColor=0; }
}
getch();
return ;
}
