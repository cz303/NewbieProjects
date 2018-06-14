object Form1: TForm1
  Left = 80
  Top = 187
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'StreamLabs API'
  ClientHeight = 401
  ClientWidth = 534
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 534
    Height = 401
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 0
    object TabSheet2: TTabSheet
      Caption = 'Test'
      ImageIndex = 1
      object PostDonation: TButton
        Left = 318
        Top = 3
        Width = 51
        Height = 47
        Caption = 'Add Donation'
        TabOrder = 0
        WordWrap = True
        OnClick = PostDonationClick
      end
      object TestLog: TMemo
        Left = 0
        Top = 248
        Width = 526
        Height = 125
        Align = alBottom
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 1
      end
      object GetDonation: TButton
        Left = 3
        Top = 3
        Width = 62
        Height = 47
        Caption = 'Get Last Donation'
        TabOrder = 2
        WordWrap = True
        OnClick = GetDonationClick
      end
      object EditName: TEdit
        Left = 143
        Top = 2
        Width = 121
        Height = 21
        TabOrder = 3
        Text = 'TestName'
      end
      object EditAmount: TEdit
        Left = 270
        Top = 3
        Width = 42
        Height = 21
        NumbersOnly = True
        TabOrder = 4
        Text = '3'
      end
      object EditMessage: TEdit
        Left = 143
        Top = 30
        Width = 169
        Height = 21
        TabOrder = 5
        Text = #1090#1077#1089#1090#1086#1074#1086#1077' '#1089#1086#1086#1073#1097#1077#1085#1080#1077
      end
      object TestFollow: TButton
        Left = 71
        Top = 3
        Width = 66
        Height = 47
        Caption = 'Test Follow Alert'
        TabOrder = 6
        WordWrap = True
        OnClick = TestFollowClick
      end
      object ButtonOpenBrowser: TButton
        Left = 447
        Top = 3
        Width = 66
        Height = 47
        Caption = 'Open alert box'
        TabOrder = 7
        WordWrap = True
        OnClick = ButtonOpenBrowserClick
      end
      object ChromiumWindow1: TChromiumWindow
        Left = 0
        Top = 64
        Width = 526
        Height = 184
        Align = alBottom
        TabOrder = 8
      end
      object ReloadEvents: TButton
        Left = 375
        Top = 3
        Width = 66
        Height = 47
        Caption = 'Connect socket'
        TabOrder = 9
        WordWrap = True
        OnClick = ReloadEventsClick
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Connection'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object log: TMemo
        Left = 0
        Top = 64
        Width = 526
        Height = 309
        Align = alBottom
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
      object DissconectBt: TButton
        Left = 255
        Top = 3
        Width = 263
        Height = 55
        Caption = 'Disconnect'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = DissconectBtClick
      end
      object ConnectBt: TButton
        Left = 3
        Top = 3
        Width = 246
        Height = 55
        Caption = 'Connect'
        CommandLinkHint = 'generate token'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = ConnectBtClick
      end
    end
  end
  object ButtonRefresh: TButton
    Left = 324
    Top = 1
    Width = 75
    Height = 17
    Caption = 'Refresh'
    Enabled = False
    TabOrder = 1
    OnClick = ButtonRefreshClick
  end
  object CheckBoxAutoUp: TCheckBox
    Left = 405
    Top = 1
    Width = 84
    Height = 17
    Caption = 'AutoRefresh'
    TabOrder = 2
    OnClick = CheckBoxAutoUpClick
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
    Left = 408
    Top = 120
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 408
    Top = 216
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
    Left = 408
    Top = 168
  end
end
