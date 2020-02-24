#pragma once
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include <cstdio>

#include <codecvt>
#pragma comment(lib, "shlwapi")
#include <shlwapi.h>
#include <atlstr.h>
#include <vector>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#include <list>
#include <iterator>
#include <algorithm>

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
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(13, 58);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(661, 404);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(39, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 19);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(239, 8);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"表示";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(686, 474);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"MyForm";
			this->Text = L"GetCommandHistory";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		ShellExecute(NULL, L"open", L"powershell.exe", L"/c Get-Content (Get-PSReadlineOption).HistorySavePath > .\\test.txt -Encoding utf8", L"", SW_HIDE);

		setlocale(LC_ALL, "");
		CString path = _T(".\\test.txt");

		while (!PathFileExists(path))
		{
			if (PathFileExists(path)) {
				break;
			}
		}
		wifstream ifs(path);
		ifs.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, little_endian>));
		wstring str((istreambuf_iterator<wchar_t>(ifs)), istreambuf_iterator<wchar_t>());


		ifs >> str;
		String^ s1 = gcnew String(str.c_str());
		std::string str1 = msclr::interop::marshal_as<std::string>(s1);

		auto separator = std::string("\r\n");
		auto separator_length = separator.length();

		auto list = std::vector<std::string>();

		if (separator_length == 0) {
			list.push_back(str1);
		}
		else {
			auto offset = std::string::size_type(0);
			while (1) {
				auto pos = str1.find(separator, offset);
				if (pos == std::string::npos) {
					list.push_back(str1.substr(offset));
					break;
				}
				list.push_back(str1.substr(offset, pos - offset));
				offset = pos + separator_length;
			}
		}

		list.erase(list.end() - 1);

		int val = int::Parse(this->textBox1->Text);

		val = val + 1;

		int displayRowCount;
		std::string t;
		for (int i = list.size() - 1; i > list.size() - val; i--) {
			t += list[i] + "\r\n";
		}

		auto v = gcnew System::String(t.c_str());

		this->richTextBox1->Text = v;
	}
};
}
