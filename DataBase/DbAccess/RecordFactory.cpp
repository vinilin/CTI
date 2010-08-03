// TableFactory.cpp: implementation of the TableFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "../ProtocalParse/RecordAgentNo.h"
#include "../ProtocalParse/RecordCallLog.h"
#include "../ProtocalParse/RecordSwitchGroup.h"
#include "../ProtocalParse/RecordSysOption.h"
using namespace CTI::PP;
namespace CTI
{
    namespace DBAccess
    {
        RecordFactory::RecordFactory()
        {

        }

        RecordFactory::~RecordFactory()
        {

        }
        IRecord* RecordFactory::CreateRecord(IResultSet* rs, int tableType)
        {
            IRecord* rd = NULL;
            switch(tableType)
            {
            case T_Sys_option:
                rd = new RecordSysOption();
                CopyData(rs,(RecordSysOption*)rd);
                break;
            case T_Line_AgentNo:
                rd = new RecordAgentNo();
                CopyData(rs,(RecordAgentNo*)rd);
                break;
            case T_Call_Log:
                rd = new RecordCallLog();
                CopyData(rs,(RecordCallLog*)rd);
                break;
            case T_Switch_Group:
                rd = new RecordSwitchGroup();
                CopyData(rs,(RecordSwitchGroup*)rd);
                break;
            }
            
            return rd;
        }
        void RecordFactory::CopyData(IResultSet* rs, RecordAgentNo * rd)
        {
            stru_Line_AgentNo *agentNo  = (stru_Line_AgentNo *) rd->Data();
            agentNo->Groupid = (*(*rs)["GroupID"]);
            agentNo->ID = (*rs)["ID"]->AsLong();
            agentNo->Line = (*rs)["Line"]->AsLong();
            strcpy(agentNo->Phone,((*rs)["Phone"])->AsString().c_str());
            
        }
        void RecordFactory::CopyData(IResultSet* rs, RecordCallLog * rd)
        {
            stru_Call_Log *callLog = (stru_Call_Log*) rd->Data();
            callLog->CallLen = (*(*rs)["CallLen"]);
            callLog->ID = (*rs)["ID"]->AsLong();
            strcpy(callLog->CallBegin,((*rs)["CallBegin"])->AsString().c_str());
            strcpy(callLog->Callee,((*rs)["Callee"])->AsString().c_str());
            strcpy(callLog->CallEnd,((*rs)["CallEnd"])->AsString().c_str());
            strcpy(callLog->Caller,((*rs)["Caller"])->AsString().c_str());
        }
        void RecordFactory::CopyData(IResultSet* rs, RecordSysOption * rd)
        {
            stru_Sys_option *sysOption = (stru_Sys_option *)rd->Data();
            strcpy(sysOption->IniValue,((*rs)["IniValue"])->AsString().c_str());
            strcpy(sysOption->OpText,((*rs)["OpText"])->AsString().c_str());
            strcpy(sysOption->TitleName,((*rs)["TitleName"])->AsString().c_str());
        }
        void RecordFactory::CopyData(IResultSet* rs, RecordSwitchGroup * rd)
        {
            stru_Switch_Group *switchGroup = (stru_Switch_Group *) rd->Data();
            switchGroup->CallLaw = (*(*rs)["CallLaw"]);
            switchGroup->ID =  (*rs)["ID"]->AsLong();
            switchGroup->limit =  (*(*rs)["limit"]);
            switchGroup->ringlen =  (*(*rs)["ringlen"]);
        }
    }
}
