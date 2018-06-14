//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "math.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeCanvas"
#pragma link "TeePenDlg"
#pragma link "sColorSelect"
#pragma link "sSpeedButton"
#pragma link "sSkinManager"
#pragma link "sCheckBox"
#pragma link "acProgressBar"
#pragma link "sLabel"
#pragma link "sEdit"
#pragma resource "*.dfm"
#include <IniFiles.hpp>

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
Form1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
if(PageControl1->TabIndex==0)
  OpenDialog1->Filter = "Текстовые файлы|*.txt;*.rtf";
if(PageControl1->TabIndex==1)
  OpenDialog1->Filter = "Изображение или параметры построения|*.bmp;*.ppg";

if(OpenDialog1->Execute())
{
	if(PageControl1->TabIndex==0){
	  RichEdit1->SelStart  = 0;
	  RichEdit1->SelLength = 1;
	   if(sSkinManager1->Active == true)
		RichEdit1->SelAttributes->Color = sSkinManager1->GetActiveEditFontColor();
	   else
		RichEdit1->SelAttributes->Color = clBlack;
	  RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style.Clear();
	  RichEdit1->Lines->LoadFromFile(OpenDialog1->FileName);
	  ResultLabel->Caption = 0;
	}
	if(PageControl1->TabIndex==1)
	{
	 if(findsubs(OpenDialog1->FileName,".bmp",1)){
		Image1->Picture->LoadFromFile(OpenDialog1->FileName);
		Image1->Visible = true;
		}
	 if(findsubs(OpenDialog1->FileName,".ppg",1)){
		TIniFile *ini = new TIniFile(OpenDialog1->FileName);
		LabX->Text = ini->ReadString("Circle","X",NULL);
		LabY->Text = ini->ReadString("Circle","Y",NULL);
		LabR->Text = ini->ReadString("Circle","R",NULL);
		LabX1->Text = ini->ReadString("Line","X1",NULL);
		LabY1->Text = ini->ReadString("Line","Y1",NULL);
		LabX2->Text = ini->ReadString("Line","X2",NULL);
		LabY2->Text = ini->ReadString("Line","Y2",NULL);
		Mo->Text = ini->ReadString("GSize","Mo",NULL);
		delete(ini);
	 }
	}
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N2Click(TObject *Sender)
{
 if(PageControl1->TabIndex==0)
  SaveDialog1->Filter = "Текстовый файл|*.txt|Отформатированный текстовый файл|*.rtf";
if(PageControl1->TabIndex==1)
  SaveDialog1->Filter = "Изображение|*.bmp|Параметры построяния|*.ppg";

if(SaveDialog1->Execute())
{
	if(PageControl1->TabIndex==0)
	{
	 if(SaveDialog1->FilterIndex == 1)
	  {
	  RichEdit1->PlainText = true;
	  if(findsubs(SaveDialog1->FileName,".txt",0)==0)
		RichEdit1->Lines->SaveToFile(SaveDialog1->FileName+".txt");
	  else
		RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
	  RichEdit1->PlainText = false;
	  }
	 if(SaveDialog1->FilterIndex == 2)
		{
		if(findsubs(SaveDialog1->FileName,".rtf",0)==0)
			RichEdit1->Lines->SaveToFile(SaveDialog1->FileName+".rtf");
		else
			RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
		}
      }
		if(PageControl1->TabIndex==1)
		{
		  if(SaveDialog1->FilterIndex == 1)
		  {
			if(Image1->Visible==true)
			{
				Image1->Canvas->Font->Size=7;
				Image1->Canvas->TextOut(2,6, "Круг: ["+LabX->Text+";"+LabY->Text+"] R-"+LabR->Text);
				Image1->Canvas->TextOut(2,18, "Точка1: ["+LabX1->Text+";"+LabY1->Text+"]");
				Image1->Canvas->TextOut(2,30, "Точка2: ["+LabX2->Text+";"+LabY2->Text+"]");
				if(findsubs(SaveDialog1->FileName,".bmp",0)!=0)
				  Image1->Picture->SaveToFile(SaveDialog1->FileName);
				else
				  Image1->Picture->SaveToFile(SaveDialog1->FileName+".bmp");
			}
			else
				MessageBox(NULL,"Для сохранения не хватает графика","Ошибка",MB_OK|MB_ICONERROR);
			}

		  if(SaveDialog1->FilterIndex == 2){
			  String path;
			  if(findsubs(SaveDialog1->FileName,".ppg",0)!=0)
				 path=SaveDialog1->FileName;
			  else
				 path=SaveDialog1->FileName+".ppg";

			 TIniFile *Ini = new TIniFile(path);

			 Ini->WriteString("Circle","X",LabX->Text);
			 Ini->WriteString("Circle","Y",LabY->Text);
			 Ini->WriteString("Circle","R",LabR->Text);
			 Ini->WriteString("Line","X1",LabX1->Text);
			 Ini->WriteString("Line","Y1",LabY1->Text);
			 Ini->WriteString("Line","X2",LabX2->Text);
			 Ini->WriteString("Line","Y2",LabY2->Text);
			 Ini->WriteString("GSize","Mo",Mo->Text);

			 delete(Ini);
		   }
		}


SaveDialog1->FileName="";
}
}
//---------------------------------------------------------------------------


bool TForm1::findsimvol(String s1,String s2)
{
bool result = false;
  for(int i=1;i<=s1.Length();i++)  {
	for(int i2=1;i2<=s2.Length();i2++)   {
	  if(s1[i]==s2[i2]){
	   result = true;
	   break;
	  }
	}
  }
 return result;
}
//---------------------------------------------------------------------------

double TForm1::round (double x, int precision)
{
   double mult = pow(10, precision);
   if (x > 0)
	  return floor(x * mult+0.5) / mult;
   else
	  return ceil(x * mult-0.5) / mult;
}

double TForm1::max(double a,double b)
{
  if(a>b)
  return a;
  if(b>a)
  return b;
  if(b==a)
  return a;
}
//---------------------------------------------------------------------------


double TForm1::min(double a,double b)
{
  if(a<b)
  return a;
  if(b<a)
  return b;
  if(b==a)
  return a;
}
//---------------------------------------------------------------------------


int TForm1::findsubs(String s1,String s2,int pos)
{
int result = 0;
String temp;

 if(CheckBox2->Checked==false)
  { s1 = s1.LowerCase(); s2 = s2.LowerCase(); }

  for(int i=pos;i<=s1.Length();i++)  {
	   temp = s1.SubString(i,s2.Length());
	   if(temp==s2)
		{
		result = i;
		break;
		}
	}
 return result;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
Edit1->SetFocus();
findcout=0;
int temp,enter=0;
String word,sentence;
bool redit=false,endofline=false,bingo = false;
ResultLabel->Caption = 0;

if(Edit1->Text.Length()!=0 && findsimvol(Edit1->Text,"!. ?;,:")==false){
RichEdit1->SelStart = 0;
temp = RichEdit1->Text.Length();
RichEdit1->SelLength = temp;
 if(sSkinManager1->Active == true)
	RichEdit1->SelAttributes->Color = sSkinManager1->GetActiveEditFontColor();
 else
	RichEdit1->SelAttributes->Color = clBlack;

RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style.Clear();

RichEdit1->SelLength = 0;
findcout=0;
temp=1;
sProgressBar1->Visible = true;
sProgressBar1->Max = RichEdit1->Text.Length();

 for(int i=1;i<=RichEdit1->Text.Length();i++)
 {
  sProgressBar1->Position=i;

	if(findsimvol(RichEdit1->Text[i],"!.?")==false)
		{
		sentence += RichEdit1->Text[i];
		temp=1;

	 if(RichEdit1->Text[i]==(char)13)
			enter++;
		}

	if(findsimvol(RichEdit1->Text[i],"!.?"))
	{
	   sentence += RichEdit1->Text[i];

	   while(findsubs(sentence,Edit1->Text,temp)!=0)
	   {
		if(CheckBox1->Checked == false)
		 {
		   redit = true;
		 }
		 if(CheckBox1->Checked == true)
		 {
		  if(findsubs(sentence,Edit1->Text,temp) != 1){
		   if(findsimvol(sentence[findsubs(sentence,Edit1->Text,temp)-1],"!. ?;,:][()") &&
			  findsimvol(sentence[findsubs(sentence,Edit1->Text,temp)+Edit1->Text.Length()],"!. ?;,:][()")	)
			 redit = true;
		  }
		  else
		  {
		   if(findsimvol(sentence[findsubs(sentence,Edit1->Text,temp)+Edit1->Text.Length()],"!. ?;,:][()")	)
			 redit = true;
          }
		 }

		 if(redit)
		 {

		 for(int i2=findsubs(sentence,Edit1->Text,temp);i2<sentence.Length();i2++)
		   {	if(sentence[i2]==(char)13) endofline=true; }

	 //	 if(RichEdit1->Text[i-sentence.Length()+findsubs(sentence,Edit1->Text,temp)-enter]==Edit1->Text[1])
					RichEdit1->SelStart=i-sentence.Length()+findsubs(sentence,Edit1->Text,temp)-enter-1;
	 //	 if(RichEdit1->Text[i-sentence.Length()+findsubs(sentence,Edit1->Text,temp)-enter+1]==Edit1->Text[1])
	 //			RichEdit1->SelStart=i-sentence.Length()+findsubs(sentence,Edit1->Text,temp)-enter-1;
		 if(endofline && Edit1->Text.Length()>1)
		   RichEdit1->SelStart=i-sentence.Length()+findsubs(sentence,Edit1->Text,temp)-enter;


			 RichEdit1->SelLength = Edit1->Text.Length();
			 RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsBold;
			 RichEdit1->SelAttributes->Color = clRed;
			 RichEdit1->SelLength = 0;
			 findcout++;
			 bingo = true;
			 redit = false;
		 }
		 temp = findsubs(sentence,Edit1->Text,temp)+Edit1->Text.Length();
		}

	   if(bingo && N8->Checked==false)
		  {
			 RichEdit1->SelStart = i-sentence.Length();
			 RichEdit1->SelLength = sentence.Length();

			RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsBold;
			RichEdit1->SelLength = 0;
			bingo = false;
		  }

 //	ShowMessage(sentence);
		ResultLabel->Caption = findcout;
		ResultLabel->Refresh();
		sProgressBar1->Refresh();
		sentence = "";
		}

}
 /*
	if(findsimvol(RichEdit1->Text[i],"!. ?;,:")==false)
		{
		word += RichEdit1->Text[i];

		if(findsubs(word,Edit1->Text,i) != 0 && CheckBox1->Checked == false)
			{
			bingo = true;
			if(selend==false){
		 //	if(i-word.Length()+findsubs(word,Edit1->Text)-1 > 0)
		 //		{
			   //		if(RichEdit1->Text[i-word.Length()]=='\n')
			   //			RichEdit1->SelStart = i-word.Length()+findsubs(word,Edit1->Text)-3;
			   //		else
		 //				RichEdit1->SelStart = i-word.Length()+findsubs(word,Edit1->Text)-1;
		 //		}
		 //	 else
			   RichEdit1->SelStart = sword+findsubs(word,Edit1->Text,i)-1;

			RichEdit1->SelLength = Edit1->Text.Length();
			RichEdit1->SelAttributes->Color = clRed;
			RichEdit1->SelLength = 0;
			selend=true;
			}
			if(RichEdit1->Text[i+1]==' '){
				findcout++;
				selend=false;
				word = "";
			}
			}
		}
	else{
		if((word.LowerCase()).Compare(Edit1->Text.LowerCase()) == 0 && CheckBox1->Checked == true)
			{
			bingo = true;
			RichEdit1->SelStart = sword;
			RichEdit1->SelLength = Edit1->Text.Length();
			RichEdit1->SelAttributes->Color = clRed;
			RichEdit1->SelLength = 0;
			findcout++;
			}
		word = "";
		}

	if(findsimvol(RichEdit1->Text[i]," ")==true)
		sword=i;
 */

sProgressBar1->Visible = false;
if(findcout==0)
	MessageBox(NULL,"Совпадений не найдено","Результат",MB_OK|MB_ICONINFORMATION);

}
else
MessageBox(NULL,"Неверное слово для поиска\nОно должно быть без пробелов\nИ не содержать знаки !.?:,;","Ошибка",MB_OK|MB_ICONERROR);

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
 LabX->SetFocus();
  if(Mo->Text=="" || LabX->Text=="" || LabY->Text=="" || LabR->Text=="" ||
	 LabX1->Text=="" || LabY1->Text=="" || LabX2->Text=="" || LabY2->Text=="")
		MessageBox(NULL,"Нехватает данных","Ошибка",MB_OK|MB_ICONERROR);
  else
	if(LabX1->Text==LabX2->Text && LabY1->Text==LabY2->Text)
		MessageBox(NULL,"Концы отрезка совпадают","Ошибка",MB_OK|MB_ICONERROR);
  else
	if(LabR->Text.ToDouble()<0)
		MessageBox(NULL,"Радиус окружности не может быть отрицательным","Ошибка",MB_OK|MB_ICONERROR);
	else
  {
	if(LabR->Text.ToDouble()==0)
        MessageBox(NULL,"Окружность проецируеться в точку","Результат",MB_OK|MB_ICONINFORMATION);

	int peres, i, numX=0, numY=0, mb=Mo->Text.ToInt();;
	float iLabX=LabX->Text.ToDouble(),iLabY=LabY->Text.ToDouble(),iLabR=LabR->Text.ToDouble(),
			iLabY2=LabY2->Text.ToDouble()-iLabY,iLabY1=LabY1->Text.ToDouble()-iLabY,
			iLabX1=LabX1->Text.ToDouble()-iLabX,iLabX2=LabX2->Text.ToDouble()-iLabX;
	float x1,x2,y1,y2,d,d1,k,b,A,B,C,a1,b1,c1,R;
	bool ristrue=true;

  	A=iLabY2-iLabY1;
	B=iLabX1-iLabX2;
	C=iLabX2*iLabY1-iLabX1*iLabY2;

  // k=abs((iLabY1-iLabY2)/(iLabX1-iLabX2));
  // b=iLabY1-k*iLabX1;

  //	d = (pow((A*A*iLabY)-(B*(C+A*iLabX)),2))-((A*A+B*B)*(pow(C+(A*iLabX),2)+((A*A*B*B)-(A*A*iLabR*iLabR))));
  //	d = (pow((A*A+B*B),2)*iLabY1*iLabY1)-((2*(A*A*iLabY-B*(C+A*iLabX))*iLabY1)+(pow((C+A*iLabX),2)+A*A*B*B-A*A*iLabR*iLabR));
  //		d=(pow((2*k*b-2*iLabX-2*iLabY*k),2)-(4+4*k*k)*(b*b-iLabR*iLabR+iLabX*iLabX+iLabY*iLabY-2*iLabY*b));
  //	 ShowMessage(d);

	a1=(iLabY2+iLabY)-(iLabY1+iLabY);
	b1=(iLabX1+iLabX)-(iLabX2+iLabX);
	c1=((iLabX2+iLabX)*(iLabY1+iLabY))-((iLabX1+iLabX)*(iLabY2+iLabY));

	d1=(abs(a1*iLabX+b1*iLabY+c1)/sqrt(a1*a1+b1*b1));
  //  d1=abs(A*iLabX1+B*iLabY1+C)/sqrt(A*A+B*B);


// ShowMessage(B);
// ShowMessage(A);
// ShowMessage(C);
//   ShowMessage(C*C - iLabR*iLabR*(A*A+B*B));
//   ShowMessage(d1);
//  if(((iLabX==0 && iLabY!=0) || (iLabX!=0 && iLabY==0)) && d1!=iLabR)
//  C=0;
  R=sqrt(pow(0-iLabX,2)+pow(0-iLabY,2));
//  ShowMessage(R);
//  ShowMessage(d1+R);
//  ShowMessage(iLabR+R);
// ShowMessage(iLabR*iLabR*(A*A+B*B)+0.01);
// ShowMessage(C*C);

 if(d1+R<iLabR+R || d1+R==iLabR+R)
 {
   float x0 = -A*C/(A*A+B*B), y0 = -B*C/(A*A+B*B);
	  x1=x0+iLabX; y1=y0+iLabY;

		  if (C*C > iLabR*iLabR*(A*A+B*B)+0.01)
			peres=0;
		  else
		  if (abs (C*C - iLabR*iLabR*(A*A+B*B)) < 0.01)
			peres=1;
		  else
		  {
			double d = iLabR*iLabR - C*C/(A*A+B*B);
			double mult = sqrt (d / (A*A+B*B));
			x1 = x0 + B * mult + iLabX;
			x2 = x0 - B * mult + iLabX;
			y1 = y0 - A * mult + iLabY;
			y2 = y0 + A * mult + iLabY;
			peres=2;
		  }

		if((round(x1,1)>max(iLabX1+iLabX,iLabX2+iLabX) || round(x1,1)<min(iLabX1+iLabX,iLabX2+iLabX) || round(y1,1)>max(iLabY1+iLabY,iLabY2+iLabY) || round(y1,1)<min(iLabY1+iLabY,iLabY2+iLabY)) &&
		   (round(x2,1)>max(iLabX1+iLabX,iLabX2+iLabX) || round(x2,1)<min(iLabX1+iLabX,iLabX2+iLabX) || round(y2,1)>max(iLabY1+iLabY,iLabY2+iLabY) || round(y2,1)<min(iLabY1+iLabY,iLabY2+iLabY)))
		 peres=0;
		 else
		if((round(x2,1)>max(iLabX1+iLabX,iLabX2+iLabX) || round(x2,1)<min(iLabX1+iLabX,iLabX2+iLabX) || round(y2,1)>max(iLabY1+iLabY,iLabY2+iLabY) || round(y2,1)<min(iLabY1+iLabY,iLabY2+iLabY)))
		  peres = 1;
		 else
		if((round(x1,1)>max(iLabX1+iLabX,iLabX2+iLabX) || round(x1,1)<min(iLabX1+iLabX,iLabX2+iLabX) || round(y1,1)>max(iLabY1+iLabY,iLabY2+iLabY) || round(y1,1)<min(iLabY1+iLabY,iLabY2+iLabY)))
		 { x1=x2; y1=y2; peres = 1; }

}
else
 peres=0;

/* switch (peres) {
	case 0: if(MessageBox(NULL,"Нету точек пересечения, нарисовать график?","Результат",MB_YESNO|MB_ICONQUESTION)==IDYES)
			  ristrue=true;
	break;
	case 1: if(MessageBox(NULL,"Одна точка пересечения, нарисовать график?","Результат",MB_YESNO|MB_ICONQUESTION)==IDYES)
			  ristrue=true;
	break;
	case 2: if(MessageBox(NULL,"Две точки пересечения, нарисовать график?","Результат",MB_YESNO|MB_ICONQUESTION)==IDYES)
			  ristrue=true;
	break;
}    */


/*  k=abs((iLabY1-iLabY2)/(iLabX2-iLabX1));
  b=iLabY1-k*iLabX1;

  a1 = 1+k*k;
  b1 = -2*iLabX + 2*k*b - 2*k*iLabY;
  c1 = b*b + iLabX*iLabX - 2*b*iLabY + iLabY*iLabY - iLabR*iLabR;

  d = pow(b1,2)-4*a1*c1;

   x1=(-b1-sqrt(d))/(2*a1);
   x2=(-b1+sqrt(d))/(2*a1);

   y1=k*x1+b;
   y2=k*x2+b;
  */

/*	if(d1>iLabR)
	{
	 peres=0;
	 ShowMessage("Нет точек пресечения");
	}
	 else
	 {
	  if(d1==iLabR){
		peres=1;
		ShowMessage("Одна точка пересечения");
	  }
	  if(d1<iLabR)
	  {
		peres=2;
	   //    y1=pow(A,2)*iLabY-B*(C+A*iLabX)+sqrt(d);
	   //	 y1=pow(A,2)*iLabY-B*(C+A*iLabX)-sqrt(d);

	   //	 x1=(-(B/A)*y1)-(C/A);
	   //	 x2=(-(B/A)*y2)-(C/A);
		ShowMessage("Две точки пересечения в ["+(String)x1+","+(String)y1+"] и ["+(String)x2+","+(String)y2+"]" );

	  //	ShowMessage("Две точки пересечения");

	  //	PH=sqrt(iLabR*iLabR-d1*d1);

	  }
*/



if(ristrue){
  Image1->Visible=true;

  if(N9->Checked==false){
	Image1->Canvas->Pen->Color = sColorSelect4->ColorValue;
	Image1->Canvas->Pen->Width=5555;
	Image1->Picture->Graphic->SetSize(Image1->Width,Image1->Height);
//  Image1->Picture->Graphic->Width = Image1->Width;
//  Image1->Picture->Graphic->Height = Image1->Height;
	Image1->Canvas->MoveTo(0,0);
	Image1->Canvas->LineTo(Image1->Width,Image1->Height);
	allperes=0;
	}
  Image1->Canvas->Pen->Width=1;

	allperes+=peres;

	Image1->Canvas->Brush->Style = bsClear;
	// Image1->Canvas->Pen->Style = psClear;

	Image1->Canvas->Pen->Color = sColorSelect1->ColorValue;
   // Image1->Canvas->MoveTo(Image1->Width/2+LabX->Text.ToDouble(),Image1->Height+LabY->Text.ToDouble());
   //	Image1->Canvas->Ellipse(Image1->Width/2+LabX->Text.ToDouble()-LabR->Text.ToDouble(),Image1->Height+LabY->Text.ToDouble()-LabR->Text.ToDouble(),
   //							Image1->Width/2+LabX->Text.ToDouble()+LabR->Text.ToDouble(),Image1->Height+LabY->Text.ToDouble()+LabR->Text.ToDouble());
	  Image1->Canvas->Ellipse(Image1->Width/2+(LabX->Text.ToDouble()-LabR->Text.ToDouble())*mb,Image1->Height/2+(-LabY->Text.ToDouble()-LabR->Text.ToDouble())*mb,
								Image1->Width/2+(LabX->Text.ToDouble()+LabR->Text.ToDouble())*mb,Image1->Height/2+(-LabY->Text.ToDouble()+LabR->Text.ToDouble())*mb);


   Image1->Canvas->Pen->Color = sColorSelect2->ColorValue;
   Image1->Canvas->MoveTo(Image1->Width/2+LabX1->Text.ToDouble()*mb,Image1->Height/2-LabY1->Text.ToDouble()*mb);
   Image1->Canvas->LineTo(Image1->Width/2+LabX2->Text.ToDouble()*mb,Image1->Height/2-LabY2->Text.ToDouble()*mb);


  Image1->Canvas->Pen->Color = sColorSelect3->ColorValue;
  Image1->Canvas->Font->Color= sColorSelect3->ColorValue;


  if((8*((100*mb)/15))/100<9)
  Image1->Canvas->Font->Size=(8*((100*mb)/15))/100;
  else
  Image1->Canvas->Font->Size=9;
  // Image1->Canvas->Font->Style = Image1->Canvas->Font->Style << fsBold;
  Image1->Canvas->TextOut((Image1->Width/2)+4,(Image1->Height/2), "0");


  Image1->Canvas->MoveTo((Image1->Width/2),(Image1->Height/2));
  for(i=(Image1->Height/2)-mb;i<Image1->Height+mb*2;i=i+mb)
	{
	Image1->Canvas->LineTo((Image1->Width/2),i);
	Image1->Canvas->MoveTo((Image1->Width/2)-2,i);
	Image1->Canvas->LineTo((Image1->Width/2)+2,i);
	Image1->Canvas->MoveTo((Image1->Width/2),i);
	if(i<Image1->Height)
	numY++;
	}

  Image1->Canvas->MoveTo((Image1->Width/2),(Image1->Height/2));

  for(i=(Image1->Height/2)-mb;i>0-mb*2;i=i-mb)
	{
	Image1->Canvas->LineTo((Image1->Width/2),i);
	Image1->Canvas->MoveTo((Image1->Width/2)-2,i);
	Image1->Canvas->LineTo((Image1->Width/2)+2,i);
	Image1->Canvas->MoveTo((Image1->Width/2),i);
	}


  Image1->Canvas->MoveTo((Image1->Width/2),(Image1->Height/2));

  for(i=(Image1->Width/2)-mb;i>0-mb*2;i=i-mb)
	{
	Image1->Canvas->LineTo(i,Image1->Height/2);
	Image1->Canvas->MoveTo(i,Image1->Height/2-2);
	Image1->Canvas->LineTo(i,Image1->Height/2+2);
	Image1->Canvas->MoveTo(i,Image1->Height/2);
	if(i>0)
	numX++;
	}

  Image1->Canvas->MoveTo((Image1->Width/2),(Image1->Height/2));

  for(i=(Image1->Width/2)-mb;i<Image1->Width+mb*2;i=i+mb)
	{
	Image1->Canvas->LineTo(i,Image1->Height/2);
	Image1->Canvas->MoveTo(i,Image1->Height/2-2);
	Image1->Canvas->LineTo(i,Image1->Height/2+2);
	Image1->Canvas->MoveTo(i,Image1->Height/2);
	}

	numY = numY - 2;
	if(abs(LabX->Text.ToDouble())+LabR->Text.ToDouble()>numX || abs(LabY->Text.ToDouble())+LabR->Text.ToDouble()>numY ||
	 abs(LabX1->Text.ToDouble())>numX  || abs(LabY1->Text.ToDouble())>numY  || abs(LabX2->Text.ToDouble())>numX || abs(LabY2->Text.ToDouble())>numY )
	   MessageBox(NULL,"Внимание! Возможно некоторые точки выходят за область графика","Результат",MB_OK|MB_ICONINFORMATION);

	Image1->Canvas->MoveTo((Image1->Width/2),0);
	Image1->Canvas->LineTo((Image1->Width/2)+6,8);
	Image1->Canvas->MoveTo((Image1->Width/2),0);
	Image1->Canvas->LineTo((Image1->Width/2)-6,8);

	Image1->Canvas->MoveTo(Image1->Width,Image1->Height/2);
	Image1->Canvas->LineTo(Image1->Width-8,Image1->Height/2-6);
	Image1->Canvas->MoveTo(Image1->Width,Image1->Height/2);
	Image1->Canvas->LineTo(Image1->Width-8,Image1->Height/2+6);



	  switch (peres) {
		   case 0: // ShowMessage("Нет точек пересечения");
		   Label10->Caption=(String)allperes+" Точка(и/ек) пересечения";
			break;
		   case 1: //	ShowMessage("Одна точка пересечения в ["+(String)x11+";"+(String)y11+"]");
			 // ShowMessage("Одна точка пересечения");
			 Label10->Caption=(String)allperes+" Точка(и/ек) пересечения";

			  if(N20->Checked!=true){
			  Image1->Canvas->TextOut((Image1->Width/2)+5+(x1)*mb,
			  Image1->Height/2+3+(-y1)*mb, "["+String(round(x1,1))
			  +";"+String(round(y1,1))+"]");
			  }

			  Image1->Canvas->Pen->Color = clRed;
			  Image1->Canvas->Pen->Width = 4;

			 if(mb>50)
				R=0.03;
			  else
				R=0.05;

			  Image1->Canvas->Ellipse(Image1->Width/2+1+(x1+R)*mb,Image1->Height/2+1+(-y1+R)*mb,
									  Image1->Width/2+1+(x1-R)*mb,Image1->Height/2+1+(-y1-R)*mb);

			break;
		   case 2: //	ShowMessage("Две точки пересечения в ["+(String)x11+";"+(String)y11+"] и ["+(String)x22+";"+(String)y22+"]" );
			 // ShowMessage("Две точки пересечения");
			 Label10->Caption=(String)allperes+" Точка(и/ек) пересечения";

			  if(N20->Checked!=true){
			  Image1->Canvas->TextOut((Image1->Width/2)+5+(x1)*mb,
			  Image1->Height/2+3+(-y1)*mb, "["+String(round(x1,1))
			  +";"+String(round(y1,1))+"]");

			  Image1->Canvas->TextOut((Image1->Width/2)+5+(x2)*mb,
			  Image1->Height/2+3+(-y2)*mb, "["+String(round(x2,1))
			  +";"+String(round(y2,1))+"]");
			  }

			  if(mb>50)
				R=0.03;
			  else
				R=0.05;

			  Image1->Canvas->Pen->Color = clRed;
			  Image1->Canvas->Pen->Width = 4;

			  Image1->Canvas->Ellipse(Image1->Width/2+1+(x1+R)*mb,Image1->Height/2+1+(-y1+R)*mb,
									  Image1->Width/2+1+(x1-R)*mb,Image1->Height/2+1+(-y1-R)*mb);
			  Image1->Canvas->Ellipse(Image1->Width/2+1+(x2+R)*mb,Image1->Height/2+1+(-y2+R)*mb,
									  Image1->Width/2+1+(x2-R)*mb,Image1->Height/2+1+(-y2-R)*mb);

			break;
	  }
	}
	else
	  Image1->Visible=false;
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::MoKeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8)) {}

else
 {
 Key = 0;
 Beep();
 }

}
//---------------------------------------------------------------------------



