// Column.h: interface for the Column class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMN_H__102F2E60_9DBA_4EA9_B9AB_C488641FFB31__INCLUDED_)
#define AFX_COLUMN_H__102F2E60_9DBA_4EA9_B9AB_C488641FFB31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mysql.h>


namespace CTI
{
    namespace Mysql
    {
		class ResultSet;
        class Column  
        {
        private:
            MYSQL_FIELD *m_field;
			int m_index;
			ResultSet *m_resultSet;
        public:
            Column(ResultSet* res, MYSQL_FIELD* field,int index);
            virtual ~Column();
		public:
			inline std::string ColumnName()
			{
				ASSERT(m_field != NULL);
				return m_field->name;
			}
            inline int DataType()
            {
                return m_field->type;
            }
			std::string AsString();
            long AsLong();
            int AsInt();
            double AsDouble();
        };
    }
}
#endif // !defined(AFX_COLUMN_H__102F2E60_9DBA_4EA9_B9AB_C488641FFB31__INCLUDED_)
