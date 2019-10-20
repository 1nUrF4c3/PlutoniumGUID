//=====================================================================================

#include "MainDlg.h"
#include <random>

//=====================================================================================

unsigned int cMainDlg::GenerateNew() 
{
	static std::random_device rd;
	static std::uniform_int_distribution<unsigned int> dist(0x0, 0xFFFFFFFF);

	return dist(rd);
}

//=====================================================================================
