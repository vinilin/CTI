// TableFactory.h: interface for the TableFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEFACTORY_H__7068CB86_A4F1_42CA_AD63_C29AF48978BF__INCLUDED_)
#define AFX_TABLEFACTORY_H__7068CB86_A4F1_42CA_AD63_C29AF48978BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../ProtocalParse/IRecord.h"
#include "../ProtocalParse/RecordAgentNo.h"
#include "../ProtocalParse/RecordCallLog.h"
#include "../ProtocalParse/RecordSwitchGroup.h"
#include "../ProtocalParse/RecordSysOption.h"
#include "IResultSet.h"

using namespace CTI::PP;
namespace CTI
{
    namespace DBAccess
    {
        class RecordFactory  
        {
        public:
            RecordFactory();
            virtual ~RecordFactory();
        public:
            PP::IRecord* CreateRecord(IResultSet* rs, int tableType);
        private:
            void CopyData(IResultSet* rs, RecordAgentNo * rd);
            void CopyData(IResultSet* rs, RecordCallLog * rd);
            void CopyData(IResultSet* rs, RecordSysOption * rd);
            void CopyData(IResultSet* rs, RecordSwitchGroup * rd);
        };
    }

}


#endif // !defined(AFX_TABLEFACTORY_H__7068CB86_A4F1_42CA_AD63_C29AF48978BF__INCLUDED_)
