unit GeneralForm;


interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ComCtrls, Vcl.StdCtrls, ConnectForm, TokenU, Data.DBXJSON,
  IdBaseComponent, IdComponent, IdTCPConnection, IdTCPClient, IdHTTP, System.IniFiles, IdSSL, IdSSLOpenSSL, ShellApi,
  Vcl.ExtCtrls, IdIOHandler, IdIOHandlerSocket, IdIOHandlerStack,
  Web.Win.Sockets, Data.DB, Datasnap.DBClient, Datasnap.Win.MConnect,
  Datasnap.Win.SConnect, Vcl.OleCtrls, SHDocVw, uCEFWindowParent, uCEFChromiumWindow, uCEFChromium,
  uCEFInterfaces, uCEFApplication, uCEFTypes, uCEFConstants;


type
  TForm1 = class(TForm)
    PageControl: TPageControl;
    TabSheet2: TTabSheet;
    TabSheet3: TTabSheet;
    log: TMemo;
    DissconectBt: TButton;
    ConnectBt: TButton;
    IdHTTP1: TIdHTTP;
    Timer1: TTimer;
    PostDonation: TButton;
    ButtonRefresh: TButton;
    IdSSLIOHandlerSocketOpenSSL1: TIdSSLIOHandlerSocketOpenSSL;
    CheckBoxAutoUp: TCheckBox;
    TestLog: TMemo;
    GetDonation: TButton;
    EditName: TEdit;
    EditAmount: TEdit;
    EditMessage: TEdit;
    TestFollow: TButton;
    ButtonOpenBrowser: TButton;
    ReloadEvents: TButton;
    ChromiumWindow1: TChromiumWindow;
    procedure ConnectBtClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure DissconectBtClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure ButtonRefreshClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure CheckBoxAutoUpClick(Sender: TObject);
    procedure PostDonationClick(Sender: TObject);
    procedure GetDonationClick(Sender: TObject);
    procedure TestFollowClick(Sender: TObject);
    procedure ButtonOpenBrowserClick(Sender: TObject);
    procedure ReloadEventsClick(Sender: TObject);
    procedure FormShow(Sender: TObject);

  private
    { Private declarations }
        JsonObj: TJSONObject;
        Responce: string;
        Ini: Tinifile;
        procedure CaptionChange();
  public
    { Public declarations }

  end;


var
  Form1: TForm1;
  ConnectForm: TForm2;

implementation

{$R *.dfm}

procedure TForm1.ConnectBtClick(Sender: TObject);
begin
        if Token.Token = '' then
          begin
                  if  Assigned(ConnectForm) = False then
                  begin
                    ConnectForm := TForm2.Create(self);
                  end;

                  try
                    ConnectForm.ShowModal;
                  finally
                    FreeAndNil(ConnectForm);
                    CaptionChange();
                  end;
          end
        else
          begin
                  ShowMessage('Токен уже есть');
          end;

end;

procedure TForm1.DissconectBtClick(Sender: TObject);
begin
        Token.Code := '';
        Token.Token := '';
        Token.Refresh_Token := '';
        Token.socket_token := '';
        Token.TokenExpire := 0;

        ConnectBt.Enabled := true;
        DissconectBt.Enabled := false;
        ButtonRefresh.Enabled := false;
end;

procedure TForm1.FormActivate(Sender: TObject);
begin
        CaptionChange();
end;

//-------------------------------------------
// Сохранение и загрузка из INI-файла
procedure TForm1.FormCreate(Sender: TObject);
begin

        Ini:=TiniFile.Create(extractfilepath(paramstr(0))+'auth.ini');
        Token.Code := Ini.ReadString('API','Code','');
        Token.Token := Ini.ReadString('API','access_token','');
        Token.Refresh_Token := Ini.ReadString('API','refresh_token','');
        Token.TokenExpire := Ini.ReadInteger('API','expire',0);
        CheckBoxAutoUp.Checked := Ini.ReadBool('Self','AutoRefresh',false);
        Token.socket_token :=  Ini.ReadString('API','socket_token','');
        Ini.Free;

        if Token.Refresh_Token <> '' then
           begin
             Timer1.Enabled := true;
             ConnectBt.Enabled := false;
             DissconectBt.Enabled := true;
           end;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  Ini:=TiniFile.Create(extractfilepath(paramstr(0))+'auth.ini');
  Ini.WriteString('API','Code', Token.Code);
  Ini.WriteString('API','access_token', Token.Token);
  Ini.WriteString('API','refresh_token', Token.Refresh_Token);
  Ini.WriteInteger('API','expire', Token.TokenExpire);
  Ini.WriteBool('Self','AutoRefresh', CheckBoxAutoUp.Checked);
  Ini.WriteString('API','socket_token',Token.socket_token);
  Ini.Free;
