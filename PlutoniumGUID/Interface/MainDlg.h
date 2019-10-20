//=====================================================================================

#pragma once

#include "../Resources/Resource.h"
#include "../Interface/WinAPI/Button.hpp"
#include "../Interface/WinAPI/Dialog.hpp"
#include "../Helpers/Memory.hpp"
#include "../Helpers/Message.hpp"

//=====================================================================================

#define OFF_GUID_1 0x3030CA8
#define OFF_GUID_2 0x3030CB0
#define OFF_GUID_3 0x20345B58
#define OFF_GUID_4 0x20315EE0

//=====================================================================================

class cMainDlg : public cDialog
{
public:

	cMainDlg(HINSTANCE instance);
	~cMainDlg() {};

private:

	template<typename... Parameters>
	inline std::string VariadicText(LPCSTR format, Parameters... params) 
	{
		char szBuffer[0x1000] = { NULL };
		sprintf_s(szBuffer, format, params...);
		return szBuffer;
	}

	DLG_HANDLER(OnInit);
	DLG_HANDLER(OnClose);
	DLG_HANDLER(OnGenerateNew);

	unsigned int GenerateNew();

	ctrl::cButton _generateGuid;

	HINSTANCE _instance = NULL;
};

//=====================================================================================