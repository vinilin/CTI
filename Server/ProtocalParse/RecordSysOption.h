// TSysOption.h: interface for the TSysOption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSYSOPTION_H__6380FB4A_CCBD_4F32_A272_5A08312A03E0__INCLUDED_)
#define AFX_TSYSOPTION_H__6380FB4A_CCBD_4F32_A272_5A08312A03E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../CommonLib/CTI_Typedfile.h"
#include "IRecord.h"
namespace CTI
{
	namespace PP
	{
        class RecordSysOption  : public IRecord
		{
        private:
            stru_Sys_option m_data;
		public:
			RecordSysOption();
			virtual ~RecordSysOption();
        public:
            inline virtual int Size() const
            {
                return sizeof(stru_Sys_option);
            }
            inline virtual int Index()const {return 0;}
            inline virtual void* Data() const
            {
                return (void*)&m_data;
            }
		};
	}

}


#endif // !defined(AFX_TSYSOPTION_H__6380FB4A_CCBD_4F32_A272_5A08312A03E0__INCLUDED_)
