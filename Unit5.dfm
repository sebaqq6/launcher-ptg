object fMapa: TfMapa
  Left = 387
  Top = 205
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Launcher PTG - Mapa '#346'wiata'
  ClientHeight = 591
  ClientWidth = 609
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object imgMap: TImage
    Left = 0
    Top = 0
    Width = 609
    Height = 513
    Center = True
    Stretch = True
  end
  object Bevel1: TBevel
    Left = 0
    Top = 576
    Width = 609
    Height = 17
  end
  object statusbar: TStatusBar
    Left = 0
    Top = 572
    Width = 609
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object RadioGroup1: TRadioGroup
    Left = 0
    Top = 512
    Width = 609
    Height = 57
    Caption = 'Opcje'
    TabOrder = 1
  end
  object onlyPlayer: TRadioButton
    Left = 8
    Top = 528
    Width = 145
    Height = 17
    Caption = 'Poka'#380' moj'#261' pozycj'#281'.'
    Checked = True
    TabOrder = 2
    TabStop = True
  end
  object showAllPlayers: TRadioButton
    Left = 8
    Top = 544
    Width = 233
    Height = 17
    Caption = 'Poka'#380' pozycj'#281' wszystkich graczy ONLINE.'
    TabOrder = 3
  end
  object autoRefMap: TCheckBox
    Left = 256
    Top = 536
    Width = 113
    Height = 17
    Caption = 'Auto-Od'#347'wie'#380'anie.'
    Checked = True
    State = cbChecked
    TabOrder = 4
  end
  object bRefresh: TButton
    Left = 424
    Top = 528
    Width = 113
    Height = 33
    Caption = 'Od'#347'wie'#380'!'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = bRefreshClick
  end
  object IdHTTP1: TIdHTTP
    Request.Accept = '*/*'
    Request.ContentLength = 0
    Request.ContentRangeEnd = 0
    Request.ContentRangeStart = 0
    Request.ContentType = 'application/x-www-form-urlencoded'
    Request.ProxyPort = 0
    Request.UserAgent = 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)'
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 16000
    OnTimer = Timer1Timer
    Left = 32
  end
end
