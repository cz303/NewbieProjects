program Project1;

uses
  Vcl.Forms,
  GeneralForm in 'GeneralForm.pas' {Form1},
  ConnectForm in 'ConnectForm.pas' {Form2},
  TokenU in 'TokenU.pas',
  uCEFApplication,
  WinApi.Windows;

{$R *.res}

begin
 GlobalCEFApp := TCefApplication.Create;

  if GlobalCEFApp.StartMainProcess then
    begin
      Application.Initialize;
      Application.MainFormOnTaskbar := True;
      Application.CreateForm(TForm1, Form1);
      Application.Run;
    end;

  GlobalCEFApp.Free;
end.
