//=====================================================================================

#include "Interface/MainDlg.h"

//=====================================================================================

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	InitCommonControls();

	cMainDlg MainDLG(hInstance);

	return (INT)MainDLG.RunModeless();
}

//=====================================================================================