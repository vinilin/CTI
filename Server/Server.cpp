// Server.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Server.h"
#include "CommonLib/CTI_Typedfile.h"
#include "CommonLib/MessageQueue.h"
#include "CommonLib/ThreadPool.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CServerApp
CThreadPool g_threadPool;
MessageQueue g_inQueue; // �������
MessageQueue g_outQueue; // �������
BEGIN_MESSAGE_MAP(CServerApp, CWinApp)
	//{{AFX_MSG_MAP(CServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerApp construction

CServerApp::CServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CServerApp object

CServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CServerApp initialization

BOOL CServerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}
void CServerApp::Start()
{
	// ��������
    m_mainTh = AfxBeginThread(CServerApp::MainTh,this);
    // ��������߳�
    AfxBeginThread(CServerApp::OutTh,this);
}

UINT CServerApp::MainTh(LPVOID param)
{
    CServerApp* app = (CServerApp*)param;
    
    // �����̳߳����߳�����
    g_threadPool.SetPoolSize(20);
    
    // �����߳�
    g_threadPool.Create();
    
    while(true)
    {
        MessageQueue::ValueType msg = g_msgQueue.Pop();
        //�����̴߳�����Ϣ
        g_threadPool.Run(CServerApp::WorkTh,msg,Low);
    }
    return 0;
}

DWORD CServerApp::WorkTh(LPVOID param)
{
    UserPoolData* ud = (UserPoolData*)param;
    MessageQueue::ValueType msg = (MessageQueue::ValueType)ud->pData;
    switch(msg->DataType())
    {
    case D_BASE_INIT_COMP:
        // ͨ����ʼ��

        break;
    case D_BASE_CALLIN:
        // ������
        break;
    case D_BASE_TRUNK_INFO:
        // ��̬����
        break;
    case D_DB_RESULT:
        // ������
        RunSql(msg);
        break;
    case D_DB_FIELD:
        // ��̬����
        RunDynSql(msg);
        break;
    }
    //�ͷ���Ϣռ���ڴ�
    delete msg;
    return 0;
}

void Start()
{
    theApp.Start();
}

int Moduleinput(UINT unitid,unsigned short taskclass,unsigned short moduleid,UINT datatype,char * databuff,unsigned long datalen,UINT leave0,UINT leave1,char * leaveV)
{
    LINE_HEAD  data;
    data.unitid = unitid;
    data.taskclass = taskclass;
    data.moduleid = moduleid;
    data.datatype = datatype;
    memcpy(data.databuff,databuff,datalen);
    data.leave0 = leave0;
    data.leave1 = leave1;
    memcpy(data.leaveV,leaveV, sizeof(leaveV));
    data.datalen = datalen;
    MessageChunk *chunk = new MessageChunk(data);
    g_inQueue.Push(chunk);
    return 0;
}
