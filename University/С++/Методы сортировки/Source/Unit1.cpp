// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------


// Функция создания массива
void __fastcall TForm1::CreateMasClick(TObject *Sender) {
	delete[]array;
	array = new int[EMn->Text.ToInt()];

	srand(time(NULL));
	for (int i = 0; i < EMn->Text.ToInt(); i++) {
		array[i] = rand() % EMaxNumber->Text.ToInt()+1;
		if (CNegative->Checked) {
			if (rand() % 4 == 1)
				array[i] = -array[i];
		}
	}
	Memo1->Lines->Text = Print(array);
	Start->Enabled = true;
}
// ---------------------------------------------------------------------------

// Функция возвращает массив в виде текста
String TForm1::Print(int *mas) {
	String result;
	for (int i = 0; i < EMn->Text.ToInt(); i++) {
		result = result + (String)mas[i] + " ";
	}
	return result;
}
// ---------------------------------------------------------------------------

// Функция для вызова сортировки по методу хоара
void TForm1::SortXoar() {
	TTime time;
	time = Time();

	int *mas = new int[EMn->Text.ToInt()];
	for (int i = 0; i < EMn->Text.ToInt(); i++)
		mas[i] = array[i];

	if (CRealTime->Checked)
		SortQuick2(mas, 0, EMn->Text.ToInt() - 1, time);
	else
		SortQuick1(mas, 0, EMn->Text.ToInt() - 1);

	time = Time() - time;
	LTimeX->Caption = time.FormatString("nn:ss:zz");
	Memo3->Lines->Text = Print(mas);
	LOpX->Caption = FormatInt(CountOpX);

	delete[]mas;

}
// ---------------------------------------------------------------------------


// Функция сортировки хоара без мониторинга процесса сортировки
void TForm1::SortQuick1(int *mas, int left, int right) {

			int i = left;
			int j = right;
			int x = mas[(left + right)/2];
			CountOpX += 3;

			do {
			CountOpX += 1;
			  while (mas[i] < x) {
				++i; CountOpX += 2;	}
			  while (x < mas[j]){
				--j; CountOpX += 2;	}
			  if ( i <= j ) { CountOpX += 1;
			   if( i < j ) {    CountOpX += 4;
				 int t = mas[i];
				 mas[i] = mas[j];
				 mas[j] = t;
               }
				++i;
				--j;
				CountOpX += 2;
              }
            } while (i <= j);

			CountOpX += 2;
			if (left < j)
			  SortQuick1(mas, left, j);
			if (i < right)
			  SortQuick1(mas, i, right);

}
// ---------------------------------------------------------------------------


// Функция сортировки хоара с выводом информации о процессе сортировки
void TForm1::SortQuick2(int *mas, int left, int right, TTime time) {
	int i = left;
	int j = right;
	int x = mas[(left + right)/2];
    CountOpX += 3;
	TTime temp;


			do {
			CountOpX += 1;
			  while (mas[i] < x) {
				++i; CountOpX += 2;	}
			  while (x < mas[j]){
				--j; CountOpX += 2;	}
			  if ( i <= j ) { CountOpX += 1;
			   if( i < j ) {    CountOpX += 4;
				 int t = mas[i];
				 mas[i] = mas[j];
				 mas[j] = t;

				temp = Time() - time;
				LTimeX->Caption = temp.FormatString("nn:ss:zz");
				Memo3->Lines->Text = Print(mas);
				LOpX->Caption = FormatInt(CountOpX);
				LOpX->Refresh();
				LTimeX->Refresh();
				Memo3->Refresh();
               }
				++i;
				--j;
				CountOpX += 2;
              }
            } while (i <= j);

			CountOpX += 2;
			if (left < j)
			  SortQuick2(mas, left, j,time);
			if (i < right)
			  SortQuick2(mas, i, right,time);

}
// ---------------------------------------------------------------------------

