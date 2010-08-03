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
            ErrorTypes  m_type;         // 错误类型
            sword       m_code;         // 自定义错误码
            sb4         m_oraCode;      // Oracle的错误码 ORA-xxxxx
#if defined (_WIN32)
            ULONG       m_winapiCode;	// win32 api 错误码
#endif

            std::string	m_description;	// 错误描述
            std::string	m_source;	// 错误发生的源文件名
            long	m_lineNO;	// 错误发生的行号
            
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
            // 获取Oracle OCI错误信息
            void OracleError( sword oraErrCode
                    , OCIError *errorHandle, OCIEnv *env_handle );

            // 获取自定义Oracle错误信息
            void OracleError( sword errCode);
		public:
            // 获取错误信息
            std::string	Details () const;

        };
    }
};
#endif // !defined(AFX_ERROR_H__295F97CB_D57B_478E_922C_905FFA570F14__INCLUDED_)
