// ConnectionManager.cpp: implementation of the ConnectionManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataBase.h"
#include "ConnectionManager.h"
#include "DbAccess/DbFactory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
	namespace DB
	{
		ConnectionManager::ConnectionManager()
		{
			
		}
		
		ConnectionManager::~ConnectionManager()
		{
			std::for_each(m_connMap.begin(),m_connMap.end(),ConnReleaseHelper());
			m_connMap.clear();
		}
		void ConnectionManager::Add(PP::ConnectionInfo& connInfo)
		{
            m_lock.Lock(INFINITE);
			DBAccess::IConnection* conn = CreateConn(connInfo);
			m_connMap.insert(std::make_pair(connInfo.ConId(),conn));
            m_lock.Unlock();
		}
		DBAccess::IConnection* ConnectionManager::CreateConn(PP::ConnectionInfo &connInfo)
		{
			DBAccess::DbFactory fac;
			return fac.GetConnection(connInfo);
		}
		
		DBAccess::IConnection* ConnectionManager::Find( int connid )
		{
            m_lock.Lock(INFINITE);
            DBAccess::IConnection* conn = NULL;
			if(m_connMap.find(connid) != m_connMap.end())
			{
               
				conn =  m_connMap[connid];
			}
            m_lock.Unlock();
			return conn;
		}
	}
}

