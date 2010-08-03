// ResultSet.h: interface for the ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESULTSET_H__CC9A76C2_5BFF_4516_B430_596DAE6D3DCC__INCLUDED_)
#define AFX_RESULTSET_H__CC9A76C2_5BFF_4516_B430_596DAE6D3DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4786)
namespace CTI
{
    namespace Oracle
    {
		class Column;
		class Connection;
		class Statement;

        class ResultSet  
        {
			friend class Column;
			friend class Statement;
			friend class Connection;
        private:
            typedef std::vector <Column*> Columns;
            typedef std::map <std::string, Column*> ColumnsMap;

            Columns         m_columns; 
            ColumnsMap      m_columnsMap;
            Connection      *m_conn;
            OCIStmt         *m_rsHandle;
            Statement       *m_stmt;

            ub2     m_fetchCount;
            ub4     m_rowsFetched;
            ub4     m_currentRow;
            bool    m_isEod;
            bool    m_isDescribed;
            bool    m_isDefined;
        private:
            ResultSet(OCIStmt* rs , Connection *conn, ub2 fetchSize = FETCH_SIZE);
            virtual ~ResultSet();

            void Initialize();
            void Cleanup();
            void Attach(OCIStmt *rs, Connection *conn, ub2 fetchSize = FETCH_SIZE);

            ub4 RowsCount();
            void AttachStatement(Statement *stmt);
            void Describe();
            void Define();
            void FetchRows();
        public:
            ub4 ColumnsCount();
            inline bool Eod() const 
            {
                return m_currentRow >= m_rowsFetched && m_isEod;
            };
            inline bool operator ++ ()
            {
                return Next();
            }
            bool Next();

            Column& operator [] (std::string const& columnName);
            Column& operator [] (ub2 columnIndex);
            inline void Release()
            {
                delete this;
            }

        };
    }
};

#endif // !defined(AFX_RESULTSET_H__CC9A76C2_5BFF_4516_B430_596DAE6D3DCC__INCLUDED_)
