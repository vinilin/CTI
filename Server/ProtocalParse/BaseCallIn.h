// BaseCallIn.h: interface for the BaseCallIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASECALLIN_H__571C36D7_42CB_4A12_9518_8C23ED2FDEE0__INCLUDED_)
#define AFX_BASECALLIN_H__571C36D7_42CB_4A12_9518_8C23ED2FDEE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include "../CommonLib/CTI_Typedfile.h"

namespace CTI { namespace PP{
    class BaseCallIn  
    {
    private:
        struBase_Trunk_Callin m_data;
    public:
        BaseCallIn();
        virtual ~BaseCallIn();
    public:
        inline std::string Callee(){return m_data.Callee;}
        inline std::string Caller(){return m_data.Caller;}
        inline std::string OraCallee(){return m_data.oraCallee;}
        inline UINT Line(){return m_data.Line;}
        inline int TrunkId(){return m_data.Trunkid;}
        inline int CardId(){return m_data.Cardid;}
        inline time_t CallTime(){return m_data.Calltime;}

    public:
        BaseCallIn& operator= ( const struBase_Trunk_Callin& o );
        operator struBase_Trunk_Callin() const;
        bool operator== (const BaseCallIn & rhs);
    };
}}
#endif // !defined(AFX_BASECALLIN_H__571C36D7_42CB_4A12_9518_8C23ED2FDEE0__INCLUDED_)
