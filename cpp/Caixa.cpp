//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Windows.h"
#include "Caixa.h"
#include <Vcl.Printers.hpp>
// Inclui o formulário de Login para que possamos usar seus componentes
#include "Login.h"
#include "Fechamento.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
// Construtor padrão.
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormShow(TObject *Sender)
{
	BorderStyle = bsNone;         // Remove bordas e barra de título
	WindowState = wsMaximized;    // Maximiza a janela
}


void __fastcall TForm3::Button1Click(TObject *Sender)
{
	if (lvProdutos->Selected)
	{
		TListItem *produtoSelecionado = lvProdutos->Selected;
		int idProduto = (int)produtoSelecionado->Data;

		// Verifica se o produto já está na lista de venda
		for (int i = 0; i < lvVenda->Items->Count; i++)
		{
			if ((int)lvVenda->Items->Item[i]->Data == idProduto)
			{
				// Já existe, aumenta a quantidade
				int qtd = lvVenda->Items->Item[i]->SubItems->Strings[1].ToInt();
				qtd++;
				lvVenda->Items->Item[i]->SubItems->Strings[1] = IntToStr(qtd);
				AtualizarTotalVenda(); // move para cá
				return;
			}
		}

		// Consulta o preço do produto
		Form1->ADOQuery1->Close();
		Form1->ADOQuery1->SQL->Text = "SELECT PRECO_VENDA FROM produto WHERE ID_PRODUTO = :id";
		Form1->ADOQuery1->Parameters->ParamByName("id")->Value = idProduto;
		Form1->ADOQuery1->Open();

		if (!Form1->ADOQuery1->IsEmpty())
		{
			float preco = Form1->ADOQuery1->FieldByName("PRECO_VENDA")->AsFloat;

			// Adiciona novo item à venda
			TListItem *itemVenda = lvVenda->Items->Add();
			itemVenda->Caption = produtoSelecionado->Caption; // Nome
			itemVenda->SubItems->Add(FormatFloat("0.00", preco)); // Preço
			itemVenda->SubItems->Add("1"); // Quantidade inicial
			itemVenda->Data = (void*)idProduto;
		}
	}

	AtualizarTotalVenda(); // move para cá
}

