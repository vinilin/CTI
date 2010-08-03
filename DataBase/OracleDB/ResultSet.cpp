// ResultSet.cpp: implementation of the ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResultSet.h"
#include "Statement.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace CTI
{
    namespace Oracle 
    {
        ResultSet::ResultSet (OCIStmt *rs, Connection *use, ub2 fetchSize) 
        {
            Initialize ();
            try
            {
                Attach (rs, use, fetchSize);
            }
            catch (...)
            {
                Cleanup ();
                throw;
            }
        }

        ResultSet::~ResultSet ()
        {
            Cleanup ();
        }


        void ResultSet::Initialize (void)
        {
        m_conn = NULL;
        m_rsHandle = NULL;
        m_stmt = NULL;
        m_fetchCount = 0;
        m_rowsFetched = 0;
        m_currentRow = 0;
        m_isEod = false;
        m_isDescribed = false;
        m_isDefined = false;
        }

        void ResultSet::Cleanup ()
        {
            // free columns
            for (Columns::iterator i = m_columns.begin (); i != m_columns.end (); ++i)
            {
                delete (*i);
            }
            m_columns.clear ();

            // when resultset is created by statement.select - freed by statement object
            // when created by parameter.as_resultset - freed by parameter object
            if (m_rsHandle) 
            {
                m_rsHandle = NULL;
            }

            // statement attached to be released?
            if (m_stmt) 
            {
                m_stmt->Release ();
                m_stmt = NULL;
            }
        }

        void ResultSet::Attach ( OCIStmt *rs, Connection *use, ub2 fetchSize)
        {
            m_conn = use;
            m_rsHandle = rs;
            m_stmt = NULL;
            m_fetchCount = fetchSize;

            m_rowsFetched = 0;
            m_currentRow = 0;
            m_isEod = false;

            m_isDescribed = false;
            m_isDefined = false;

            Describe ();
            Define ();
        }

        ub4 ResultSet::ColumnsCount (void)
        {
            sword result;
            ub4 count;
            count = 0;
            result = OCIAttrGet (m_rsHandle, OCI_HTYPE_STMT,
                        &count, NULL, OCI_ATTR_PARAM_COUNT, m_conn->m_errorHandle);
            if (result == OCI_SUCCESS)
            {
                    return count;
            }
            else
            {
                throw Error (result, m_conn->m_errorHandle, __FILE__, __LINE__);
            }
        }

        ub4 ResultSet::RowsCount (void)
        {
            sword result;
            ub4	count;
            count = 0;
            result = OCIAttrGet ( m_rsHandle, OCI_HTYPE_STMT,
                        &count, NULL, OCI_ATTR_ROW_COUNT, m_conn->m_errorHandle);
            if (result == OCI_SUCCESS)
            {
                    return count;
            }
            else
            {
                throw Error (result, m_conn->m_errorHandle, __FILE__, __LINE__);
            }
        }

        void ResultSet::Describe (void)
        {
            sword result;
            ub4 count, i;
            count = ColumnsCount ();
            m_columns.reserve (count);
            for (i=0; i<count; i++)
            {
            // 获取列信息
                OCIParam *paramHandle = NULL;
                text *paramName = NULL;
                ub4 nameLen = 0;
                ub2 ociType = 0;
                ub4 size = 0;
                result = OCIParamGet ( m_rsHandle, OCI_HTYPE_STMT, m_conn->m_errorHandle
                            , reinterpret_cast <void **> (&paramHandle), i + 1);	// first is 1

                if (result == OCI_SUCCESS)
                {
                    // 获取列名
                    result = OCIAttrGet ( paramHandle, OCI_DTYPE_PARAM,
                                &paramName, &nameLen, OCI_ATTR_NAME, m_conn->m_errorHandle);
                }

                if (result == OCI_SUCCESS)
                {
                    // 获取数据类型
                    result = OCIAttrGet ( paramHandle, OCI_DTYPE_PARAM,
                        &ociType, NULL, OCI_ATTR_DATA_TYPE, m_conn->m_errorHandle);
                }

                if (result == OCI_SUCCESS)
                {
                    // 最大数据长度(字节)
                    result = OCIAttrGet ( paramHandle, OCI_DTYPE_PARAM,
                                &size, NULL, OCI_ATTR_DATA_SIZE, m_conn->m_errorHandle);
                }

                if (paramHandle)
                {
                    // 忽略错误，直接释放句柄
                    OCIDescriptorFree ( paramHandle, OCI_DTYPE_PARAM);
                }

                // error situation?
                if (result != OCI_SUCCESS)
                {
                    throw Error (result, m_conn->m_errorHandle, __FILE__, __LINE__);

                    // setup new column, alloc memory for fetch buffer, indicators and data lens;
                    // column.constructor could possibly throw an out-of-memory exception
                    // in this case resultset will be partially initialized
                    Column *c = new Column ( this, reinterpret_cast <const char *> (paramName),
                                        nameLen, ociType, size, m_fetchCount);

                    // add to array AND to map
                    // (makes possible to address columns by name AND index)
                    m_columns.push_back (c);
                    m_columnsMap [c->m_colName] = c;
                }
                m_isDescribed = true;
                m_isDefined = false;
            }
        }


        void ResultSet::Define (void)
        {
            Columns::iterator i;
            sword result;
            ub4 position;

            // define all columns
            position = 1;
            result = OCI_SUCCESS;
            for (i=m_columns.begin () ; result == OCI_SUCCESS && i!=m_columns.end (); ++i)
            {
                result = OCIDefineByPos ( m_rsHandle
                            , &((*i)->m_defineHandle)
                            , m_conn->m_errorHandle
                            , position++
                            , (*i)->m_fetchBuffer
                            , (*i)->m_size
                            ,(*i)->m_ociType
                            , (*i)->m_indicators
                            , (*i)->m_dataLens
                            , NULL
                            , OCI_DEFAULT);

#if defined (UNICODE)
/*
// request text columns as unicode (2.0)
if (result == OCI_SUCCESS &&
(*i)->col_type == DT_TEXT)
{
ub4	value = OCI_UCS2ID;
result = OCIAttrSet (
(*i)->define_handle,
OCI_HTYPE_DEFINE,
&value,
sizeof (value),
OCI_ATTR_CHARSET_ID,
conn->error_handle);
}
*/
#endif // UNICODE defined?

                if (result != OCI_SUCCESS)
                {
                    throw Error (result, m_conn->m_errorHandle, __FILE__, __LINE__);
                }
            }
            m_isDefined = true;
        }

        void ResultSet::AttachStatement (Statement *select)
        {
                // prerequisites
                ASSERT (select);
                m_stmt = select;
        }

       void ResultSet::FetchRows (void)
       {
            // prerequisites
            ASSERT (m_isDescribed && m_isDefined);
            sword result;
            ub4 m_oldRowsCount = m_rowsFetched;
            result = OCIStmtFetch ( m_rsHandle, m_conn->m_errorHandle,
                        m_fetchCount, OCI_FETCH_NEXT, OCI_DEFAULT);
            if (result == OCI_SUCCESS || result == OCI_NO_DATA 
                || result == OCI_SUCCESS_WITH_INFO)
            {
                m_rowsFetched = RowsCount ();
                if (m_rowsFetched - m_oldRowsCount != m_fetchCount)
                {
                    m_isEod = true;
                }
            }
            else
            {
                throw Error (result, m_conn->m_errorHandle, __FILE__, __LINE__);
            }
        }

        bool ResultSet::Next (void)
        {
                // prerequisites
            ASSERT (m_isDescribed && m_isDefined);

            m_currentRow++;
            if (m_currentRow >= m_rowsFetched)
            {
                if (!m_isEod)
                {
                    // fetch new block of rows; fetch_rows will set is_eod on true
                    // when last block if rows has been fetched; will also update rows_fetched
                    FetchRows ();
                }
                else
                {
                    return false;
                }
            }
            if (m_currentRow >= m_rowsFetched)
            {
                return false;
            }
            return true;
        }

        Column& ResultSet::operator [] (std::string const& columnName)
        {
            ColumnsMap::iterator i = m_columnsMap.find (columnName.c_str());
            if (i == m_columnsMap.end ())
            {
                // column with such name is not found
                throw Error (EC_COLUMN_NOT_FOUND, __FILE__, __LINE__);
            }
            return (*(i->second));
        }

        Column& ResultSet::operator [] (ub2 columnIndex)
        {
            if (columnIndex < FIRST_COLUMN_NO ||
                    columnIndex > m_columns.size ())
            {
                    // no column with such index
                throw Error (EC_COLUMN_NOT_FOUND, __FILE__, __LINE__);
            }
            return (*(m_columns.at (columnIndex - FIRST_COLUMN_NO)));
        }
    }
}
