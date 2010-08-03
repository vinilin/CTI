// Connection.h: interface for the Connection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTION_H__CA9B25F7_E160_484A_BAFF_B941DB3990F8__INCLUDED_)
#define AFX_CONNECTION_H__CA9B25F7_E160_484A_BAFF_B941DB3990F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StdAfx.h"

#include "Error.h"
#include "ResultSet.h"

namespace CTI
{
    namespace Mysql
    {
        class Connection  
        {
        private:
            MYSQL *m_mysql;
            bool m_autoCommit;
        public:
            Connection();
            virtual ~Connection();

        public:
            void Open(std::string host
				, std::string user
				, std::string password
				, std::string db
				, int port = 0
				, const char* unixSocket = NULL 
                , unsigned long clientFlag = 0);
            void Close();
			void Execute(std::string const& sql);
			ResultSet* Select(std::string const& sql); 
            BOOL IsOpen()
            {
                return m_mysql == NULL;
            }
            inline void SetAutoCommit(bool b = true)
            {
                ASSERT(m_mysql != NULL);
                if(mysql_autocommit(m_mysql,b) != 0)
                {
                    throw Error(m_mysql, __FILE__, __LINE__);
                }
                m_autoCommit = b;
            }

        };
    }
}
#endif // !defined(AFX_CONNECTION_H__CA9B25F7_E160_484A_BAFF_B941DB3990F8__INCLUDED_)
