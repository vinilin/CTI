// DbInfo.h: interface for the DbInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBINFO_H__51B30C7F_D8FF_4C4A_990F_8EEB2B8EEEBA__INCLUDED_)
#define AFX_DBINFO_H__51B30C7F_D8FF_4C4A_990F_8EEB2B8EEEBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../CommonLib/CTI_Typedfile.h"
#include "IRecord.h"
#include <string>
namespace CTI
{
	namespace PP
	{
		class DbInfo  
		{
		private:
			struDBinfo m_data;
            int m_rcCount;
		public:
			DbInfo();
			virtual ~DbInfo();
            
		public:
			inline UINT Line() { return m_data.Line; }
			inline UINT BaseId() { return m_data.baseid; }
			inline UINT NodeId() { return m_data.nodeid; }
			inline int	ConId()	{ return m_data.conid; }
			inline int  DbType() { return m_data.dbtype; }
			inline int  NodeObjId() { return m_data.nodeObjid; }
			inline int  SqlType() { return m_data.sqltype; }
			inline std::string StrSql() { return m_data.strsql; }
			inline char* DbResult() { return m_data.DBresult; }
			inline int	ResultFlag() { return m_data.ResultFlag; }
			inline int  TableFlag() { return m_data.tableflag; }
            inline int  DataLen() { return m_data.datalen; }

		public:
			DbInfo& operator= ( const struDBinfo& o );
			operator struDBinfo() const;
            BOOL operator << (const IRecord* tb);

		};
	}
}


#endif // !defined(AFX_DBINFO_H__51B30C7F_D8FF_4C4A_990F_8EEB2B8EEEBA__INCLUDED_)
