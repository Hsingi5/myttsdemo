﻿
// MyttsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Mytts.h"
#include "MyttsDlg.h"
#include "afxdialogex.h"
#include <sapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyttsDlg 对话框



CMyttsDlg::CMyttsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYTTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CMyttsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ShowName);
	DDX_Control(pDX, IDC_PROGRESS1, jindu);
}

BEGIN_MESSAGE_MAP(CMyttsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyttsDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMyttsDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CMyttsDlg 消息处理程序

BOOL CMyttsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	LOGFONT logfont;
	CFont* pfont1 = ShowName.GetFont();
	pfont1->GetLogFont(&logfont);
	logfont.lfHeight = logfont.lfHeight * 3;   //这里可以修改字体的高比例
	logfont.lfWidth = logfont.lfWidth * 3;   //这里可以修改字体的宽比例
	static   CFont   font1;
	font1.CreateFontIndirect(&logfont);
	ShowName.SetFont(&font1);
	font1.Detach();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyttsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyttsDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyttsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyttsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	ISpVoice* pVoice = NULL;
	if (FAILED(::CoInitialize(NULL)))
		ShowName.AddString((CString)("FAIL SPEAK"));
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (!SUCCEEDED(hr))
		return;
	jindu.SetRange(0, 100);
	WCHAR buff[256];

	for (int i = 0; i < 200; i++) {
		jindu.OffsetPos(1);
		UpdateWindow();
		stringstream b;
		b << i;
		string xa;
		b >> xa;
		char * mid = (char *)xa.data();
		swprintf(buff,L"%S",mid);
		ShowName.AddString((CString)xa.c_str());
		UpdateWindow();
		
		ShowName.ResetContent();
		Sleep(50);
	}
	hr = pVoice->Speak(buff, 0, NULL);
	
	// this part is for test...........................................
	
	
	{
		
		pVoice->Release();
		pVoice = NULL;
	}
	::CoUninitialize();
}


void CMyttsDlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}
