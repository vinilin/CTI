// Column.cpp: implementation of the Column class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Column.h"
#include "ResultSet.h"
#include "Connection.h"
#include "Error.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace Oracle
    {
  Column::Column (
                 ResultSet *rs,
                 const char *name,
                 ub4 nameLen,
                 ub2 ociDataType,
                 ub4 maxDataSize,
				 int fetchSize)	// = FETCH_SIZE
  {
	  // prerequisites
	  ASSERT (rs && name);
	  
	  Initialize ();
	  
	  m_colName = std::string (name, nameLen);
	  m_ociType = ociDataType;
	  
	  // decide the format we want oci to return data in (m_ociType member)
	  switch (ociDataType)
	  {
	  case	SQLT_INT:	// integer
	  case	SQLT_LNG:	// long
	  case	SQLT_UIN:	// unsigned int
		  
	  case	SQLT_NUM:	// numeric
	  case	SQLT_FLT:	// float
	  case	SQLT_VNU:	// numeric with length
	  case	SQLT_PDN:	// packed decimal
		  m_ociType = SQLT_VNU;
		  m_colType = DT_NUMBER;
		  m_size = sizeof (OCINumber);
		  break;
		  
	  case	SQLT_DAT:	// date
	  case	SQLT_ODT:	// oci date - should not appear?
		  m_ociType = SQLT_ODT;
		  m_colType = DT_DATE;
		  m_size = sizeof (OCIDate);
		  break;
		  
	  case	SQLT_CHR:	// character string
	  case	SQLT_STR:	// zero-terminated string
	  case	SQLT_VCS:	// variable-character string
	  case	SQLT_AFC:	// ansi fixed char
	  case	SQLT_AVC:	// ansi var char
	  case	SQLT_VST:	// oci string type
		  m_ociType = SQLT_STR;
		  m_colType = DT_TEXT;
		  m_size = (maxDataSize + 1) * CHAR_SIZE; // + 1 for terminating zero!
		  break;
		  
	  default:
		  throw Error (EC_UNSUP_ORA_TYPE, __FILE__, __LINE__);
	  }
	  
	  // allocate memory for m_indicators, Column lengths and fetched data
	  m_indicators = new sb2 [fetchSize];
	  
	  if (m_colType == DT_TEXT)
		  // only text Columns requires length
		  m_dataLens = new ub2 [fetchSize];
	  else
		  m_dataLens = NULL;
	  
	  m_fetchBuffer = new char [m_size * fetchSize];
	  
	  m_defineHandle = NULL;
	  
	  if (!m_indicators || !m_fetchBuffer)
	  {
		  Cleanup (); // because there could be some memory allocated
		  // no memory
		  throw Error (EC_NO_MEMORY, __FILE__, __LINE__);
	  }
	  
	  m_resultSet = rs;
  }


        Column::~Column()
        {

        }

        void Column::Initialize (void)
        {
            m_colType = DT_UNKNOWN;
            m_ociType = 0;
            m_size = 0;
            m_indicators = NULL;
            m_dataLens = NULL;
            m_fetchBuffer = NULL;
            m_defineHandle = NULL;
            m_resultSet = NULL;
        }

        void Column::Cleanup (void)
        {
            // set all to null to be save to call cleanup more than once for a single instance
            if (m_indicators) 
            {
                delete [] m_indicators, m_indicators = NULL;
            }

            if (m_dataLens) 
            {
                delete [] m_dataLens, m_dataLens = NULL;
            }

            if (m_fetchBuffer) 
            {
                delete [] m_fetchBuffer, m_fetchBuffer = NULL;
            }
        }


        bool Column::IsNull (void) const
        {
            // prerequisites
            ASSERT (m_resultSet);
            ub2	rowNo = static_cast <ub2> (m_resultSet->m_currentRow % m_resultSet->m_fetchCount);
            return (m_indicators [rowNo] == -1);
        }

        Pstr Column::AsString (void) const
        {
            // prerequisites
            ASSERT (m_resultSet);
            ub2 rowNo = static_cast <ub2> (m_resultSet->m_currentRow % m_resultSet->m_fetchCount);
            if (m_colType == DT_TEXT && m_indicators [rowNo] != -1)
            {
                return (reinterpret_cast <Pstr> (m_fetchBuffer + m_size * rowNo));
            }
            else
            {
                throw Error (EC_BAD_OUTPUT_TYPE, __FILE__, __LINE__);
            }
        }

        double Column::AsDouble (void) const
        {
            // prerequisites
            ASSERT (m_resultSet);
            ub2 rowNo = static_cast <ub2> (m_resultSet->m_currentRow % m_resultSet->m_fetchCount);
            if (m_colType == DT_NUMBER && m_indicators [rowNo] != -1)
            {
                double value;
                sword result = ::OCINumberToReal (m_resultSet->m_conn->m_errorHandle, 
                                    reinterpret_cast <OCINumber *> (m_fetchBuffer) + rowNo,
                                    sizeof (double), &value);
                if (result == OCI_SUCCESS)
                {
                    return value;
                }
                else
                {
                    throw Error (result, m_resultSet->m_conn->m_errorHandle, __FILE__, __LINE__);
                }
            }
            else
            {
                throw Error (EC_BAD_OUTPUT_TYPE, __FILE__, __LINE__);
            }
        }

        long Column::AsLong (void) const
        {
            // prerequisites
            ASSERT (m_resultSet);
            ub2	rowNo = static_cast <ub2> (m_resultSet->m_currentRow % m_resultSet->m_fetchCount);
            if (m_colType == DT_NUMBER && m_indicators [rowNo] != -1)
            {
                long value;
                sword result = OCINumberToInt ( m_resultSet->m_conn->m_errorHandle, 
                                reinterpret_cast <OCINumber *> (m_fetchBuffer) + rowNo,
                                sizeof (long), OCI_NUMBER_SIGNED, &value);
                if (result == OCI_SUCCESS)
                {
                    return (value);
                }
                else
                {
                   throw Error (result, m_resultSet->m_conn->m_errorHandle, __FILE__, __LINE__);
                }
            }
            else
            {
                throw Error (EC_BAD_OUTPUT_TYPE, __FILE__, __LINE__);
            }
        }

        DateTime Column::AsDatetime (void) const
        {
            // prerequisites
            ASSERT (m_resultSet);
            ub2	rowNo = static_cast <ub2> (m_resultSet->m_currentRow % m_resultSet->m_fetchCount);
            if (m_colType == DT_DATE && m_indicators [rowNo] != -1)
            {
                return DateTime (*(reinterpret_cast <OCIDate *> (m_fetchBuffer) + rowNo));
            }
            else
            {
                throw Error (EC_BAD_OUTPUT_TYPE, __FILE__, __LINE__);
            }
        }
    }
}