// Сортировка методом слияния
void TForm1::SortMarge() {
 TTime time= Time();

    int * a = new int[EMn->Text.ToInt()];
	for (int i = 0; i < EMn->Text.ToInt(); i++)
		a[i] = array[i];

  mergeSort(a, EMn->Text.ToInt(), time);

	time = Time() - time;
	LTimeP->Caption = time.FormatString("nn:ss:zz");
	Memo2->Lines->Text = Print(a);
	LOpP->Caption = FormatInt(CountOpP);
	delete[]a;

}
// ---------------------------------------------------------------------------


 void TForm1::mergeSort(int *mas, int len,TTime time) {
// Слияние двух упорядоченных массивов
// m1 - Первый массив
// m2 - Второй массив
// l1 - Длина первого массива
// l2 - Длина второго массива
// Возвращает объединённый массив

  TTime temp;
	int n=1, l, ost;
	int * mas1;


	while (n<len){
	l=0;  CountOpP+=2;

		while (l<len)
		   {
		   if (l+n >= len) break;   CountOpP+=2;
		   // ost = (l+n*2>len) ? (len-(l+n)) : n;   CountOpP+=2;
			if(l+n*2>len)
			 ost=len-(l+n);
			else
			 ost=n;

		   CountOpP+=2;
		   mas1 = merge(mas+l, mas+l+n, n, ost);
		   for (int i=0; i<n+ost; i++){ mas[l+i] = mas1[i]; CountOpP+=3;
           		   	 if (CRealTime->Checked) {

					temp = Time() - time;
					LTimeP->Caption = temp.FormatString("nn:ss:zz");
					Memo2->Lines->Text = Print(mas);
					LOpP->Caption = FormatInt(CountOpP);
					Memo2->Refresh();
					LOpP->Refresh();
					LTimeP->Refresh();
									}
		   }
           delete [] mas1;
		   l+=n*2;  CountOpP+=2;
		   }
	   n*=2;
	}
}
// ---------------------------------------------------------------------------

 int* TForm1::merge(int *m1, int* m2, int l1, int l2)
 {
	int* ret = new int[l1+l2];
	int n = 0;   CountOpP+=2;
    // Сливаем массивы, пока один не закончится
    while (l1 && l2){
        if (*m1 < *m2){
           ret[n] = *m1;
		   m1++; l1--; CountOpP+=4;}
        else {
           ret[n] = *m2;
		   m2++; l2--; }
	   n++; CountOpP+=4;}
    // Если закончился первый массив
    if (l1 == 0){
        for (int i=0; i<l2; i++){
			ret[n++] = *m2++; CountOpP+=3;}}
    // Если закончился второй массив
    else {
        for (int i=0; i<l1; i++){
           ret[n++] = *m1++; CountOpP+=3;}}
	return ret;
}
// ---------------------------------------------------------------------------


// Функция сортировки вставками
void TForm1::SortInsert() {
	int * mas = new int[EMn->Text.ToInt()];
	int x, i, j;

	for (int i = 0; i < EMn->Text.ToInt(); i++)
		mas[i] = array[i];

	TTime time, temp;
	time = Time();

	if (CRealTime->Checked) {
		for (i = 0; i < EMn->Text.ToInt(); i++) {

			CountOpI += 3;
			x = mas[i];
			// поиск места элемента в готовой последовательности
			for (j = i - 1; j >= 0 && mas[j] > x; j--) {
				CountOpI += 3;
				mas[j + 1] = mas[j]; // сдвигаем элемент направо, пока не дошли

				Memo4->Lines->Text = Print(mas);
				Memo4->Refresh();
			} // место найдено, вставить элемент
			CountOpI++;
			mas[j + 1] = x;
				temp = Time() - time;
				LTimeI->Caption = temp.FormatString("nn:ss:zz");
				LOpI->Caption = FormatInt(CountOpI);
				LOpI->Refresh();
				LTimeI->Refresh();

		}
	}
	else {

		for (i = 0; i < EMn->Text.ToInt(); i++) {
			CountOpI += 3;
			x = mas[i];
			// поиск места элемента в готовой последовательности
			for (j = i - 1; j >= 0 && mas[j] > x; j--) {
				CountOpI += 3;
				mas[j + 1] = mas[j]; // сдвигаем элемент направо, пока не дошли
			} // место найдено, вставить элемент
			CountOpI++;
			mas[j + 1] = x;
		}

	}

	time = Time() - time;
	LTimeI->Caption = time.FormatString("nn:ss:zz");
	Memo4->Lines->Text = Print(mas);
	LOpI->Caption = FormatInt(CountOpI);
	delete[]mas;

}
// ---------------------------------------------------------------------------


