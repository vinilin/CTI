// FieldInfo.h: interface for the FieldInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDINFO_H__F5C9AA1D_F083_42A7_B822_580B80224882__INCLUDED_)
#define AFX_FIELDINFO_H__F5C9AA1D_F083_42A7_B822_580B80224882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../CommonLib/CTI_Typedfile.h"
#include <string>
namespace CTI
{
	namespace PP 
	{
		class FieldInfo  
		{
		private:
			Trunk_Fieldinfo m_data;
		public:
			FieldInfo();
			virtual ~FieldInfo();
		public:
            inline UINT Line() { return m_data.Line; }
            inline UINT BaseId() { return m_data.baseid; }
            inline UINT NodeId() { return m_data.nodeid; }
            inline int	ConId()	{ return m_data.conid; }
            inline int  DbType() { return m_data.dbtype; }
            inline int  NodeObjId() { return m_data.nodeObjid; }
			inline int  SqlType() { return m_data.sqltype; }
            inline std::string StrSql() { return m_data.strsql; }
			FieldInfo& operator= ( const Trunk_Fieldinfo& o );
			operator Trunk_Fieldinfo() const;

		};

	}
}

#endif // !defined(AFX_FIELDINFO_H__F5C9AA1D_F083_42A7_B822_580B80224882__INCLUDED_)
