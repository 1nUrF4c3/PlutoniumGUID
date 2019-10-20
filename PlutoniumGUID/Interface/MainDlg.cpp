//=====================================================================================

#include "MainDlg.h"

//=====================================================================================

cMainDlg::cMainDlg(HINSTANCE instance) : cDialog(IDD_MAIN), _instance(instance)
{
	_messages[WM_INITDIALOG] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnInit);
	_messages[WM_COMMAND] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnCommand);
	_messages[WM_CLOSE] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnClose);

	_events[IDC_GENERATENEW] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnGenerateNew);
}

//=====================================================================================

INT_PTR cMainDlg::OnInit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	cDialog::OnInit(hDlg, message, wParam, lParam);

	HICON hIcon = LoadIcon(_instance, MAKEINTRESOURCE(IDI_ICON));

	SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	DeleteObject(hIcon);

	_generateGuid.Attach(_hwnd, IDC_GENERATENEW);

	return TRUE;
}

//=====================================================================================

INT_PTR cMainDlg::OnClose(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return cDialog::OnClose(hDlg, message, wParam, lParam);
}

//=====================================================================================

INT_PTR cMainDlg::OnGenerateNew(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	unsigned int guid = GenerateNew();

	if (!cMemory::MemWrite("t6rmp.exe", (LPVOID)OFF_GUID_1, &guid, sizeof(unsigned int)) ||
		!cMemory::MemWrite("t6rmp.exe", (LPVOID)OFF_GUID_2, VariadicText("%x", guid).c_str(), VariadicText("%x", guid).length()) ||
		!cMemory::MemWrite("t6rmp.exe", (LPVOID)OFF_GUID_3, &guid, sizeof(unsigned int)) ||
		!cMemory::MemWrite("t6rmp.exe", (LPVOID)OFF_GUID_4, &guid, sizeof(unsigned int)))
		cMessage::ShowError(_hwnd, "Failure.");

	else
		cMessage::ShowInfo(_hwnd, "Success!");

	return TRUE;
}

//=====================================================================================