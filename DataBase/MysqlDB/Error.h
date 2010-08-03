// Error.h: interface for the Error class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERROR_H__D6817BDD_EAAF_4B52_8001_020B30439496__INCLUDED_)
#define AFX_ERROR_H__D6817BDD_EAAF_4B52_8001_020B30439496__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <mysql.h>
#include <exception>
namespace CTI
{
    namespace Mysql
    {
        class Error  :public exception
        {
        private:
            std::string m_message;
			std::string m_file;
			int m_line;
            int m_code;
        public:
            Error(MYSQL* mysql, const char* file , int line);
            virtual ~Error();
        public:
            std::string Message()
            {
                return m_message;
            }

        };

    }
}
#endif // !defined(AFX_ERROR_H__D6817BDD_EAAF_4B52_8001_020B30439496__INCLUDED_)
