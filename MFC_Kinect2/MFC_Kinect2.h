
// MFC_Kinect2.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_Kinect2App: 
// �аѾ\��@�����O�� MFC_Kinect2.cpp
//

class CMFC_Kinect2App : public CWinApp
{
public:
	CMFC_Kinect2App();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Kinect2App theApp;