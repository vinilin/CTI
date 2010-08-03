// Semaphore.h: interface for the CSemaphore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEMAPHORE_H__CF5F0F55_7C66_4D9E_8319_486D958AD1BD__INCLUDED_)
#define AFX_SEMAPHORE_H__CF5F0F55_7C66_4D9E_8319_486D958AD1BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_SEM_COUNT 10000000
#define MIN_SEM_COUNT 0

namespace CTI
{
	namespace Common
	{
		class Semaphore
		{
		private:
			HANDLE m_semaphore;
		public:
			Semaphore(int min = 0, int max = 20);
			~Semaphore();
			void Lock(int timeout);
			void Unlock();
		};
	}
}


#endif // !defined(AFX_SEMAPHORE_H__CF5F0F55_7C66_4D9E_8319_486D958AD1BD__INCLUDED_)
