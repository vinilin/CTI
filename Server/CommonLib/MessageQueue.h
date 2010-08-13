// MessageQueue.h: interface for the MessageQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEQUEUE_H__90368C4D_692A_43F9_BD13_D6742196F121__INCLUDED_)
#define AFX_MESSAGEQUEUE_H__90368C4D_692A_43F9_BD13_D6742196F121__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <queue>
#include "stdafx.h"
#include "Mutex.h"
#include "Semaphore.h"


namespace CTI
{
	namespace Common //protocal parse
	{
        template <class Key, class Value>
        class ThSafeMap
        {
        private:
            std::map<Key,Value> m_map;
            Mutex m_mutex;
            void Add(Key key, Value value)
            {
                assert(m_map.find(key) == m_map.end());
                m_mutex.Lock();
                m_map[key] = value;
                m_mutex.Unlock();
            }
            void Remove(Key key)
            {
                m_mutex.Lock();
                m_map.erase(key);
                m_mutex.Unlock();
            }
            Value Get(Key key)
            {
                m_mutex.Lock();
                Value tmp = m_map[key];
                m_mutex.Unlock();
            }
        };

        template < class T  >
        class QsynchronizeQueue 
        {
        private:
            std::queue<T> m_queue;
            Mutex m_mutex;
	    Semaphore m_sem;
		public:
			typedef T ValueType;
        public:
            QsynchronizeQueue() :m_sem(MIN_SEM_COUNT,MAX_SEM_COUNT)
            { }
		
            ~QsynchronizeQueue(){}

            T Pop(int timeout = INFINITE)
            {
                    m_sem.Lock(timeout);
                    m_mutex.Lock(timeout);
                    T tmp = m_queue.front();
                    m_queue.pop();
                    m_mutex.Unlock();
                    return tmp;
            }
		
            void Push(const T& item,int timeout = INFINITE)
            {
                    m_mutex.Lock(timeout);
                    m_queue.push(item);
                    m_sem.Unlock();
                    m_mutex.Unlock();
            }
        };
    }
}

#endif // !defined(AFX_MESSAGEQUEUE_H__90368C4D_692A_43F9_BD13_D6742196F121__INCLUDED_)
