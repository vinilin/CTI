// Connection.cpp: implementation of the Connection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Connection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace Mysql
    {
        Connection::Connection()
        {
            m_mysql = mysql_init(NULL);
        }

        Connection::~Connection()
        {
            Close();
        }
        void Connection::Open(std::string host
                            , std::string user
                            , std::string password
                            , std::string db
                            , int port
                            , const char* unixSocket
                            , unsigned long clientFlag)
        {
            ASSERT(m_mysql != NULL);
            if(!mysql_real_connect( m_mysql
                            ,host.c_str()
                            ,user.c_str()
                            ,password.c_str()
                            ,db.c_str()
                            ,port
                            ,unixSocket
                            ,clientFlag) )
            {
                throw Error(m_mysql,__FILE__, __LINE__);
            }
	    //mysql_query(&mysql,"set names gbk");//设置为中文
        }
        void Connection::Execute(std::string const& sql)
        {
            ASSERT(m_mysql != NULL);

            if(mysql_query(m_mysql, sql.c_str()) != 0)
            {
                throw Error(m_mysql, __FILE__, __LINE__);
            }
        }
        ResultSet* Connection::Select(std::string const& sql)
        {
            ASSERT(m_mysql != NULL);
			Execute(sql);
			ResultSet *rs = NULL;
            if(mysql_field_count(m_mysql) > 0)
            {
                rs = new ResultSet(m_mysql);
            }
			return rs;
        }
        
        void Connection::Close()
        {
            if(m_mysql != NULL)
            {
              mysql_close(m_mysql);
              m_mysql = NULL;
            }
        }
        
            
    }
}
