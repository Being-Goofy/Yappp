#include "signIn.h"
#include "chat.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void main(array<String^>^ args) {

	Application::
		SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Pro::SignIn frm;
	Application::Run(% frm);

	if (frm.si) {
		Project1::MyForm1 form;
		Application::Run(% form);
	}
}