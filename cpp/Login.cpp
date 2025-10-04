//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Login.h"
#include "Cadastro.h"
#include "Caixa.h"
#include <System.Hash.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	// 1. Validação de campos obrigatórios
	if (Usuario->Text.Trim().IsEmpty() || Senha->Text.IsEmpty())
	{
		ShowMessage("Por favor, preencha o login e a senha.");
		Usuario->SetFocus();
		return;
	}

	// 2. Criptografia da senha usando SHA256
	String senhaPura = Senha->Text;
	String senhaHasheada = THashSHA2::GetHashString(senhaPura);

	// 3. Tentativa de acesso ao banco de dados
	try
	{
		ADOQuery1->Close();
		ADOQuery1->Connection = ADOConnection1;

		// Definindo a SQL com parâmetros nomeados
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("SELECT id_usuario, login FROM usuario");
		ADOQuery1->SQL->Add("WHERE login = :pLogin AND senha = :pSenhaHash");

		// Associando os valores aos parâmetros
		ADOQuery1->Parameters->ParamByName("pLogin")->Value = Usuario->Text.Trim();
		ADOQuery1->Parameters->ParamByName("pSenhaHash")->Value = senhaHasheada;

		// Executando a consulta
		ADOQuery1->Open();

		// 4. Verificando se encontrou o usuário
		if (ADOQuery1->IsEmpty())
		{
			ShowMessage("Login ou senha inválidos!");
			Senha->Clear();
			Usuario->SelectAll();
			Usuario->SetFocus();
		}
		else
		{
			// Login bem-sucedido
			TForm3* formCaixa = new TForm3(this);
			formCaixa->Show();
			this->Hide();
		}
	}
	catch (const Exception &E)
	{
		ShowMessage("Erro ao validar o acesso.\nDetalhes: " + E.Message);
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    	// No Form1, no botão que chama a tela de cadastro
	// Cria uma instância do Form2
	TForm2 *FormCadastro = new TForm2(this);
	try
	{
		// O ShowModal vai exibir o Form2 e PAUSAR a execução aqui
		// até que o FormCadastro seja fechado. O Form1 fica esperando no fundo.
		FormCadastro->ShowModal();
	}
	__finally
	{
		// Assim que o FormCadastro fechar, o código continua e
		// libera a memória dele. O Form1 volta a ser o foco.
		delete FormCadastro;
	}
}
//---------------------------------------------------------------------------