end;
//-------------------------------------------


procedure TForm1.FormShow(Sender: TObject);
begin
   ChromiumWindow1.CreateBrowser;
end;

// Получение информации о донатах, запрашиваеться 1 последняя запись
procedure TForm1.GetDonationClick(Sender: TObject);
var
  JsonArray: TJSONArray;
begin
            try
                IdHTTP1.Request.UserAgent:='Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36';
                IdHTTP1.Request.Accept := 'application/json, text/javascript, */*; q=0.01';
                IdHTTP1.Request.ContentType := 'application/x-www-form-urlencoded; charset=UTF-8';
                IdHTTP1.Request.CharSet:='utf-8';
                Resp_Json:=IdHTTP1.Get('https://streamlabs.com/api/v1.0/donations?access_token='+Token.Token+'&limit=1');
            finally
                // TestLog.Lines.Add(IdHTTP1.ResponseText);

            end;
               if IdHTTP1.ResponseText = 'HTTP/1.1 200 OK' then
                begin
                  JSONObject := TJSONObject.ParseJSONValue(Resp_Json) as TJSONObject;
                  JsonArray := JSONObject.Get('data').JsonValue as TJSONArray;

                  if Assigned(JSONObject) then
                    begin
                      TestLog.Lines.Add('Name:'+(JsonArray.Get(0) as TJSONObject).Get('name').JsonValue.Value
                      +' Amount:'+Format('%.2f', [
                          StrToFloat(StringReplace(
                              (JsonArray.Get(0) as TJSONObject).Get('amount').JsonValue.Value
                              ,'.',',',[rfReplaceAll, rfIgnoreCase]))
                      ])
                      +LowerCase((JsonArray.Get(0) as TJSONObject).Get('currency').JsonValue.Value)
                      +' Msg:"'+(JsonArray.Get(0) as TJSONObject).Get('message').JsonValue.Value+'"');
                    end
                  else
                      ShowMessage('Ошибка парсинга JSON-данных');
                end
                else
                    TestLog.Lines.Add('Ошибка запроса донатов');
end;

// Таймер меняющий надпись главного окна и если истекло время - то обновляет токен
procedure TForm1.Timer1Timer(Sender: TObject);
begin
  CaptionChange();
end;

// Добавление доната
procedure TForm1.PostDonationClick(Sender: TObject);
begin
        PostData:=TStringList.Create;
        PostData.Clear;
        PostData.Add('access_token='+Token.Token);
        PostData.Add('name='+EditName.Text);
        PostData.Add('message='+EditMessage.Text);
        PostData.Add('identifier=777553');
        PostData.Add('amount='+EditAmount.Text);
        PostData.Add('currency=RUB');

        try
          try
              IdHTTP1.Request.UserAgent:='Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36';
              IdHTTP1.Request.Accept := 'application/json, text/javascript, */*; q=0.01';
              IdHTTP1.Request.ContentType := 'application/x-www-form-urlencoded; charset=UTF-8';
              IdHTTP1.Request.CharSet:='utf-8';
              Responce:=IdHTTP1.Post('https://streamlabs.com/api/v1.0/donations',PostData);
          except
              TestLog.Lines.Add('Ошибка при POST запросе');
          end;
        finally
           TestLog.Lines.Add(IdHTTP1.ResponseText);
        end;

           if IdHTTP1.ResponseText = 'HTTP/1.1 200 OK' then
            begin
              JsonObj := TJSONObject.ParseJSONValue(Responce) as TJSONObject;

              if Assigned(JsonObj) then
                begin
                   TestLog.Lines.Add('donation id: '+StringReplace(JsonObj.Get('donation_id').JsonValue.ToString,'"','',[rfReplaceAll, rfIgnoreCase]));
                end
              else
                  ShowMessage('Ошибка парсинга JSON-данных');
            end
            else
                TestLog.Lines.Add('Ошибка запроса добавления информации о донате');
end;

// Загружает в браузер страницу с socketIO клиентом
procedure TForm1.ReloadEventsClick(Sender: TObject);
begin
          ChromiumWindow1.LoadURL('http://127.0.0.1:80/socket.html?token='+Token.socket_token);
end;

