//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sButton"
#pragma link "sEdit"
#pragma link "sLabel"
#pragma link "sMemo"
#pragma link "sSkinManager"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
if(Edit2->Text.Length()<Edit1->Text.Length())
{
	ShowMessage("Зачетка не может быть длинее даты рождения");
}
else{
double temp, x, ostx,osty;
String result,ost,xtemp,mtemp;
String result2[5];
String result2dr[5];
String result2sum[4];
String result2min[4];

	Memo1->Clear(); Memo2->Clear(); Memo3->Clear();  Memo4->Clear();
	// ----------------  2 --------------------------------
	Memo1->Lines->Add("Перевод в двоичную систему");
	Memo1->Lines->Add("");

	for (temp = Edit2->Text.ToDouble(); temp > 2; ) {
		ost = (int)fmod(temp, 2);
		result += ost;
		temp = temp/2;
		modf(temp, &x);
		xtemp = x;
		Memo1->Lines->Add(xtemp + "\tОстаток - " + ost);
	}
	result+=xtemp;

	 for (int i = result.Length(); i>0; i--) {
	 result2[0] = result2[0] +result[i];
	}

	Memo2->Lines->Add("Перевод в двоичную систему");
	Memo2->Lines->Add("");

	for (temp = Edit1->Text.ToInt(); result2dr[0].Length() <= Edit3->Text.ToInt(); ) {
		temp = temp * 2;
		xtemp = temp;
		if(xtemp.Length()<=Edit1->Text.Length())
		 ost=0;
		if(xtemp.Length()>Edit1->Text.Length())
		 {ost=xtemp[1]; xtemp.Delete(1,1); }

		result2dr[0] += ost;
		temp=xtemp.ToInt();

		Memo2->Lines->Add(xtemp + "\tОстаток - " + ost);
	}

	Memo3->Lines->Add(Edit2->Text+","+Edit1->Text+"^10 = "+result2[0]+","+result2dr[0]+"^2");
	// ----------------  2 --------------------------------



	// ----------------  3 --------------------------------
	Memo1->Lines->Add("");   result="";
	Memo1->Lines->Add("Перевод в троичную систему");
	Memo1->Lines->Add("");

	for (temp = Edit2->Text.ToDouble(); temp > 3; ) {
		ost = (int)fmod(temp, 3);
		result += ost;
		temp = temp/3;
		modf(temp, &x);
		xtemp = x;
		Memo1->Lines->Add(xtemp + "\tОстаток - " + ost);
	}
	result+=xtemp;

	for (int i = result.Length(); i>0; i--) {
	 result2[1] = result2[1] +result[i];
	}

	Memo2->Lines->Add("");
	Memo2->Lines->Add("Перевод в троичную систему");
	Memo2->Lines->Add("");  result2dr[1]="";

	for (temp = Edit1->Text.ToInt(); result2dr[1].Length() <= Edit4->Text.ToInt(); ) {
		temp = temp * 3;
		xtemp = temp;
		if(xtemp.Length()<=Edit1->Text.Length())
		 ost=0;
		if(xtemp.Length()>Edit1->Text.Length())
		 {ost=xtemp[1]; xtemp.Delete(1,1); }

		result2dr[1] += ost;
		temp=xtemp.ToInt();

		Memo2->Lines->Add(xtemp + "\tОстаток - " + ost);
	}

	Memo3->Lines->Add(Edit2->Text+","+Edit1->Text+"^10 = "+result2[1]+","+result2dr[1]+"^3");
	// ---------------- 3 --------------------------------

	// ----------------  8 --------------------------------
	Memo1->Lines->Add("");    result="";
	Memo1->Lines->Add("Перевод в восмеричную систему");
	Memo1->Lines->Add("");

	for (temp = Edit2->Text.ToDouble(); temp > 8; ) {
		ost = (int)fmod(temp, 8);
		result += ost;
		temp = temp/8;
		modf(temp, &x);
		xtemp = x;
		Memo1->Lines->Add(xtemp + "\tОстаток - " + ost);
	}
	result+=xtemp;

	for (int i = result.Length(); i>0; i--) {
	 result2[2] = result2[2] +result[i];
	}

	Memo2->Lines->Add("");
	Memo2->Lines->Add("Перевод в восмеричную систему");
	Memo2->Lines->Add("");  result2dr[2]="";

	for (temp = Edit1->Text.ToInt(); result2dr[2].Length() <= Edit5->Text.ToInt(); ) {
		temp = temp * 8;
		xtemp = temp;
		if(xtemp.Length()<=Edit1->Text.Length())
		 ost=0;
		if(xtemp.Length()>Edit1->Text.Length())
		 {ost=xtemp[1]; xtemp.Delete(1,1); }

		result2dr[2] += ost;
		temp=xtemp.ToInt();

		Memo2->Lines->Add(xtemp + "\tОстаток - " + ost);
	}

	Memo3->Lines->Add(Edit2->Text+","+Edit1->Text+"^10 = "+result2[2]+","+result2dr[2]+"^8");

	// ----------------  8 --------------------------------

	// ----------------  16 --------------------------------
	Memo1->Lines->Add("");    result="";
	Memo1->Lines->Add("Перевод в шестнадцатиричную систему");
	Memo1->Lines->Add("");

	for (temp = Edit2->Text.ToDouble(); temp > 16; ) {
		ost = (int)fmod(temp, 16);
		result += decTOhex(ost);
		temp = temp/16;
		modf(temp, &x);
		xtemp = x;
		Memo1->Lines->Add(xtemp + "\tОстаток - " + ost);
	}
	result+=decTOhex(xtemp);

	for (int i = result.Length(); i>0; i--) {
	 result2[3] = result2[3] +result[i];
	}

	Memo2->Lines->Add("");
	Memo2->Lines->Add("Перевод в шестнадцатиричную систему");
	Memo2->Lines->Add("");  result2dr[2]="";

	for (temp = Edit1->Text.ToInt(); result2dr[3].Length() <= Edit6->Text.ToInt(); ) {
		temp = temp * 16;
		xtemp = temp;
		if(xtemp.Length()<=Edit1->Text.Length())
		 ost=0;
		if(xtemp.Length()>Edit1->Text.Length())
		 {
		if(xtemp.Length()-Edit1->Text.Length()==1)
		 { ost= xtemp[1]; xtemp.Delete(1, 1); }
			if (xtemp.Length() - Edit1->Text.Length() == 2) {
				ost = xtemp[1];
				ost += xtemp[2];
				xtemp.Delete(1, 1);
				xtemp.Delete(1, 1);
			}
		}

		result2dr[3] += decTOhex(ost);
		temp = xtemp.ToInt();

		Memo2->Lines->Add(xtemp + "\tОстаток - " + ost);
	}

	Memo3->Lines->Add(Edit2->Text + "," + Edit1->Text + "^10 = " + result2[3]
		+ "," + result2dr[3] + "^16");

	// ----------------  16 --------------------------------


		// ------------------  3->5 --------------------------------
	Memo3->Lines->Add("");   result2[4]="";
	Memo3->Lines->Add("Перевод из троичной в пятеричную систему");


	String stemp[2];  String pr1,pr2; int kk; stemp[0]=""; stemp[1]="";
 //	if(result2[1][1]=='0')
//		result2[1].Delete(1,1);

	for(int i=result2[1].Length(); i>=1; i--)
	 {
			 pr1 += (String(result2[1][result2[1].Length()-i+1]))+"*3^"+(i-1)+"+";
				if(	((String(result2[1][result2[1].Length()-i+1])).ToInt()*pow(3,i-1))!=0)
  pr2 +=(String( to5((String(result2[1][result2[1].Length()-i+1])).ToInt()*pow(3,i-1))))+"+";
	 kk=			(String(result2[1][result2[1].Length()-i+1])).ToInt()*pow(3,i-1);

   //	  ShowMessage((String(to5(kk).ToInt()))+"+"+(String(temp))+"="+(String(plustoplus5(temp,to5(kk)))));
	  if(kk!=0)
	   stemp[0] = plustoplus5(stemp[0],to5(kk));

	 }
   //	ShowMessage((String(plustoplus5("1402",to5(33)))));
  //  ShowMessage(to5(3));
 //	result2[4]=stemp;


	Memo3->Lines->Add(pr1+"="+pr2+"="+stemp[0]);
	Memo3->Lines->Add("");
	// ---------------- 3->5 --------------------------------



	// ------------------  Сложение --------------------------------
	temp = Edit2->Text.ToInt()+Edit1->Text.ToInt();
	Memo3->Lines->Add("Сложение в десятиной - "+Edit2->Text+"+"+Edit1->Text+"="+temp);

	int sum;
	// ------------------  Сложение в двоичной -----------------------------
	Memo4->Lines->Add("Идет сложение в двоичной ("+result2[0]+"+"+to2(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to2(Edit1->Text.ToInt());
	int i2 =  mtemp.Length();
	int s,s2;
	for(int i=result2[0].Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=(String(result2[0][i])).ToInt(); s2=(String(mtemp[i2])).ToInt();
			sum = s+s2+ostx;
			  if(sum==2) {result+=0; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk;}
			  if(sum==1) {result+=1; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk;}
			  if(sum==3) {result+=1; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk;}
			  }
		  if(i>=1 && i2<1)
			{    s=(String(result2[0][i])).ToInt();
			 sum = s+ostx;
			  if(sum==2) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk;}
			  if(sum==1) {result+=1; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk;}
			  if(sum==3) {result+=1; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk;}
			}
		  if(i<1 && i2>=1)
			{  s2=(String(mtemp[i2])).ToInt();
			 sum = s2+ostx;
			  if(sum==2) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk;}
			  if(sum==1) {result+=1; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk;}
			  if(sum==3) {result+=1; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk;}
			}

			bk:
			i2--;
		}
		if(ostx!=0)
	 result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2sum[0] = result2sum[0] +result[i];
	}
	Memo3->Lines->Add("Сложение в двоичной - "+result2[0]+"+"+mtemp+"="+result2sum[0]);

	Memo3->Lines->Add("Проверка");
	pr1="",pr2="";  temp=0;

	for(int i=result2sum[0].Length(); i>=1; i--)
	 {
	 pr1 += (String(result2sum[0][result2sum[0].Length()-i+1]))+"*2^"+(i-1)+"+";
	 if((String(result2sum[0][result2sum[0].Length()-i+1])).ToInt()*(pow(2,(i-1)))!=0)
	 pr2 += (String((String(result2sum[0][result2sum[0].Length()-i+1])).ToInt()*(pow(2,(i-1)))))+"+";
	 temp = temp+(String(result2sum[0][result2sum[0].Length()-i+1])).ToInt()*(pow(2,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));

	// ------------------  Сложение в троичной -----------------------------
	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет сложение в троичной ("+result2[1]+"+"+to3(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to3(Edit1->Text.ToInt());
	i2 =  mtemp.Length();
	for(int i=result2[1].Length();i>=1; i--)
		{
 /*	   	  if(i>=1 && i2>=1)
			{ s=(String(result2[1][i])).ToInt(); s2=(String(mtemp[i2])).ToInt();
			sum = s+s2+ostx;
			  if(sum==2) {result+=2; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 2, остаток "+(String(ostx))); goto bk3;}
			  if(sum==1) {result+=1; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum==3) {result+=0; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk3;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk3;}
			  if(sum==4) {result+=1; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum==5) {result+=2; ostx=2; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 2, остаток "+(String(ostx))); goto bk3;}
			  }
		  if(i>=1 && i2<1)
			{ s=(String(result2[1][i])).ToInt();
			sum = s+ostx;
			  if(sum==2) {result+=2; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 2, остаток "+(String(ostx))); goto bk3;}
			  if(sum==1) {result+=1; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum==3) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk3;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk3;}
			  if(sum==4) {result+=1; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum==5) {result+=2; ostx=2; Memo4->Lines->Add("Сносим "+(String(s))+", результат 2, остаток "+(String(ostx))); goto bk3;}
			  }
		  if(i<1 && i2>=1)
			{ s2=(String(mtemp[i2])).ToInt();
			  sum = s2+ostx;
			  if(sum==2) {result+=2; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 2, остаток "+(String(ostx))); goto bk3;}
			  if(sum==1) {result+=1; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum==3) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk3;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk3;}
			  if(sum==4) {result+=1; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum==5) {result+=2; ostx=2; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 2, остаток "+(String(ostx))); goto bk3;}
			  } */
		  if(i>=1 && i2>=1)
			{
			s=(String(result2[1][i])).ToInt(); s2=(String(mtemp[i2])).ToInt();
			sum = s+s2+ostx;
			  if(sum>3)  {result+=sum-3; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum-3))+", остаток "+(String(ostx))); goto bk3;}
			  if(sum==3) {result+=0; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum<3) {result+=sum; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk3;}
			 }
		  if(i>=1 && i2<1)
			{
			s=(String(result2[1][i])).ToInt();
			sum = s+ostx;
			  if(sum>3)  {result+=sum-3; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum-3))+", остаток "+(String(ostx))); goto bk3;}
			  if(sum==3) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum<3) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk3;}

			}
		  if(i<1 && i2>=1)
			{
			s2=(String(mtemp[i2])).ToInt();
			sum = s2+ostx;
			  if(sum>3)  {result+=sum-3; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum-3))+", остаток "+(String(ostx))); goto bk3;}
			  if(sum==3) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk3;}
			  if(sum<3)  {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk3;}
			}

			bk3:
			i2--;
		}
		if(ostx!=0)
     result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2sum[1] = result2sum[1] +result[i];
	}
	Memo3->Lines->Add("Сложение в троичной - "+result2[1]+"+"+mtemp+"="+result2sum[1]);

	Memo3->Lines->Add("Проверка");
	temp=0; pr1="",pr2="";

	for(int i=result2sum[1].Length(); i>=1; i--)
	 {
	 pr1 += (String(result2sum[1][result2sum[1].Length()-i+1]))+"*3^"+(i-1)+"+";
	 if((String(result2sum[1][result2sum[1].Length()-i+1])).ToInt()*(pow(3,(i-1)))!=0)
	 pr2 += (String((String(result2sum[1][result2sum[1].Length()-i+1])).ToInt()*(pow(3,(i-1)))))+"+";
	 temp = temp+(String(result2sum[1][result2sum[1].Length()-i+1])).ToInt()*(pow(3,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));

	// ------------------  Сложение в восмеричной -----------------------------
	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет сложение в восмеричной ("+result2[2]+"+"+to8(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to8(Edit1->Text.ToInt());
	i2 =  mtemp.Length();
	for(int i=result2[2].Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=(String(result2[2][i])).ToInt(); s2=(String(mtemp[i2])).ToInt();
			sum = s+s2+ostx;
			  if(sum>8)  {result+=sum-8; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum-8))+", остаток "+(String(ostx))); goto bk8;}
			  if(sum==8) {result+=0; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk8;}
			  if(sum<8) {result+=sum; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk8;}
			 }
		  if(i>=1 && i2<1)
			{
			s=(String(result2[2][i])).ToInt();
			sum = s+ostx;
			  if(sum>8)  {result+=sum-8; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum-8))+", остаток "+(String(ostx))); goto bk8;}
			  if(sum==8) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk8;}
			  if(sum<8) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk8;}

			}
		  if(i<1 && i2>=1)
			{
			s2=(String(mtemp[i2])).ToInt();
			sum = s2+ostx;
			  if(sum>8)  {result+=sum-8; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum-8))+", остаток "+(String(ostx))); goto bk8;}
			  if(sum==8) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk8;}
			  if(sum<8) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk8;}
			}

			bk8:
			i2--;
		}
		if(ostx!=0)
	 result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2sum[2] = result2sum[2]+result[i];
	}
	Memo3->Lines->Add("Сложение в восмеричной - "+result2[2]+"+"+mtemp+"="+result2sum[2]);

	Memo3->Lines->Add("Проверка");
	temp=0;   pr1="",pr2="";

	for(int i=result2sum[2].Length(); i>=1; i--)
	 {
	 pr1 += (String(result2sum[2][result2sum[2].Length()-i+1]))+"*8^"+(i-1)+"+";
	 if((String(result2sum[2][result2sum[2].Length()-i+1])).ToInt()*(pow(8,(i-1)))!=0)
	 pr2 += (String((String(result2sum[2][result2sum[2].Length()-i+1])).ToInt()*(pow(8,(i-1)))))+"+";
	 temp = temp+(String(result2sum[2][result2sum[2].Length()-i+1])).ToInt()*(pow(8,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));

	// ------------------  Сложение в шестнадцатиричной -----------------------------
	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет сложение в шестнадцатиричной ("+result2[3]+"+"+to16(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to16(Edit1->Text.ToInt());
	i2 =  mtemp.Length();

	for(int i=result2[3].Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=hexTOdec(result2[3][i]); s2=hexTOdec(mtemp[i2]);

			sum = s+s2+ostx;
			  if(sum>16)  {result+=sum-16; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum-16))+", остаток "+(String(ostx))); goto bk16;}
			  if(sum==16) {result+=0; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk16;}
			  if(sum<16) {result+=decTOhex((String(sum))); ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk16;}
			 }
		  if(i>=1 && i2<1)
			{
			s=hexTOdec(result2[3][i]);
			sum = s+ostx;
			  if(sum>16)  {result+=sum-16; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum-16))+", остаток "+(String(ostx))); goto bk16;}
			  if(sum==16) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk16;}
			  if(sum<16) {result+=decTOhex((String(sum))); ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk16;}

			}
		  if(i<1 && i2>=1)
			{
			s2=hexTOdec(mtemp[i2]);
			sum = s2+ostx;
			  if(sum>16)  {result+=sum-16; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum-16))+", остаток "+(String(ostx))); goto bk16;}
			  if(sum==16) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk16;}
			  if(sum<16) {result+=decTOhex((String(sum))); ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk16;}
			}


			bk16:
			i2--;
		}
		if(ostx!=0)
     result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2sum[3] = result2sum[3]+result[i];
	}
	Memo3->Lines->Add("Сложение в шестнадцатиричной - "+result2[3]+"+"+mtemp+"="+result2sum[3]);

	Memo3->Lines->Add("Проверка");
	temp=0;  pr1="",pr2="";

	for(int i=result2sum[3].Length(); i>=1; i--)
	 {
	 pr1 += (String(hexTOdec(result2sum[3][result2sum[3].Length()-i+1])))+"*16^"+(i-1)+"+";
	 if((String(hexTOdec(result2sum[3][result2sum[3].Length()-i+1]))).ToInt()*(pow(16,(i-1)))!=0)
	 pr2 += (String((String(hexTOdec(result2sum[3][result2sum[3].Length()-i+1]))).ToInt()*(pow(16,(i-1)))))+"+";
	 temp = temp+(String(hexTOdec(result2sum[3][result2sum[3].Length()-i+1]))).ToInt()*(pow(16,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));

	// ------------------  Сложение --------------------------------

  // ---------------------Вычитание----------------------------------
	temp = Edit2->Text.ToInt()-Edit1->Text.ToInt();
    Memo3->Lines->Add(""); Memo3->Lines->Add("");
	Memo3->Lines->Add("Вычитаение в десятиной - "+Edit2->Text+"-"+Edit1->Text+"="+temp);

 // ------------------  Вычитание в двоичной -----------------------------
	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет вычитание в двоичной ("+result2[0]+"-"+to2(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to2(Edit1->Text.ToInt());
	i2 =  mtemp.Length();
	for(int i=result2[0].Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=(String(result2[0][i])).ToInt(); s2=(String(mtemp[i2])).ToInt();
			sum = s-s2-ostx;
			  if(sum<0)  {result+=sum+2; ostx=1; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum+2))+", остаток "+(String(ostx))); goto bk22;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk22;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk22;}
			 }
		  if(i>=1 && i2<1)
			{
			s=(String(result2[0][i])).ToInt();
			sum = s-ostx;
			  if(sum<0)  {result+=sum+2; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum+2))+", остаток "+(String(ostx))); goto bk22;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk22;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk22;}
			 }
		  if(i<1 && i2>=1)
			{
			s2=(String(mtemp[i2])).ToInt();
			sum = s2-ostx;
			  if(sum<0)  {result+=sum+2; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum+2))+", остаток "+(String(ostx))); goto bk22;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk22;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk22;}
			 }

			bk22:
			i2--;
		}
		if(ostx!=0)
     result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2min[0] = result2min[0] +result[i];
	}
	Memo3->Lines->Add("Вычитание в двоичной - "+result2[0]+"-"+mtemp+"="+result2min[0]);

	Memo3->Lines->Add("Проверка");
	temp=0; pr1="",pr2="";

	for(int i=result2min[0].Length(); i>=1; i--)
	 {
	 pr1 += (String(result2min[0][result2min[0].Length()-i+1]))+"*2^"+(i-1)+"+";
	 if((String(result2min[0][result2min[0].Length()-i+1])).ToInt()*(pow(2,(i-1)))!=0)
	 pr2 += (String((String(result2min[0][result2min[0].Length()-i+1])).ToInt()*(pow(2,(i-1)))))+"+";
	 temp = temp+(String(result2min[0][result2min[0].Length()-i+1])).ToInt()*(pow(2,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));
	// ---------------------Вычитание----------------------------------

	 // ------------------  Вычитание в троичной -----------------------------
	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет вычитание в троичной ("+result2[3]+"-"+to3(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to3(Edit1->Text.ToInt());
	i2 =  mtemp.Length();
	for(int i=result2[1].Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=(String(result2[1][i])).ToInt(); s2=(String(mtemp[i2])).ToInt();
			sum = s-s2-ostx;
			  if(sum<0)  {result+=sum+3; ostx=1; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum+3))+", остаток "+(String(ostx))); goto bk33;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk33;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk33;}
			 }
		  if(i>=1 && i2<1)
			{
			s=(String(result2[1][i])).ToInt();
			sum = s-ostx;
			  if(sum<0)  {result+=sum+3; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum+3))+", остаток "+(String(ostx))); goto bk33;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk33;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk33;}
			 }
		  if(i<1 && i2>=1)
			{
			s2=(String(mtemp[i2])).ToInt();
			sum = s2-ostx;
			  if(sum<0)  {result+=sum+3; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum+3))+", остаток "+(String(ostx))); goto bk33;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk33;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk33;}
			 }

			bk33:
			i2--;
		}
		if(ostx!=0)
     result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2min[1] = result2min[1] +result[i];
	}
	Memo3->Lines->Add("Вычитание в троичной - "+result2[1]+"-"+mtemp+"="+result2min[1]);

	Memo3->Lines->Add("Проверка");
	temp=0; pr1="",pr2="";

	for(int i=result2min[1].Length(); i>=1; i--)
	 {
	 pr1 += (String(result2min[1][result2min[1].Length()-i+1]))+"*3^"+(i-1)+"+";
	 if((String(result2min[1][result2min[1].Length()-i+1])).ToInt()*(pow(3,(i-1)))!=0)
	 pr2 += (String((String(result2min[1][result2min[1].Length()-i+1])).ToInt()*(pow(3,(i-1)))))+"+";
	 temp = temp+(String(result2min[1][result2min[1].Length()-i+1])).ToInt()*(pow(3,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));
	// ---------------------Вычитание----------------------------------

	 // ------------------  Вычитание в восмеричной -----------------------------
	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет вычитание в восмеричной ("+result2[3]+"-"+to8(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to8(Edit1->Text.ToInt());
	i2 =  mtemp.Length();
	for(int i=result2[2].Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=(String(result2[2][i])).ToInt(); s2=(String(mtemp[i2])).ToInt();
			sum = s-s2-ostx;
			  if(sum<0)  {result+=sum+8; ostx=1; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum+8))+", остаток "+(String(ostx))); goto bk88;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk88;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk88;}
			 }
		  if(i>=1 && i2<1)
			{
			s=(String(result2[2][i])).ToInt();
			sum = s-ostx;
			  if(sum<0)  {result+=sum+8; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum+8))+", остаток "+(String(ostx))); goto bk88;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk88;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk88;}
			 }
		  if(i<1 && i2>=1)
			{
			s2=(String(mtemp[i2])).ToInt();
			sum = s2-ostx;
			  if(sum<0)  {result+=sum+8; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum+8))+", остаток "+(String(ostx))); goto bk88;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk88;}
			  if(sum>0) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk88;}
			 }

			bk88:
			i2--;
		}
		if(ostx!=0)
     result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2min[2] = result2min[2] +result[i];
	}
	Memo3->Lines->Add("Вычитание в восмеричной - "+result2[2]+"-"+mtemp+"="+result2min[2]);

	Memo3->Lines->Add("Проверка");
	temp=0; pr1="",pr2="";

	for(int i=result2min[2].Length(); i>=1; i--)
	 {
	 pr1 += (String(result2min[2][result2min[2].Length()-i+1]))+"*8^"+(i-1)+"+";
	 if((String(result2min[2][result2min[2].Length()-i+1])).ToInt()*(pow(8,(i-1)))!=0)
	 pr2 += (String((String(result2min[2][result2min[2].Length()-i+1])).ToInt()*(pow(8,(i-1)))))+"+";
	 temp = temp+(String(result2min[02][result2min[2].Length()-i+1])).ToInt()*(pow(8,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));
	// ---------------------Вычитание----------------------------------

	 // ------------------  Вычитание в шестнадцатеричной -----------------------------
	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет вычитание в шестнадцатеричной ("+result2[3]+"-"+to16(Edit1->Text.ToInt())+")");
	x=0; ostx=0; result="";
	mtemp = to16(Edit1->Text.ToInt());
	i2 =  mtemp.Length();
	for(int i=result2[3].Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=hexTOdec(result2[3][i]); s2=hexTOdec(mtemp[i2]);
			sum = s-s2-ostx;
			  if(sum<0)  {result+=decTOhex((String(sum+16))); ostx=1; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum+16))+", остаток "+(String(ostx))); goto bk66;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk66;}
			  if(sum>0) {result+=decTOhex((String(sum))); ostx=0; Memo4->Lines->Add("Вычитаем "+(String(s))+"-"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk66;}
			 }
		  if(i>=1 && i2<1)
			{
			s=hexTOdec(result2[3][i]);
			sum = s-ostx;
			  if(sum<0)  {result+=decTOhex((String(sum+16))); ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum+16))+", остаток "+(String(ostx))); goto bk66;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат 0, остаток "+(String(ostx))); goto bk66;}
			  if(sum>0) {result+=decTOhex((String(sum))); ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk66;}
			 }
		  if(i<1 && i2>=1)
			{
			s2=hexTOdec(mtemp[i2]);
			sum = s2-ostx;
			  if(sum<0)  {result+=decTOhex((String(sum+16))); ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum+16))+", остаток "+(String(ostx))); goto bk66;}
			  if(sum==0) {result+=0; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 0, остаток "+(String(ostx))); goto bk66;}
			  if(sum>0) {result+=decTOhex((String(sum))); ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk66;}
			 }

			bk66:
			i2--;
		}
		if(ostx!=0)
     result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2min[3] = result2min[3]+result[i];
	}
	Memo3->Lines->Add("Вычитание в шестнадцатеричной - "+result2[3]+"-"+mtemp+"="+result2min[3]);

	Memo3->Lines->Add("Проверка");
	temp=0; pr1="",pr2="";

	for(int i=result2min[3].Length(); i>=1; i--)
	 {
	 pr1 += (String(hexTOdec(result2min[3][result2min[3].Length()-i+1])))+"*16^"+(i-1)+"+";
	 if((String(hexTOdec(result2min[3][result2min[3].Length()-i+1]))).ToInt()*(pow(16,(i-1)))!=0)
	 pr2 += (String((String(hexTOdec(result2min[3][result2min[3].Length()-i+1]))).ToInt()*(pow(16,(i-1)))))+"+";
	 temp = temp+(String(hexTOdec(result2min[3][result2min[3].Length()-i+1]))).ToInt()*(pow(16,(i-1)));
	 }
	result2[4]=(String(temp));
	Memo3->Lines->Add(pr1+"="+pr2+"="+(String(temp)));
	// ---------------------Вычитание----------------------------------
}
}
// ---------------------------------------------------------------------------




