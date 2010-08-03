// Error.cpp: implementation of the Error class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Error.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace Mysql
    {
        Error::Error(MYSQL* mysql, const char* file , int line)
        {
            m_message = mysql_error(mysql);
			m_file = file;
			m_line = line;
        }

        Error::~Error()
        {

        }
    }
}
