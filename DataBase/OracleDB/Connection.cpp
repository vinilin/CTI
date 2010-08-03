// Connection.cpp: implementation of the Connection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Connection.h"
#include "Error.h"
#include "Statement.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace Oracle
    {
        Connection::Connection()
        {
			Initialize();
        }

        Connection::~Connection()
        {
			Close();
        }
        void Connection::Initialize()
        {
            m_environmentHandle = NULL;
            m_serverHandle = NULL;
            m_errorHandle = NULL;
            m_sessionHandle = NULL;
            m_svcContextHandle = NULL;

            m_isOpened = false;
            m_isAvailable = false;
            m_isBlocking = false;
        }

        void Connection::OraHandleAlloc(void ** handle, int type, int size, char * mem)
        {
            ASSERT(m_environmentHandle != NULL);
            sword result = 0;
            result = OCIHandleAlloc ( m_environmentHandle
                        , handle, type , size , (void**) mem);
            if (result != OCI_SUCCESS)
            {
                throw Error(result, m_environmentHandle, __FILE__, __LINE__);
            }
        }

        void Connection::Open( std::string const &serviceName  // Oracle������
                    ,std::string const &usrName                //�û���
                    ,std::string const &pwd                   //����
					,std::string const& db
                    ,ULONG envMode                             // OCI����ģʽ
                    ,BOOL nonBlockingMode                      // ��������ģʽ
                    )
        {
            ASSERT( (!serviceName.empty()) && (!usrName.empty()) );
            ASSERT( !m_isOpened);

            sword result = 0;
            // �����������
            result = OCIEnvCreate( &m_environmentHandle
                        , envMode, NULL,  NULL, NULL, NULL, 0, NULL );
            if(result != OCI_SUCCESS)
            {
                throw Error(EC_ENV_CREATE_FAILED, __FILE__, __LINE__);
            }

            // ����OCI_HTYPE_SERVER���// ���价�����
            OraHandleAlloc ((void **) &m_serverHandle , OCI_HTYPE_SERVER);
            // ����OCI_HTYPE_ERROR���
            OraHandleAlloc ((void **) &m_errorHandle, OCI_HTYPE_ERROR);

            // ����������������
            result = OCIServerAttach ( m_serverHandle, m_errorHandle
                        , (text *) serviceName.c_str(),  serviceName.size(), OCI_DEFAULT);

            if (result != OCI_SUCCESS)
            {
                throw Error (result, m_errorHandle, __FILE__, __LINE__);
            }

            // ����OCI_HTYPE_SVCCTX���
            OraHandleAlloc ((void **) &m_svcContextHandle, OCI_HTYPE_SVCCTX);

            result = OCIAttrSet ( m_svcContextHandle, OCI_HTYPE_SVCCTX,
                        m_serverHandle, sizeof (OCIServer *), OCI_ATTR_SERVER, m_errorHandle);

            if (result != OCI_SUCCESS)
            {// ���价�����
                throw Error (result, m_errorHandle, __FILE__, __LINE__);
            }

            // �����û��Ự���
            OraHandleAlloc ( (void **) &m_sessionHandle, OCI_HTYPE_SESSION);	

            // �����û��������뵽�û��Ự�����
            result = OCIAttrSet ( m_sessionHandle, OCI_HTYPE_SESSION,
                        (text *) usrName.c_str(), usrName.size(), OCI_ATTR_USERNAME, m_errorHandle);

            if (result != OCI_SUCCESS)
            {
                throw Error (result, m_environmentHandle, __FILE__, __LINE__);
            }

            result = OCIAttrSet ( m_sessionHandle, OCI_HTYPE_SESSION,
                        (text *) pwd.c_str(), pwd.size(), OCI_ATTR_PASSWORD, m_errorHandle);

            if (result != OCI_SUCCESS)
            {
                throw Error (result, m_environmentHandle, __FILE__, __LINE__);
            }

            // �����Ự
            result = OCISessionBegin ( m_svcContextHandle,
                        m_errorHandle, m_sessionHandle, OCI_CRED_RDBMS, OCI_DEFAULT);

            if (result != OCI_SUCCESS)
            {
                throw Error (result, m_environmentHandle, __FILE__, __LINE__);
            }

            // �����û��Ự���Ե������������ľ��
            result = OCIAttrSet ( m_svcContextHandle, OCI_HTYPE_SVCCTX,
                        m_sessionHandle, sizeof (OCISession *), OCI_ATTR_SESSION, m_errorHandle);

            if (result != OCI_SUCCESS)
            {
                throw Error (result, m_environmentHandle, __FILE__, __LINE__);
            }

            // ��������ģʽ
            if (result == OCI_SUCCESS && nonBlockingMode)
            {
                ub1 attrValue;
                attrValue = 1;
                result = OCIAttrSet ( m_serverHandle, OCI_HTYPE_SERVER,
                            &attrValue, sizeof (attrValue), OCI_ATTR_NONBLOCKING_MODE, m_errorHandle);
            }

            if (result == OCI_SUCCESS)
            {
                m_isOpened = true;
                m_isAvailable = true;
                m_isBlocking = !nonBlockingMode;
            }
            else
                throw Error(result, m_errorHandle, __FILE__, __LINE__);
        }

        void Connection::Close (void)
        {
            sword result;

            // just in case switch server to blocking mode
            if (m_serverHandle != NULL)
            {
                ub1 attrValue;
                attrValue = 0;
                result = OCIAttrSet ( m_serverHandle, OCI_HTYPE_SERVER, &attrValue
                            , sizeof (attrValue), OCI_ATTR_NONBLOCKING_MODE, m_errorHandle);
            }
            else
            {
                result = OCI_SUCCESS;
            }

            // �����Ự
            if (m_svcContextHandle != NULL && m_errorHandle != NULL)
            {
                if (m_sessionHandle != NULL)
                {
                    result = OCISessionEnd ( m_svcContextHandle
                                , m_errorHandle, m_sessionHandle, OCI_DEFAULT);
                }
                else
                {
                    result = OCI_SUCCESS;
                }

                // ��Oracle���ݿ����
                if (result == OCI_SUCCESS)
                {
                    result = OCIServerDetach ( m_serverHandle, m_errorHandle, OCI_DEFAULT);
                }
            }
            else
            {
                result = OCI_SUCCESS;
            }

            // �ͷž��
            if (result == OCI_SUCCESS && m_svcContextHandle != NULL)
            {
                result = OCIHandleFree ( m_svcContextHandle, OCI_HTYPE_SVCCTX);
            }

            if (result == OCI_SUCCESS && m_sessionHandle != NULL)
            {
                m_svcContextHandle = NULL;
                result = OCIHandleFree ( m_sessionHandle, OCI_HTYPE_SESSION);
            }

            if (result == OCI_SUCCESS && m_errorHandle != NULL)
            {
                m_sessionHandle = NULL;
                result = OCIHandleFree ( m_errorHandle, OCI_HTYPE_ERROR);
            }

            if (result == OCI_SUCCESS && m_serverHandle != NULL)
            {
                m_errorHandle = NULL;
                result = OCIHandleFree ( m_serverHandle, OCI_HTYPE_SERVER);
            }

            if (result == OCI_SUCCESS && m_environmentHandle != NULL)
            {
                m_serverHandle = NULL;
                result = OCIHandleFree ( m_environmentHandle, OCI_HTYPE_ENV);
                if (result == OCI_SUCCESS)
                {
                    m_environmentHandle = NULL;
                }
            }

            if (result == OCI_SUCCESS)
            {
                m_isOpened = false;
                m_isAvailable = false;
                m_isBlocking = false;
            }
        }
        
        void Connection::Execute(std::string sqlBlock)
        {
                     // prerequisites
			ASSERT (!sqlBlock.empty());
            Statement st (*this, sqlBlock);
            st.ExecutePrepare();
        }
		Statement* Connection::Prepare ( const std::string& sqlBlock)	// = -1
		{
			// prerequisites
			ASSERT (!sqlBlock.empty());
			
			return new Statement (*this, sqlBlock);
		}

		ResultSet*	Connection::Select ( const std::string &select)	// = -1
		{
			// prerequisites
			ASSERT (!select.empty());
			
			Statement	*s = Prepare (select);
			try
			{
				ResultSet	*r = s->Select ();
				r->AttachStatement (s);
				return r;
			}
			catch (...)
			{
				s->Release ();
				throw;
			}
		}

    }

};
