// DbInfo.cpp: implementation of the DbInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DbInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
	namespace PP
	{
        DbInfo::DbInfo():m_rcCount(0)
		{
            memset(&m_data,0,sizeof(struDBinfo));
		}

		DbInfo::~DbInfo()
		{

		}
		DbInfo& DbInfo::operator = ( const struDBinfo& o )
		{
			memcpy(&m_data,&o,sizeof(struDBinfo));
            m_rcCount = 0;
			return *this;
		}

		DbInfo::operator struDBinfo() const
		{
			return m_data;
		}   
        BOOL DbInfo::operator << (const IRecord* tb)
        {
            ASSERT(tb != NULL);
            if((tb->Size() + m_data.datalen) > MAX_DBRESULT_LEN)
            {
                return FALSE;
            }
            else
            {
                memcpy(m_data.DBresult+m_data.datalen,tb->Data(),tb->Size());
                m_data.datalen += tb->Size();
            }
            return TRUE;
        }
	}
}