int TForm2::hexTOdec(String y)
{
  if(y=="A") return 10; if(y=="D") return 13;
  if(y=="B") return 11; if(y=="E") return 14;
  if(y=="C") return 12; if(y=="F") return 15;
  if(y.ToInt()<10) return y.ToInt();
}

String TForm2::decTOhex(String y)
{
  if(y=="10") return "A"; if(y=="13") return "D";
  if(y=="11") return "B"; if(y=="14") return "E";
  if(y=="12") return "C"; if(y=="15") return "F";
  if(y.ToInt()<10) return y;
}

String TForm2::to2(int y)
{
   double temp, x, ostx;
String result,result2,ost,xtemp;

	if(y>2){
	for (temp = y; temp > 2; ) {
		ost = (int)fmod(temp, 2);
		result += ost;
		temp = temp/2;
		modf(temp, &x);
		xtemp = x;
	}
	}
	else xtemp=y;

	result+=xtemp;

	for (int i = result.Length(); i>0; i--) {
	 result2 = result2 + result[i];
	}
	return  result2;
}

String TForm2::to3(int y)
{
   double temp, x, ostx;
String result,result2,ost,xtemp;

	if(y>3){
	for (temp = y; temp > 3; ) {
		ost = (int)fmod(temp, 3);
		result += ost;
		temp = temp/3;
		modf(temp, &x);
		xtemp = x;
	}
	}
	else xtemp=y;

	result+=xtemp;

	for (int i = result.Length(); i>0; i--) {
	 result2 = result2 + result[i];
	}

	return  result2;
}

