#include <iostream.h>
#include <windows.h>	
#include <stdlib.h>
#include <stdio.h>
#include <fstream.h>
#include <conio.h>

 void newFile();
 void viewFile();
 void viewDBfilter();
 void viewDB();
 void curPos(int, int);
 void search();
 int showdbitem(int,int,bool,bool,bool,bool,bool,bool,bool,char);
 void setcolor(WORD);
 void addline();
 void editline();	
 int res(int, int); 
 char* rus(const char*); 

  struct db{
 char name[256];
 char firstname[256];
 char lastname[256];
 int number;
 double clock;
 double tarif;
 double pribl;
 };

 db dbtemp[450];

  int action;	
  char temp[260] = {""};
  char dbname[260] = {""};
  char pathfile[5] = "db\\";
  char bufRus[600];


void main()
{
bool haos = true;
SetConsoleTitle(rus("BZdb - База данных сотрудников v1.1"));

 

while(haos)
{

action = 0;
setcolor(0xA+(0x8<<4));

 printf(rus("\t\t\t\tГлавное меню\t\t\t\t\t\n"));
setcolor(0x7+(0x0<<4));

 printf(rus("1) Просмотр базы \n2) Создать базу \n\n0) Выход\n"));
 printf(rus("\n Выберите тип действия: >"));
  scanf("%d",&action); 

	 switch(action)
	{
	 case 2: {newFile(); break;}
	 case 1: {viewFile(); break;}
	 case 0: {system("cls"); return; break;}
	 default : {MessageBox(NULL, "Неизвестная команда!", "Console Error", MB_OK|MB_ICONWARNING);break;}
	}
system("cls");
}

}



void newFile()
{

system("cls");
action = 0;

 setcolor(0xA+(0x8<<4));
 printf(rus("\t\t\t\tСоздание новой базы\t\t\t\t"));
 setcolor(0x7+(0x0<<4));
 printf(rus("\n1) Ввести имя \n\n0) Вернуться\n"));
 printf(rus("\n Выберите тип действия: >")); 
 
 scanf("%d",&action);

 switch(action)
 {
	case 1:{
			strcpy(pathfile,"db\\");
			printf(rus("Введите название новой базы: \n>"));

			scanf("%s",dbname); 
	
			strcat(pathfile,dbname);
			strcat(pathfile,".dbz");

			ofstream file(pathfile, ios::out);

			file.close();
			
			return;
			break;
		   }

	case 0: {return; break;}
	default : {MessageBox(NULL, "Неизвестная команда!", "Console Error", MB_OK|MB_ICONWARNING); getch();break;}
 }



}

