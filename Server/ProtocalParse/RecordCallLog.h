// TCallLog.h: interface for the TCallLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCALLLOG_H__022B3BD1_2BA0_4EB0_BCB7_C60B8BE7BBBB__INCLUDED_)
#define AFX_TCALLLOG_H__022B3BD1_2BA0_4EB0_BCB7_C60B8BE7BBBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IRecord.h"
#include "../CommonLib/CTI_Typedfile.h"
namespace CTI
{
    namespace PP
	{
        class RecordCallLog  : public IRecord
        {
        private:
            stru_Call_Log m_data;
        public:
	        RecordCallLog();
	        virtual ~RecordCallLog();
        public:
            inline virtual int Size()const
            {
                return sizeof(stru_Call_Log);
            }
            inline virtual int Index() const{return 0;}
            inline virtual void* Data() const
            {
                return (void*) &m_data;
            }
        };
    }
}

#endif // !defined(AFX_TCALLLOG_H__022B3BD1_2BA0_4EB0_BCB7_C60B8BE7BBBB__INCLUDED_)
