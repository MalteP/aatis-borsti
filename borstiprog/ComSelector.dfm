object Form2: TForm2
  Left = 138
  Top = 125
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsDialog
  Caption = 'BorstiProg'
  ClientHeight = 115
  ClientWidth = 202
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 185
    Height = 65
    BevelInner = bvLowered
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 8
      Width = 149
      Height = 13
      Caption = 'Bitte wählen Sie den COM-Port:'
    end
    object ComboBox1: TComboBox
      Left = 16
      Top = 32
      Width = 153
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object Button1: TButton
    Left = 112
    Top = 80
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = Button1Click
  end
end