void viewFile()
{
	bool haos3 = true;
	char dbname1[666][256];
	int i=1,max;
	char notepad[256];

system("cls");
setcolor(0xA+(0x8<<4));
 printf(rus("\t\t\t\tДоступные базы\t\t\t\t\t\n"));
setcolor(0x7+(0x0<<4));

printf(rus("Выберите базу из списка:\n"));

WIN32_FIND_DATA winFileData;
HANDLE hFile;
	char szPath[256];
	if(GetCurrentDirectory(sizeof(szPath),szPath))
	{
	lstrcat(szPath,"\\db\\*.dbz");
	hFile = FindFirstFile(szPath,&winFileData);
	if (hFile!=INVALID_HANDLE_VALUE)
	{
	do
		{
		strcpy(dbname1[i],winFileData.cFileName);
		
		memset(temp, 0, 260);
		strcpy(dbname,dbname1[i]);
		
		strncpy (temp,dbname,strlen(dbname)-4); 
		memset(dbname, 0, 256);


		strcpy(pathfile,"db\\");
		strcat(pathfile,dbname1[i]);

		ifstream dbline(pathfile);
		int nn=0; dbline.getline(dbname,256,' ');
		while(!dbline.eof())
			{dbline.getline(dbname,256,'\n'); nn++;};
		dbline.close();
		
		if(nn==0) nn=1;
		printf(rus("%d) %s (всего работников - %d)\n"),i,temp,nn-1); 
		i++; max=i;
		}
		while (FindNextFile(hFile,&winFileData)!=0);
	FindClose(hFile);
	}

printf(rus("\n Выберите базу: >"));  scanf("%d",&i);
if(i>=max || i==0) return;

char title[256]={""};
strncpy(title,dbname1[i],strlen(dbname1[i])-4);
strcpy(dbname,dbname1[i]);
strcpy(pathfile,"db\\");
strcat(pathfile,dbname);

system("cls");



while(haos3)
{
system("cls");
	setcolor(0xA+(0x8<<4));

	printf(rus("\t\t\t\t База: %s"),title);

	CONSOLE_SCREEN_BUFFER_INFO bi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);

	while(bi.dwCursorPosition.X<79){
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		printf(" ");
		}


	 setcolor(0x7+(0x0<<4));

 curPos(0,1);
 printf(rus("\n1) Просмотр работников\n"));
 printf(rus("2) Просмотр по фильтру \n3) Открыть в системе\n"));
 printf(rus("4) Редактирование базы \n5) Добавить новую запись \n6) Поиск \n7) Удалить базу\n\n0) Вернуться\n"));
 printf(rus("\n Выберите тип действия: >"));
 scanf("%d",&action);

 switch(action)
 {
	case 1: {viewDB(); break;}
	case 2: {viewDBfilter(); break;}
	case 3: {strcpy(notepad,"notepad.exe ");
		strcat(notepad,pathfile);
		WinExec(notepad,SW_SHOW);; break;}
	case 4: {editline(); break;}
	case 5: {addline(); break;}
	case 6: {search(); break;}
	case 7: {

		if(MessageBox(NULL, "Вы точно хотите это сделать?",
			"Удаление базы", MB_YESNO|MB_ICONQUESTION)
			== IDYES)
			remove(pathfile);
		return;
		break;}
	case 0: {haos3=false; break;}
	default : {MessageBox(NULL, "Неизвестная команда!", "Console Error", MB_OK|MB_ICONWARNING); getch();break;}

 }
}
}

}



void viewDBfilter()
{
 db dbfilter;

 char pribl,tarif,clock,number;

 strcpy(dbfilter.name," ");
 strcpy(dbfilter.firstname," ");
 strcpy(dbfilter.lastname," ");
 strcpy(&number," ");
 strcpy(&clock," ");
 strcpy(&tarif," ");
 strcpy(&pribl," ");


bool haos4 = true;
bool temp1[9]={false,false,false,false,false,false,false,false,false};
int list2=1,i2;

 while(haos4)
 {
 
system("cls");

i2=showdbitem(9,list2,temp1[1],temp1[2],temp1[3],temp1[4],temp1[5],temp1[6],temp1[7],'.');


printf(rus("\n\n1)[%s] Имя"),dbfilter.name);
printf(rus("\n2)[%s] Фамилия"),dbfilter.firstname);
printf(rus("\n3)[%s] Отчество"),dbfilter.lastname);
printf(rus("\n4)[%s] Табельный номер"),&number);
printf(rus("\n5)[%s] Отработанные часы"),&clock);
printf(rus("\n6)[%s] Тариф"),&tarif);
printf(rus("\n7)[%s] Прибль с учетом налога"),&pribl);

printf(rus("\n\n8) Листать назад"));
printf(rus("\n9) Литсать вперед"));
printf(rus("\n0) Вернуться\n>"));

scanf("%d",&action);

 switch(action)
 {
 case 1:	{ 
	 if(strcmp(dbfilter.name," ")==0){temp1[1]=true;strcpy(dbfilter.name,"*");}
	 else {temp1[1]=false;strcpy(dbfilter.name," "); }
	 break;}
 case 2:	 {
	 if(strcmp(dbfilter.firstname," ")==0){temp1[2]=true;strcpy(dbfilter.firstname,"*");}
	 else {temp1[2]=false;strcpy(dbfilter.firstname," ");}
	 break;}
 case 3:	 {
	 if(strcmp(dbfilter.lastname," ")==0){temp1[3]=true;strcpy(dbfilter.lastname,"*");}
	 else {temp1[3]=false;strcpy(dbfilter.lastname," ");}
	 break;}
 case 4:	 {
	 if(strcmp(&number," ")==0){temp1[4]=true;strcpy(&number,"*");}
	 else {temp1[4]=false;strcpy(&number," ");}
	 break;}
 case 5:	{
	 if(strcmp(&clock," ")==0){temp1[5]=true;strcpy(&clock,"*");}
	 else {temp1[5]=false;strcpy(&clock," ");}
	 break;}
 case 6:	{
	 if(strcmp(&tarif," ")==0){temp1[6]=true;strcpy(&tarif,"*");}
	 else {temp1[6]=false;strcpy(&tarif," ");}
	 break;}
 case 7:	{
	 if(strcmp(&pribl," ")==0){temp1[7]=true;strcpy(&pribl,"*");}
	 else {temp1[7]=false;strcpy(&pribl," ");}
	 break;}
	case 8: {if(list2!=1)list2-=9; break;}
	case 9: {if(list2+10<=i2)list2+=9; break;} 
 case 0:	{ 
	  haos4=false; 
	  break; }
 default : {MessageBox(NULL, "Неизвестная команда!", "Console Error", MB_OK|MB_ICONWARNING); getch();}
 }


 }
 
}

