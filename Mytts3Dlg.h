
// Mytts3Dlg.h: 头文件
//

#pragma once

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
};
