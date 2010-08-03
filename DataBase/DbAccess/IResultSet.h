// IResultSet.h: interface for the IResultSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRESULTSET_H__2454C0B4_F9C3_41CD_9B43_E8946F1282F4__INCLUDED_)
#define AFX_IRESULTSET_H__2454C0B4_F9C3_41CD_9B43_E8946F1282F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "IColumn.h"

namespace CTI
{
	namespace DBAccess
	{

		class IResultSet 
		{
		
		public:
			virtual bool Next() = 0;
            virtual int GetColumnCount() = 0;

			virtual IColumn* IResultSet::operator[](std::string const &columnName) = 0;
			virtual IColumn* IResultSet::operator[](int columnIndex) = 0;
		};
	}
}


#endif // !defined(AFX_IRESULTSET_H__2454C0B4_F9C3_41CD_9B43_E8946F1282F4__INCLUDED_)