void viewDB()
{

	bool haos5 = true;
	int i1=0,list=1;

	
while(haos5)
{

 system("cls");

 i1=showdbitem(9,list,true,true,true,true,true,true,false,'.');


printf(rus("\n\n8) Листать назад"));
printf(rus("\n9) Литсать вперед"));
printf(rus("\n0) Вернуться\n\n>"));

scanf("%d",&action);

 switch(action)
 {
	case 8: {if(list!=1)list-=9; break;}
	case 9: {if(list+10<=i1)list+=9; break;} 
	case 0:	{haos5=false; break;}
	default : {MessageBox(NULL, "Неизвестная команда!", "Console Error", MB_OK|MB_ICONWARNING); break;}
 }

}


}





void curPos(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}







void search()
{

bool haos7 = true;
int list3=1,i3=0,x,wsi=0;
char ws[260],ek='\0';
int n2=1,m2=1,len[8]={1,3,7,8,5,7,5,9};
db dbitem[450];
int k1=0,k=0;

while(haos7)
{
system("cls");

setcolor(0xA+(0x8<<4));
 printf(rus("\t\t\t\tПоиск по базе\t\t\t\t\t\n"));
setcolor(0x7+(0x0<<4));

	i3=0; n2=1;

	ifstream dbline(pathfile);

 	while(!dbline.eof() && n2<450)
		{
		memset(dbitem[n2].name, 0, 256);
		memset(dbitem[n2].firstname, 0, 256);
		memset(dbitem[n2].lastname, 0, 256);

	    dbline.getline(dbitem[n2].name,256,' ');
		if(strlen(dbitem[n2].name)>0){
		dbline.getline(dbitem[n2].firstname,256,' ');
		dbline.getline(dbitem[n2].lastname,256,' ');
		dbline >> dbitem[n2].number; 
		dbline >> dbitem[n2].clock; 
		dbline >> dbitem[n2].tarif;	dbline.getline(temp,256,'\n');


		switch(x)
		{
		case 1:{if(strstr(dbitem[n2].name,ws)!=0){n2++; i3=n2;} break;}
		case 2:{if(strstr(dbitem[n2].firstname,ws)!=0){n2++; i3=n2;} break;}
		case 3:{if(strstr(dbitem[n2].lastname,ws)!=0){n2++; i3=n2;} break;}
		case 4:{
			if(ek=='<' && dbitem[n2].number<wsi){n2++; i3=n2;}
			if(ek=='>' && dbitem[n2].number>wsi){n2++; i3=n2;}
			if(ek=='=' && dbitem[n2].number==wsi){n2++; i3=n2;}
			break;}
		case 5:{
			 if(ek=='<' && dbitem[n2].clock<wsi){n2++; i3=n2;}
			 if(ek=='>' && dbitem[n2].clock>wsi){n2++; i3=n2;}
			 if(ek=='=' && dbitem[n2].clock==wsi){n2++; i3=n2;}
			break;}
		case 6:{
			 if(ek=='<' && dbitem[n2].tarif<wsi){n2++; i3=n2;}
			 if(ek=='>' && dbitem[n2].tarif>wsi){n2++; i3=n2;}
			 if(ek=='=' && dbitem[n2].tarif==wsi){n2++; i3=n2;}
			break; }
		}
		}
	}

	dbline.close();


if(i3>0)
{

	for(m2=list3;m2<n2+9 && m2<i3; m2++) 
	{
			if(len[1]<(int)strlen(dbitem[m2].name)) 
			 len[1]=strlen(dbitem[m2].name);
			if(len[2]<(int)strlen(dbitem[m2].firstname)) 
			 len[2]=strlen(dbitem[m2].firstname);
			if(len[3]<(int)strlen(dbitem[m2].lastname)) 
			 len[3]=strlen(dbitem[m2].lastname);


				k1=res(dbitem[m2].number,1);

			if(len[4]<k1) 
			 len[4]=k1; k1=1;

				k1=res((int)dbitem[m2].clock,1);

			if(len[5]<k1) 
			 len[5]=k1; k1=1;

	
				k1=res((int)dbitem[m2].tarif,1);

			if(len[6]<k1) 
			 len[6]=k1; k1=1;

	}


 curPos(0,1);
 setcolor(0xA+(0x8<<4));
  printf(rus("# "));
   for(m2=list3; m2>0;m2=m2/10)
	   printf(" "); 
 
  printf(rus("Имя "));
  for(m2=0; m2<len[1]-3; m2++)printf(" ");
  printf(rus("Фамилия "));	
  for(m2=0; m2<len[2]-7; m2++)printf(" ");
  printf(rus("Отчество "));  
  for(m2=0; m2<len[3]-8; m2++)printf(" ");
  printf(rus("Номер "));	
  for(m2=0; m2<len[4]-4; m2++)printf(" ");
  printf(rus("От.часы "));	
  for(m2=0; m2<len[5]-6; m2++)printf(" ");
  printf(rus("Тариф "));	


 CONSOLE_SCREEN_BUFFER_INFO bi;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
 
  	while(bi.dwCursorPosition.X<79)
		{
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		printf(" ");
		}

 setcolor(0x7+(0x0<<4));

	for(n2=list3; n2<list3+9 && n2<i3; n2++)
	{
		int x=1;
		curPos(0,n2-list3+2);
		printf("%d. ", n2); 
		printf(rus("%s"),dbitem[n2].name);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		x=1+bi.dwCursorPosition.X+len[1]-strlen(dbitem[n2].name);
		curPos(x, n2-list3+2);
		printf(rus("%s"),dbitem[n2].firstname);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		x=1+bi.dwCursorPosition.X+len[2]-strlen(dbitem[n2].firstname);
		curPos(x, n2-list3+2);
		printf(rus("%s"),dbitem[n2].lastname);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		x=1+bi.dwCursorPosition.X+len[3]-strlen(dbitem[n2].lastname);
		curPos(x, n2-list3+2);
		printf("%d",dbitem[n2].number);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
				k1=res(dbitem[n2].number,-1);
		x=1+bi.dwCursorPosition.X+len[4]-k1; k1=-1;
		curPos(x, n2-list3+2);
		printf("%4.2f",dbitem[n2].clock);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
				k1=res((int)dbitem[n2].clock,-1);
		x=-2+bi.dwCursorPosition.X+len[5]-k1; k1=-1;
		curPos(x, n2-list3+2);
		printf("%4.2f",dbitem[n2].tarif);
	}	
}
	else
		printf(rus("\nНичего не найдено"));


printf(rus("\n\n1) По имени"));
printf(rus("\n2) По фамилии"));
printf(rus("\n3) По отчеству"));
printf(rus("\n4) По табельному номеру"));
printf(rus("\n5) По отработанным часам"));
printf(rus("\n6) По тарифу"));
if(i3==0) i3=1;
printf(rus("\n\n\tПоказано<%d/%d>"),n2-1,i3-1);
printf(rus("\n8) Листать назад"));
printf(rus("\n9) Литсать вперед")); 
printf(rus("\n0) Вернуться\n>"));

scanf("%d",&action);

 switch(action)
 {
 case 1:{printf(rus("\nВведите слово для поиска:"));x=1; scanf("%s",ws); break;}	
 case 2:{printf(rus("\nВведите слово для поиска:"));x=2; scanf("%s",ws); break;}
 case 3:{printf(rus("\nВведите слово для поиска:"));x=3; scanf("%s",ws); break;}
 case 4:{
	 printf(rus("\nВведите условие сравнения (<,>,=):")); scanf("%s",&ek);
	 printf(rus("Введите число:"));x=4; scanf("%d",&wsi); 
	 break;}
 case 5:{
	 printf(rus("\nВведите условие сравнения (<,>,=):")); scanf("%s",&ek);
	 printf(rus("Введите число:"));x=5; scanf("%d",&wsi); 
	 break;}
 case 6:{
	 printf(rus("\nВведите условие сравнения (<,>,=):")); scanf("%s",&ek);
	 printf(rus("Введите число:"));x=6; scanf("%d",&wsi); 
	 break;}
 
 case 8: {if(list3!=1)list3-=9; break;}
 case 9: {if(list3+10<=i3)list3+=9; break;} 
 case 0:{	
	  haos7=false; return; 
	  break; }
 default : {MessageBox(NULL, "Неизвестная команда!", "Console Error", MB_OK|MB_ICONWARNING); getch();}
 }

}


}













