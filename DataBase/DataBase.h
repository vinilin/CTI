// DataBase.h : main header file for the DATABASE DLL
//

#if !defined(AFX_DATABASE_H__98FEA210_749B_4E5B_8F6C_EBD6BFA680F1__INCLUDED_)
#define AFX_DATABASE_H__98FEA210_749B_4E5B_8F6C_EBD6BFA680F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CommonLib/MessageQueue.h"
#include "CommonLib/ThreadPool.h"
#include "ConnectionManager.h"
#include "ProtocalParse/MessageChunk.h"

/////////////////////////////////////////////////////////////////////////////
// CDataBaseApp
// See DataBase.cpp for the implementation of this class
//
using namespace CTI::PP;
using namespace CTI::Common;
typedef QsynchronizeQueue<MessageChunk*> MessageQueue;

extern MessageQueue g_msgQueue;
extern ModuleSend g_moduleSend;
extern CThreadPool g_threadPool;
extern CTI::DB::ConnectionManager g_connMgr;

class CDataBaseApp : public CWinApp
{

private:
	CWinThread *m_mainTh;

public:
	CDataBaseApp();
public:
	// 启动函数，启动主线程获取消息
	void  Start();

	// 主线程函数，获取消息并派送到线程池内处理
	static UINT MainTh(LPVOID param); 

	// 工作线程函数，处理具体的消息。
	static DWORD WINAPI WorkTh(LPVOID param);

    static UINT OutTh(LPVOID param);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataBaseApp)
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDataBaseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
        
};
extern "C" void AFX_EXT_API Start();
extern "C" int AFX_EXT_API	Moduleinput(UINT unitid,unsigned short taskclass,unsigned short moduleid,UINT datatype,char * databuff,unsigned long datalen,UINT leave0,UINT leave1,char * leaveV);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASE_H__98FEA210_749B_4E5B_8F6C_EBD6BFA680F1__INCLUDED_)
