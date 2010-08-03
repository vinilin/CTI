// ResultSet.h: interface for the ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSET_H__778F3D1D_3DE5_429C_888A_9647B3E157C8__INCLUDED_)
#define AFX_RESULTSET_H__778F3D1D_3DE5_429C_888A_9647B3E157C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IResultSet.h"
#include <winsock2.h>
#include "../OracleDB/Oracle.h"
#include "../MysqlDB/ResultSet.h"
#include "../SqlServerDB/ado2.h"

namespace CTI
{
	namespace DBAccess
	{
		//////////////////////////////////////////////////////////////////////////
		//Oracle ResultSet
		class OracleRS : public IResultSet
		{

		private:	
			Oracle::ResultSet *m_resultSet;
            std::map<int,IColumn*> m_colMap;
            std::map<std::string,IColumn*> m_colNameMap;
		public:
			OracleRS(Oracle::ResultSet *rs);
			virtual ~OracleRS();
		public:
			bool Next();
			IColumn* operator [](std::string  const &columName);
			IColumn* operator [](int columnIndex);
            virtual int GetColumnCount() 
            {
               return m_resultSet->ColumnsCount();
            }
            void Initialize();
		};

		//////////////////////////////////////////////////////////////////////////
		//Mysql ResultSet
		class MysqlRS : public IResultSet
		{
		private:
			Mysql::ResultSet* m_resultSet;
		public:
			MysqlRS(Mysql::ResultSet* rs);
			~MysqlRS();
		public:
			virtual bool Next();
			virtual IColumn* operator[](std::string  const &columnName);
			virtual IColumn* operator[](int columnIndex);
            virtual int GetColumnCount() 
            {
                return m_resultSet->GetColumnCount();
            }
		};

		//////////////////////////////////////////////////////////////////////////
		// Sqlserver ResultSet
		class SqlserverRS : public IResultSet
		{
		private:
			Sqlserver::CADORecordset* m_resultSet;
            std::map<int, IColumn*> m_colMap;
            std::map<std::string, IColumn*> m_colNameMap;
            std::string m_strSql;
            bool m_isFirst;
		public:
            SqlserverRS(Sqlserver::CADODatabase* db,std::string sql);
            ~SqlserverRS();
		public:
			virtual bool Next();
            //按列名获取列，区分大小写；
			virtual IColumn* operator[](std::string const &columnName);
            //按列索引获取列
			virtual IColumn* operator[](int columnIndex);

            virtual int GetColumnCount();
            void Initialize();  
            
            //************************************
            // Method:    operator=
            // FullName:  CTI::DBAccess::SqlserverRS::operator=
            // Access:    public 
            // Returns:   SqlserverRS&
            // Qualifier: 赋值函数，赋值效率较低，赋值时会赋值m_resultSet的指针和m_strSql
            //，然后会重新构造m_colMap和m_colNameMap,
            // Parameter: const SqlserverRS & rhs
            //************************************
            SqlserverRS& operator = (const SqlserverRS& rhs);
            
		};
	}
}
#endif // !defined(AFX_RESULTSET_H__778F3D1D_3DE5_429C_888A_9647B3E157C8__INCLUDED_)
