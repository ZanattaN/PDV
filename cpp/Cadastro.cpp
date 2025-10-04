//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Cadastro.h"
#include "Login.h"
#include <System.Hash.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{

// --- 1. Validação Básica ---
	if (nome_cad->Text.IsEmpty() || usuario_cad->Text.IsEmpty() || senha_cad->Text.IsEmpty())
	{
		ShowMessage("Por favor, preencha os campos de usuário e senha.");
		return;
	}

	// --- 2. Criptografia da senha ---
	String senhaPura = senha_cad->Text;
	String senhaHasheada = THashSHA2::GetHashString(senhaPura);

	// --- 3. Preparação e Execução da Query ---
	try
	{
		if (!Form1->ADOConnection1->Connected)
		{
			Form1->ADOConnection1->Connected = true;
		}

		Form1->ADOQuery1->SQL->Clear();
		Form1->ADOQuery1->SQL->Add("INSERT INTO usuario (nome, login, senha) VALUES (:nome, :login, :senha)");

		Form1->ADOQuery1->Parameters->ParamByName("nome")->Value = nome_cad->Text.Trim();
		Form1->ADOQuery1->Parameters->ParamByName("login")->Value = usuario_cad->Text.Trim();
		Form1->ADOQuery1->Parameters->ParamByName("senha")->Value = senhaHasheada;

		Form1->ADOQuery1->ExecSQL();

		ShowMessage("Usuário cadastrado com sucesso!");

		// Limpa os campos e fecha o formulário
		nome_cad->Clear();
		usuario_cad->Clear();
		senha_cad->Clear();
		nome_cad->SetFocus();
		Close();
	}
	catch (Exception &E)
	{
		ShowMessage("Erro ao cadastrar: " + E.Message);
	}

}
//---------------------------------------------------------------------------