int  TForm2::max(int x, int y)
{
  if(x>y)
  return x;
  if(x<y)
  return y;
  if(x==y)
  return x;
}

String  TForm2::plustoplus5(String x, String y)
{

	Memo4->Lines->Add("");
	Memo4->Lines->Add("Идет сложение в пятеричной ("+x+"+"+y+")");
	int	sum=0,i2, ostx=0,s,s2; String result,result2,temp;

	if(x.Length()<y.Length())
	  { temp =  x; x = y; y = temp; }

	i2=y.Length();
   //	ShowMessage((String(x))+" "+(String(y)));
	for(int i=x.Length();i>=1; i--)
		{
		  if(i>=1 && i2>=1)
			{
			s=(String(x[i])).ToInt(); s2=(String(y[i2])).ToInt();
			sum = s+s2+ostx;
			  if(sum>5)  {result+=sum-5; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum-5))+", остаток "+(String(ostx))); goto bk5;}
			  if(sum==5) {result+=0; ostx=1; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk5;}
			  if(sum<5) {result+=sum; ostx=0; Memo4->Lines->Add("Складываем "+(String(s))+"+"+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk5;}
			 }
		  if(i>=1 && i2<1)
			{
			s=(String(x[i])).ToInt();
			sum = s+ostx;
			  if(sum>5)  {result+=sum-5; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum-5))+", остаток "+(String(ostx))); goto bk5;}
			  if(sum==5) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s))+", результат 1, остаток "+(String(ostx))); goto bk5;}
			  if(sum<5) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk5;}

			}
		  if(i<1 && i2>=1)
			{
			s2=(String(y[i2])).ToInt();
			sum = s2+ostx;
			  if(sum>5)  {result+=sum-5; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum-5))+", остаток "+(String(ostx))); goto bk5;}
			  if(sum==5) {result+=0; ostx=1; Memo4->Lines->Add("Сносим "+(String(s2))+", результат 1, остаток "+(String(ostx))); goto bk5;}
			  if(sum<5) {result+=sum; ostx=0; Memo4->Lines->Add("Сносим "+(String(s2))+", результат "+(String(sum))+", остаток "+(String(ostx))); goto bk5;}
			}

			bk5:
			i2--;
		}

	  if(ostx!=0)
	  result+=ostx;

	for (int i = result.Length(); i>0; i--) {
	 result2 = result2+result[i];
	}
