// Connection.h: interface for the Connection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTION_H__E6EE35B3_5308_4A2C_9D62_2E56043B5D70__INCLUDED_)
#define AFX_CONNECTION_H__E6EE35B3_5308_4A2C_9D62_2E56043B5D70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable: 4786)
#include "Oracle.h"
namespace CTI
{
    namespace Oracle
    {
		class ResultSet;
		class Column;
		class Statement;

        class Connection  
        {
			friend class ResultSet;
			friend class Column;
			friend class Statement;
        private:
            OCIEnv				*m_environmentHandle;   // Oracle�������
            OCIServer	        *m_serverHandle;        // ������
            mutable OCIError	*m_errorHandle;	        // ���ܻᱻ���Oracle API�ı�
            OCISession	        *m_sessionHandle;       // �Ự���
            OCISvcCtx	        *m_svcContextHandle;    // �������ݾ��

            bool		 m_isOpened;
            bool		 m_isAvailable;	        // (used for connection pooling)?
            bool		 m_isBlocking;		// ���ݿ�����ģʽ
        public:
            Connection();
            virtual ~Connection();
        private: 
            void Initialize();
            void OraHandleAlloc(void ** handle, int type, int size = 0, char * mem = NULL);
        public:
            void Open( std::string const &serviceName 
				,std::string const &usrName, std::string const &pwd,std::string const& db = ""
                    ,ULONG envMode = OCI_OBJECT ,BOOL nonBlockingMode = false);
            void Close();
            inline void Commit()
            {
                Execute("commit");
            }
            inline void RollBack()
            {
                Execute("rollback");
            }
            BOOL IsOpend()
            {
                return m_isOpened;
            }
            void Execute(std::string sql);
			ResultSet*	Select ( const std::string &select);
			Statement*  Prepare ( const std::string& sqlBlock);	// = -1
        };
    }
}


#endif // !defined(AFX_CONNECTION_H__E6EE35B3_5308_4A2C_9D62_2E56043B5D70__INCLUDED_)
