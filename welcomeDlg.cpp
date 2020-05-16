// welcomeDlg.cpp: 实现文件
//

#include "pch.h"
#include "Mytts.h"
#include "welcomeDlg.h"
#include "afxdialogex.h"


// welcomeDlg 对话框

IMPLEMENT_DYNAMIC(welcomeDlg, CDialogEx)

welcomeDlg::welcomeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

welcomeDlg::~welcomeDlg()
{
}

void welcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(welcomeDlg, CDialogEx)
END_MESSAGE_MAP()


// welcomeDlg 消息处理程序
