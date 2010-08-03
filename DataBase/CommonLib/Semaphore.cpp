// Semaphore.cpp: implementation of the CSemaphore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Semaphore.h"
#include <exception>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace CTI
{
	namespace Common
	{
		void CTI::Common::Semaphore::Unlock()
		{
			ASSERT(m_semaphore != NULL);
			long xx = 0;
			ReleaseSemaphore(m_semaphore,1,&xx);
		}
		
		Semaphore::Semaphore( int min /*= 0*/, int max /*= 20*/ )
		{
			m_semaphore = CreateSemaphore(NULL, min, max, NULL);
		}
		
		Semaphore::~Semaphore()
		{
			if(m_semaphore != NULL)
			{
				ASSERT(m_semaphore != NULL);
				CloseHandle(m_semaphore);
			}
		}
		
		void Semaphore::Lock( int timeout )
		{
			ASSERT(m_semaphore != NULL);
			DWORD rs = WaitForSingleObject(m_semaphore,timeout);
			if(rs == WAIT_TIMEOUT)
			{
				throw exception("timeout");
			}
		}
	}
}
