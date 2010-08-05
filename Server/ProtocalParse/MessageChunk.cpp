// MessageChunk.cpp: implementation of the MessageChunk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MessageChunk.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
    namespace PP 
    {

        MessageChunk::MessageChunk()
        {
            memset(&m_data,0,sizeof(m_data));
			m_read =0;
			m_write	=0;
        }

        MessageChunk::MessageChunk(LINE_HEAD const& chunk)
        {
			memcpy(&m_data, &chunk,sizeof(chunk));
			m_read = 0;
			m_write = 0;
        }
		MessageChunk::MessageChunk(const MessageChunk& chunk)
		{
			*this = chunk;
		}

        MessageChunk::~MessageChunk()
        {
        }

        BOOL MessageChunk::operator<< (const ConnectionInfo& o)
        {
			m_data.datatype = D_DB_CONNECT;
			struConnectinfo conn = o;
			memcpy(m_data.databuff+m_write,&conn,sizeof(struConnectinfo));
			m_write += sizeof(struConnectinfo);
			m_data.datalen = m_write;
			return TRUE;
        }

        BOOL MessageChunk::operator >> (ConnectionInfo& o)
        {
			ASSERT(m_data.datatype == D_DB_CONNECT);
			if(m_data.datalen == m_read)
			{
				return FALSE;
			}
			o = *((struConnectinfo*)m_data.databuff+m_read);
			m_read += sizeof(struConnectinfo);

			return TRUE;
        }

		BOOL MessageChunk::operator<< (const DbInfo& o)
        {
			
			m_data.datatype = D_DB_RESULT;
			struDBinfo dbinfo = o;
			memcpy(m_data.databuff+m_write,&dbinfo,sizeof(struDBinfo));
			m_write += sizeof(struDBinfo);
			m_data.datalen = m_write;
			return TRUE;
        }
		
        BOOL MessageChunk::operator >> (DbInfo& o)
        {
			ASSERT(m_data.datatype == D_DB_RESULT);
			if(m_data.datalen == m_read)
			{
				return FALSE;
			}
			o = *((struDBinfo*)m_data.databuff+m_read);
			m_read += sizeof(struDBinfo);
			return TRUE;
        }

		BOOL MessageChunk::operator<< (const FieldInfo& o)
        {
			m_data.datatype = D_DB_FIELD;
			Trunk_Fieldinfo dbinfo = o;
			memcpy(m_data.databuff+m_write,&dbinfo,sizeof(Trunk_Fieldinfo));
			m_write += sizeof(Trunk_Fieldinfo);
			m_data.datalen = m_write;
			return TRUE;
        }
		
        BOOL MessageChunk::operator >> (FieldInfo& o)
        {
			ASSERT(m_data.datatype == D_DB_FIELD);
			if(m_data.datalen == m_read)
			{
				return false;
			}
			o = *((Trunk_Fieldinfo*)m_data.databuff+m_read);
			m_read += sizeof(Trunk_Fieldinfo);
			return TRUE;
        }

		MessageChunk& MessageChunk::operator=(const MessageChunk& chunk)
		{
			m_read = chunk.m_read;
			m_write = chunk.m_write;
			memcpy(&m_data,&chunk,sizeof(LINE_HEAD));
			return *this;
		}
		MessageChunk& MessageChunk::operator=(const LINE_HEAD& chunk)
		{
			m_read = 0;
			m_write = 0;
			memcpy(&m_data,&chunk,sizeof(LINE_HEAD));
			return *this;
		}
		MessageChunk::operator LINE_HEAD()
		{
			return m_data;
		}
    }
}

