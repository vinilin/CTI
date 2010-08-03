#if !defined(AFX_MAINTHREAD_H__EFAE5A24_AD4A_44DD_BDD1_D56AE8A0923B__INCLUDED_)
#define AFX_MAINTHREAD_H__EFAE5A24_AD4A_44DD_BDD1_D56AE8A0923B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// MainThread thread

class MainThread : public CWinThread
{
	DECLARE_DYNCREATE(MainThread)
protected:
	MainThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MainThread();

	// Generated message map functions
	//{{AFX_MSG(MainThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTHREAD_H__EFAE5A24_AD4A_44DD_BDD1_D56AE8A0923B__INCLUDED_)
