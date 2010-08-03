// ResultSet.cpp: implementation of the ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ResultSet.h"
#include "Column.h"
#include <algorithm>

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

        OracleRS::OracleRS(Oracle::ResultSet *rs)
		{
            ASSERT(rs != NULL);
			m_resultSet = rs;
            Initialize();
		}
        void OracleRS::Initialize()
        {
            int cols = m_resultSet->ColumnsCount();
            for(int i  = 0; i < cols; ++i)
            {
                IColumn *col = new OracleColumn(m_resultSet->operator [](i));
                m_colMap.insert(std::make_pair(i,col));
                std::string colName = col->ColumnName();
                std::transform(colName.begin(),colName.end(),colName.begin(),tolower);
                m_colNameMap.insert(std::make_pair(colName,col));
            }
        }
        OracleRS::~OracleRS()
        {
            std::map<int,IColumn*>::iterator beg =  m_colMap.begin();
            for(;beg != m_colMap.end(); ++beg)
            {
                delete beg->second;
            }
            m_colMap.clear();
            m_colNameMap.clear();
        }

		bool OracleRS::Next()
		{
			return m_resultSet->Next();
		}
		
		IColumn* OracleRS::operator[]( std::string  const &columName )
		{
            std::string colName = columName;
            std::transform(colName.begin(),colName.end(),colName.begin(),tolower);
            return m_colNameMap[colName];
		}
		
		IColumn* OracleRS::operator[]( int columnIndex )
		{
			return m_colMap[columnIndex];
		}
        
        
        //////////////////////////////////////////////////////////////////////////
        // sqlserver
        SqlserverRS::SqlserverRS( Sqlserver::CADODatabase* db,std::string sql )
        {
            ASSERT(db != NULL);
            m_resultSet = new Sqlserver::CADORecordset(db);
            m_strSql = sql;
            m_isFirst = true;
            Initialize();
          
        }
        void SqlserverRS::Initialize()
        {
            if(! m_resultSet->Open(m_strSql.c_str()))
            {
                std::cout<<m_resultSet->GetLastErrorString()<<std::endl;
                return;
            }
            
            // 构造结果集中对应的列。
            int cols = m_resultSet->GetFieldCount();
            for(int i  = 0 ; i < cols; ++i)
            {
                Sqlserver::CADOFieldInfo finfo;
                m_resultSet->GetFieldInfo(i,&finfo);
                IColumn *col = new SqlserverColumn(m_resultSet, finfo.m_strName,i);
                //以索引作为key
                m_colMap.insert(std::make_pair(i,col));
                // 以列名作为key
                std::string colName = finfo.m_strName;
                std::transform(colName.begin(),colName.end(),colName.begin(),tolower);
                m_colNameMap.insert(std::make_pair(colName,col));
            }
          
        }
        
        bool SqlserverRS::Next()
        {
            ASSERT(m_resultSet != NULL);
            if(m_isFirst)
            {
                m_isFirst = false;
            }
            else
            {
                m_resultSet->MoveNext();
            }

            return !m_resultSet->IsEof();
        }
        
        IColumn* SqlserverRS::operator[]( std::string const &columnName )
        {
            std::string colName = columnName;
            std::transform(colName.begin(),colName.end(),colName.begin(),tolower);
            ASSERT(m_colNameMap.find(colName) != m_colNameMap.end());
            return m_colNameMap[colName];
        }
        
        IColumn* SqlserverRS::operator[]( int columnIndex )
        {
            ASSERT(m_colMap.find(columnIndex) != m_colMap.end());
            return m_colMap[columnIndex];
        }
        
        int SqlserverRS::GetColumnCount()
        {
            return m_resultSet->GetFieldCount();
        }
        
        SqlserverRS::~SqlserverRS()
        {
            std::map<int, IColumn*>::iterator beg = m_colMap.begin();
            std::map<int, IColumn*>::iterator end = m_colMap.end();
            for(;beg != end;)
            {
                delete beg->second;
                beg->second = NULL;
            }
            m_colMap.clear();
            m_colNameMap.clear();
            if(m_resultSet != NULL)
            {
                m_resultSet->Close();
                delete m_resultSet;
            }

        }
        
        SqlserverRS& SqlserverRS::operator=( const SqlserverRS& rhs )
        {
           m_resultSet = rhs.m_resultSet;
           m_strSql = rhs.m_strSql;
           m_isFirst = true;
           Initialize();
           return *this;
        }
        //////////////////////////////////////////////////////////////////////////
        //mysql
        
        bool MysqlRS::Next()
        {
            return m_resultSet->Next();
        }
        
        IColumn* MysqlRS::operator[]( std::string  const &columnName )
        {
            Mysql::Column& x = m_resultSet->operator [](columnName);
            return new MysqlColumn(x);
        }
        
        IColumn* MysqlRS::operator[]( int columnIndex )
        {
            return new MysqlColumn(m_resultSet->operator [](columnIndex));
        }
        
        MysqlRS::~MysqlRS()
        {
            
        }
        
        MysqlRS::MysqlRS( Mysql::ResultSet* rs )
        {
            ASSERT(rs != NULL);
            m_resultSet = rs;
        }
	}
}