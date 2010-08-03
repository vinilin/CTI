// Column.cpp: implementation of the Column class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Column.h"



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
		//////////////////////////////////////////////////////////////////////////
		// oracle
		BOOL OracleColumn::IsNull() const
		{
			return m_column.IsNull();
		}
		
        OracleColumn::OracleColumn(Oracle::Column& col):m_column(col)
		{
		
		}
		
		OracleColumn::~OracleColumn()
		{
		}
		
		std::string OracleColumn::AsString() const
		{
			return m_column.AsString();
		}
		
		double OracleColumn::AsDouble() const
		{
			return m_column.AsDouble();
		}
		
		long OracleColumn::AsLong() const
		{
			return m_column.AsLong();
		}
		//////////////////////////////////////////////////////////////////////////
		// mysql
		MysqlColumn::MysqlColumn(Mysql::Column &col)
            :m_column(col)
		{
		}
		
		BOOL MysqlColumn::IsNull() const
		{
            return TRUE;
		}
		
		std::string MysqlColumn::AsString() const
		{
			return m_column.AsString();
		}
		
		double MysqlColumn::AsDouble() const
		{
            return m_column.AsDouble();
		}
		
		long MysqlColumn::AsLong() const
		{
            return m_column.AsLong();
		}
        int MysqlColumn::AsInt() const
        {
            return m_column.AsInt();
        }
		
		MysqlColumn::~MysqlColumn()
		{
		}
		

		///////////////////////////////////////////////////////////////////////////
		// Sqlserver
        
        SqlserverColumn::SqlserverColumn( Sqlserver::CADORecordset* rs,std::string name )
        {
            ASSERT(rs != NULL);
            m_column = rs;
            m_name = name;
            m_idx = -1;
        }
        
        SqlserverColumn::SqlserverColumn( Sqlserver::CADORecordset* rs, int idx )
        {
            ASSERT(rs != NULL);
            m_column = rs;
            m_idx  = idx;
            m_name = "";
        }
        
        SqlserverColumn::SqlserverColumn( Sqlserver::CADORecordset* rs, std::string name, int idx )
        {
            m_name = name;
            m_idx  = idx;
            m_column = rs;
        }
        
        BOOL SqlserverColumn::IsNull() const
        {
            return m_idx == -1 ? m_column->IsFieldNull(m_name.c_str()) : m_column->IsFieldNull(m_idx);
        }
        
        std::string SqlserverColumn::AsString() const
        {
            CString value;
            m_idx == -1 ? m_column->GetFieldValue(m_name.c_str(),value) : m_column->GetFieldValue(m_idx,value);
            return (LPCSTR) value;
        }
        int SqlserverColumn::AsInt() const
        {
            int value;
            m_idx == -1 ? m_column->GetFieldValue(m_name.c_str(),value) : m_column->GetFieldValue(m_idx,value);
            return value;
        }
		double SqlserverColumn::AsDouble() const
		{
            double value;
            m_idx == -1 ? m_column->GetFieldValue(m_name.c_str(),value) : m_column->GetFieldValue(m_idx,value);
            return value;
		}
		
		long SqlserverColumn::AsLong() const
		{
            long value;
            m_idx == -1 ? m_column->GetFieldValue(m_name.c_str(),value) : m_column->GetFieldValue(m_idx,value);
            return value;
		}
		
		SqlserverColumn::~SqlserverColumn()
		{
		}
        
        std::string SqlserverColumn::ColumnName()
        {
            Sqlserver::CADOFieldInfo info;
            m_column->GetFieldInfo(m_idx,&info);
            return info.m_strName;
        }
        
	}
}


