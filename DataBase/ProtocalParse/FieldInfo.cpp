// FieldInfo.cpp: implementation of the FieldInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FieldInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace CTI
{
	namespace PP
	{
		FieldInfo::FieldInfo()
		{
			
		}
		
		FieldInfo::~FieldInfo()
		{
			
		}
		FieldInfo& FieldInfo::operator = ( const Trunk_Fieldinfo& o )
		{
			m_data = o;
			return *this;
		}
		FieldInfo::operator Trunk_Fieldinfo() const
		{
			return m_data;
		}		
	}
}
