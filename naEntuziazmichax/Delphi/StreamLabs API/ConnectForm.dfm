object Form2: TForm2
  Left = 0
  Top = 0
  Anchors = []
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Login'
  ClientHeight = 653
  ClientWidth = 713
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 447
    Top = 475
    Width = 258
    Height = 22
    Caption = 'Renew token'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Font.Quality = fqClearTypeNatural
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 504
    Width = 697
    Height = 131
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 8
    Top = 421
    Width = 433
    Height = 21
    Enabled = False
    TabOrder = 1
    OnChange = Edit1Change
  end
  object Button2: TButton
    Left = 447
    Top = 421
    Width = 258
    Height = 21
    Caption = 'Get Code'
    Enabled = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 447
    Top = 448
    Width = 258
    Height = 21
    Caption = 'Get Token'
    Enabled = False
    TabOrder = 3
    OnClick = Button3Click
  end
  object Edit2: TEdit
    Left = 8
    Top = 448
    Width = 433
    Height = 21
    Enabled = False
    ReadOnly = True
    TabOrder = 4
    OnChange = Edit2Change
  end
  object Edit3: TEdit
    Left = 8
    Top = 475
    Width = 433
    Height = 21
    Enabled = False
    ReadOnly = True
    TabOrder = 5
    OnChange = Edit3Change
  end
  object CEFWindowParent1: TCEFWindowParent
    Left = 0
    Top = 0
    Width = 713
    Height = 415
    Align = alTop
    TabOrder = 6
  end
  object IdHTTP1: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL1
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 104
    Top = 272
  end
  object IdSSLIOHandlerSocketOpenSSL1: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvTLSv1_2
    SSLOptions.SSLVersions = [sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 104
    Top = 320
  end
  object ChromiumWindowLogin: TChromium
    OnAddressChange = ChromiumWindowLoginAddressChange
    OnAfterCreated = ChromiumWindowLoginAfterCreated
    Left = 104
    Top = 368
  end
end
