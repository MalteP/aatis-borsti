object Form1: TForm1
  Left = 244
  Top = 142
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'BorstiProg'
  ClientHeight = 489
  ClientWidth = 305
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefault
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 289
    Height = 425
    BevelInner = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 20
      Width = 120
      Height = 13
      Caption = 'Fernbedienungs-Adresse:'
    end
    object Label2: TLabel
      Left = 16
      Top = 44
      Width = 76
      Height = 13
      Caption = 'Taste Frontlicht:'
    end
    object Label3: TLabel
      Left = 16
      Top = 68
      Width = 63
      Height = 13
      Caption = 'Taste Sirene:'
    end
    object Label4: TLabel
      Left = 16
      Top = 92
      Width = 95
      Height = 13
      Caption = 'Taste Blinker (links):'
    end
    object Label5: TLabel
      Left = 16
      Top = 116
      Width = 103
      Height = 13
      Caption = 'Taste Blinker (rechts):'
    end
    object Label6: TLabel
      Left = 16
      Top = 140
      Width = 91
      Height = 13
      Caption = 'Taste Blinker (aus):'
    end
    object Label7: TLabel
      Left = 16
      Top = 164
      Width = 90
      Height = 13
      Caption = 'Taste Warnblinker:'
    end
    object Label8: TLabel
      Left = 16
      Top = 188
      Width = 95
      Height = 13
      Caption = 'Taste Blinker (auto):'
    end
    object Label9: TLabel
      Left = 16
      Top = 212
      Width = 116
      Height = 13
      Caption = 'Taste Blitzlicht (blitzend):'
    end
    object Label10: TLabel
      Left = 16
      Top = 236
      Width = 127
      Height = 13
      Caption = 'Taste Blitzlicht (leuchtend):'
    end
    object Label11: TLabel
      Left = 16
      Top = 260
      Width = 111
      Height = 13
      Caption = 'Taste Motor (linksfahrt):'
    end
    object Label12: TLabel
      Left = 16
      Top = 284
      Width = 119
      Height = 13
      Caption = 'Taste Motor (geradeaus):'
    end
    object Label13: TLabel
      Left = 16
      Top = 308
      Width = 119
      Height = 13
      Caption = 'Taste Motor (rechtsfahrt):'
    end
    object Label15: TLabel
      Left = 16
      Top = 332
      Width = 123
      Height = 13
      Caption = 'Motor-Richtungskorrektur:'
    end
    object Label16: TLabel
      Left = 16
      Top = 396
      Width = 79
      Height = 13
      Caption = 'Bluetooth-Name:'
    end
    object Label14: TLabel
      Left = 224
      Top = 340
      Width = 6
      Height = 13
      Caption = 'L'
    end
    object Label17: TLabel
      Left = 224
      Top = 364
      Width = 8
      Height = 13
      Caption = 'R'
    end
    object Label18: TLabel
      Left = 152
      Top = 20
      Width = 6
      Height = 13
      Caption = 'L'
    end
    object Label19: TLabel
      Left = 208
      Top = 20
      Width = 8
      Height = 13
      Caption = 'H'
    end
    object Edit1: TEdit
      Left = 168
      Top = 16
      Width = 25
      Height = 21
      TabOrder = 0
    end
    object Edit2: TEdit
      Left = 224
      Top = 16
      Width = 25
      Height = 21
      TabOrder = 1
    end
    object Edit3: TEdit
      Left = 168
      Top = 40
      Width = 25
      Height = 21
      TabOrder = 2
    end
    object Edit4: TEdit
      Left = 168
      Top = 64
      Width = 25
      Height = 21
      TabOrder = 3
    end
    object Edit5: TEdit
      Left = 168
      Top = 88
      Width = 25
      Height = 21
      TabOrder = 4
    end
    object Edit6: TEdit
      Left = 168
      Top = 112
      Width = 25
      Height = 21
      TabOrder = 5
    end
    object Edit7: TEdit
      Left = 168
      Top = 136
      Width = 25
      Height = 21
      TabOrder = 6
    end
    object Edit8: TEdit
      Left = 168
      Top = 160
      Width = 25
      Height = 21
      TabOrder = 7
    end
    object Edit9: TEdit
      Left = 168
      Top = 184
      Width = 25
      Height = 21
      TabOrder = 8
    end
    object Edit10: TEdit
      Left = 168
      Top = 208
      Width = 25
      Height = 21
      TabOrder = 9
    end
    object Edit11: TEdit
      Left = 168
      Top = 232
      Width = 25
      Height = 21
      TabOrder = 10
    end
    object Edit12: TEdit
      Left = 168
      Top = 256
      Width = 25
      Height = 21
      TabOrder = 11
    end
    object Edit13: TEdit
      Left = 168
      Top = 280
      Width = 25
      Height = 21
      TabOrder = 12
    end
    object Edit14: TEdit
      Left = 168
      Top = 304
      Width = 25
      Height = 21
      TabOrder = 13
    end
    object Edit15: TEdit
      Left = 240
      Top = 336
      Width = 25
      Height = 21
      TabOrder = 14
    end
    object Edit16: TEdit
      Left = 240
      Top = 360
      Width = 25
      Height = 21
      TabOrder = 15
    end
    object Edit17: TEdit
      Left = 168
      Top = 392
      Width = 97
      Height = 21
      TabOrder = 16
    end
    object TrackBar1: TTrackBar
      Left = 16
      Top = 352
      Width = 201
      Height = 25
      Max = 255
      Min = -255
      Orientation = trHorizontal
      Frequency = 17
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 17
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = TrackBar1Change
    end
  end
  object Button2: TButton
    Left = 216
    Top = 440
    Width = 75
    Height = 25
    Caption = 'Schreiben'
    Enabled = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button1: TButton
    Left = 128
    Top = 440
    Width = 75
    Height = 25
    Caption = 'Lesen'
    Enabled = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 470
    Width = 305
    Height = 19
    Panels = <
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 440
    object Datei1: TMenuItem
      Caption = '&Datei'
      object EinstellungenLaden1: TMenuItem
        Caption = 'Preset &laden...'
        OnClick = EinstellungenLaden1Click
      end
      object Presetspeichern1: TMenuItem
        Caption = 'Preset &speichern...'
        OnClick = Presetspeichern1Click
      end
      object Zurcksetzen1: TMenuItem
        Caption = '&Zurücksetzen'
        OnClick = Zurcksetzen1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Beenden1: TMenuItem
        Caption = '&Beenden'
        OnClick = Beenden1Click
      end
    end
    object Port1: TMenuItem
      Caption = '&COM-Port'
      object Auswahl1: TMenuItem
        Caption = '&Auswahl'
        OnClick = Auswahl1Click
      end
      object Verbinden1: TMenuItem
        Caption = '&Verbinden'
        OnClick = Verbinden1Click
      end
      object Trennen1: TMenuItem
        Caption = '&Trennen'
        OnClick = Trennen1Click
      end
    end
    object Extras1: TMenuItem
      Caption = '&Extras'
      object Fernbedienunganalysieren1: TMenuItem
        Caption = '&Fernbedienung analysieren...'
        OnClick = Fernbedienunganalysieren1Click
      end
    end
  end
  object SerialPortNG1: TSerialPortNG
    CommPort = 'COM2'
    EventChar = #10
    ErrorNoise = 255
    OnRxClusterEvent = SerialPortNG1RxClusterEvent
    Left = 40
    Top = 440
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.bpp'
    Filter = 'BorstiProg Preset (*.bpp)|*.bpp'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 72
    Top = 440
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.bpp'
    Filter = 'BorstiProg Preset (*.bpp)|*.bpp'
    Left = 104
    Top = 440
  end
  object Timer1: TTimer
    Interval = 5
    OnTimer = Timer1Timer
    Left = 8
    Top = 408
  end
end
