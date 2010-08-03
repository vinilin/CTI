// Statement.cpp: implementation of the Statement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Statement.h"
#include "ResultSet.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace Oracle
    {
        Statement::Statement(Connection &conn, std::string sqlBlock)
        {
            m_conn = &conn;
            Initialize();
            try
            {
                Prepare(sqlBlock);
            }
            catch(...)
            {
                Cleanup();
                throw;
            }
        }

        Statement::~Statement()
        {
            Cleanup();
        }
        void Statement::Initialize()
        {
            m_stmtHandle = NULL;
            m_isPrepared = false;
            m_isExecuted = false;
            m_type = ST_UNKNOWN;
        }
        void Statement::Cleanup()
        {
            if(m_stmtHandle != NULL)
            {
                OCIHandleFree(m_stmtHandle, OCI_HTYPE_STMT);
                m_stmtHandle = NULL;
            }
        }
        void Statement::Prepare(std::string const& sqlBlock)
        {
            ASSERT(m_conn != NULL && sqlBlock.empty() != true);
            ASSERT(m_stmtHandle == NULL);
            sword result;

            result  = OCIHandleAlloc(m_conn->m_environmentHandle
                        , (void **) &m_stmtHandle,OCI_HTYPE_STMT, 0, NULL);
            if(result == OCI_SUCCESS)
            {
                result  = OCIStmtPrepare(m_stmtHandle, m_conn->m_errorHandle
                            , (text*) sqlBlock.c_str(), sqlBlock.size(), OCI_NTV_SYNTAX, OCI_DEFAULT);
            }
            else
            {
                throw Error (result, m_conn->m_environmentHandle, __FILE__, __LINE__);
            }
            if(result == OCI_SUCCESS)
            {
                ub2 stmtType = 0;
                result = OCIAttrGet (m_stmtHandle, OCI_HTYPE_STMT
                        , &stmtType, NULL, OCI_ATTR_STMT_TYPE, m_conn->m_errorHandle);
                m_type = (StatementType)stmtType;
            }
            if( result == OCI_SUCCESS)
            {
                m_isPrepared = true;
                m_isExecuted = false; 
            }
            else
            {
                throw Error (result, m_conn->m_errorHandle, __FILE__, __LINE__);
            }
        }
        void Statement::ExecutePrepare ()
        {
            ASSERT(m_conn != NULL && m_isPrepared);
            sword result;
            ub4 iters;
            iters = (m_type == ST_SELECT) ? 0 : 1;
            result = OCIStmtExecute(m_conn->m_svcContextHandle, 
                        m_stmtHandle, m_conn->m_errorHandle, iters, 0, NULL, NULL, OCI_DEFAULT);
            if(result == OCI_SUCCESS)
            {
                m_isExecuted = true;
            }
            else 
                throw Error(result, m_conn->m_errorHandle, __FILE__, __LINE__);
        }

        ResultSet* Statement::Select()
        {
            ASSERT(m_isPrepared && m_type == ST_SELECT);
            Execute();
            ResultSet *r = new ResultSet(m_stmtHandle, m_conn);
            try
            {
                r->FetchRows();
                return (r);
            }
            catch(...)
            {
                if(r) delete r;
                throw;
            }
        }
    }
}
