// ConnectionManager.h: interface for the ConnectionManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTIONMANAGER_H__5F677581_596C_4DBC_862E_5ADBBC64D030__INCLUDED_)
#define AFX_CONNECTIONMANAGER_H__5F677581_596C_4DBC_862E_5ADBBC64D030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <map>
#include "DBAccess/IConnection.h"
#include "ProtocalParse/ConnectionInfo.h"
#include "CommonLib/Mutex.h"

namespace CTI
{
	namespace DB
	{
		class ConnectionManager  
		{
			typedef std::map<int , DBAccess::IConnection*> ConnMap;
		private:
			 ConnMap m_connMap;
             Common::Mutex m_lock;
		public:
			ConnectionManager();
			virtual ~ConnectionManager();
		public:
			DBAccess::IConnection* Find(int connid);
			void Add(PP::ConnectionInfo& conn);
			void Remove(int connid);
		private:
			DBAccess::IConnection* CreateConn(PP::ConnectionInfo &connInfo);
			class ConnReleaseHelper
			{
			public:
				inline void operator ()(ConnMap::value_type &conn)
				{
					delete conn.second;
				}
			};
		};
	}
}


#endif // !defined(AFX_CONNECTIONMANAGER_H__5F677581_596C_4DBC_862E_5ADBBC64D030__INCLUDED_)
