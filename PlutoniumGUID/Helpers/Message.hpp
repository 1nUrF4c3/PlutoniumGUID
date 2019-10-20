//=====================================================================================

#pragma once

#include "../Interface/WinAPI/StdAfx.hpp"

//=====================================================================================

class cMessage
{
public:

	enum eMsgType
	{
		Error,
		Warning,
		Info,
		Question,
	};

	static void ShowError(HWND parent, const std::string& msg, const std::string& title = "Error")
	{
		Show(msg, title, Error, parent);
	}

	static void ShowWarning(HWND parent, const std::string& msg, const std::string& title = "Warning")
	{
		Show(msg, title, Warning, parent);
	}

	static void ShowInfo(HWND parent, const std::string& msg, const std::string& title = "Info")
	{
		Show(msg, title, Info, parent);
	}

	static bool ShowQuestion(HWND parent, const std::string& msg, const std::string& title = "Question")
	{
		return Show(msg, title, Question, parent) == IDYES;
	}

private:

	static int Show(const std::string& msg, const std::string& title, eMsgType type, HWND parent = NULL)
	{
		UINT uType;

		switch (type)
		{
		case Error:
			uType = MB_OK | MB_ICONERROR;
			break;

		case Warning:
			uType = MB_OK | MB_ICONWARNING;
			break;

		case Info:
			uType = MB_OK | MB_ICONINFORMATION;
			break;

		case Question:
			uType = MB_YESNO | MB_ICONQUESTION;
			break;
		}

		return MessageBox(parent, msg.c_str(), title.c_str(), uType);
	}
};

//=====================================================================================