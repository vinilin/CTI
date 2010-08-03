// ResultSet.h: interface for the ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSET_H__98DBA21B_1B4C_42DF_B7AE_6DAAFF5CA8B6__INCLUDED_)
#define AFX_RESULTSET_H__98DBA21B_1B4C_42DF_B7AE_6DAAFF5CA8B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <mysql.h>
#include <map>
#include <vector>
#include "Column.h"

namespace CTI
{
    namespace Mysql
    {
        class ResultSet  
        {
		private:
			typedef std::vector <Column*> Columns;
            typedef std::map <std::string, Column*> ColumnsMap;
        private:
			Columns         m_columns; 
            ColumnsMap      m_columnsMap;
            MYSQL_RES		*m_resultSet;
			MYSQL_ROW		m_currentRow;
			int				m_numFields;
        public:
            ResultSet(MYSQL *mysql);
            virtual ~ResultSet();
			
		public:
			bool Next();
			UINT64 ResultSet::RowsCount();
			inline MYSQL_ROW & CurrentRow()
			{
				return m_currentRow;
			}
            inline int GetColumnCount()
            {
                return m_columns.size();
            }
			Column& ResultSet::operator []( int columnIndex);
			Column& ResultSet::operator [](std::string const&columnName);
        };
    }
}

#endif // !defined(AFX_RESULTSET_H__98DBA21B_1B4C_42DF_B7AE_6DAAFF5CA8B6__INCLUDED_)