// Сортировка по методу шелла
void TForm1::SortShell() {
	int * mas = new int[EMn->Text.ToInt()];
	long i, j, g;
	short c; // флаг
	float temp;

	for (int i = 0; i < EMn->Text.ToInt(); i++)
		mas[i] = array[i];

	TTime time, ttemp;

	if (CRealTime->Checked) {
		time = Time();
		g = EMn->Text.ToInt() / 2;
		CountOpS+=2;
		do {
			i = g;
			CountOpS++;
			do {
				j = i - g;
				c = 1;
				CountOpS += 3;
				do {
					if (mas[j] <= mas[j + g]) {
						c = 0;
						CountOpS += 2;
					}
					else {
						temp = mas[j];
						mas[j] = mas[j + g];
						mas[j + g] = temp;
						CountOpS += 3;

						ttemp = Time() - time;
						LTimeS->Caption = ttemp.FormatString("nn:ss:zz");
						Memo5->Lines->Text = Print(mas);
						LOpS->Caption = FormatInt(CountOpS);
						Memo5->Refresh();
						LOpS->Refresh();
						LTimeS->Refresh();
					}
					j--;
					CountOpS += 2;
				}
				while (j >= 0 && c);
				i++;
				CountOpS += 1;
			}
			while (i < EMn->Text.ToInt());
			g = g / 2;
			CountOpS += 1;
		}
		while (g > 0);

	}
	else {
		time = Time();
		g = EMn->Text.ToInt() / 2;
		CountOpS++;
		do {
			i = g;
			CountOpS++;
			do {
				j = i - g;
				c = 1;
				CountOpS += 2;
				do {
					if (mas[j] <= mas[j + g]) {
						c = 0;
						CountOpS += 3;
					}
					else {
						temp = mas[j];
						mas[j] = mas[j + g];
						mas[j + g] = temp;
						CountOpS += 3;
					}
					j--;
					CountOpS += 2;
				}
				while (j >= 0 && c);
				i++;
				CountOpS += 2;
			}
			while (i < EMn->Text.ToInt());
			g = g / 2;
			CountOpS += 2;
		}
		while (g > 0);

	}

	time = Time() - time;
	LTimeS->Caption = time.FormatString("nn:ss:zz");
	Memo5->Lines->Text = Print(mas);
	LOpS->Caption = FormatInt(CountOpS);
	delete[]mas;

}
// ---------------------------------------------------------------------------


// Функция вызова сортировок
void __fastcall TForm1::StartClick(TObject *Sender) {
	Start->Enabled = false;
	Start->Refresh();

	Memo2->Clear();
	Memo3->Clear();
	Memo4->Clear();
	Memo5->Clear();
	LTimeX->Caption = "00:00:00";
	LTimeP->Caption = "00:00:00";
	LTimeI->Caption = "00:00:00";
	LTimeS->Caption = "00:00:00";
	CountOpX = 0;
	CountOpP = 0;
	CountOpI = 0;
	CountOpS = 0;
	LOpP->Caption = 0;
	LOpX->Caption = 0;
	LOpI->Caption = 0;
	LOpS->Caption = 0;
	Result->Refresh();
	ok[0] = false;
	ok[1] = false;
	ok[2] = false;
	ok[3] = false;

	DWORD threadID;

	if (CParalel->Checked) {
		if (CPusyr->Checked) {
			threadID = 0;
			hthread1 = CreateThread(0, 0, SortP, NULL, 0, &threadID);
			SetThreadPriority(hthread1, THREAD_PRIORITY_HIGHEST);

		}

		if (CXoar->Checked) {
			threadID = 1;
			hthread2 = CreateThread(0, 0, SortX, NULL, 0, &threadID);
			SetThreadPriority(hthread2, THREAD_PRIORITY_HIGHEST);

		}

		if (CInsert->Checked) {
			threadID = 2;
			hthread3 = CreateThread(0, 0, SortI, NULL, 0, &threadID);
			SetThreadPriority(hthread3, THREAD_PRIORITY_HIGHEST);

		}

		if (CShell->Checked) {
			threadID = 4;
			hthread4 = CreateThread(0, 0, SortS, NULL, 0, &threadID);
			SetThreadPriority(hthread4, THREAD_PRIORITY_HIGHEST);

		}

		threadID = 3;
		hthread5 = CreateThread(0, 0, StartChek, NULL, 0, &threadID);

	}
	else {
		if (CXoar->Checked)
			SortXoar();
		if (CInsert->Checked)
			SortInsert();
		if (CPusyr->Checked)
			SortMarge();
		if (CShell->Checked)
			SortShell();
		Start->Enabled = true;
	}
}
// ---------------------------------------------------------------------------


