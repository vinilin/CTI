// DbFactory.h: interface for the DbFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBFACTORY_H__D9A5B900_A24B_48BB_89D0_89D8D80EDA33__INCLUDED_)
#define AFX_DBFACTORY_H__D9A5B900_A24B_48BB_89D0_89D8D80EDA33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IConnection.h"
#include "../ProtocalParse/ConnectionInfo.h"
using namespace CTI::PP;
namespace CTI
{
	namespace DBAccess
	{
		class DbFactory  
		{
		public:
			DbFactory();
			virtual ~DbFactory();
		public:
			static IConnection* GetConnection(ConnectionInfo const& connInfo);
			
		};
	}
}

#endif // !defined(AFX_DBFACTORY_H__D9A5B900_A24B_48BB_89D0_89D8D80EDA33__INCLUDED_)
