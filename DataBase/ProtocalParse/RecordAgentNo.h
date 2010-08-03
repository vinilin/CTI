// TAgentNo.h: interface for the TAgentNo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAGENTNO_H__181A9FD7_6331_4A1A_9992_5F022BAE2975__INCLUDED_)
#define AFX_TAGENTNO_H__181A9FD7_6331_4A1A_9992_5F022BAE2975__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IRecord.h"
#include "../CommonLib/CTI_Typedfile.h"
namespace CTI
{
    namespace PP
	{
        class RecordAgentNo  : public IRecord
        {
        private:
            stru_Line_AgentNo m_data;
        public:
	        RecordAgentNo();
	        virtual ~RecordAgentNo();
        public:
            inline virtual int Size()const
            {
                return sizeof(stru_Line_AgentNo);
            }
            inline virtual int Index() const{return 0;}
            inline virtual void* Data() const
            {
                return (void*)&m_data;
            }
        };
    }
}

#endif // !defined(AFX_TAGENTNO_H__181A9FD7_6331_4A1A_9992_5F022BAE2975__INCLUDED_)
