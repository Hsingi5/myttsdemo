
// MyttsDlg.h: 头文件
//

#pragma once

#include "windows.h"
#include <string>
#include <sstream>
// CMyttsDlg 对话框
class CMyttsDlg : public CDialogEx
{
// 构造
public:
	CMyttsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTTS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList1();
	CListBox ShowName;
	CFont    name_size;
	// this  is the progress line
	CProgressCtrl jindu;
};
