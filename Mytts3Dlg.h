
// Mytts3Dlg.h: 头文件
//

#pragma once
#include <locale.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sapi.h>
#include "resource.h"

#define WM_YOU_CAN_PICK (WM_USER + 1)

class CMytts3DlgAutoProxy;



// CMytts3Dlg 对话框
class CMytts3Dlg : public CDialog
{
	DECLARE_DYNAMIC(CMytts3Dlg);
	friend class CMytts3DlgAutoProxy;

// 构造
public:
	CMytts3Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CMytts3Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTTS3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CMytts3DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	CEdit editname;
	afx_msg void OnBnClickedButton2();
	CListBox namelist;

	// for test.
	void ReadStringCharToUnicode(CString& str);
	CString getUtf8File(CString filename);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeEdit2();
	
	//消息响应函数,未完成。
	afx_msg  LRESULT  Youcanpick(WPARAM wParam, LPARAM lParam);

	CEdit show_name;
	ISpVoice* pVoice;


	//这个变量用于 暂停/继续 键
	bool pause;

	//用于中间框的显示
	CFont m_editFont;

	afx_msg void OnBnClickedButton1();

	// 这是抽中名单对应的变量
	CListBox picklist;
	afx_msg void OnLbnSelchangeList4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit3();
	CEdit picktimes;
	
	//bool 简陋线程锁,这里是关于多进程的问题的
	struct pick_struct* ps;
	HANDLE m_hThread;//线程句柄 


	//将抽取对应的函数写到这里来。
	void Do_pick();
};



//这里是为了多线程的准备
struct pick_struct {
	UINT times;
	CMytts3Dlg* dlg;
};

DWORD WINAPI ThreadProc(LPVOID lpParam);