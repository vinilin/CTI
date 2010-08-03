// Connection.cpp: implementation of the Connection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Connection.h"

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
	namespace DBAccess
	{
		//////////////////////////////////////////////////////////////////////////
		// Oracle数据库
		OraConnection::~OraConnection()
		{
			m_conn.Close();
		}
		OraConnection::OraConnection( const ConnectionInfo& connInfo ) :IConnection(connInfo)
		{
			
		}
		void OraConnection::Open()
		{
			m_conn.Open(m_connInfo.Server(),m_connInfo.User(),m_connInfo.Password());
		}
		
		void OraConnection::Execute( std::string sql )
		{
			m_conn.Execute(sql);
		}
		
		IResultSet* OraConnection::Select( std::string sql )
		{
            return new DBAccess::OracleRS(m_conn.Select(sql));
			//return NULL;
		}
        
        BOOL OraConnection::IsOpen()
        {
            return m_conn.IsOpend();
        }
        
        void OraConnection::Close()
        {
            m_conn.Close();
        }
		

		//////////////////////////////////////////////////////////////////////////
		//Mysql数据库
		MysqlConnection::MysqlConnection( const ConnectionInfo& connInfo ) :IConnection(connInfo)
		{
			
		}
		
		MysqlConnection::~MysqlConnection()
		{
			m_conn.Close();
		}
		
		void MysqlConnection::Open()
		{
			m_conn.Open(m_connInfo.Server(),m_connInfo.User(),m_connInfo.Password(),m_connInfo.Database());
		}
		
		void MysqlConnection::Execute( std::string sql )
		{
			m_conn.Execute(sql);
		}
		
		IResultSet* MysqlConnection::Select( std::string sql )
		{
            return new MysqlRS(m_conn.Select(sql));
		}

		//////////////////////////////////////////////////////////////////////////
		// SqlServer数据库
		SqlConnection::SqlConnection( const ConnectionInfo& connInfo ) : IConnection(connInfo)
		{
            std::string strConn = "Provider=SQLOLEDB.1;Persist Security Info=True;User ID=";
            strConn+=connInfo.User();
            strConn+=";Password=";
            strConn+=connInfo.Password();
            strConn+=";Initial Catalog=";
            strConn+=connInfo.Database();
            strConn+=";Data Source=";
            strConn+=connInfo.Server();
            m_conn.SetConnectionString(strConn.c_str());
		}
		
		void SqlConnection::Open()
		{
			m_conn.Open();
        }
		
		void SqlConnection::Execute( std::string sql )
		{
			m_conn.Execute(sql.c_str());
		}
		
		IResultSet* SqlConnection::Select( std::string sql )
		{
			SqlserverRS* rs = new SqlserverRS(&m_conn,sql);
            return rs;
		}
        
        SqlConnection::~SqlConnection()
        {
            m_conn.Close();
        }
        
        BOOL SqlConnection::IsOpen()
        {
            return m_conn.IsOpen();
        }
        
        void SqlConnection::Close()
        {
            m_conn.Close();
        }
        

	}
}

