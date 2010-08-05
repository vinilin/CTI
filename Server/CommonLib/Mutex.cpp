// Mutex.cpp: implementation of the CMutex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mutex.h"
#include <exception>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
	namespace Common
	{

		
		Mutex::Mutex()
		{
			m_mutex = CreateMutex(NULL, FALSE, NULL);
		}
		
		Mutex::~Mutex()
		{
			if(m_mutex != NULL)
			{
				ASSERT(m_mutex != NULL);
				CloseHandle(m_mutex);
			}
		}
		
		void Mutex::Lock( int timeout )
		{
			ASSERT(m_mutex != NULL);
			DWORD rs = WaitForSingleObject(m_mutex,timeout);
			if(rs == WAIT_TIMEOUT)
			{
				throw exception("timeout");
			}
		}
		
		void Mutex::Unlock()
		{
			ASSERT(m_mutex != NULL);
			ReleaseMutex(m_mutex);
		}
	}
}

