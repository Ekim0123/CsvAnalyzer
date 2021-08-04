//-----------------------------------------------------
// Purpose    : Header of CvsAnalyzer_frm class.
//              Handles the windows form UI.
//-----------------------------------------------------
// Clas       : CsvAnalyzer_frm class
//-----------------------------------------------------

#include "FileHandler.h"
#include <string>

namespace CsvAnalyzer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;
	using namespace std;

	/// <summary>
	/// Summary for CsvAnalyzer_frm
	/// </summary>
	public ref class CsvAnalyzer_frm : public System::Windows::Forms::Form
	{
	public:
		FileHandler^ g_fHandler;

		CsvAnalyzer_frm(void)
		{
			InitializeComponent();
			g_fHandler = gcnew FileHandler();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CsvAnalyzer_frm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ openFile_btn;
	protected:
	private: System::Windows::Forms::TextBox^ filePath_txtBox;
	private: System::Windows::Forms::Button^ analyze_btn;
	private: System::Windows::Forms::Button^ gen_file_btn;
	private: System::Windows::Forms::Label^ text_label;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;
	private: System::Windows::Forms::RichTextBox^ richTextBox;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFile_btn = (gcnew System::Windows::Forms::Button());
			this->filePath_txtBox = (gcnew System::Windows::Forms::TextBox());
			this->analyze_btn = (gcnew System::Windows::Forms::Button());
			this->gen_file_btn = (gcnew System::Windows::Forms::Button());
			this->text_label = (gcnew System::Windows::Forms::Label());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->richTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// openFile_btn
			// 
			this->openFile_btn->Location = System::Drawing::Point(23, 49);
			this->openFile_btn->Name = L"openFile_btn";
			this->openFile_btn->Size = System::Drawing::Size(112, 30);
			this->openFile_btn->TabIndex = 0;
			this->openFile_btn->Text = L"Open File";
			this->openFile_btn->UseVisualStyleBackColor = true;
			this->openFile_btn->Click += gcnew System::EventHandler(this, &CsvAnalyzer_frm::openFile_btn_Click);
			// 
			// filePath_txtBox
			// 
			this->filePath_txtBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->filePath_txtBox->Location = System::Drawing::Point(141, 48);
			this->filePath_txtBox->Name = L"filePath_txtBox";
			this->filePath_txtBox->Size = System::Drawing::Size(382, 28);
			this->filePath_txtBox->TabIndex = 1;
			// 
			// analyze_btn
			// 
			this->analyze_btn->Location = System::Drawing::Point(171, 108);
			this->analyze_btn->Name = L"analyze_btn";
			this->analyze_btn->Size = System::Drawing::Size(117, 48);
			this->analyze_btn->TabIndex = 2;
			this->analyze_btn->Text = L"Analyze File";
			this->analyze_btn->UseVisualStyleBackColor = true;
			this->analyze_btn->Click += gcnew System::EventHandler(this, &CsvAnalyzer_frm::analyze_btn_Click);
			// 
			// gen_file_btn
			// 
			this->gen_file_btn->Enabled = false;
			this->gen_file_btn->Location = System::Drawing::Point(171, 255);
			this->gen_file_btn->Name = L"gen_file_btn";
			this->gen_file_btn->Size = System::Drawing::Size(117, 48);
			this->gen_file_btn->TabIndex = 3;
			this->gen_file_btn->Text = L"Generate file";
			this->gen_file_btn->UseVisualStyleBackColor = true;
			this->gen_file_btn->Click += gcnew System::EventHandler(this, &CsvAnalyzer_frm::gen_file_btn_Click);
			// 
			// text_label
			// 
			this->text_label->AutoSize = true;
			this->text_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->text_label->Location = System::Drawing::Point(167, 190);
			this->text_label->Name = L"text_label";
			this->text_label->Size = System::Drawing::Size(60, 24);
			this->text_label->TabIndex = 4;
			this->text_label->Text = L"label1";
			this->text_label->Visible = false;
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog";
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->Filter = L"CSV file format|*.csv";
			this->saveFileDialog->Title = L"Save csv file";
			// 
			// richTextBox
			// 
			this->richTextBox->Location = System::Drawing::Point(23, 340);
			this->richTextBox->Name = L"richTextBox";
			this->richTextBox->Size = System::Drawing::Size(478, 184);
			this->richTextBox->TabIndex = 5;
			this->richTextBox->Text = L"";
			// 
			// CsvAnalyzer_frm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(536, 540);
			this->Controls->Add(this->richTextBox);
			this->Controls->Add(this->text_label);
			this->Controls->Add(this->gen_file_btn);
			this->Controls->Add(this->analyze_btn);
			this->Controls->Add(this->filePath_txtBox);
			this->Controls->Add(this->openFile_btn);
			this->Name = L"CsvAnalyzer_frm";
			this->Text = L"CsvAnalyzer_frm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openFile_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog->ShowDialog();
		filePath_txtBox->Text = openFileDialog->FileName;
	}
	private: System::Void analyze_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		int ret = 0;

		//Check file format.
		if (!filePath_txtBox->Text->Contains(".csv")) {
			MessageBox::Show("File format is invalid!");
			return;
		}

		text_label->Visible = true;
		text_label->Text = "Please wait...";

		//Disable the button to avoid being clicked again during the process.
		analyze_btn->Enabled = false;
		openFile_btn->Enabled = false;

		//Convert System::String to std::string before starting the analyze process.
		char* file_name = (char*)(Marshal::StringToHGlobalAnsi(filePath_txtBox->Text)).ToPointer();
		ret = g_fHandler->startAnalyzeCSVFile(file_name);
		if (ret == PROCESS_OPEN_ERR) {
			MessageBox::Show("File open error!\nFile is open for edit. Please close the file.");
		}
		else {
			//Enable disbled/hidden buttons for another processing.
			analyze_btn->Enabled = true;
			openFile_btn->Enabled = true;

			//Prepare for file generation.
			gen_file_btn->Enabled = true;
			text_label->Text = "Processing completed!";
		}
	}
	private: System::Void gen_file_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		int ret = PROCESS_OK;
		list<outputData>* output;
		string str;
		String^ sysString;

		saveFileDialog->ShowDialog();

		output = g_fHandler->getOutputData();

		for (auto it = output->begin(); it != output->end(); it++) {
			str = it->phone_num + ", " + to_string(it->total_sent) + ", " + to_string(it->total_received) + ", " + it->day_highest + ", " + it->receiver_num + ", " + it->interlocutor + "\n";
			sysString = gcnew String(str.c_str());
			richTextBox->Text += sysString;
		}

		richTextBox->SaveFile(saveFileDialog->FileName);
	}
};
}
