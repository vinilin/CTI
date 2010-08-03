#ifndef _ORACLE_H
#define _ORACLE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable: 4786)
#include "StdAfx.h"
namespace CTI
{
	namespace Oracle
	{
#define	ORALIB_NO_ERROR_DISPLAY
            // maximal length (in characters) of a text input and/or output parameter
            const ub2 MAX_OUTPUT_TEXT_BYTES = 1024;
            
            // number of rows to request on each fetch
            const ub2 FETCH_SIZE = 20;
            
            // maximal length (in ansi characters) of user-supplied error message to format
            const ub2 ERROR_FORMAT_MAX_MSG_LEN = 1024;
            
            // index of the first column in a result set (one of 0, 1)
            const ub2 FIRST_COLUMN_NO = 1;
            
            // index of the first parameter in a statement (one of 0, 1)
            const ub2 FIRST_PARAMETER_NO = 1;
            
            // unicode/ansi
            // keep in mind, that those are valid for data values only
            // parameter and column names are still in ansi
#if defined (UNICODE)
		typedef std::wstring String;
		typedef const wchar_t *Pstr;
		const int CHAR_SIZE = sizeof (wchar_t);
#else
		typedef std::string String;
		typedef const char *Pstr;
		const int CHAR_SIZE = sizeof (char);
#endif
		
		
		// IN means an input parameter; OUT is an output parameter
		// IN OUT is both input and output parameter
		// OPTIONAL means, that value is not required - a default will be used instead
#if	!defined (IN)
#	define	IN
#endif
#if	!defined (OUT)
#	define	OUT
#endif
#if	!defined (OPTIONAL)
#	define	OPTIONAL
#endif
		
		
		// internal data types are 4 only: number, date, text and result se
		
		// parameter prefixes (for example: :n1 is a number, :sName is a text)
		enum ParameterPrefixesEnum
		{
			PP_ARRAY = 't',
				PP_NUMERIC = 'n',
				PP_DATE = 'd',
				PP_TEXT = 's',
				PP_RESULT_SET = 'c'
		};
	}
	
}; // oralib namespace



#include "error.h"

#include "datetime.h"
#include "connection.h"
#include "column.h"
#include "resultset.h"
#include "statement.h"
#endif
