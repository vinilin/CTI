// ResultSet.cpp: implementation of the ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResultSet.h"
#include "Error.h"
#include  <algorithm> 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace Mysql
    {
        ResultSet::ResultSet(MYSQL* mysql)
        {
            ASSERT(mysql != NULL);
            m_resultSet = mysql_store_result(mysql);
            if(!m_resultSet)
            {
                throw Error(mysql, __FILE__, __LINE__);
            }
			//m_currentRow = mysql_fetch_row(m_resultSet);
			m_numFields = mysql_num_fields(m_resultSet);
			
			for(int i = 0; i < m_numFields; ++i)
			{
                MYSQL_FIELD *field = mysql_fetch_field_direct(m_resultSet,i);
				Column *col = new Column(this, field,i);
				m_columns.push_back(col);
                std::string n = col->ColumnName();
                std::transform(n.begin(),n.end(),n.begin(),tolower);
                m_columnsMap.insert(std::make_pair(n,col));
			}
			
			
        }

        ResultSet::~ResultSet()
        {
			if(m_resultSet != NULL)
			{
				mysql_free_result(m_resultSet);
			}
            //delete this;
        }
        bool ResultSet::Next()
        {
			m_currentRow = mysql_fetch_row(m_resultSet);
			if(m_currentRow)
			{
				return true;
			}
            return false;
        }
        UINT64 ResultSet::RowsCount()
        {
			UINT64 count = mysql_num_rows(m_resultSet);
			return count;
        }
        
        Column& ResultSet::operator [](std::string const&columnName)
        {
            std::string col = columnName;
            std::transform(col.begin(),col.end(),col.begin(),tolower);
            ASSERT(m_columnsMap.find(col) != m_columnsMap.end());
            Column &x = *m_columnsMap[col];
            
            return x;
        }
        Column& ResultSet::operator []( int columnIndex)
        {
            ASSERT(m_columns.size() > columnIndex);
			return *m_columns[columnIndex];
        }
    }
}
