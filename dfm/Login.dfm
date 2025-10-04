object Form1: TForm1
  Left = 0
  Top = 0
  Caption = ']'
  ClientHeight = 624
  ClientWidth = 1105
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object DBGrid1: TDBGrid
    Left = 777
    Top = 8
    Width = 320
    Height = 120
    DataSource = DataSource1
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1105
    Height = 624
    Align = alClient
    Color = clActiveBorder
    ParentBackground = False
    TabOrder = 1
    ExplicitWidth = 1099
    ExplicitHeight = 607
    object bem_vindo: TLabel
      Left = 144
      Top = 76
      Width = 178
      Height = 52
      Alignment = taCenter
      Caption = 'Bem-Vindo'
      Color = clNone
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -44
      Font.Name = 'Arial Narrow'
      Font.Style = [fsUnderline]
      ParentColor = False
      ParentFont = False
    end
    object Label1: TLabel
      Left = 160
      Top = 248
      Width = 145
      Height = 32
      Caption = 'Usu'#225'rio Novo'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object Bevel1: TBevel
      Left = 520
      Top = 0
      Width = 17
      Height = 624
      Shape = bsLeftLine
    end
    object Label2: TLabel
      Left = 777
      Top = 88
      Width = 68
      Height = 38
      Caption = 'Login'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -28
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
    end
    object Button1: TButton
      Left = 176
      Top = 376
      Width = 105
      Height = 49
      Caption = 'Cadastrar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button1Click
    end
    object Usuario: TEdit
      Left = 720
      Top = 248
      Width = 201
      Height = 23
      TabOrder = 1
      TextHint = 'Usu'#225'rio'
    end
    object Senha: TEdit
      Left = 720
      Top = 328
      Width = 201
      Height = 23
      ParentShowHint = False
      PasswordChar = '*'
      ShowHint = True
      TabOrder = 2
      TextHint = 'Senha'
    end
    object Button2: TButton
      Left = 770
      Top = 432
      Width = 75
      Height = 25
      Caption = 'Button2'
      TabOrder = 3
      OnClick = Button2Click
    end
  end
  object ADOConnection1: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=MSDASQL.1;Password=B!cE@8!8%eW9uSrpL*Ms1ZVMe3s;Persist ' +
      'Security Info=True;User ID=root;Data Source=pdv_db'
    Left = 544
    Top = 24
  end
  object ADOQuery1: TADOQuery
    Active = True
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'SELECT * FROM pdv.caixa;')
    Left = 424
    Top = 80
  end
  object ADOTable1: TADOTable
    Connection = ADOConnection1
    CursorType = ctStatic
    MasterSource = DataSource1
    TableName = 'venda'
    Left = 432
    Top = 24
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 488
    Top = 24
  end
end
