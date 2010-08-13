// ConnectionInfo.h: interface for the ConnectionInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONINFO_H__47670F4C_85D2_4ACE_BA76_F3355B3F9A15__INCLUDED_)
#define AFX_CONNECTIONINFO_H__47670F4C_85D2_4ACE_BA76_F3355B3F9A15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include "../CommonLib/DataType.h"
#include "../CommonLib/CTI_Typedfile.h"

namespace CTI
{
    namespace PP // ProtocalParse
    {
		
        class ConnectionInfo  
        {
        private:
	    struConnectinfo m_connInfo;
        public:
            ConnectionInfo();
            virtual ~ConnectionInfo();
        public:
            inline Common::int32 ConId() const{ return m_connInfo.conid; }
            inline Common::int32 DbType() const{ return m_connInfo.DBtype; }
            inline std::string  Server() const{ return m_connInfo.Server; }
            inline std::string  Database() const{ return m_connInfo.database; }
            inline std::string  User() const { return m_connInfo.user; }
            inline std::string  Password() const{ return m_connInfo.pwd; }
            inline Common::int32 ConnectType() const{ return m_connInfo.connecttype; }
            inline Common::int32 ConNumber() const{ return m_connInfo.conNumber; }

        public:
            ConnectionInfo& operator= ( const struConnectinfo& o );
            operator struConnectinfo() const;
            bool operator== (const ConnectionInfo & rhs);

        };
    }
}

#endif // !defined(AFX_CONNECTIONINFO_H__47670F4C_85D2_4ACE_BA76_F3355B3F9A15__INCLUDED_)
