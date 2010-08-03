// DataBase.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "DataBase.h"
#include "DBAccess/Connection.h"
#include "ProtocalParse/MessageChunk.h"
#include "ProtocalParse/DbInfo.h"
#include "SqlServerDB/ado2.h"
#include "DBAccess/RecordFactory.h"
#include "ProtocalParse/FieldInfo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define THREAD_POOL_SIZE 20

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
// CDataBaseApp
MessageQueue g_msgQueue;
ModuleSend g_moduleSend = NULL;
CThreadPool g_threadPool;
std::map<int,struConnectinfo*> g_connMap;
CTI::DB::ConnectionManager g_connMgr;
MessageQueue g_outMsgQueue;

typedef int (*_Moduleoutput)(UINT unitid,unsigned short taskclass,unsigned short moduleid,UINT datatype,char * databuff,unsigned long datalen,UINT leave0,UINT leave1,char * leaveV);
_Moduleoutput g_moduleOutPut = NULL;
/************************************************************************/
/* 从消息中分离出连接信息数据											*/
/************************************************************************/
void AddConnInof(MessageChunk* chunk)
{
	CTI::PP::ConnectionInfo conn ;
	//CTI::PP::MessageChunk msg(*info);
	while(*chunk >> conn)
	{
		g_connMgr.Add(conn);
	}
}

/************************************************************************/
/* 动态表查询以及数据填充                                               */
/************************************************************************/
void RunDynSql(MessageChunk* chunk)
{
    CTI::PP::FieldInfo sql;
    try
    {

        while(*chunk >> sql)
        {
            CTI::DBAccess::IConnection* conn = g_connMgr.Find(sql.ConId());
            if(conn != NULL)
		    {
                if(!conn->IsOpen())
                {
                   conn->Open();
                }
                MessageChunk* rsChunk = new MessageChunk();
                *rsChunk = *chunk;
                CTI::DBAccess::IResultSet* rs = conn->Select(sql.StrSql());
                while(rs->Next())
                {
                    Trunk_Fieldinfo finfo;
                    int cols = rs->GetColumnCount();
                    for(int i = 0; i < cols; ++i )
                    {
                        finfo.Fieldclass[i] = rs->operator [](i)->DataType();
                        finfo.Fieldnamelen[i] = (rs->operator [](i)->ColumnName()).size();
                        char* pFieldName = (char*) malloc(finfo.Fieldnamelen[i]+1);
                        memset(pFieldName,0,finfo.Fieldnamelen[i]+1);
                        memcpy(pFieldName,(rs->operator [](i)->ColumnName()).c_str(),finfo.Fieldnamelen[i]);
                        finfo.pFieldname[i] = pFieldName;
                        void* pcontent = NULL;
                        switch(rs->operator [](i)->DataType())
                        {
                        case 1: //整形
                            finfo.ContentLen[i] = sizeof(int);
                            pcontent = malloc(sizeof(int));
                            *((int*)pcontent) = rs->operator [](i)->AsInt();
                            break;
                        case 2: //小数
                            finfo.ContentLen[i] = sizeof(double);
                            pcontent = malloc(sizeof(double));
                            *((double*)pcontent) = rs->operator [](i)->AsDouble();
                            break;
                        case 3: //字符串
                        case 4: //日期
                            finfo.ContentLen[i] = rs->operator [](i)->AsString().size();
                            pcontent = malloc(rs->operator [](i)->AsString().size());
                            memcpy(pcontent,rs->operator [](i)->AsString().c_str(),finfo.ContentLen[i] );
                            break;
                        default:
                            break;
                        }
                    }
                }
                *rsChunk << sql;
                delete rs;
                g_outMsgQueue.Push(rsChunk);
                if(conn->ConnType() == 1)
                {
                    conn->Close();
                }
            } 
        }

    }
    catch(exception e)
    {

    }
}
/************************************************************************/
/* 定表查询以及填充数据                                                 */
/************************************************************************/
void RunSql(MessageChunk* chunk)
{
    try
    {
        CTI::PP::DbInfo sql;
        MessageChunk* rsChunk = new MessageChunk();
        *rsChunk = *chunk;
        while(*chunk >> sql)
        {
            CTI::DBAccess::IConnection* conn = g_connMgr.Find(sql.ConId());
            if(conn != NULL)
            {
                if(!conn->IsOpen())
                {
                    conn->Open();
                }
                CTI::DBAccess::IResultSet* rs = conn->Select(sql.StrSql());
                CTI::DBAccess::RecordFactory fac;
                
                while(rs->Next())
                {
                    CTI::PP::IRecord* rc = fac.CreateRecord(rs,sql.TableFlag());
                    sql << rc;
                }
                *rsChunk << sql;
                delete rs;
                g_outMsgQueue.Push(rsChunk);
                if(conn->ConnType() == 1)
                {
                    conn->Close();
                }
            }
	    }

    }
    catch (exception e)
    {
       
    }

}


BEGIN_MESSAGE_MAP(CDataBaseApp, CWinApp)
	//{{AFX_MSG_MAP(CDataBaseApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataBaseApp construction

CDataBaseApp::CDataBaseApp()
{
	m_mainTh = NULL;
	
}

void CDataBaseApp::Start()
{
	// 创建输入
	m_mainTh = AfxBeginThread(CDataBaseApp::MainTh,this);
    // 创建输出线程
    AfxBeginThread(CDataBaseApp::OutTh,this);
}


UINT CDataBaseApp::MainTh(LPVOID param)
{
	CDataBaseApp* app = (CDataBaseApp*)param;

	// 设置线程池内线程数量
	g_threadPool.SetPoolSize(THREAD_POOL_SIZE);

	// 创建线程
	g_threadPool.Create();

	while(true)
	{
		MessageQueue::ValueType msg = g_msgQueue.Pop();
		//启动线程处理消息
		g_threadPool.Run(CDataBaseApp::WorkTh,msg,Low);
	}
	return 0;
}
UINT CDataBaseApp::OutTh(LPVOID param)
{
    while(true)
    {
        MessageQueue::ValueType msg = g_outMsgQueue.Pop();
        if(g_moduleOutPut != NULL)
        {
            // 输出
            //g_moduleOutPut(msg.)
        }
            
        delete msg;
    }

}
DWORD CDataBaseApp::WorkTh(LPVOID param)
{
	UserPoolData* ud = (UserPoolData*)param;
	MessageQueue::ValueType msg = (MessageQueue::ValueType)ud->pData;
	switch(msg->DataType())
	{
	case D_DB_CONNECT:
		// 添加数据库连接信息
		AddConnInof(msg);
		break;
	case D_DB_RESULT:
        // 定表处理
		RunSql(msg);
		break;
	case D_DB_FIELD:
        // 动态表处理
        RunDynSql(msg);
		break;
	}
	//释放消息占用内存
	delete msg;
	return 0;
}



/////////////////////////////////////////////////////////////////////////////
// The one and only CDataBaseApp object

CDataBaseApp theApp;
// 动态库启动接口
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
	g_msgQueue.Push(chunk);
	return 0;
}