// Error.h: interface for the Error class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERROR_H__295F97CB_D57B_478E_922C_905FFA570F14__INCLUDED_)
#define AFX_ERROR_H__295F97CB_D57B_478E_922C_905FFA570F14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable: 4786)
namespace CTI
{
    namespace Oracle
    {
        enum ErrorCodes
        {
            EC_OCI_ERROR = -1,
            EC_ENV_CREATE_FAILED = 1000,
            EC_TIMEOUT,
            EC_NO_MEMORY,
            EC_BAD_PARAM_TYPE,
            EC_POOL_NOT_SETUP,
            EC_BAD_INPUT_TYPE,
            EC_BAD_OUTPUT_TYPE,
            EC_BAD_TRANSFORM,
            EC_BAD_PARAM_PREFIX,
            EC_UNSUP_ORA_TYPE,
            EC_PARAMETER_NOT_FOUND,
            EC_COLUMN_NOT_FOUND,
            EC_INTERNAL
        };


        // error types
        enum ErrorTypes
        {
            ET_UNKNOWN = 0,
            ET_ORACLE,
            ET_ORALIB,
            ET_WINAPI
        };

        class Error  
        {
        private:
            ErrorTypes  m_type;         // ��������
            sword       m_code;         // �Զ��������
            sb4         m_oraCode;      // Oracle�Ĵ����� ORA-xxxxx
#if defined (_WIN32)
            ULONG       m_winapiCode;	// win32 api ������
#endif

            std::string	m_description;	// ��������
            std::string	m_source;	// ��������Դ�ļ���
            long	m_lineNO;	// ���������к�
            
        public:
            Error( sword oraErr, OCIError *errorHandle
                    , std::string const& sourceName = ""
                    , long lineNumber = -1);

            Error ( sword oraErr, OCIEnv *env_handle
                    , std::string const& sourceName = ""
                    , long lineNumber = -1);		

            Error ( sword errCode 
                    , std::string const& sourceName = ""
                    , long lineNumber = -1);		
            virtual ~Error();
        private:
            // ��ȡOracle OCI������Ϣ
            void OracleError( sword oraErrCode
                    , OCIError *errorHandle, OCIEnv *env_handle );

            // ��ȡ�Զ���Oracle������Ϣ
            void OracleError( sword errCode);
		public:
            // ��ȡ������Ϣ
            std::string	Details () const;

        };
    }
};
#endif // !defined(AFX_ERROR_H__295F97CB_D57B_478E_922C_905FFA570F14__INCLUDED_)