void setcolor(WORD color)
{
 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(hConsole, color);
}




int showdbitem(int max,int n1,bool name,bool fn, bool ln, bool num, bool cl, bool tf, bool pl, char znak)
{


	int n=1,m=1,i=1,len[8]={1,3,7,8,5,7,5,9};
	db dbitem[450];
	int k1=1;
	ifstream dbline(pathfile); 
	
	
	while(!dbline.eof() && n<450){
		memset(dbitem[n].name, 0, 256);
		memset(dbitem[n].firstname, 0, 256);
		memset(dbitem[n].lastname, 0, 256);

	    dbline.getline(dbitem[n].name,256,' ');
		if(strlen(dbitem[n].name)>0){
		dbline.getline(dbitem[n].firstname,256,' ');
		dbline.getline(dbitem[n].lastname,256,' ');
		dbline >> dbitem[n].number; 
		dbline >> dbitem[n].clock; 
		dbline >> dbitem[n].tarif; dbline.getline(temp,256,'\n');
		if(dbitem[n].clock>144)
		 dbitem[n].pribl=dbitem[n].tarif*dbitem[n].clock*2*87/100;
		else
		 dbitem[n].pribl=dbitem[n].tarif*dbitem[n].clock*87/100;
		
		strcpy(dbtemp[n].name,dbitem[n].name);
		strcpy(dbtemp[n].firstname,dbitem[n].firstname);
		strcpy(dbtemp[n].lastname,dbitem[n].lastname);
		dbtemp[n].number=dbitem[n].number;
		dbtemp[n].clock=dbitem[n].clock;
		dbtemp[n].tarif=dbitem[n].tarif;

		n++; i=n;}
	}


	for(m=n1;m<n1+max && m<i; m++) {
			if(len[1]<(int)strlen(dbitem[m].name)) 
			 len[1]=strlen(dbitem[m].name);
			if(len[2]<(int)strlen(dbitem[m].firstname)) 
			 len[2]=strlen(dbitem[m].firstname);
			if(len[3]<(int)strlen(dbitem[m].lastname)) 
			 len[3]=strlen(dbitem[m].lastname);
	


			 k1=res(dbitem[m].number,1);

			if(len[4]<k1) 
			 len[4]=k1;

			k1=res((int)dbitem[m].clock,1); 

			if(len[5]<k1) 
				len[5]=k1;

			k1=((int)dbitem[m].tarif,1);

			if(len[6]<k1) 
			 len[6]=k1; 
	}


 curPos(0,0);
 setcolor(0xA+(0x8<<4));
  if(name || fn || ln || num || cl || tf || pl){

  if(znak!=')'){
	  printf(rus("# ")); 
	   for(m=n1+max-1; m>0;m=m/10)
		   printf(" "); }
  else {printf(rus("   # ")); 
		   for(m=n1+max-1; m>0;m=m/10)
		   printf(" ");}}
 
	if(name){
  printf(rus("Имя "));
  for(m=0; m<len[1]-3; m++)printf(" ");}
	if(fn){
  printf(rus("Фамилия "));	
  for(m=0; m<len[2]-7; m++)printf(" ");}
	if(ln){
  printf(rus("Отчество "));  
  for(m=0; m<len[3]-8; m++)printf(" ");}
	if(num){
  printf(rus("Номер "));	
  for(m=0; m<len[4]-4; m++)printf(" ");}
	if(cl){
  printf(rus("От.часы "));	
  for(m=0; m<len[5]-6; m++)printf(" ");}
	if(tf){
  printf(rus("Тариф "));	
  for(m=0; m<len[6]-4; m++)printf(" ");}
	if(pl)
  printf(rus("Зар.Плата ($)")); 

 CONSOLE_SCREEN_BUFFER_INFO bi;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
  	while(bi.dwCursorPosition.X<79 && bi.dwCursorPosition.Y==0){
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		printf(" ");
		}

 setcolor(0x7+(0x0<<4));

	for(n=n1; n<n1+max && n<i; n++){
		int x;
		if(name || fn || ln || num || cl || tf || pl){
		x=1; k1=-1;
		curPos(0,n-n1+1); 

		if(znak!=')'){
			printf("%d%s ", n,&znak);}
		else
			printf("%d%s %d. ", n-n1+1,&znak,n);
			if(res(n,1)<res(n1+max-1,1))printf(" ");
		}

		if(name){
		printf(rus("%s"),dbitem[n].name);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		x=1+bi.dwCursorPosition.X+len[1]-strlen(dbitem[n].name);
		curPos(x, n-n1+1);}
		if(fn){
		printf(rus("%s"),dbitem[n].firstname);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		x=1+bi.dwCursorPosition.X+len[2]-strlen(dbitem[n].firstname);
		curPos(x, n-n1+1);}
		if(ln){
		printf(rus("%s"),dbitem[n].lastname);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
		x=1+bi.dwCursorPosition.X+len[3]-strlen(dbitem[n].lastname);
		curPos(x, n-n1+1);}
		if(num){
		printf("%d",dbitem[n].number);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);	
				k1=res(dbitem[n].number,-1); 
		x=1+bi.dwCursorPosition.X+len[4]-k1;
		curPos(x, n-n1+1);}
		if(cl){
		printf("%4.2f",dbitem[n].clock);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
				k1=res((int)dbitem[n].clock,-1);
		x=-2+bi.dwCursorPosition.X+len[5]-k1;
		curPos(x, n-n1+1);}
		if(tf){
		printf("%4.2f",dbitem[n].tarif);
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bi);
				k1=res((int)dbitem[n].tarif,-1);
		x=-1+bi.dwCursorPosition.X+len[6]-k1;
		curPos(x, n-n1+1);}
		if(pl)
		printf("%4.2f",dbitem[n].pribl);
	}
	if(name || fn || ln || num || cl || tf || pl)
		printf(rus("\n\nПоказано <%d> из <%d>"),n-1,i-1);

	dbline.close();
	return i;
}






