// Mutex.h: interface for the CMutex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUTEX_H__9982AFC2_2A5B_4A02_AC59_A9B2DBE04166__INCLUDED_)
#define AFX_MUTEX_H__9982AFC2_2A5B_4A02_AC59_A9B2DBE04166__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace CTI
{
	namespace Common
	{
         class Mutex
            {
            public:
                Mutex();
                ~Mutex();
            public:
                void Lock(int timeout);
                void Unlock();
            private:
                Mutex(const Mutex&);
                Mutex& operator = (const Mutex&);
                HANDLE m_mutex;
            };
	}
}
#endif // !defined(AFX_MUTEX_H__9982AFC2_2A5B_4A02_AC59_A9B2DBE04166__INCLUDED_)
