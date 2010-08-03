// ITable.h: interface for the ITable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITABLE_H__C9B912EC_555B_4FD9_8B86_E0BCF3F2EADB__INCLUDED_)
#define AFX_ITABLE_H__C9B912EC_555B_4FD9_8B86_E0BCF3F2EADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace CTI
{
	namespace PP
	{
		class IRecord  
		{
		public:
            virtual int Size() const = 0;
            virtual int Index() const= 0;
            virtual void* Data() const= 0;

		};
	}
}


#endif // !defined(AFX_ITABLE_H__C9B912EC_555B_4FD9_8B86_E0BCF3F2EADB__INCLUDED_)
