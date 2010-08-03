// Statement.h: interface for the Statement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATEMENT_H__3B8E6EF4_3F93_4387_9466_D408531E1279__INCLUDED_)
#define AFX_STATEMENT_H__3B8E6EF4_3F93_4387_9466_D408531E1279__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Oracle.h"
#pragma warning (disable: 4786)
namespace CTI
{
    namespace Oracle
    {

        enum StatementType
        {
                ST_UNKNOWN,
                ST_SELECT = OCI_STMT_SELECT,
                ST_UPDATE = OCI_STMT_UPDATE,
                ST_DELETE = OCI_STMT_DELETE,
                ST_INSERT = OCI_STMT_INSERT,
                ST_CREATE = OCI_STMT_CREATE,
                ST_DROP = OCI_STMT_DROP,
                ST_ALTER = OCI_STMT_ALTER,
                ST_BEGIN = OCI_STMT_BEGIN,
                ST_DECLARE = OCI_STMT_DECLARE
        };

		class Connection;

        class Statement  
        {
			friend class Connection;
        private:
            Connection          *m_conn;
            OCIStmt				*m_stmtHandle;
            std::string         m_sql;
            StatementType       m_type;

            bool                m_isPrepared;
            bool                m_isExecuted;
        public:
            Statement(Connection &conn, std::string sqlBlock);
            ~Statement();
        private:
            void Initialize ();
            void Cleanup ();
            void Prepare(std::string const& sqlBlock);
            void ExecutePrepare();
        public:
            inline void Execute()
            {
                ExecutePrepare();
            }
            ResultSet* Select();
            inline void Release()
            {
                delete this;
            }
        };
    }
}

#endif // !defined(AFX_STATEMENT_H__3B8E6EF4_3F93_4387_9466_D408531E1279__INCLUDED_)
