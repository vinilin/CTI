// BaseTrunkInfo.cpp: implementation of the BaseTrunkInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseTrunkInfo.h"
#include "../CommonLib/CTI_Typedfile.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI { namespace PP {
    BaseTrunkInfo::BaseTrunkInfo()
    {

    }

    BaseTrunkInfo::~BaseTrunkInfo()
    {

    }
    BaseTrunkInfo& BaseTrunkInfo::operator= ( const struBase_Trunk_Info& o )
    {
        return *this;
    }
    BaseTrunkInfo::operator struBase_Trunk_Info() const
    {
    }
    bool BaseTrunkInfo::operator== (const BaseTrunkInfo & rhs)
    {
        return true;
    }
}}
