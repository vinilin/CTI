// Column.h: interface for the Column class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMN_H__CE5CC2F0_1CFC_4F0B_84C3_36DAB80B847A__INCLUDED_)
#define AFX_COLUMN_H__CE5CC2F0_1CFC_4F0B_84C3_36DAB80B847A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IColumn.h"
#include <winsock2.h>
#include "../MysqlDB/Column.h"
#include "../OracleDB/Oracle.h"
#include "../SqlServerDB/ado2.h"

namespace CTI
{
    namespace DBAccess
    {
		//////////////////////////////////////////////////////////////////////////
		// oracle
        enum enumDataType
        {
           DT_INTEGER = 1,
           DT_DOUBLE,
           DT_STRING,
           DT_DATE
        }; 

        class OracleColumn : public IColumn
        {
        private:
            Oracle::Column &m_column;
        public:
            OracleColumn(Oracle::Column& col);
            virtual ~OracleColumn();
        public:

            virtual BOOL IsNull () const;
			
            // 将列值作为字符串返回
            virtual std::string AsString () const;
			
            // 将列值作为double返回
            double AsDouble () const;
			
            // 将列值作为long返回
            virtual long AsLong () const;
            virtual int AsInt() const{return 0;}

            std::string ColumnName()
            {
                return m_column.ColumnName();
            }
            
            int DataType()
            {
                
                return m_column.DataType();
            }
        };
		//////////////////////////////////////////////////////////////////////////
		// mysql
        class MysqlColumn : public IColumn
        {
        private:
            Mysql::Column &m_column;
        public:
            MysqlColumn(Mysql::Column &col);
            virtual ~MysqlColumn();
        public:
            virtual BOOL IsNull () const;
			
            // 将列值作为字符串返回
            virtual std::string AsString () const;
			
            // 将列值作为double返回
            double AsDouble () const;
			
            // 将列值作为long返回
            virtual long AsLong () const;
            virtual int AsInt() const;
            std::string ColumnName()
            {
                return m_column.ColumnName();
            }
            
            int DataType()
            {
                return m_column.DataType();
            }
        };
		
		//////////////////////////////////////////////////////////////////////////
		// sqlserver
        class SqlserverColumn : public IColumn
        {
        private:
            Sqlserver::CADORecordset *m_column;
            std::string m_name;
            int m_idx;
        public:
            SqlserverColumn(Sqlserver::CADORecordset* rs,std::string name);
            SqlserverColumn(Sqlserver::CADORecordset* rs, int idx);
            SqlserverColumn(Sqlserver::CADORecordset* rs, std::string name, int idx);
            virtual ~SqlserverColumn();
        public:
            virtual BOOL IsNull () const;
			
            // 将列值作为字符串返回
            virtual std::string AsString () const;
			
            // 将列值作为double返回
            double AsDouble () const;
			
            // 将列值作为long返回
            virtual long AsLong () const;
            virtual int AsInt() const;
            std::string ColumnName();
            
            int DataType()
            {
                Sqlserver::CADOFieldInfo info;
                m_column->GetFieldInfo(m_idx,&info);
                using namespace Sqlserver;
                switch(info.m_nType)
                {
                case CADORecordset::typeInteger:
                case CADORecordset::typeBigInt:
                case CADORecordset::typeSmallInt:
                case CADORecordset::typeTinyInt:
                    return DT_INTEGER;
                case CADORecordset::typeDouble:
                case CADORecordset::typeCurrency:
                    return DT_DOUBLE;
                case CADORecordset::typeDBTimeStamp:
                case CADORecordset::typeVarChar:
                case CADORecordset::typeDate:
                    return DT_STRING;
                default:
                    return -1;
                }
            }
        };
    }
}
#endif // !defined(AFX_COLUMN_H__CE5CC2F0_1CFC_4F0B_84C3_36DAB80B847A__INCLUDED_)
