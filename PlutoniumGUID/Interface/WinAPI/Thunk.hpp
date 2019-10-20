//=====================================================================================

#pragma once

#include <stdint.h>
#include <winnt.h>

//=====================================================================================

#if defined (_M_AMD64) || defined (__x86_64__)
#define USE64
#elif defined (_M_IX86) || defined (__i386__)
#define USE32
#endif

//=====================================================================================

#pragma pack(push, 1)
struct sThunkData
{
#if defined USE32
	uint8_t  mov1 = 0xB8;
	void* pInst = nullptr;
	uint16_t fs1 = '\x64\xA3';
	uint8_t  fs2 = FIELD_OFFSET(NT_TIB, ArbitraryUserPointer);
	uint8_t  fs3 = 0;
	uint16_t fs4 = 0;
	uint8_t  mov2 = 0xB8;
	void* pFn = nullptr;
	uint16_t jmp1 = '\xFF\xE0';
#elif defined USE64
	uint16_t mov1 = '\x48\xB8';
	void* pInst = nullptr;
	uint32_t fs1 = '\x65\x48\x89\x04';
	uint8_t  fs2 = 0x25;
	uint8_t  fs3 = FIELD_OFFSET(NT_TIB, ArbitraryUserPointer);
	uint8_t  fs4 = 0;
	uint16_t fs5 = 0;
	uint16_t mov2 = '\x48\xB8';
	void* pFn = nullptr;
	uint16_t jmp1 = '\xFF\xE0';
#endif
	void Setup(void* pInstance, void* pMethod)
	{
		pInst = pInstance;
		pFn = pMethod;
	}
};
#pragma pack(pop)

//=====================================================================================

template<typename Function, typename Class>
class cWin32Thunk;

//=====================================================================================

template<typename Return, typename... Parameters, typename Class>
class cWin32Thunk < Return(WINAPI*)(Parameters...), Class >
{
public:

	using TypeMember = Return(Class::*)(Parameters...);
	using TypeFree = Return(WINAPI*)(Parameters...);

	cWin32Thunk(TypeMember pfn, Class* pInstance)
		: _pMethod(pfn)
		, _pInstance(pInstance)
	{
		DWORD dwOld = 0;
		VirtualProtect(&_thunk, sizeof(_thunk), PAGE_EXECUTE_READWRITE, &dwOld);
		_thunk.Setup(this, &cWin32Thunk::WrapHandler);
	}

	static Return WINAPI WrapHandler(Parameters... args)
	{
		auto _this = reinterpret_cast<cWin32Thunk*>(((PNT_TIB)NtCurrentTeb())->ArbitraryUserPointer);
		return (_this->_pInstance->*_this->_pMethod)(args...);
	}

	TypeFree GetThunk()
	{
		return reinterpret_cast<TypeFree>(&_thunk);
	}

private:

	TypeMember _pMethod = nullptr;
	Class* _pInstance = nullptr;
	sThunkData _thunk;
};

//=====================================================================================