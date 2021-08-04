//-----------------------------------------------------
// Purpose    : Implements the CvsAnalyzer_frm class.
//              Handles the windows form UI.
//-----------------------------------------------------
// Clas       : CsvAnalyzer_frm class
//-----------------------------------------------------

#include "CsvAnalyzer_frm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

//Run windows form
void main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	CsvAnalyzer::CsvAnalyzer_frm frm;
	Application::Run(% frm);
}