// TableFactory.h: interface for the TableFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEFACTORY_H__7068CB86_A4F1_42CA_AD63_C29AF48978BF__INCLUDED_)
#define AFX_TABLEFACTORY_H__7068CB86_A4F1_42CA_AD63_C29AF48978BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../ProtocalParse/IRecord.h"
#include "IResultSet.h"
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
            PP::IRecord* GetTable(IResultSet* rs, int tableType);
        };
    }

}


#endif // !defined(AFX_TABLEFACTORY_H__7068CB86_A4F1_42CA_AD63_C29AF48978BF__INCLUDED_)
