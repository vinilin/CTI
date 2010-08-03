// TSwitchGroup.h: interface for the TSwitchGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSWITCHGROUP_H__142C67BD_845C_4C7C_9871_8D5807F41556__INCLUDED_)
#define AFX_TSWITCHGROUP_H__142C67BD_845C_4C7C_9871_8D5807F41556__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IRecord.h"
#include "../CommonLib/CTI_Typedfile.h"
namespace CTI
{
    namespace PP
	{
        class RecordSwitchGroup  : public IRecord
        {
        private:
            stru_Switch_Group m_data;
        public:
	        RecordSwitchGroup();
	        virtual ~RecordSwitchGroup();
        public:
            inline virtual int Size() const
            {
                return sizeof(stru_Switch_Group);
            }
            inline virtual int Index() const{return 0;}
            inline virtual void* Data() const
            {
                return (void*)&m_data;
            }
        };
    }
}

#endif // !defined(AFX_TSWITCHGROUP_H__142C67BD_845C_4C7C_9871_8D5807F41556__INCLUDED_)
