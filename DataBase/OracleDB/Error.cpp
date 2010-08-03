// Error.cpp: implementation of the Error class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Error.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace CTI
{
    namespace Oracle
    {
        Error::Error( sword oraErr, OCIError *errorHandle
                , std::string const& sourceName, long lineNumber)
        {
            OracleError ( oraErr, errorHandle, NULL);
            m_type = ET_ORACLE;
            m_winapiCode = 0;
            m_source = sourceName;
            m_lineNO = lineNumber;
        }

        Error::Error( sword oraErr, OCIEnv *env_handle
                , std::string const& sourceName , long lineNumber)
        {
            OracleError ( oraErr, NULL, env_handle);

            m_type = ET_ORACLE;
            m_winapiCode = 0;
            m_source = sourceName;
            m_lineNO = lineNumber;
        }

        Error::Error ( sword errCode 
                , std::string const& sourceName 
                , long lineNumber )
        {
            OracleError (errCode);

            m_type = ET_ORALIB;
            m_oraCode = 0;
            m_winapiCode = 0;
            m_source = sourceName;
            m_lineNO = lineNumber;
        }

		Error::~Error ()
		{
		}

        void Error::OracleError( sword oraErrCode
                , OCIError *errorHandle, OCIEnv *env_handle )
        {
            bool get_details = false;
            ASSERT (errorHandle != NULL || env_handle != NULL);

            m_code = oraErrCode;

            switch (oraErrCode)
            {
            case OCI_SUCCESS:
                m_description = "(OCI_SUCCESS)";
                break;
            case OCI_SUCCESS_WITH_INFO:
                m_description = "(OCI_SUCCESS_WITH_INFO)";
                get_details = true;
                break;
            case OCI_ERROR:
                m_description = "(OCI_ERROR)";
                get_details = true;
                break;
            case OCI_NO_DATA:
                m_description = "(OCI_NO_DATA)";
                get_details = true;
                break;
            case OCI_INVALID_HANDLE:
                m_description = "(OCI_INVALID_HANDLE)";
                break;
            case OCI_NEED_DATA:
                m_description = "(OCI_NEED_DATA)";
                break;
            case OCI_STILL_EXECUTING:
                m_description = "(OCI_STILL_EXECUTING)";
                get_details = true;
                break;
            case OCI_CONTINUE:
                m_description = "(OCI_CONTINUE)";
                break;
            default:
                m_description = "unknown";
            }

	    // ªÒ»°œÍœ∏¥ÌŒÛ√Ë ˆ
            if (get_details)
            {
                const int max_text_len = 4000;
                char *errorText = new char [max_text_len];
                if (errorText)
                {
                    *errorText = '\0';
                    if (errorHandle)
                    {
                        OCIErrorGet ( errorHandle, 1, NULL
                            ,&m_oraCode, reinterpret_cast<text *> (errorText),
                            max_text_len, OCI_HTYPE_ERROR);
                    }
                    else
                    {
                        OCIErrorGet ( env_handle, 1, NULL
                            , &m_oraCode, reinterpret_cast<text *> (errorText)
                            , max_text_len, OCI_HTYPE_ENV);
                    }
                    m_description += " ";
                    m_description += errorText;
                    delete [] errorText;
                }
            }
        }

        void Error::OracleError( sword errCode)
        {
            m_code = errCode;
            switch (errCode)
            {
            case EC_ENV_CREATE_FAILED:
                m_description = "(EC_ENV_CREATE_FAILED) Environment handle creation failed";
                break;
            case EC_TIMEOUT:
                m_description = "(EC_TIMEOUT) Statement took too long to complete and has been aborted";
                break;
            case EC_NO_MEMORY:
                m_description = "(EC_NO_MEMORY) Memory allocation request has failed";
                break;
            case EC_BAD_PARAM_TYPE:
                m_description = "(EC_BAD_PARAM_TYPE) Parameter m_type is incorrect";
                break;
            case EC_POOL_NOT_SETUP:
                m_description = "(EC_POOL_NOT_SETUP) Connection pool has not been setup yet";
                break;
            case EC_BAD_INPUT_TYPE:
                m_description = "(EC_BAD_INPUT_TYPE) Input data doesn't have expected m_type";
                break;
            case EC_BAD_OUTPUT_TYPE:
                m_description = "(EC_BAD_OUTPUT_TYPE) Cannot convert to requested m_type";
                break;
            case EC_BAD_TRANSFORM:
                m_description = "(EC_BAD_TRANSFORM) Requested transformation is not possible";
                break;
            case EC_BAD_PARAM_PREFIX:
                m_description = "(EC_BAD_PARAM_PREFIX) Parameter prefix is not known";
                break;
            case EC_INTERNAL:
                m_description = "(EC_INTERNAL) Internal library Error. Please, report to developers";
                break;
            case EC_UNSUP_ORA_TYPE:
                m_description = "(EC_UNSUP_ORA_TYPE) "
                    "Unsupported Oracle m_type - cannot be converted to numeric, date or text";
                break;
            case EC_PARAMETER_NOT_FOUND:
                m_description = "(EC_PARAMETER_NOT_FOUND) Name not found in statement's parameters";
                break;
            case EC_COLUMN_NOT_FOUND:
                m_description = "(EC_COLUMN_NOT_FOUND) Result set doesn't contain column with such name";
                break;
            default:
                m_description = "unknown";
            }
		}

            std::string	Error::Details () const
            {
                static const char *errorTypesText [] =
                {
                    "unknown", "Oracle", "OraLib", "Win32 API"
                };

                return "Error type: " + std::string (errorTypesText [m_type]) + "\n"
					"Description: " + m_description + "\n";
            }
    }
};
