/********************************************************************
	created:	2010/05/30
	created:	30:5:2010   22:14
	filename: 	D:\Project\CTI\DataBase\DbAccess\Connection.h
	file path:	D:\Project\CTI\DataBase\DbAccess
	file base:	Connection
	file ext:	h
	author:		LinQuan
	purpose:	
*********************************************************************/


#if !defined(AFX_CONNECTION_H__B2AFA638_632D_4704_AFAE_D47F4186E78F__INCLUDED_)
#define AFX_CONNECTION_H__B2AFA638_632D_4704_AFAE_D47F4186E78F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IConnection.h"
#include "../OracleDB/Oracle.h"
#include "../MysqlDB/Connection.h"
#include "../SqlServerDB/ado2.h"
#include "ResultSet.h"

namespace CTI
{
	namespace DBAccess
	{
		//////////////////////////////////////////////////////////////////////////
		// oracle
		class OraConnection : public IConnection
		{
		private:
			CTI::Oracle::Connection m_conn;
		public:
			OraConnection(const ConnectionInfo& connInfo);
			virtual ~OraConnection();
		public:
			virtual void Open();
            virtual BOOL IsOpen();
            virtual void Close();
			virtual void Execute(std::string sql);
			virtual IResultSet* Select(std::string sql);
		};

		//////////////////////////////////////////////////////////////////////////
		// mysql
		class MysqlConnection : public IConnection
		{
		private:
			CTI::Mysql::Connection m_conn;
		public:
			MysqlConnection(const ConnectionInfo& connInfo);
			~MysqlConnection();
		public:
			virtual void Open();
            virtual BOOL IsOpen()
            {
               return m_conn.IsOpen();
            }
            virtual void Close()
            {
                 m_conn.Close();
            }
			virtual void Execute(std::string sql);
			virtual IResultSet* Select(std::string sql);
		};

		//////////////////////////////////////////////////////////////////////////
		// SqlServer
		class SqlConnection: public IConnection
		{
		private:
			CTI::Sqlserver::CADODatabase m_conn;
		public:
			SqlConnection(const ConnectionInfo& connInfo);
			~SqlConnection();
			virtual void Open();
            virtual BOOL IsOpen();
            virtual void Close();
			virtual void Execute(std::string sql);
			virtual IResultSet* Select(std::string sql);
		};
	}
}

#endif // !defined(AFX_CONNECTION_H__B2AFA638_632D_4704_AFAE_D47F4186E78F__INCLUDED_)
