// BaseInitComp.cpp: implementation of the BaseInitComp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseInitComp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI { namespace PP {

    BaseInitComp::BaseInitComp()
    {

    }

    BaseInitComp::~BaseInitComp()
    {

    }

    BaseInitComp& BaseInitComp::operator= ( const struBASE_INIT_COMP& o )
    {
        return *this;
    }

     BaseInitComp::operator struBASE_INIT_COMP() const
    {
        
    }

    bool BaseInitComp::operator== (const BaseInitComp & rhs)
    {
        return true;
    }
}}
