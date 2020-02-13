#pragma once
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include <cstdio>

#include <codecvt>

namespace GetCommandHistory {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(13, 13);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(661, 449);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(686, 474);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"MyForm";
			this->Text = L"GetCommandHistory";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		ShellExecute(NULL, L"open", L"powershell.exe", L"/c Get-Content (Get-PSReadlineOption).HistorySavePath > .\\test.txt ", L"", SW_HIDE);

		setlocale(LC_ALL, "");

		wifstream ifs(".\\test.txt");
		ifs.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, little_endian>));
		wstring str((istreambuf_iterator<wchar_t>(ifs)), istreambuf_iterator<wchar_t>());


		ifs >> str;
		String^ s1 = gcnew String(str.c_str());

		this->richTextBox1->Text = s1;
	}
	};
}
