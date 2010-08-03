// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "../OracleDB/Oracle.h"
//#include "../MysqlDB/Connection.h"
//#include "../Connection.h"
#include "../CommonLib/CTI_Typedfile.h"
#include <string>
#include "../SqlServerDB/ado2.h"
//using namespace CTI::PP;
//CTI::PP::MessageQueue queue;

//typedef int (*ModuleSend)(unsigned long param1)
typedef void (*_Start)();
typedef int	(* _Moduleinput)(UINT unitid,unsigned short taskclass,unsigned short moduleid,UINT datatype,char * databuff,unsigned long datalen,UINT leave0,UINT leave1,char * leaveV);

_Moduleinput modinput;
//************************************
// Method:    AddConnectionInfo
// FullName:  AddConnectionInfo
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int dbType 数据库类型
// Parameter: int count 创建连接数
//************************************

struConnectinfo GetConnectionInfo(int dbType,const std::string& server,const std::string& db, const std::string& user, const std::string& pwd)
{
	static int connId = 0;
	struConnectinfo conn;
	conn.conid = ++connId;
	conn.connecttype= 1;
	conn.conNumber = 1;
	strcpy(conn.Server,server.c_str());
	strcpy(conn.pwd,pwd.c_str());
	strcpy(conn.user, user.c_str());
	conn.DBtype = dbType;
	strcpy(conn.database,db.c_str());
	return conn;
}

LINE_HEAD* MsgChunkFac(int dataType)
{
    LINE_HEAD* pHead = (LINE_HEAD*)malloc(sizeof(LINE_HEAD));
    memset(pHead,0,sizeof(LINE_HEAD));
    pHead->datatype = dataType;
    pHead->moduleid = 1;
    pHead->unitid = 1;
    pHead->taskclass = 1;
    return pHead;
}

int PushData(LINE_HEAD* pHead,void* data, int dataLen, int pos = 0)
{
    ASSERT(NULL != pHead);
    if(pHead->datalen + dataLen > sizeof(pHead->databuff))
        return -1;
    memcpy(pHead->databuff+pos,data,dataLen);
    pHead->datalen = dataLen;
	return dataLen;
}

struDBinfo getDbInfo(std::string sql,int connId,int tbf)
{
    struDBinfo db;
    memset(&db,0,sizeof(struDBinfo));
    db.baseid=1;
    db.conid = connId;
    db.datalen = -1;
    db.Line = 2;
    db.nodeid =3;
    db.nodeObjid = 4;
    db.ResultFlag = 1;
    db.sqltype = 1;
    strcpy(db.strsql,sql.c_str());
    db.tableflag = tbf;
    return db;
}
Trunk_Fieldinfo getFieldInfo(std::string sql,int connId)
{
    Trunk_Fieldinfo db;
    memset(&db,0,sizeof(Trunk_Fieldinfo));
    db.baseid=1;
    db.conid = connId;
    db.Line = 2;
    db.nodeid =3;
    db.nodeObjid = 4;
    db.sqltype = 1;
    strcpy(db.strsql,sql.c_str());
    return db;
}
void SendMsg(LINE_HEAD& head)
{
    modinput(head.unitid,head.taskclass,head.moduleid,head.datatype,head.databuff,head.datalen,head.leave0,head.leave1,head.leaveV);
}
using namespace CTI::Sqlserver;
int main(int argc, char* argv[])
{
    /*
    CADODatabase ado;
    ado.SetConnectionString("Provider=SQLOLEDB.1;Persist Security Info=True;User ID=sa;Password=111111;Initial Catalog=cti;Data Source=127.0.0.1");
			ado.Open();
    CADORecordset rs(&ado);
    rs.Open("select * from t_line_agentno");
    if(!rs.IsEof())
    {

    }
    */
   // ::CoInitialize(NULL);
	HMODULE mod = LoadLibrary("DataBase.dll");
    ::CoInitialize(NULL);
	_Start start = (_Start)GetProcAddress(mod,"Start");
	modinput = (_Moduleinput)GetProcAddress(mod,"Moduleinput");
	start();
//	for (int i = 0; i < 1 ; ++i)
	{
        LINE_HEAD* head = MsgChunkFac(D_DB_CONNECT);
        struConnectinfo conn = GetConnectionInfo(3,"127.0.0.1","cti","sa","111111");
        int dlen = PushData(head,&conn,sizeof(struConnectinfo));
        SendMsg(*head);
        free(head);
        system("pause");
        head = MsgChunkFac(D_DB_RESULT);
        struDBinfo dbinfo = getDbInfo(" select * from T_Line_AgentNo",conn.conid,T_Line_AgentNo);
        PushData(head,&dbinfo,sizeof(struDBinfo));
        SendMsg(*head);
        free(head);
        system("pause");
        head = MsgChunkFac(D_DB_FIELD);
        Trunk_Fieldinfo finfo = getFieldInfo("select * from Table_1",conn.conid);
        PushData(head,&finfo,sizeof(Trunk_Fieldinfo));
        SendMsg(*head);
        head = NULL;
	}

	system("pause");
	FreeLibrary(mod);
	return 0;
}

