// Column.cpp: implementation of the Column class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Column.h"
#include "ResultSet.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace Mysql
    {
        Column::Column(ResultSet *res, MYSQL_FIELD* field, int index)
        {
			ASSERT(res != NULL);
			ASSERT(field != NULL);
			m_resultSet = res;
			m_field = field;
			m_index = index;
        }
		

        Column::~Column()
        {

        }
        
        std::string Column::AsString()
        {
            ASSERT(m_field->type == MYSQL_TYPE_VAR_STRING);
            MYSQL_ROW row = m_resultSet->CurrentRow();
            return row[m_index];
        }
        
        long Column::AsLong()
        {
            ASSERT(m_field->type == MYSQL_TYPE_LONG);
            MYSQL_ROW row = m_resultSet->CurrentRow();
            return atol(row[m_index]);
        }
        
        int Column::AsInt()
        {
            ASSERT(m_field->type == MYSQL_TYPE_LONG);
            MYSQL_ROW row = m_resultSet->CurrentRow();
            return atoi(row[m_index]);
        }
        
        double Column::AsDouble()
        {
            ASSERT(m_field->type == MYSQL_TYPE_DOUBLE);
            MYSQL_ROW row = m_resultSet->CurrentRow();
            return atof(row[m_index]);
            
        }
    }
}
