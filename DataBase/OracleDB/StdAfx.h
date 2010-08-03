// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Windows Header Files:
#include <afx.h>
#include <afxwin.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tchar.h>
#include <time.h>



#ifndef	__STDC__
#	define	__STDC__	1
#	include <oci.h>
#	undef	__STDC__
#else
#	include <oci.h>
#endif

// Local Header Files

// c++ stl Header Files
#include <iostream>
#include <map>
#include <string>
#include <vector>
// oracle  Header Files
#include <oci.h>

#if defined (UNICODE)
typedef std::wstring String;
typedef const wchar_t *Pstr;
const int CHAR_SIZE = sizeof (wchar_t);
#else
typedef std::string String;
typedef const char *Pstr;
const int CHAR_SIZE = sizeof (char);
#endif
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
// TODO: reference additional headers your program requires here
#ifndef ASSERT
#define ASSERT(x) assert(x)
#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
