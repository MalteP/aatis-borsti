object Form3: TForm3
  Left = 652
  Top = 131
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'BorstiProg'
  ClientHeight = 263
  ClientWidth = 321
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 305
    Height = 217
    BevelInner = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 287
      Height = 13
      Caption = 'Taste auf der Fernbedienung drücken, um Code anzuzeigen.'
    end
    object Memo1: TMemo
      Left = 16
      Top = 32
      Width = 273
      Height = 169
      TabOrder = 0
    end
  end
  object Button1: TButton
    Left = 232
    Top = 232
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
end