void __fastcall TForm1::LabXKeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8) || (Key <= '-') || (Key <= ',')) {}

else
 {
 Key = 0;
 Beep();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabYKeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8) || (Key <= '-') || (Key <= ',') ) {}

else
 {
 Key = 0;
 Beep();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabRKeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8) || (Key == ',')) {}

else
 {
 Key = 0;
 Beep();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabX1KeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8) || (Key <= '-') || (Key <= ',')) {}

else
 {
 Key = 0;
 Beep();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabY1KeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8) || (Key <= '-') || (Key <= ',')) {}

else
 {
 Key = 0;
 Beep();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabX2KeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8) || (Key <= '-') || (Key <= ',')) {}

else
 {
 Key = 0;
 Beep();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabY2KeyPress(TObject *Sender, wchar_t &Key)
{
if ((Key >= '0') && (Key <= '9') || (Key == 8) || (Key <= '-') || (Key <= ',')) {}

else
 {
 Key = 0;
 Beep();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MoExit(TObject *Sender)
{
if(Mo->Text.ToInt()>100)
  Mo->Text = 100;
if(Mo->Text.ToInt()<10)
  Mo->Text = 10;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
		  bool &Resize)
{
  if(NewWidth<465 || NewHeight<357)
   Resize=false;
  else
   Resize=true;

}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormResize(TObject *Sender)
{
 RichEdit1->Width=435+(Form1->Width-465);
 RichEdit1->Height=213+(Form1->Height-357);
 Image1->Width=264+(Form1->Width-465);
 Image1->Height=236+(Form1->Height-357);
 sProgressBar1->Top = 253+(Form1->Height-357);
 sProgressBar1->Width = 435+(Form1->Width-465);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sColorSelect1Change(TObject *Sender)
{
if(Image1->Visible == true)
Button2->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sColorSelect2Change(TObject *Sender)
{
if(Image1->Visible == true)
Button2->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sColorSelect3Change(TObject *Sender)
{
if(Image1->Visible == true)
Button2->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sColorSelect4Change(TObject *Sender)
{
if(Image1->Visible == true)
Button2->Click();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::setskin(short index)
{
	sSkinManager1->Active = true;

	N10->Checked=false;
	N11->Checked=false;
	N12->Checked=false;
	N13->Checked=false;
	N14->Checked=false;
	N15->Checked=false;
	N16->Checked=false;
	N17->Checked=false;
	N18->Checked=false;

	switch(index){
	case 0:
	 sSkinManager1->Active=false;

	 sLabel1->Font->Color = clBlack;
	 sLabel2->Font->Color = clBlack;
	 ResultLabel->Font->Color = clBlack;
	 sLabel3->Font->Color = clBlack;
	 sLabel4->Font->Color = clBlack;
	 sLabel5->Font->Color = clBlack;
	 sLabel6->Font->Color = clBlack;
	 sLabel7->Font->Color = clBlack;
	 sLabel8->Font->Color = clBlack;
	 Label10->Font->Color = clBlack;
	 Label5->Font->Color = clBlack;
	 sLabel9->Font->Color = clBlack;
	 sLabel10->Font->Color = clBlack;
	 sLabel11->Font->Color = clBlack;
	 sLabel12->Font->Color = clBlack;
	 sLabel13->Font->Color = clBlack;
	 LabX2->Color = clWhite;
	 LabY2->Color = clWhite;
	 LabY2->Font->Color = clBlack;
	 LabX2->Font->Color = clBlack;

	 N10->Checked = true;
	 break;
	case 1: sSkinManager1->SkinName="Office2007 Black (internal)"; N11->Checked = true; break;
	case 2: sSkinManager1->SkinName="Calcium (internal)"; N12->Checked = true; break;
	case 3: sSkinManager1->SkinName="FalloutStyle (internal)"; N13->Checked = true; break;
	case 4: sSkinManager1->SkinName="HeroesStyle (internal)"; N14->Checked = true; break;
	case 5: sSkinManager1->SkinName="MacOS2 (internal)"; N15->Checked = true; break;
	case 6: sSkinManager1->SkinName="Terminal4bit (internal)"; N16->Checked = true; break;
	case 7: sSkinManager1->SkinName="WMP11 (internal)"; N17->Checked = true; break;
	case 8: sSkinManager1->SkinName="Nautilus (internal)"; N18->Checked = true; break;
		default: sSkinManager1->SkinName="Nautilus (internal)"; N18->Checked = true; break;
	}

	  RichEdit1->SelStart  = 0;
	  RichEdit1->SelLength = RichEdit1->Text.Length();
	  if(sSkinManager1->Active == true)
		RichEdit1->SelAttributes->Color = sSkinManager1->GetActiveEditFontColor();
	  else
		RichEdit1->SelAttributes->Color = clBlack;
	  RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style.Clear();

	Form1->Hide();
	Form1->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N10Click(TObject *Sender)
{
index=0;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
index=1;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N12Click(TObject *Sender)
{
index=2;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
index=3;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N14Click(TObject *Sender)
{
index=4;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N15Click(TObject *Sender)
{
index=5;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N16Click(TObject *Sender)
{
index=6;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N17Click(TObject *Sender)
{
index=7;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N18Click(TObject *Sender)
{
index=8;
setskin(index);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+"settings.ini");
Ini->WriteInteger("Options","SkinIndex",index);
Ini->WriteBool("N1","SentenceBold",N8->Checked);
Ini->WriteBool("N2","EveryClear",N9->Checked);
Ini->WriteBool("N2","ShowCorPer",N20->Checked);
delete(Ini);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
if(FileExists(ExtractFilePath(Application->ExeName)+"settings.ini"))
	{
	TIniFile *ini = new TIniFile("./settings.ini");
	index = ini->ReadInteger("Options","SkinIndex",NULL);
	N8->Checked =  ini->ReadBool("N1","SentenceBold",NULL);
	N9->Checked =  ini->ReadBool("N2","EveryClear",NULL);
	N20->Checked =  ini->ReadBool("N2","ShowCorPer",NULL);
	delete(ini);
	}
else
	index = 8;
setskin(index);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
if(WinExec(AnsiString(ExtractFilePath(Application->ExeName)+"help.html").c_str() ,0)==ERROR_FILE_NOT_FOUND)
 MessageBox(NULL,"Инструкция не найдена","Ошибка",MB_OK|MB_ICONERROR);
else
if(WinExec(AnsiString(ExtractFilePath(Application->ExeName)+"help.html").c_str() ,0)==0)
 MessageBox(NULL,"The system is out of memory or resources","Ошибка",MB_OK|MB_ICONERROR);

 ShellExecute(NULL, NULL, AnsiString(ExtractFilePath(Application->ExeName)+"help.html").c_str(), NULL, NULL, SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::N8Click(TObject *Sender)
{
 if(N8->Checked==false)
	N8->Checked = true;
 else
    N8->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
 if(N9->Checked==false)
	N9->Checked = true;
 else
	N9->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N20Click(TObject *Sender)
{
 if(N20->Checked==false)
	N20->Checked = true;
 else
	N20->Checked=false;
}
//---------------------------------------------------------------------------