Memo4->Lines->Add("");
return result2;
}

String TForm2::to5(int y)
{
   double temp, x, ostx;
   String result,result2,ost,xtemp;

	if(y>5){
	for (temp = y; temp > 5; ) {
		ost = (int)fmod(temp, 5);
		result += ost;
		temp = temp/5;
		modf(temp, &x);
		xtemp = x;
	}
	}
	else xtemp=y;

	result+=xtemp;

	for (int i = result.Length(); i>0; i--) {
	 result2 = result2 + result[i];
	}

	return  result2;
}

String TForm2::to8(int y)
{
   double temp, x, ostx;
String result,result2,ost,xtemp;


	if(y>8){
	for (temp = y; temp > 8; ) {
		ost = (int)fmod(temp, 8);
		result += ost;
		temp = temp/8;
		modf(temp, &x);
		xtemp = x;
	}
	}
	else xtemp=y;

	result+=xtemp;

	for (int i = result.Length(); i>0; i--) {
	 result2 = result2 + result[i];
	}
	return  result2;
}


String TForm2::to16(int y)
{
   double temp, x, ostx;
String result,result2,ost,xtemp;

if(y>15){
	for (temp = y; temp > 16; ) {
		ost = (int)fmod(temp, 16);
		if(ost=="10") ost = "A"; if(ost=="13") ost = "D";
		if(ost=="11") ost = "B"; if(ost=="14") ost = "E";
		if(ost=="12") ost = "C"; if(ost=="15") ost = "F";
		result += ost;
		temp = temp/16;
		modf(temp, &x);
		xtemp = x;
	}
	result+=xtemp;
	}
	else
	result=decTOhex(y);

	for (int i = result.Length(); i>0; i--) {
	 result2 = result2 + result[i];
	}
	return  result2;
}
