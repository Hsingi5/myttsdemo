
// Mytts3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Mytts3.h"
#include "Mytts3Dlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMytts3Dlg 对话框


IMPLEMENT_DYNAMIC(CMytts3Dlg, CDialog);

CMytts3Dlg::CMytts3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MYTTS3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CMytts3Dlg::~CMytts3Dlg()
{
	// 如果该对话框有自动化代理，则
	//  此对话框的返回指针为 null，所以它知道
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CMytts3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editname);
	DDX_Control(pDX, IDC_LIST1, namelist);
}

BEGIN_MESSAGE_MAP(CMytts3Dlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMytts3Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMytts3Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMytts3Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMytts3Dlg 消息处理程序

BOOL CMytts3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMytts3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMytts3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CMytts3Dlg::OnClose()
{
	if (CanExit())
		CDialog::OnClose();
}

void CMytts3Dlg::OnOK()
{
	if (CanExit())
		CDialog::OnOK();
}

void CMytts3Dlg::OnCancel()
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CMytts3Dlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CMytts3Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMytts3Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码



}


void CMytts3Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* name;
	name = (CEdit *)GetDlgItem(IDC_EDIT1);
	CString str;
	name->GetWindowTextW(str);
	if (str.GetLength() != 0) {
		namelist.AddString(str);
		MessageBox(str, _T("添加成功！"), MB_OK);
	}
	name->SetWindowTextW(L"");
	UpdateWindow();

}
