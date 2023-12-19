
// FSK.h: PROJECT_NAME 应用程序的主头文件
//

#if !defined(AFX_FSK_H)
#define AFX_FSK_H

#if _MSC_VER > 1600
#pragma once
#endif // _MSC_VER > 1600

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CFSKApp:
// 有关此类的实现，请参阅 FSK.cpp
//

class CFSKApp : public CWinApp
{
public:
	CFSKApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CFSKApp theApp;


#endif