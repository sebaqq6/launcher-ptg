object fSettings: TfSettings
  Left = 506
  Top = 232
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Ustawienia'
  ClientHeight = 324
  ClientWidth = 327
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 0
    Width = 313
    Height = 105
    Caption = 'Autostart'
    TabOrder = 0
  end
  object rAutoNone: TRadioButton
    Left = 16
    Top = 16
    Width = 113
    Height = 17
    Caption = 'Nic nie r'#243'b.'
    TabOrder = 1
    OnClick = rAutoNoneClick
  end
  object rAutoGta: TRadioButton
    Left = 16
    Top = 32
    Width = 297
    Height = 17
    Caption = 'Automatycznie zaloguj do gry.'
    TabOrder = 2
    OnClick = rAutoGtaClick
  end
  object rAutoWWW: TRadioButton
    Left = 16
    Top = 48
    Width = 193
    Height = 17
    Caption = 'Automatycznie uruchom forum.'
    TabOrder = 3
    OnClick = rAutoWWWClick
  end
  object rAutoTS: TRadioButton
    Left = 16
    Top = 64
    Width = 193
    Height = 17
    Caption = 'Automatycznie '#322#261'cz z serwerem TS3.'
    TabOrder = 4
    OnClick = rAutoTSClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 112
    Width = 313
    Height = 57
    Caption = 'Czat'
    TabOrder = 5
    object Label1: TLabel
      Left = 72
      Top = 32
      Width = 160
      Height = 13
      Caption = 'Od'#347'wie'#380'aj czat co            sekund.'
    end
    object checkAutoRef: TCheckBox
      Left = 8
      Top = 16
      Width = 105
      Height = 17
      Caption = 'Auto-od'#347'wie'#380'anie.'
      TabOrder = 0
      OnClick = checkAutoRefClick
    end
    object cRefEdit: TCSpinEdit
      Left = 160
      Top = 32
      Width = 33
      Height = 22
      MaxValue = 9
      MinValue = 1
      TabOrder = 1
      Value = 1
      OnChange = cRefEditChange
    end
  end
  object rAutoWWWTS: TRadioButton
    Left = 16
    Top = 80
    Width = 265
    Height = 17
    Caption = 'Automatycznie '#322#261'cz z serwerem TS3 i forum.'
    TabOrder = 6
    OnClick = rAutoWWWTSClick
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 176
    Width = 313
    Height = 41
    Caption = 'Changelog'
    TabOrder = 7
    object cRefChangelog: TCheckBox
      Left = 8
      Top = 16
      Width = 297
      Height = 17
      Caption = 'Wy'#322#261'cz od'#347'wie'#380'anie changelogu.'
      TabOrder = 0
      OnClick = cRefChangelogClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 224
    Width = 313
    Height = 97
    Caption = 'Radio'
    TabOrder = 8
    object Label2: TLabel
      Left = 128
      Top = 40
      Width = 46
      Height = 13
      Caption = 'G'#322'o'#347'no'#347#263
    end
    object rPTGStatus: TCheckBox
      Left = 8
      Top = 16
      Width = 129
      Height = 17
      Caption = 'Uruchom radio.'
      TabOrder = 0
      OnClick = rPTGStatusClick
    end
    object rVolume: TTrackBar
      Left = 48
      Top = 56
      Width = 209
      Height = 25
      Max = 100
      Orientation = trHorizontal
      Frequency = 1
      Position = 50
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = rVolumeChange
    end
  end
  object Memo1: TMemo
    Left = 16
    Top = 24
    Width = 289
    Height = 65
    Lines.Strings = (
      'debug bass...')
    TabOrder = 9
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 256
    Top = 8
  end
end
