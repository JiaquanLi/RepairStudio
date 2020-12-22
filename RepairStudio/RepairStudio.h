// RepairStudio.h : main header file for the RepairStudio application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CRepairStudioApp:
// See RepairStudio.cpp for the implementation of this class
//

class CRepairStudioApp : public CBCGPWinApp
{
public:
	CRepairStudioApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
private:
	ULONG_PTR	m_gdiplusToken;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRepairStudioApp theApp;