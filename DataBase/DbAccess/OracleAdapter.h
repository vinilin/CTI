// OracleAdapter.h: interface for the OracleAdapter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORACLEADAPTER_H__6EAF50C1_E972_46A2_96F5_64641E04E99D__INCLUDED_)
#define AFX_ORACLEADAPTER_H__6EAF50C1_E972_46A2_96F5_64641E04E99D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../ProtocalParse/ConnectionInfo.h"
#include "../OracleDB/Connection.h"

using namespace CTI::PP;
namespace CTI
{
	namespace DBAccess
	{
		class OraRsAdapter
		{
		public:
			
		};
		class OraConnAdpter
		{
		private:
			CTI::Oracle::Connection m_conn;
		public:
			OraConnAdpter();
			~OraConnAdpter();
		public:
			void Open(const ConnectionInfo& connInfo);
			void Execute(const std::string& sql);
			Oracle::ResultSet* Select(const std::string& sql);
		};
	}
}


#endif // !defined(AFX_ORACLEADAPTER_H__6EAF50C1_E972_46A2_96F5_64641E04E99D__INCLUDED_)
