object Form3: TForm3
  Left = 0
  Top = 0
  Align = alClient
  Caption = 'Form3'
  ClientHeight = 614
  ClientWidth = 1059
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  OnCreate = FormCreate
  TextHeight = 15
  object panel: TPanel
    Left = 0
    Top = 0
    Width = 1059
    Height = 614
    Align = alClient
    TabOrder = 0
    object lvVenda: TListView
      AlignWithMargins = True
      Left = 4
      Top = 108
      Width = 787
      Height = 502
      Align = alClient
      Columns = <
        item
          Caption = 'Nome'
          MaxWidth = 500
          Width = 300
        end
        item
          Caption = 'Pre'#231'o'
          MaxWidth = 200
          Width = 200
        end
        item
          Caption = 'Qtd'
          Width = 80
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      ViewStyle = vsReport
    end
    object Panel2: TPanel
      AlignWithMargins = True
      Left = 797
      Top = 108
      Width = 258
      Height = 502
      Align = alRight
      TabOrder = 1
      ExplicitTop = 111
      DesignSize = (
        258
        502)
      object lblTroco: TLabel
        Left = 94
        Top = 109
        Width = 68
        Height = 37
        Align = alCustom
        Caption = 'Troco'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -32
        Font.Name = 'Arial Narrow'
        Font.Style = []
        ParentFont = False
      end
      object lblValorPago: TLabel
        Left = 90
        Top = 217
        Width = 72
        Height = 37
        Align = alCustom
        Caption = 'Pagar'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -32
        Font.Name = 'Arial Narrow'
        Font.Style = []
        ParentFont = False
        Layout = tlCenter
      end
      object lblTotal: TLabel
        Left = 96
        Top = 6
        Width = 59
        Height = 37
        Caption = 'Total'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -32
        Font.Name = 'Arial Narrow'
        Font.Style = []
        ParentFont = False
      end
      object finalizar: TButton
        Left = 49
        Top = 375
        Width = 161
        Height = 49
        Caption = 'Finalizar'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -24
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = BtnFinalizarVenda
      end
      object edtTotal: TEdit
        Left = 49
        Top = 49
        Width = 161
        Height = 32
        Anchors = []
        TabOrder = 1
      end
      object edtTroco: TEdit
        Left = 49
        Top = 160
        Width = 161
        Height = 33
        Anchors = []
        TabOrder = 2
      end
      object edtPagar: TEdit
        Left = 48
        Top = 274
        Width = 161
        Height = 31
        Anchors = []
        TabOrder = 3
      end
      object btnImpressora: TButton
        Left = 16
        Top = 456
        Width = 75
        Height = 25
        Caption = 'Impressora'
        TabOrder = 4
        OnClick = btnImpressoraClick
      end
      object btnPagina: TButton
        Left = 160
        Top = 456
        Width = 75
        Height = 25
        Caption = 'P'#225'gina'
        TabOrder = 5
        OnClick = btnPaginaClick
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 1057
      Height = 104
      Align = alTop
      TabOrder = 2
      DesignSize = (
        1057
        104)
      object edtCreditoValor: TEdit
        Left = 312
        Top = 56
        Width = 121
        Height = 23
        Hint = 'Cr'#233'dito'
        Anchors = []
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        TextHint = 'Cr'#233'dito'
        OnChange = edtCreditoChange
      end
      object edtDebitoValor: TEdit
        Left = 464
        Top = 56
        Width = 121
        Height = 23
        Anchors = []
        TabOrder = 1
        TextHint = 'D'#233'bito'
        OnChange = edtDebitoValorChange
      end
      object edtDinheiroValor: TEdit
        Left = 464
        Top = 8
        Width = 121
        Height = 23
        Hint = 'Dinheiro'
        Anchors = []
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        TextHint = 'Dinheiro'
        OnChange = edtDinheiroValorChange
      end
      object edtPixValor: TEdit
        Left = 312
        Top = 8
        Width = 121
        Height = 23
        Hint = 'PIX'
        Anchors = []
        TabOrder = 3
        TextHint = 'PIX'
        OnChange = edtPixPagarChange
      end
      object chkCredito: TCheckBox
        Left = 168
        Top = 16
        Width = 105
        Height = 21
        Caption = 'Cr'#233'dito'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -22
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = chkCreditoClick
      end
      object chkDebito: TCheckBox
        Left = 168
        Top = 61
        Width = 105
        Height = 32
        Caption = 'D'#233'bito'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -22
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        OnClick = chkDebitoClick
      end
      object chkDinheiro: TCheckBox
        Left = 24
        Top = 64
        Width = 105
        Height = 25
        Caption = 'Dinheiro'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -22
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        OnClick = chkDinheiroClick
      end
      object chkPix: TCheckBox
        Left = 24
        Top = 8
        Width = 105
        Height = 33
        Caption = 'PIX'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -22
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
        OnClick = chkPixClick
      end
      object lvProdutos: TListView
        Left = 823
        Top = 40
        Width = 225
        Height = 53
        Anchors = [akTop, akRight]
        Columns = <
          item
          end>
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Segoe UI'
        Font.Style = []
        ReadOnly = True
        ParentFont = False
        TabOrder = 8
        ViewStyle = vsTile
        OnClick = Button1Click
      end
      object edtBusca: TEdit
        Left = 823
        Top = 11
        Width = 225
        Height = 23
        Anchors = [akTop, akRight]
        TabOrder = 9
        TextHint = 'Pesquisa'
        OnChange = edtBuscaChange
      end
      object chkVendaRapida: TCheckBox
        Left = 624
        Top = 30
        Width = 166
        Height = 37
        Caption = 'Venda Rapida'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -24
        Font.Name = 'Arial Narrow'
        Font.Style = []
        ParentFont = False
        TabOrder = 10
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 768
    Top = 736
    object Caixa1: TMenuItem
      Caption = 'CAIXA'
      ShortCut = 112
    end
    object Estoque1: TMenuItem
      Caption = 'ESTOQUE'
      ShortCut = 113
    end
    object SANGRIA1: TMenuItem
      Caption = 'SANGRIA'
    end
    object GERENCIAR1: TMenuItem
      Caption = 'GERENCIAR'
    end
    object FECHAMENTO1: TMenuItem
      Caption = 'FECHAMENTO'
      OnClick = FECHAMENTO1Click
    end
  end
  object PrintDialog1: TPrintDialog
    Left = 797
    Top = 452
  end
  object PrinterSetupDialog1: TPrinterSetupDialog
    Left = 1016
    Top = 448
  end
end
