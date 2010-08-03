// IConnection.cpp: implementation of the IConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "IConnection.h"

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
		IConnection::IConnection(const ConnectionInfo& connInfo)
			:m_connInfo(connInfo)
		{
		}
	}
}