void addline()
{

system("cls");

db dbitem;

setcolor(0xA+(0x8<<4));
 printf(rus("\t\t\t\tДобавление новой записи\t\t\t\t\n"));
setcolor(0x7+(0x0<<4));


	printf(rus("Введите имя:"));
		scanf("%s",dbitem.name);
	printf(rus("Введите фамилию:"));
		scanf("%s",dbitem.firstname);
	printf(rus("Введите отчество:"));
		scanf("%s",dbitem.lastname);
	printf(rus("Введите табельный номер:"));
		scanf("%d",&dbitem.number);
	printf(rus("Введите количество отработанных часов:"));
		scanf("%lf",&dbitem.clock);
	printf(rus("Введите тариф:"));
		scanf("%lf",&dbitem.tarif);

    ofstream lineRecords(pathfile, ios::app);

    lineRecords <<""<< dbitem.name << " "
         << dbitem.firstname << " "
         << dbitem.lastname << " "
         << dbitem.number << " "
		 << dbitem.clock << " "
		 << dbitem.tarif << "\n";

	lineRecords.close();
}



void editline()
{

bool haos6=true,edit=false;
int ii; int n3,list4=1;


while(haos6)
{
action=0,n3=0,edit=false;

system("cls");

setcolor(0xA+(0x8<<4));
 printf(rus("\t\t\t\tРедактирование записи\t\t\t\n"));
setcolor(0x7+(0x0<<4));


ii=showdbitem(7,list4,true,true,true,true,true,true,false,')');


printf(rus("\n\n8) Листать назад"));
printf(rus("\n9) Литсать вперед"));
printf(rus("\n0) Вернуться\n\n>"));

scanf("%d",&action);

 switch(action)
 {
	case 1:
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: {edit=true; n3=list4+action-1; break;}

	case 8: {if(list4>1)list4-=7; break;}
	case 9: {if(list4+8<=ii)list4+=7; break;} 
	case 0:	{haos6=false; return; break;}
	default : {MessageBox(NULL, "Неизвестная команда!", "Console Error", MB_OK|MB_ICONWARNING); break;}
 }


	if(edit)
	{
	printf(rus("\n\nСтарое значение - %s \n"),dbtemp[n3].name);
	printf(rus("Введите новое имя:"));
		scanf("%s",dbtemp[n3].name); 
	printf(rus("Старое значение - %s \n"),dbtemp[n3].firstname);
	printf(rus("Введите новую фамилию:"));
		scanf("%s",dbtemp[n3].firstname);
	printf(rus("Старое значение - %s \n"),dbtemp[n3].lastname);
	printf(rus("Введите новое отчество:"));
		scanf("%s",dbtemp[n3].lastname);
	printf(rus("Старое значение - %d \n"),dbtemp[n3].number);
	printf(rus("Введите новый табельный номер:"));
		scanf("%d",&dbtemp[n3].number); 
	printf(rus("Старое значение - %4.2f \n"),dbtemp[n3].clock);
	printf(rus("Введите новое количество отработанных часов:"));
		scanf("%lf",&dbtemp[n3].clock);
	printf(rus("Старое значение - %4.2f \n"),dbtemp[n3].tarif);
	printf(rus("Введите новый тариф:"));
		scanf("%lf",&dbtemp[n3].tarif);

    ofstream lineWrite(pathfile, ios::out);
	

	for(int ii1=1;ii1<ii;ii1++)
	{
    lineWrite
		 << dbtemp[ii1].name << " "
         << dbtemp[ii1].firstname << " "
         << dbtemp[ii1].lastname << " "
         << dbtemp[ii1].number << " "
		 << dbtemp[ii1].clock << " "
		 << dbtemp[ii1].tarif<< "\n";
	}
	lineWrite.close();
	}
}
}


int res(int k,int k22)
{
	int k12=k22;
		for(int kk=k; kk>0;kk=kk/10)
	k12++;

return k12;
}


char* rus(const char* text) 
{
      CharToOem(text, bufRus);
      return bufRus;
}