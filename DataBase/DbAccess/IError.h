// IError.h: interface for the IError class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IERROR_H__36441BA7_4BEF_40FD_8D17_FCFDE145CFDC__INCLUDED_)
#define AFX_IERROR_H__36441BA7_4BEF_40FD_8D17_FCFDE145CFDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
namespace CTI
{
	namespace DBAccess
	{
		class IError  
		{
		public:
			virtual std::string Message() = 0;
		};
	}

}


#endif // !defined(AFX_IERROR_H__36441BA7_4BEF_40FD_8D17_FCFDE145CFDC__INCLUDED_)
