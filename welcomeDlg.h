﻿#pragma once


// welcomeDlg 对话框

class welcomeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(welcomeDlg)

public:
	welcomeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~welcomeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
