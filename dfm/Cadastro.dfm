object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 476
  ClientWidth = 929
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 929
    Height = 476
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 176
    ExplicitTop = 80
    ExplicitWidth = 185
    ExplicitHeight = 41
    object Label1: TLabel
      Left = 384
      Top = 56
      Width = 134
      Height = 45
      Caption = 'Cadastrar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -32
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object usuario_cad: TEdit
      Left = 381
      Top = 136
      Width = 134
      Height = 23
      TabOrder = 0
      TextHint = 'usuario'
    end
    object senha_cad: TEdit
      Left = 384
      Top = 256
      Width = 134
      Height = 23
      PasswordChar = '*'
      TabOrder = 1
      TextHint = 'senha'
    end
    object Button1: TButton
      Left = 381
      Top = 336
      Width = 137
      Height = 41
      Caption = 'Cadastrar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -28
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = Button1Click
    end
    object nome_cad: TEdit
      Left = 384
      Top = 192
      Width = 134
      Height = 23
      TabOrder = 3
      TextHint = 'Nome'
    end
  end
end
