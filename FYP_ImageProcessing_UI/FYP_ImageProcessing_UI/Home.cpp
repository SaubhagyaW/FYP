#include "Home.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	FYP_ImageProcessing_UI::Home homeForm;
	Application::Run(%homeForm);
}
