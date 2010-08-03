// DbFactory.cpp: implementation of the DbFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "DbFactory.h"
#include "Connection.h"
#include "../OracleDB/Oracle.h"
#include "../MysqlDB/Connection.h"
#include "../CommonLib/CTI_Typedfile.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


namespace CTI
{
	namespace DBAccess
	{
		DbFactory::DbFactory()
		{

		}

		DbFactory::~DbFactory()
		{

		}
		IConnection* DbFactory::GetConnection(ConnectionInfo const& connInfo)
		{
			IConnection* tmp = NULL;
			switch(connInfo.DbType())
			{
			case 1: // Oracle
				return new OraConnection(connInfo);
				break;
			case 2: // Mysql
				return new MysqlConnection(connInfo);
				break;
			case 3: // SqlServer
				return new SqlConnection(connInfo);
				break;
			default:
				return NULL;
            }
		}
	}
}
