// BaseCallIn.cpp: implementation of the BaseCallIn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseCallIn.h"
#include <stdio.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI { namespace PP {
    BaseCallIn::BaseCallIn()
    {

    }

    BaseCallIn::~BaseCallIn()
    {

    }
    BaseCallIn& BaseCallIn::operator= ( const struBase_Trunk_Callin& o )
    {
        memcpy((void*)&o,(void*)&m_data, sizeof(struBase_Trunk_Callin));
        return *this;
    }

    BaseCallIn::operator struBase_Trunk_Callin() const
    {
    }
    bool BaseCallIn::operator== (const BaseCallIn & rhs)
    {
       // memcpy(&m_data, &rhs.m_data, sizeof(struBase_Trunk_Callin));
        return true;
    }
}}
