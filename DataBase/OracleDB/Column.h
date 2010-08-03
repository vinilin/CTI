// Column.h: interface for the Column class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMN_H__A585C996_D8DC_417F_B758_2BBC49C4B7C9__INCLUDED_)
#define AFX_COLUMN_H__A585C996_D8DC_417F_B758_2BBC49C4B7C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable: 4786)
#include "DateTime.h"
namespace CTI
{
    namespace Oracle
    {
		enum DataType
		{
				DT_UNKNOWN,
				DT_NUMBER,
				DT_DATE,
				DT_TEXT,
				DT_RESULT_SET
		};

		class ResultSet;

        class Column  
        {
			friend class ResultSet;
        private:
            std::string     m_colName;              // in the exact case
            DataType		m_colType;              // as it will be returned
            ub2             m_ociType;              // oracle's data type
            int             m_size;	                // number of bytes required for

            sb2             *m_indicators;          // an array with indicators: 0 - ok; -1 - null
            ub2             *m_dataLens;            // an array with data lengths (for text columns)
            char            *m_fetchBuffer;         // where data is returned (fetched)

            OCIDefine       *m_defineHandle;        // used for the column
            ResultSet       *m_resultSet;           // is the column's owner

       private:
            // public not creatable; use connection.select or statement.select
            // attaches this column to a result set; allocates memory for the fetch buffer
            Column ( ResultSet *rs, const char *name,
                    ub4 nameLen, ub2 ociDataType,
                    ub4 maxDataSize, int fetchSize = FETCH_SIZE);

            // public not deletable; deleted, when result set is released
            ~Column ();

            // initialize data members
            void Initialize (void);

            // free resources allocated
            void Cleanup (void);

            
            // 私有拷贝赋值函数，禁止外部的拷贝和赋值动作。
            Column (const Column& /* col */) { };
            Column& operator = (const Column& /* col */) 
            { 
                return (*this); 
            };
       public:
            inline std::string ColumnName()
            {
                return m_colName;
            }
            inline int DataType()
            {
                return m_ociType;
            }
        public:
            // 判断列值是否为空
            bool IsNull (void) const;

            // 将列值作为字符串返回
            inline operator Pstr (void) const { return (AsString ()); };
            Pstr AsString (void) const;

            // 将列值作为double返回
            inline operator double (void) const { return (AsDouble ()); };
            double AsDouble (void) const;

            // 将列值作为long返回
            inline operator long (void) const { return (AsLong ()); };
            long AsLong (void) const;

            // 将列值作为日期返回
            inline operator DateTime (void) const { return (AsDatetime ()); };
            DateTime AsDatetime (void) const;

            // (column is not deleted by the client, but when result set is released instead)
            inline void Release (void) { };
        };
    }
}
#endif // !defined(AFX_COLUMN_H__A585C996_D8DC_417F_B758_2BBC49C4B7C9__INCLUDED_)
