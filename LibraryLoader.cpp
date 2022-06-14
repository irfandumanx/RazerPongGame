#include "LibraryLoader.h"
#include <tchar.h>
#include <iostream>

using namespace RKeyboard;
using namespace std;

void LibraryLoader::init() {
	if (ChromaAnimationAPI::InitAPI() != 0)
	{
		cerr << "Chroma kütüphanesi baþlatýlamadý. Bu bir yanlýþ dosya yolu sorunu olabilir!" << endl;
		exit(1);
	}

	ChromaSDK::APPINFOTYPE appInfo = {};

	_tcscpy_s(appInfo.Title, 256, _T("irfandumanx"));
	_tcscpy_s(appInfo.Description, 1024, _T("Masa tenisi gibi oyun adýný bilmiyorum"));
	_tcscpy_s(appInfo.Author.Name, 256, _T("Ýrfan DUMAN"));
	_tcscpy_s(appInfo.Author.Contact, 256, _T("cv.irfanduman.com.tr"));
	appInfo.SupportedDevice = (0x01); //Sadece klavye

	appInfo.Category = 1;

	RZRESULT result = ChromaAnimationAPI::InitSDK(&appInfo);
	if (result != RZRESULT_SUCCESS)
	{
		cerr << "Chroma kütüphanesi yüklenemedi. Bu bir #include sorunu olabilir!" << endl;
		exit(1);
	}
	Sleep(100); //SDK için biraz mühlet

}