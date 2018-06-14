#include "stdio.h"
#include "stdlib.h"
#include "iostream.h"


	struct l{
	short int busy;
	short int et;
	short int direct;
	short int num;
	}; 


void funk(l *Plift, int *Pn, int *Px)
{
int min=0,smin=*Pn, number=0;
bool free=false;
	
	for(int i=0;i<=2;i++)
	{
	cout<<i+1<<"-Lift na "<<Plift[i].et+1<<" etage, ";

			switch(Plift[i].busy)
		{
		case 0: cout<<"svoboden."<<endl;
			if(free==false){free = true; smin=*Pn;}
			if(abs(*Px-Plift[i].et)<smin){ 	
				smin = abs(*Px-Plift[i].et); number=i+1;}
			break;
		case 1: cout<<"zanjat, ";
			if(Plift[i].direct==0){ cout<<"edit v nis."<<endl;
				if(*Px<=Plift[i].et && Plift[i].et>min &&
					Plift[i].et<smin && free == false)
				{
					smin = Plift[i].et; 
					number=i+1;
				}
			}
			if(Plift[i].direct==1){ cout<<"edit v verh."<<endl;
				if(*Px>=Plift[i].et && Plift[i].et<smin &&
					Plift[i].et>min && free == false)
				{
					min = Plift[i].et; 
					number=i+1;
				}
			}		
			break;
		}
	}
	if(number!=0)
		cout<<endl<<"Chelovek visovet "<<number<<"-lift."<<endl;
	else
		cout<<endl<<"Nety podhodjahego lifta"<<endl;

}



int main()
{
	 
	int N=0,x=0;
	int again=1;
	l lift[3];
	
	while(again==1)
	{
	cout<<"Enter number of etag:"; 
	cin>>N;
	x = (rand()%N); 
	cout<<"Chelovek na "<<x+1<<" etage"<<endl;

	for(int i=0;i<=2;i++)
	{
		lift[i].busy = rand()%2;
			if(lift[i].busy == 1) 
				lift[i].direct = rand()%2;
		lift[i].et = rand()%N;
		lift[i].num = i;
	}

	funk(lift,&N,&x);

	cout<<endl<<"Povtorit? <1/0>:"; cin>>again; cout<<endl;
	}


	return 0;
}
