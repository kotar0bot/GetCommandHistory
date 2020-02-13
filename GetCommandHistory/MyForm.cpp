#include "MyForm.h"

using namespace GetCommandHistory;

[STAThreadAttribute]
int main() {
	Application::Run(gcnew MyForm());
	return 0;
}