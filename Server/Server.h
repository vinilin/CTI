// Server.h : main header file for the SERVER DLL
//

#if !defined(AFX_SERVER_H__E5AB8E81_30C7_40FD_A044_88AEBCB9F52F__INCLUDED_)
#define AFX_SERVER_H__E5AB8E81_30C7_40FD_A044_88AEBCB9F52F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ProtocalParse/MessageChunk.h"
#include "CommonLib/MessageQueue.h"
/////////////////////////////////////////////////////////////////////////////
// CServerApp
// See Server.cpp for the implementation of this class
//
using namespace CTI::PP;
using namespace CTI::Common;



typedef QsynchronizeQueue<MessageChunk*> MessageQueue;

class CServerApp : public CWinApp
{
    	CWinThread *m_mainTh;
public:
	CServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL]
    void  Start();
	// 主线程函数，获取消息并派送到线程池内处理
	static UINT MainTh(LPVOID param); 
    
    // 工作线程函数，处理具体的消息。
    static DWORD WINAPI WorkTh(LPVOID param);
    
    static UINT OutTh(LPVOID param);

	//{{AFX_MSG(CServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
extern "C" void AFX_EXT_API Start();
extern "C" int AFX_EXT_API	Moduleinput(UINT unitid,unsigned short taskclass,unsigned short moduleid,UINT datatype,char * databuff,unsigned long datalen,UINT leave0,UINT leave1,char * leaveV);

#endif // !defined(AFX_SERVER_H__E5AB8E81_30C7_40FD_A044_88AEBCB9F52F__INCLUDED_)
