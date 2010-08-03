// IConnection.h: interface for the IConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICONNECTION_H__9500C7A8_33C0_4110_8554_89233123E03F__INCLUDED_)
#define AFX_ICONNECTION_H__9500C7A8_33C0_4110_8554_89233123E03F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IResultSet.h"
#include "../CommonLib/CTI_Typedfile.h"
#include "../ProtocalParse/ConnectionInfo.h"
using namespace CTI::PP;
namespace CTI
{
	namespace DBAccess
	{
		class IConnection  
		{
		protected:
			ConnectionInfo m_connInfo;
		public:
			IConnection(const ConnectionInfo& connInfo);
			virtual void Open() = 0;
			virtual void Execute(std::string sql) = 0;
			//************************************
			// Method:    Select
			// FullName:  CTI::DBAccess::IConnection::Select
			// Access:    virtual public 
			// Returns:   IResultSet*
			// Qualifier: 有Select函数所获得的结果集必须手动的释放内存，使用delete进行释放
			// Parameter: std::string sql
			//************************************
			virtual IResultSet* Select(std::string sql) = 0;
            virtual BOOL IsOpen() = 0;
            virtual void Close() = 0;
			inline int ConnId()
			{
				return m_connInfo.ConId();
			}
			inline std::string Host()
			{
				return m_connInfo.Server();
			}
			inline std::string Db()
			{
				return m_connInfo.Database();
			}
			inline std::string User()
			{
				return m_connInfo.User();
			}
			inline std::string Pwd()
			{
				return m_connInfo.Password();
			}
			inline int ConnType()
			{
				return m_connInfo.ConnectType();
			}
			inline int DbType()
			{
				return m_connInfo.DbType();
			}
		};
	}
}


#endif // !defined(AFX_ICONNECTION_H__9500C7A8_33C0_4110_8554_89233123E03F__INCLUDED_)
