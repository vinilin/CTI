// BaseInitComp.h: interface for the BaseInitComp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEINITCOMP_H__03F143EC_C425_484F_B404_D61621AA7526__INCLUDED_)
#define AFX_BASEINITCOMP_H__03F143EC_C425_484F_B404_D61621AA7526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../CommonLib/CTI_Typedfile.h"

namespace CTI { namespace PP {
    class BaseInitComp  
    {
    private:
        struBASE_INIT_COMP m_data;
    public:
        BaseInitComp();
        virtual ~BaseInitComp();
    public:
        inline int BaseId(){ return m_data.Baseid; }
        inline UINT CardNo() {return m_data.CardNo;}
        inline UINT ISUPE1TrunkTotal() {return m_data.ISUPE1TrunkTotal;}
        inline UINT PBXTrunkTotal() {return m_data.PBXTrunkTotal;}
        inline UINT PBXsimuTotal() {return m_data.PBXsimuTotal;}
        inline UINT TUPE1TrunkTotal(){return m_data.TUPE1TrunkTotal;}
        inline UINT VisualTrunkTotal(){return m_data.VisualTrunkTotal;}
        inline UINT SimuTrunkTotal(){return m_data.simuTrunkTotal;}
    public:
        BaseInitComp& operator= ( const struBASE_INIT_COMP& o );
        operator struBASE_INIT_COMP() const;
        bool operator== (const BaseInitComp & rhs);
    };
}}
#endif // !defined(AFX_BASEINITCOMP_H__03F143EC_C425_484F_B404_D61621AA7526__INCLUDED_)
