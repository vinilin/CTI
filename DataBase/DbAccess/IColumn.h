// IColumn.h: interface for the IColumn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICOLUMN_H__7D515F0B_3C0D_4966_B752_8F0E46855282__INCLUDED_)
#define AFX_ICOLUMN_H__7D515F0B_3C0D_4966_B752_8F0E46855282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include "stdafx.h"
namespace CTI
{
	namespace DBAccess
	{
		class IColumn  
		{
		public:
            virtual std::string ColumnName() = 0;

            virtual int DataType() = 0;

			virtual BOOL IsNull () const = 0;
			
            // 将列值作为字符串返回
			virtual inline operator std::string()
			{
				return AsString();
			};
			virtual std::string AsString () const = 0;
			
            // 将列值作为double返回
            inline operator double () const 
			{ 
				return AsDouble (); 
			};
            virtual double AsDouble (void) const = 0;
			
            // 将列值作为long返回
            inline operator long () const 
			{ 
				return AsLong (); 
			};
            virtual long AsLong () const = 0;
            inline operator int() const
            {
                AsInt();
            }
            virtual int AsInt() const = 0;

            // 将列值作为日期返回
            //inline operator DateTime (void) cxonst 
			//{ return (AsDatetime ()); };
            //DateTime AsDatetime (void) const;
		};

	}
}

#endif // !defined(AFX_ICOLUMN_H__7D515F0B_3C0D_4966_B752_8F0E46855282__INCLUDED_)
