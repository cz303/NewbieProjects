unit ConnectForm;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.OleCtrls, SHDocVw, Vcl.StdCtrls, StrUtils, MSHTML, Data.DBXJSON,
  IdBaseComponent, IdComponent, IdTCPConnection, IdTCPClient, IdHTTP, System.IniFiles, TokenU,
  IdIOHandler, IdIOHandlerSocket, IdIOHandlerStack, IdSSL, IdSSLOpenSSL,
  Vcl.Buttons, uCEFWindowParent, uCEFChromiumWindow, Vcl.ExtCtrls, uCEFChromium,
  uCEFInterfaces, uCEFApplication, uCEFTypes, uCEFConstants, uCEFStringVisitor, uCEFCookieManager;

type
  TForm2 = class(TForm)
    Memo1: TMemo;
    Edit1: TEdit;
    Button2: TButton;
    IdHTTP1: TIdHTTP;
    Button3: TButton;
    IdSSLIOHandlerSocketOpenSSL1: TIdSSLIOHandlerSocketOpenSSL;
    Edit2: TEdit;
    Edit3: TEdit;
    SpeedButton1: TSpeedButton;
    ChromiumWindowLogin: TChromium;
    CEFWindowParent1: TCEFWindowParent;
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Edit1Change(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure Edit3Change(Sender: TObject);
    procedure Edit2Change(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ChromiumWindowLoginAddressChange(Sender: TObject;
      const browser: ICefBrowser; const frame: ICefFrame; const url: ustring);
    procedure ChromiumWindowLoginAfterCreated(Sender: TObject;
      const browser: ICefBrowser);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure GetSokectToken();
  end;



var
  Form2: TForm2;
  JSONObject: TJSONObject;
  PostData:TStringList;
  ResiveData:TStringList;
  Resp_Json: string;
  TokenExpire: integer;

implementation

{$R *.dfm}

//  Кнопка для получения кода для запроса токенов
procedure TForm2.Button2Click(Sender: TObject);
var
  CookieManager: ICefCookieManager;
  CookiesPath  : String;
begin
        CookiesPath := ExtractFilePath(Application.ExeName) + 'Cookies';
        CookieManager := TCefCookieManagerRef.Global(nil);
        CookieManager.SetStoragePath(CookiesPath,false,nil);

        Edit1.Text := '';
        Button2.Enabled := false;
        Button3.Enabled := false;
        ChromiumWindowLogin.LoadURL('https://www.streamlabs.com/api/v1.0/authorize?client_id=XXXXX&redirect_uri=http://127.0.0.1:80/OAuth.php&response_type=code&scope=donations.read+donations.create+socket.token+alerts.write');
end;

// Получение сокет токена через GET
procedure Tform2.GetSokectToken();
begin
            try
                IdHTTP1.Request.UserAgent:='Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36';
                IdHTTP1.Request.Accept := 'application/json, text/javascript, */*; q=0.01';
                IdHTTP1.Request.ContentType := 'application/x-www-form-urlencoded; charset=UTF-8';
                IdHTTP1.Request.CharSet:='utf-8';
                Resp_Json:=IdHTTP1.Get('https://streamlabs.com/api/v1.0/socket/token?access_token='+Token.Token);
            finally
                Memo1.Lines.Add(IdHTTP1.ResponseText);

            end;
               if IdHTTP1.ResponseText = 'HTTP/1.1 200 OK' then
                begin
                  JSONObject := TJSONObject.ParseJSONValue(Resp_Json) as TJSONObject;

                  if Assigned(JSONObject) then
                    begin
                      Token.socket_token := JSONObject.Get('socket_token').JsonValue.Value;
                      Memo1.Lines.Add('Socket токен получен');
                      Memo1.Lines.Add(Resp_Json);
                    end
                  else
                      ShowMessage('ќшибка парсинга JSON-данных');
                end
                else
                    Memo1.Lines.Add('ќшибка запроса токена');
end;

// Получение токенов
procedure TForm2.Button3Click(Sender: TObject);
begin
            PostData:=TStringList.Create;
            PostData.Clear;
            PostData.Add('grant_type=authorization_code');
            PostData.Add('client_id=XXXXX');
            PostData.Add('client_secret=XXXXX');
            PostData.Add('redirect_uri=http://127.0.0.1:80/OAuth.php');
            PostData.Add('code='+Edit1.Text);

            try
                IdHTTP1.Request.UserAgent:='Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36';
                IdHTTP1.Request.Accept := 'application/json, text/javascript, */*; q=0.01';
                IdHTTP1.Request.ContentType := 'application/x-www-form-urlencoded; charset=UTF-8';
                IdHTTP1.Request.CharSet:='utf-8';
                Resp_Json:=IdHTTP1.Post('https://streamlabs.com/api/v1.0/token',PostData);
            finally
                Memo1.Lines.Add(IdHTTP1.ResponseText);
            end;
               if IdHTTP1.ResponseText = 'HTTP/1.1 200 OK' then
                begin
                  JSONObject := TJSONObject.ParseJSONValue(Resp_Json) as TJSONObject;

                  if Assigned(JSONObject) then
                    begin
                       Edit2.Text := JSONObject.Get('access_token').JsonValue.Value;
                       Edit3.Text := JSONObject.Get('refresh_token').JsonValue.Value;
                       TokenExpire := DateTimeToUnix(now)+
                                StrToInt(JSONObject.Get('expires_in').JsonValue.Value);
                       Memo1.Lines.Add('Expire: '+IntToStr(TokenExpire)+
                                ' (remaining: '+IntToStr(TokenExpire-DateTimeToUnix(now))+' sec)');
                       Button2.Enabled := false;
                       Button3.Enabled := false;

                      Token.Code := Edit1.Text;
                      Token.Token := Edit2.Text;
                      Token.Refresh_Token := Edit3.Text;
                      Token.TokenExpire := TokenExpire;

                      Memo1.Lines.Add('Access и Refresh токен получен');
                      GetSokectToken();
                    end
                  else
                      ShowMessage('ќшибка парсинга JSON-данных');
                end
                else
                    Memo1.Lines.Add('ќшибка запроса токена');
end;

// Скопировать код в текстовое поле когда он будет доступен
procedure TForm2.ChromiumWindowLoginAddressChange(Sender: TObject;
  const browser: ICefBrowser; const frame: ICefFrame; const url: ustring);
begin
     if ContainsText(url,'OAuth.php?code=') then
          begin
            Edit1.Text := Copy( url,Pos('=',url)+1,Length(url)-Pos('=',url) );
            Button2.Enabled := false;
            Button3.Enabled := true;
          end;
end;

procedure TForm2.ChromiumWindowLoginAfterCreated(Sender: TObject;
  const browser: ICefBrowser);
begin
// Chrome loaded
end;

procedure TForm2.Edit1Change(Sender: TObject);
begin
        if Edit1.Text <> '' then
           begin
             Button3.Enabled := true;
             SpeedButton1.Enabled := false;
           end;

        if Edit1.Text = '' then
           begin
             Button2.Enabled := true;
             Button3.Enabled := false;
             SpeedButton1.Enabled := false;
           end;
end;

procedure TForm2.Edit2Change(Sender: TObject);
begin
        if Edit2.Text <> '' then
           begin
              Button3.Enabled := false;
           end;

        if Edit2.Text = '' then
           begin
              Button3.Enabled := true;
           end;
end;

procedure TForm2.Edit3Change(Sender: TObject);
begin
        if Edit3.Text <> '' then
           begin
             SpeedButton1.Enabled := true;
           end;

        if Edit3.Text = '' then
           begin
             SpeedButton1.Enabled := false;
           end;
end;

procedure TForm2.FormCreate(Sender: TObject);
begin
  Edit1.Text := Token.Code;
  Edit2.Text := Token.Token;
  Edit3.Text := Token.Refresh_Token;
  TokenExpire := Token.TokenExpire;

  if Edit1.Text = '' then
     begin
       Button2.Enabled := true;
       Button3.Enabled := false;
       SpeedButton1.Enabled := false;
     end;
end;

procedure TForm2.FormShow(Sender: TObject);
begin
   ChromiumWindowLogin.CreateBrowser(CEFWindowParent1, '');
end;

// Обновить токены с помощью рефреш-токена
procedure TForm2.SpeedButton1Click(Sender: TObject);
begin
            PostData:=TStringList.Create;
            PostData.Clear;
            PostData.Add('grant_type=refresh_token');
            PostData.Add('client_id=XXXXX');
            PostData.Add('client_secret=XXXXX');
            PostData.Add('redirect_uri=http://127.0.0.1:80/OAuth.php');
            PostData.Add('refresh_token='+Token.Refresh_Token);

            try
                IdHTTP1.Request.UserAgent:='Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36';
                IdHTTP1.Request.Accept := 'application/json, text/javascript, */*; q=0.01';
                IdHTTP1.Request.ContentType := 'application/x-www-form-urlencoded; charset=UTF-8';
                IdHTTP1.Request.CharSet:='utf-8';
                Resp_Json:=IdHTTP1.Post('https://streamlabs.com/api/v1.0/token',PostData);
            finally
                Memo1.Lines.Add(IdHTTP1.ResponseText);
                Memo1.Lines.Add(Resp_Json);
            end;
               if IdHTTP1.ResponseText = 'HTTP/1.1 200 OK' then
                begin
                  JSONObject := TJSONObject.ParseJSONValue(Resp_Json) as TJSONObject;

                  if Assigned(JSONObject) then
                    begin
                       Edit2.Text := JSONObject.Get('access_token').JsonValue.Value;
                       Edit3.Text := JSONObject.Get('refresh_token').JsonValue.Value;
                       TokenExpire := DateTimeToUnix(now)+
                                StrToInt(JSONObject.Get('expires_in').JsonValue.Value);
                       Memo1.Lines.Add('Expire: '+IntToStr(TokenExpire)+
                                ' (remaining: '+IntToStr(TokenExpire-DateTimeToUnix(now))+' sec)');
                       Button2.Enabled := false;
                       Button3.Enabled := false;

                      Token.Code := Edit1.Text;
                      Token.Token := Edit2.Text;
                      Token.Refresh_Token := Edit3.Text;
                      Token.TokenExpire := TokenExpire;
                    end
                  else
                      ShowMessage('ќшибка парсинга JSON-данных');
                end
                else
                    Memo1.Lines.Add('ќшибка запроса обновлени€ токена');
end;

end.
