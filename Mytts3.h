
// Mytts3.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CMytts3App:
// 有关此类的实现，请参阅 Mytts3.cpp
//

class CMytts3App : public CWinApp
{
public:
	CMytts3App();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMytts3App theApp;
