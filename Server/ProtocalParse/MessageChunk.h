// MessageChunk.h: interface for the MessageChunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGECHUNK_H__8D81E316_E97C_43A0_9409_468B48F7EBE5__INCLUDED_)
#define AFX_MESSAGECHUNK_H__8D81E316_E97C_43A0_9409_468B48F7EBE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../CommonLib/DataType.h"
#include "../CommonLib/CTI_Typedfile.h"
#include "ConnectionInfo.h"
#include "DbInfo.h"
#include "FieldInfo.h"
#include "BaseCallIn.h"
#include "BaseInitComp.h"
#include "BaseTrunkInfo.h"
using namespace CTI;
namespace CTI
{
    namespace PP // ProtocalParse
    {
        class MessageChunk  
        {
        private:
            LINE_HEAD			m_data;
        private:
	    int				m_read;
	    int				m_write;
        public:
            MessageChunk();
            MessageChunk(LINE_HEAD const& chunk);
            MessageChunk(const MessageChunk& chunk);
            virtual ~MessageChunk();
                
        public: 
            //��������
            MessageChunk& operator=(const MessageChunk& chunk);
            MessageChunk& operator=(const LINE_HEAD& chunk);
            operator LINE_HEAD();
        public:
            inline Common::u32 UnitId() { return m_data.unitid;}
            inline Common::u16 TaskClass(){ return m_data.taskclass; }
            inline Common::u16 ModuleId(){ return m_data.moduleid; }
            inline Common::u32 DataLen() { return m_data.datalen; }
            inline Common::u32 DataType(){ return m_data.datatype; }
        public:
	    // ���ݿ�������Ϣ
            BOOL operator << (const ConnectionInfo& o);
            BOOL operator >> (ConnectionInfo& o);
			
	    // ������ʽṹ
	    BOOL operator << (const DbInfo& o);
            BOOL operator >> (DbInfo& o);
			
	    // ��������ʽṹ
	    BOOL operator << (const FieldInfo& o);
            BOOL operator >> (FieldInfo& o);

            // Base��ʼ������
            BOOL operator << (const BaseInitComp& o);
            BOOL operator >> (BaseInitComp& o);

            // BaseCallIn����
            BOOL operator << (const BaseCallIn& o);
            BOOL operator >> (BaseCallIn& o);

            // ͨ��״̬��Ǩ����
            BOOL operator << (const BaseTrunkInfo& o);
            BOOL operator >> (BaseTrunkInfo& o);
        };
    }
}


#endif // !defined(AFX_MESSAGECHUNK_H__8D81E316_E97C_43A0_9409_468B48F7EBE5__INCLUDED_)
