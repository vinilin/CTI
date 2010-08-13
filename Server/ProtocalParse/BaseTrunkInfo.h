// BaseTrunkInfo.h: interface for the BaseTrunkInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASETRUNKINFO_H__ED31B5A2_5EE5_443A_A96F_B74C8B5BE845__INCLUDED_)
#define AFX_BASETRUNKINFO_H__ED31B5A2_5EE5_443A_A96F_B74C8B5BE845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../CommonLib/CTI_Typedfile.h"

namespace CTI { namespace PP {
    class BaseTrunkInfo  
    {
    private:
        struBase_Trunk_Info m_data;
    public:
        BaseTrunkInfo();
        virtual ~BaseTrunkInfo();
    public:
        inline CardId() {return m_data.Cardid;}
        inline Line() {return m_data.Line;}
        inline LineState() {return m_data.LineState;}
        inline LineType() {return m_data.Linetype;}
        inline TrunkId() {return m_data.Trunkid;}
    public:
        BaseTrunkInfo& operator= ( const struBase_Trunk_Info& o );
        operator struBase_Trunk_Info() const;
        bool operator== (const BaseTrunkInfo & rhs);
    };
}}
#endif // !defined(AFX_BASETRUNKINFO_H__ED31B5A2_5EE5_443A_A96F_B74C8B5BE845__INCLUDED_)