// Вызов тестового алерта
procedure TForm1.TestFollowClick(Sender: TObject);
begin
        PostData:=TStringList.Create;
        PostData.Clear;
        PostData.Add('access_token='+Token.Token);
        PostData.Add('type=follow');

        try
          try
              IdHTTP1.Request.UserAgent:='Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36';
              IdHTTP1.Request.Accept := 'application/json, text/javascript, */*; q=0.01';
              IdHTTP1.Request.ContentType := 'application/x-www-form-urlencoded; charset=UTF-8';
              IdHTTP1.Request.CharSet:='utf-8';
              Responce:=IdHTTP1.Post('https://streamlabs.com/api/v1.0/alerts/send_test_alert',PostData);
          except
              TestLog.Lines.Add('Ошибка при POST запросе');
          end;
        finally
           TestLog.Lines.Add(IdHTTP1.ResponseText);
        end;

           if IdHTTP1.ResponseText = 'HTTP/1.1 200 OK' then
            begin
              JsonObj := TJSONObject.ParseJSONValue(Responce) as TJSONObject;

              if Assigned(JsonObj) then
                begin
                   TestLog.Lines.Add('test alert success: '+StringReplace(JsonObj.Get('success').JsonValue.ToString,'"','',[rfReplaceAll, rfIgnoreCase]));
                end
              else
                  ShowMessage('Ошибка парсинга JSON-данных');
            end
            else
                TestLog.Lines.Add('Ошибка запроса');
end;

procedure TForm1.ButtonOpenBrowserClick(Sender: TObject);
begin
        ShellExecute(self.WindowHandle,'open','https://streamlabs.com/alert-box/v3/50D481FCB119A2FCFE6A',nil,nil, SW_SHOWNORMAL);
end;

// Рефреш токенов
procedure TForm1.ButtonRefreshClick(Sender: TObject);
begin
    Form1.Caption := 'StreamLabs API  | '+'Access token: Refreshing...'+' | Expire in: ---';
    log.Lines.Add('Refreshing Tokens...');

        PostData:=TStringList.Create;
        PostData.Clear;
        PostData.Add('grant_type=refresh_token');
        PostData.Add('client_id=XXXXX');
        PostData.Add('client_secret=XXXXX');
        PostData.Add('redirect_uri=http://127.0.0.1:80/OAuth.php');
        PostData.Add('refresh_token='+Token.Refresh_Token);

        try
          try
              IdHTTP1.Request.UserAgent:='Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36';
              IdHTTP1.Request.Accept := 'application/json, text/javascript, */*; q=0.01';
              IdHTTP1.Request.ContentType := 'application/x-www-form-urlencoded; charset=UTF-8';
              IdHTTP1.Request.CharSet:='utf-8';
              Responce:=IdHTTP1.Post('https://streamlabs.com/api/v1.0/token',PostData);
          except
              log.Lines.Add('Ошибка при запросе данных');
          end;
        finally
             log.Lines.Add(IdHTTP1.ResponseText);
        end;

           if IdHTTP1.ResponseText = 'HTTP/1.1 200 OK' then
            begin
              JsonObj := TJSONObject.ParseJSONValue(Responce) as TJSONObject;

              if Assigned(JsonObj) then
                begin
                   Token.Token := JsonObj.Get('access_token').JsonValue.Value;
                   Token.Refresh_Token := JsonObj.Get('refresh_token').JsonValue.Value;
                   Token.TokenExpire := DateTimeToUnix(now)+
                            StrToInt(JsonObj.Get('expires_in').JsonValue.Value);
                   log.Lines.Add('The token was obtaine. Expire in: '+IntToStr(Token.TokenExpire-DateTimeToUnix(now))+' sec');
                   end
              else
                  ShowMessage('Ошибка парсинга JSON-данных');
            end
            else
                log.Lines.Add('Ошибка запроса обновления токена');
end;

procedure TForm1.CaptionChange();
begin
         if (Token.TokenExpire-DateTimeToUnix(now)) < 0 then
           begin
             Form1.Caption := 'StreamLabs API  | '+'Access token: ---'+' | Expire in: ---';
             if Token.Refresh_Token = '' then
             begin
               ConnectBt.Enabled := true;
               DissconectBt.Enabled := false;
               Timer1.Enabled := false;
               Form1.CheckBoxAutoUpClick(Self.CheckBoxAutoUp);
             end
              else
               begin
                  if (Token.Refresh_Token <> '') and CheckBoxAutoUp.Checked then
                  begin
                      Timer1.Enabled := false;
                      Form1.ButtonRefreshClick(Self.ButtonRefresh);
                   end;
               end;
           end
         else
           begin
             Timer1.Enabled := true;
             Form1.Caption := 'StreamLabs API  | '+'Access token:OK'+' | Expire in:'+IntToStr(Token.TokenExpire-DateTimeToUnix(now))+' sec';
             ConnectBt.Enabled := false;
             Form1.CheckBoxAutoUpClick(Self.CheckBoxAutoUp);

           end;
end;

procedure TForm1.CheckBoxAutoUpClick(Sender: TObject);
begin
        if CheckBoxAutoUp.Checked then
           begin
                ButtonRefresh.Enabled := false;
           end
        else
            begin
               if Token.Refresh_Token <> '' then
                        ButtonRefresh.Enabled := true;
            end;

end;

end.