//---------------------------------------------------------------------------
void __fastcall TForm3::edtBuscaChange(TObject *Sender)
{
	FiltrarProdutos();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FiltrarProdutos()
{
	String termoBusca = edtBusca->Text.Trim().LowerCase();

	lvProdutos->Items->BeginUpdate();
	lvProdutos->Clear();

	Form1->ADOQuery1->Close();
	Form1->ADOQuery1->SQL->Text = "SELECT ID_PRODUTO, NOME FROM produto WHERE LOWER(NOME) LIKE :busca ORDER BY NOME";
	Form1->ADOQuery1->Parameters->ParamByName("busca")->Value = "%" + termoBusca + "%";
	Form1->ADOQuery1->Open();

	while (!Form1->ADOQuery1->Eof)
	{
		TListItem *item = lvProdutos->Items->Add();
		item->Caption = Form1->ADOQuery1->FieldByName("NOME")->AsString;
		item->Data = (void*)Form1->ADOQuery1->FieldByName("ID_PRODUTO")->AsInteger;
		Form1->ADOQuery1->Next();
	}

	lvProdutos->Items->EndUpdate();
}

void __fastcall TForm3::chkPixClick(TObject *Sender)
{
	AtualizarLayoutPagamento();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::chkDinheiroClick(TObject *Sender)
{
	AtualizarLayoutPagamento();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::chkCreditoClick(TObject *Sender)
{
	AtualizarLayoutPagamento();
}

//---------------------------------------------------------------------------

void __fastcall TForm3::chkDebitoClick(TObject *Sender)
{
	AtualizarLayoutPagamento();
}

//---------------------------------------------------------------------------


float __fastcall TForm3::CalcularTotalVenda()
{
	float total = 0;

	for (int i = 0; i < lvVenda->Items->Count; i++)
	{
		String precoStr = lvVenda->Items->Item[i]->SubItems->Strings[0];
		String qtdStr   = lvVenda->Items->Item[i]->SubItems->Strings[1];

		float preco = StrToFloatDef(StringReplace(precoStr, "R$", "", TReplaceFlags() << rfReplaceAll << rfIgnoreCase).Trim(), 0);
		int qtd = StrToIntDef(qtdStr.Trim(), 1);

		total += preco * qtd;
	}

	return total;
}

float __fastcall TForm3::CalcularPagamentoTotal()
{
	float soma = 0;

	if (chkPix->Checked)
		soma += StrToFloatDef(edtPixValor->Text.Trim(), 0);

	if (chkDebito->Checked)
		soma += StrToFloatDef(edtDebitoValor->Text.Trim(), 0);

	if (chkCredito->Checked)
		soma += StrToFloatDef(edtCreditoValor->Text.Trim(), 0);

	if (chkDinheiro->Checked)
		soma += StrToFloatDef(edtDinheiroValor->Text.Trim(), 0);

	return soma;
}

float __fastcall TForm3::CalcularTroco(float totalVenda)
{
	if (!chkDinheiro->Checked)
		return 0;

	float valorDinheiro = StrToFloatDef(edtDinheiroValor->Text.Trim(), 0);
	float troco = valorDinheiro - totalVenda;

	return troco > 0 ? troco : 0;
}




//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{

	BorderStyle = bsNone;         // Remove bordas e barra de título
	WindowState = wsMaximized;    // Maximiza a janela
	edtPixValor->Hide();
	edtDebitoValor->Hide();
	edtCreditoValor->Hide();
	edtDinheiroValor->Hide();


}
//---------------------------------------------------------------------------
void __fastcall TForm3::AtualizarLayoutPagamento()
{
	int formasSelecionadas = 0;

	bool pix     = chkPix->Checked;
	bool debito  = chkDebito->Checked;
	bool credito = chkCredito->Checked;
	bool dinheiro= chkDinheiro->Checked;

	if (pix)     formasSelecionadas++;
	if (debito)  formasSelecionadas++;
	if (credito) formasSelecionadas++;
	if (dinheiro)formasSelecionadas++;

	bool split = formasSelecionadas > 1;
	bool dinheiroUnico = dinheiro && !split;

	// Campos de valor por forma (split)
	edtPixValor->Visible      = split && pix;
	edtDebitoValor->Visible   = split && debito;
	edtCreditoValor->Visible  = split && credito;
	edtDinheiroValor->Visible = split && dinheiro;

	// Campo edtPagar só aparece se for dinheiro único
	edtPagar->Visible = dinheiroUnico;
	lblValorPago->Visible = dinheiroUnico;

	// Troco só aparece se for dinheiro único
	edtTroco->Visible = dinheiroUnico;
	lblTroco->Visible = dinheiroUnico;
}

void __fastcall TForm3::AtualizarTotalVenda()
{

	double total = 0;

	if (!chkVendaRapida->Checked) {
		for (int i = 0; i < lvVenda->Items->Count; i++) {
			String precoStr = lvVenda->Items->Item[i]->SubItems->Strings[0];
			String qtdStr   = lvVenda->Items->Item[i]->SubItems->Strings[1];

			double preco = StrToFloatDef(precoStr.Trim(), 0);
			int qtd = StrToIntDef(qtdStr.Trim(), 1);

			total += preco * qtd;
		}
		edtTotal->Text = FormatFloat("0.00", total);
	}
	else {
		// Venda rápida: usa o valor digitado manualmente
		total = StrToFloatDef(edtTotal->Text.Trim(), 0);
	}

	float pagamentoTotal = CalcularPagamentoTotal();
	float troco = CalcularTroco(total);
	edtTroco->Text = FormatFloat("0.00", troco);
}





//---------------------------------------------------------------------------
	void __fastcall TForm3::BtnFinalizarVenda(TObject *Sender)
{
	// 1. Verifica se alguma forma de pagamento foi selecionada
	if (!chkPix->Checked && !chkDebito->Checked && !chkCredito->Checked && !chkDinheiro->Checked)
	{
		ShowMessage("Selecione pelo menos uma forma de pagamento antes de finalizar.");
		return;
	}

	// 2. Calcula o total da venda
	float totalVenda = 0;

	for (int i = 0; i < lvVenda->Items->Count; i++)
	{
		String precoStr = lvVenda->Items->Item[i]->SubItems->Strings[0];
		String qtdStr   = lvVenda->Items->Item[i]->SubItems->Strings[1];

		float preco = StrToFloatDef(precoStr.Trim(), 0);
		int qtd    = StrToIntDef(qtdStr.Trim(), 1);

		totalVenda += preco * qtd;
	}

	edtTotal->Text = FormatFloat("0.00", totalVenda);

	// 3. Atualiza estoque com proteção contra estoque insuficiente
	for (int i = 0; i < lvVenda->Items->Count; i++)
	{
		int idProduto = (int)lvVenda->Items->Item[i]->Data;
		int qtdVendida = StrToIntDef(lvVenda->Items->Item[i]->SubItems->Strings[1], 1);

		// Consulta estoque atual
		Form1->ADOQuery1->Close();
		Form1->ADOQuery1->SQL->Text =
			"SELECT quantidade_estoque FROM produto WHERE id_produto = :id";
		Form1->ADOQuery1->Parameters->ParamByName("id")->Value = idProduto;
		Form1->ADOQuery1->Open();

		int estoqueAtual = Form1->ADOQuery1->FieldByName("quantidade_estoque")->AsInteger;

		if (estoqueAtual < qtdVendida)
		{
			ShowMessage("Estoque insuficiente para o produto: " + lvVenda->Items->Item[i]->Caption);
			continue; // pula este item
		}

		// Atualiza estoque
		Form1->ADOQuery1->Close();
		Form1->ADOQuery1->SQL->Text =
			"UPDATE produto SET quantidade_estoque = quantidade_estoque - :qtd WHERE id_produto = :id";
		Form1->ADOQuery1->Parameters->ParamByName("qtd")->Value = qtdVendida;
		Form1->ADOQuery1->Parameters->ParamByName("id")->Value = idProduto;
		Form1->ADOQuery1->ExecSQL();
	}

	// 4. Limpa a venda
	lvVenda->Clear();
	edtTotal->Text = "0.00";
	String formasPgto;
	if (chkPix->Checked)     formasPgto += "PIX ";
	if (chkDebito->Checked)  formasPgto += "Débito ";
	if (chkCredito->Checked) formasPgto += "Crédito ";
	if (chkDinheiro->Checked)formasPgto += "Dinheiro ";

	Impressao(formasPgto); // passa como parâmetro
	// 5. Prepara para próxima venda
	chkPix->Checked     = false;
	chkDebito->Checked  = false;
	chkCredito->Checked = false;
	chkDinheiro->Checked= false;
	AtualizarLayoutPagamento(); // oculta campos de pagamento
	ShowMessage("Venda finalizada com sucesso!");
}


void __fastcall TForm3::DistribuirPagamentoSplit(float totalVenda)
{
	// Não forçar divisão automática
	if (chkPix->Checked)     edtPixValor->Text = "0.00";
	if (chkDebito->Checked)  edtDebitoValor->Text = "0.00";
	if (chkCredito->Checked) edtCreditoValor->Text = "0.00";
	if (chkDinheiro->Checked)edtDinheiroValor->Text = "0.00";
}

void __fastcall TForm3::edtPagarChange(TObject *Sender)
{

	float totalVenda = StrToFloatDef(edtTotal->Text.Trim(), 0);
	float valorPago  = StrToFloatDef(edtPagar->Text.Trim(), 0);
	float troco      = valorPago - totalVenda;

	edtTroco->Text = FormatFloat("0.00", troco > 0 ? troco : 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::edtPixPagarChange(TObject *Sender)
{
	float totalVenda     = StrToFloatDef(edtTotal->Text.Trim(), 0);
	float valorPix       = StrToFloatDef(edtPixValor->Text.Trim(), 0);
	float valorCredito   = StrToFloatDef(edtCreditoValor->Text.Trim(), 0);
	float valorDebito    = StrToFloatDef(edtDebitoValor->Text.Trim(), 0);
	float valorDinheiro  = StrToFloatDef(edtDinheiroValor->Text.Trim(), 0);

	float pagamentoTotal = valorPix + valorCredito + valorDebito + valorDinheiro;
	float troco          = valorDinheiro - (totalVenda - (pagamentoTotal - valorDinheiro));

	edtTroco->Text = FormatFloat("0.00", troco > 0 ? troco : 0);

}
//---------------------------------------------------------------------------
void __fastcall TForm3::edtCreditoChange(TObject *Sender)
{

	float totalVenda     = StrToFloatDef(edtTotal->Text.Trim(), 0);
	float valorPix       = StrToFloatDef(edtPixValor->Text.Trim(), 0);
	float valorCredito   = StrToFloatDef(edtCreditoValor->Text.Trim(), 0);
	float valorDebito    = StrToFloatDef(edtDebitoValor->Text.Trim(), 0);
	float valorDinheiro  = StrToFloatDef(edtDinheiroValor->Text.Trim(), 0);

	float pagamentoTotal = valorPix + valorCredito + valorDebito + valorDinheiro;
	float troco          = valorDinheiro - (totalVenda - (pagamentoTotal - valorDinheiro));

	edtTroco->Text = FormatFloat("0.00", troco > 0 ? troco : 0);


}
//---------------------------------------------------------------------------

void __fastcall TForm3::edtDinheiroValorChange(TObject *Sender)
{
	float totalVenda     = StrToFloatDef(edtTotal->Text.Trim(), 0);
	float valorPix       = StrToFloatDef(edtPixValor->Text.Trim(), 0);
	float valorCredito   = StrToFloatDef(edtCreditoValor->Text.Trim(), 0);
	float valorDebito    = StrToFloatDef(edtDebitoValor->Text.Trim(), 0);
	float valorDinheiro  = StrToFloatDef(edtDinheiroValor->Text.Trim(), 0);

	float pagamentoTotal = valorPix + valorCredito + valorDebito + valorDinheiro;
	float troco          = valorDinheiro - (totalVenda - (pagamentoTotal - valorDinheiro));

	edtTroco->Text = FormatFloat("0.00", troco > 0 ? troco : 0);


}
//---------------------------------------------------------------------------

void __fastcall TForm3::edtDebitoValorChange(TObject *Sender)
{
	float totalVenda     = StrToFloatDef(edtTotal->Text.Trim(), 0);
	float valorPix       = StrToFloatDef(edtPixValor->Text.Trim(), 0);
	float valorCredito   = StrToFloatDef(edtCreditoValor->Text.Trim(), 0);
	float valorDebito    = StrToFloatDef(edtDebitoValor->Text.Trim(), 0);
	float valorDinheiro  = StrToFloatDef(edtDinheiroValor->Text.Trim(), 0);

	float pagamentoTotal = valorPix + valorCredito + valorDebito + valorDinheiro;
	float troco          = valorDinheiro - (totalVenda - (pagamentoTotal - valorDinheiro));

	edtTroco->Text = FormatFloat("0.00", troco > 0 ? troco : 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FECHAMENTO1Click(TObject *Sender)
{
	Form3->Hide();
	Form4->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Impressao(String formasPgto)
{
	TStringList *linhas = new TStringList();

	linhas->Add("           *** MINHA LOJA LTDA ***");
	linhas->Add("        CNPJ: 00.000.000/0001-00");
	linhas->Add("             CUPOM NAO FISCAL");
	linhas->Add("------------------------------------------");
	linhas->Add(PadRight("ITEM", 20) + PadLeft("QTD", 5) + PadLeft("VALOR", 12));
	linhas->Add("------------------------------------------");

	for (int i = 0; i < lvVenda->Items->Count; i++)
	{
		String nome   = lvVenda->Items->Item[i]->Caption;
		String preco  = lvVenda->Items->Item[i]->SubItems->Strings[0];
		String qtd    = lvVenda->Items->Item[i]->SubItems->Strings[1];

		String linha = PadRight(nome, 20) +
					   PadLeft(qtd, 5) +
					   PadLeft("R$" + preco, 12);

		linhas->Add(linha);
	}

	linhas->Add("------------------------------------------");
	linhas->Add("TOTAL: R$ " + edtTotal->Text);
	linhas->Add("------------------------------------------");
	linhas->Add("Pagamento: " + formasPgto);
	linhas->Add("------------------------------------------");
	linhas->Add("    OBRIGADO PELA PREFERENCIA!");
	linhas->Add("          VOLTE SEMPRE :)");
	linhas->Add("");
	linhas->Add("");

	// Comando ESC/POS para corte de papel
	linhas->Add("\x1D\x56\x42\0");

	// Monta todo o texto com \n
	AnsiString texto;
	for (int i = 0; i < linhas->Count; i++)
		texto += linhas->Strings[i] + "\n";

	// Nome da impressora padrão
	String printerName = Printer()->Printers->Strings[Printer()->PrinterIndex];


	RawPrint(printerName, texto);

	delete linhas;
}


// Ao clicar no botão para abrir a caixa de diálogo da impressora
void __fastcall TForm3::btnImpressoraClick(TObject *Sender)
{
	if (PrintDialog1->Execute())
	{
		// Se o usuário confirmou a impressão, você pode iniciar a impressão aqui
        ShowMessage("Bem-Vindo");
	}
}

// Ao clicar no botão para configurar página/impressora
void __fastcall TForm3::btnPaginaClick(TObject *Sender)
{
	PrinterSetupDialog1->Execute();
}

//---------------------------------------------------------------------------
// Preenche à direita até atingir o tamanho desejado
String __fastcall TForm3::PadRight(const String& s, int width) {
	String r = s;
	while (r.Length() < width)
		r += " ";
	if (r.Length() > width)
		r = r.SubString(1, width);
	return r;
}

String __fastcall TForm3::PadLeft(const String& s, int width) {
	String r = s;
	while (r.Length() < width)
		r = " " + r;
	if (r.Length() > width)
		r = r.SubString(r.Length() - width + 1, width);
	return r;
}



void __fastcall TForm3::RawPrint(System::UnicodeString &printerName, System::AnsiString &texto)
{
	HANDLE hPrinter;
	DWORD dwWritten;
	DOC_INFO_1W DocInfo;  // usar versão W (Unicode)
	LPBYTE pData;
	int iLen;

	// Abre a impressora pelo nome
	if (OpenPrinterW((LPWSTR)printerName.w_str(), &hPrinter, NULL))
	{
		DocInfo.pDocName   = L"Raw ESC/POS Document";
		DocInfo.pOutputFile = NULL;
		DocInfo.pDatatype   = L"RAW";

		if (StartDocPrinterW(hPrinter, 1, (LPBYTE)&DocInfo))
		{
			if (StartPagePrinter(hPrinter))
			{
				// Texto para bytes (ANSI -> ESC/POS aceita)
				iLen = texto.Length();
				pData = (LPBYTE)texto.c_str();

				WritePrinter(hPrinter, pData, iLen, &dwWritten);

				EndPagePrinter(hPrinter);
			}
			EndDocPrinter(hPrinter);
		}
		ClosePrinter(hPrinter);
	}
}
