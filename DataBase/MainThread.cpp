// MainThread.cpp : implementation file
//

#include "stdafx.h"
#include "DataBase.h"
#include "MainThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MainThread

IMPLEMENT_DYNCREATE(MainThread, CWinThread)

MainThread::MainThread()
{
}

MainThread::~MainThread()
{
}

BOOL MainThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int MainThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(MainThread, CWinThread)
	//{{AFX_MSG_MAP(MainThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MainThread message handlers
