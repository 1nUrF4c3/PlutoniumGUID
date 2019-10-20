//=====================================================================================

#pragma once

#include <Windows.h>
#include <TlHelp32.h>

//=====================================================================================

class cMemory
{
public:
	
	static BOOL MemRead(const char* process, LPCVOID address, LPVOID buffer, SIZE_T length)
	{
		return ReadProcessMemory(OpenProcess(PROCESS_ALL_ACCESS, FALSE, EnumProcess(process)), address, buffer, length, NULL);
	}

	static BOOL MemWrite(const char* process, LPVOID address, LPCVOID buffer, SIZE_T length)
	{
		return WriteProcessMemory(OpenProcess(PROCESS_ALL_ACCESS, FALSE, EnumProcess(process)), address, buffer, length, NULL);
	}

private:

	static DWORD EnumProcess(const char* name)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		PROCESSENTRY32 ProcessEntry = { NULL };
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

		for (BOOL bSuccess = Process32First(hSnapshot, &ProcessEntry); bSuccess; bSuccess = Process32Next(hSnapshot, &ProcessEntry))
		{
			if (!strcmp(ProcessEntry.szExeFile, name))
				return ProcessEntry.th32ProcessID;
		}

		return NULL;
	}
};

//=====================================================================================