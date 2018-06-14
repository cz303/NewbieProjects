
#include "stdio.h"
#include "iostream.h"
#include "stdlib.h"
#include <conio.h>


void view(int p11, int **mass, char msg [])
{
int y,u;
cout<<endl;
cout<<msg<<endl; 
	for(y = 0; y<p11; y++)
	{
		for(u = 0; u<p11; u++)
		{
		 if(mass[y][u]<0) {
			if(mass[y][u] < -9)
			 cout<<""<<mass[y][u]<<" ";
			else
			 cout<<" "<<mass[y][u]<<" ";
		  }
		 else
			 if(mass[y][u] > 9)
			cout<<" "<<mass[y][u]<<" ";
			 else
			cout<<"  "<<mass[y][u]<<" ";
		  }
		cout<<endl;
	}
}

void sortirovka(int p12, int **mass2)
{
	int inv,h,k,t; 
	for(h=0; h<p12/2; h++)
	{
		inv = mass2[h][h];
		mass2[h][h]  = mass2[p12-1-h][p12-1-h];
		mass2[p12-1-h][p12-1-h] = inv; 
	}

view(p12,mass2,"Inverse diagonale:");

for(h=0; h<p12; h++)
	{
	  for(k=h+1; k<p12; k++)
		{
		 if(mass2[h][0] < mass2[k][0]){
			for(t=0; t<p12; t++)
				{
					inv = mass2[h][t];
					mass2[h][t] = mass2[k][t];
					mass2[k][t] = inv;			
				}
		 }		 
		}
	}
view(p12,mass2,"Otsortirovannij:");
}

int main()
{

	int i,j,n;

	cout<<"Vvedite razmer massiva: "; cin>>n;


	int **x = new int *[n];
	for(int k=0; k<n; k++){
		 x[k] = new int [n];
	}


	for(i = 0; i<n; i++)
	{
		for(j = 0; j<n; j++)
		{
		x[i][j] = rand()%20;
		 if(rand()%2==1)
			x[i][j] = -x[i][j];
		}
	} 

	view(n,x,"Isxodnij massiv:");
	sortirovka(n,x);

	cin.get();
	return 0;
}
