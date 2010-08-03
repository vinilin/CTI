// ConnectionInfo.cpp: implementation of the ConnectionInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConnectionInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace PP
    {

        ConnectionInfo::ConnectionInfo()
        {

        }

        ConnectionInfo::~ConnectionInfo()
        {

        }
		ConnectionInfo& ConnectionInfo::operator= ( const struConnectinfo& o )
		{
			memcpy(&m_connInfo,&o,sizeof(o));
			return *this;
		}
		ConnectionInfo::operator struConnectinfo() const
		{
			return m_connInfo;
		}
		bool ConnectionInfo::operator== (const ConnectionInfo & rhs)
		{
			return m_connInfo.conid == rhs.ConId();
		}

    }
}