/*- Функции для потоков  -*/
DWORD __stdcall TForm1::SortX(LPVOID pParams) {
	Form1->SortXoar();
	Form1->ok[1] = true;
	return 1;
}
// ---------------------------------------------------------------------------

DWORD __stdcall TForm1::SortS(LPVOID pParams) {
	Form1->SortShell();
	Form1->ok[3] = true;
	return 1;
}
// ---------------------------------------------------------------------------

DWORD __stdcall TForm1::SortP(LPVOID pParams) {
	Form1->SortMarge();
	Form1->ok[2] = true;
	return 1;
}
// ---------------------------------------------------------------------------

DWORD __stdcall TForm1::SortI(LPVOID pParams) {
	Form1->SortInsert();
	Form1->ok[0] = true;
	return 1;
}
// ---------------------------------------------------------------------------
/*- .Функции для потоков  -*/

void __fastcall TForm1::EMnChange(TObject *Sender) {
	Start->Enabled = false;
}
// ---------------------------------------------------------------------------


// Функция слежения за окончанием работы потоков
DWORD __stdcall TForm1::StartChek(LPVOID pParams) {
Form1->TerminatedThear->Enabled = true;

chek:
	if (Form1->ok[0] && Form1->ok[1] && Form1->ok[2] && Form1->ok[3])
	   {
	   Form1->Start->Enabled = true;
	   Form1->TerminatedThear->Enabled = false;

		CloseHandle( Form1->hthread1 );
		CloseHandle( Form1->hthread2 );
		CloseHandle( Form1->hthread3 );
		CloseHandle( Form1->hthread4 );
		CloseHandle( Form1->hthread5 );
	   }
	else
		goto chek;

	return 1;
}
// ---------------------------------------------------------------------------

// Функция для вывода числа разрядами в строковый параметр
String TForm1::FormatInt(double num) {
	int del = 1;
	String result;
	double ost = 0;

	for (int u = 0; u < (String(num).Length() - 1) / 3; u++) {
		del = del * 1000;
	}

	while (String(num).Length() > 3) {
		modf(num / del, &ost);
		num = fmod(num, del);
		result += String(ost) + ",";
		del /= 1000;
	}

	if (String(num).Length() < 1)
		result = result + "000";
	else if (String(num).Length() < 2)
		result = result + "00" + String(num);
	else if (String(num).Length() < 3)
		result = result + "0" + String(num);
	else
		result += String(num);

	return result;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::CNegativeClick(TObject *Sender) {
	Start->Enabled = false;
}
// ---------------------------------------------------------------------------

// Экстренное завершение потоков
void __fastcall TForm1::TerminatedThearClick(TObject *Sender)
{
if(hthread1)
TerminateThread(hthread1,false);
if(hthread2)
TerminateThread(hthread2,false);
if(hthread3)
TerminateThread(hthread3,false);
if(hthread4)
TerminateThread(hthread4,false);
if(hthread5)
TerminateThread(hthread5,false);

CloseHandle( hthread1 );
CloseHandle( hthread2 );
CloseHandle( hthread3 );
CloseHandle( hthread4 );
CloseHandle( hthread5 );

Form1->Start->Enabled = true;
Form1->TerminatedThear->Enabled = false;
}
//---------------------------------------------------------------------------

