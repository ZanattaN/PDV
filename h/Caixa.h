//---------------------------------------------------------------------------
#ifndef CaixaH
#define CaixaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>

//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TPanel *panel;
	TMainMenu *MainMenu1;
	TMenuItem *Caixa1;
	TMenuItem *Estoque1;
	TMenuItem *SANGRIA1;
	TMenuItem *GERENCIAR1;
	TMenuItem *FECHAMENTO1;
	TListView *lvVenda;
	TPanel *Panel2;
	TButton *finalizar;
	TLabel *lblTroco;
	TLabel *lblValorPago;
	TPanel *Panel3;
	TEdit *edtCreditoValor;
	TEdit *edtDebitoValor;
	TEdit *edtDinheiroValor;
	TEdit *edtPixValor;
	TCheckBox *chkCredito;
	TCheckBox *chkDebito;
	TCheckBox *chkDinheiro;
	TCheckBox *chkPix;
	TEdit *edtTotal;
	TEdit *edtTroco;
	TLabel *lblTotal;
	TListView *lvProdutos;
	TEdit *edtBusca;
	TEdit *edtPagar;
	TCheckBox *chkVendaRapida;
	TPrintDialog *PrintDialog1;
	TPrinterSetupDialog *PrinterSetupDialog1;
	TButton *btnImpressora;
	TButton *btnPagina;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall edtBuscaChange(TObject *Sender);
	void __fastcall chkPixClick(TObject *Sender);
	void __fastcall chkDinheiroClick(TObject *Sender);
	void __fastcall chkCreditoClick(TObject *Sender);
	void __fastcall chkDebitoClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnFinalizarVenda(TObject *Sender);
	void __fastcall edtPagarChange(TObject *Sender);
	void __fastcall edtPixPagarChange(TObject *Sender);
	void __fastcall edtCreditoChange(TObject *Sender);
	void __fastcall edtDinheiroValorChange(TObject *Sender);
	void __fastcall edtDebitoValorChange(TObject *Sender);
	void __fastcall FECHAMENTO1Click(TObject *Sender);
	void __fastcall btnImpressoraClick(TObject *Sender);
	void __fastcall btnPaginaClick(TObject *Sender);
	String __fastcall PadRight(const String& s, int width);
	String __fastcall PadLeft(const String& s, int width);
	private:	// User declarations
	void __fastcall CarregarProdutos();
	void __fastcall TForm3::FiltrarProdutos();
	float __fastcall CalcularTotalVenda();
	float __fastcall CalcularPagamentoTotal();
	float __fastcall TForm3::CalcularTroco(float totalVenda);
	void __fastcall TForm3::FormShow(TObject *Sender);
	void __fastcall TForm3::AtualizarLayoutPagamento();
	void __fastcall TForm3::AtualizarTotalVenda();
	void __fastcall TForm3::DistribuirPagamentoSplit(float totalVenda);
    void __fastcall TForm3::Impressao(String formasPgto);
    void __fastcall RawPrint(System::UnicodeString &printerName, System::AnsiString &texto);
public:		// User declarations
	// Construtor padrão e simples
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
