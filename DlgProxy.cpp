
// DlgProxy.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Mytts3.h"
#include "DlgProxy.h"
#include "Mytts3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMytts3DlgAutoProxy

IMPLEMENT_DYNCREATE(CMytts3DlgAutoProxy, CCmdTarget)

CMytts3DlgAutoProxy::CMytts3DlgAutoProxy()
{
	EnableAutomation();

	// 为使应用程序在自动化对象处于活动状态时一直保持
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMytts3Dlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMytts3Dlg)))
		{
			m_pDialog = reinterpret_cast<CMytts3Dlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMytts3DlgAutoProxy::~CMytts3DlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CMytts3DlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMytts3DlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMytts3DlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMytts3 的支持来支持类型安全绑定
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {0c24bd81-9cdd-4400-9ec1-387069640989}
static const IID IID_IMytts3 =
{0x0c24bd81,0x9cdd,0x4400,{0x9e,0xc1,0x38,0x70,0x69,0x64,0x09,0x89}};

BEGIN_INTERFACE_MAP(CMytts3DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMytts3DlgAutoProxy, IID_IMytts3, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏是在此项目的 pch.h 中定义的
// {ebc507bb-b1c0-40f2-a3fa-1ef070239179}
IMPLEMENT_OLECREATE2(CMytts3DlgAutoProxy, "Mytts3.Application", 0xebc507bb,0xb1c0,0x40f2,0xa3,0xfa,0x1e,0xf0,0x70,0x23,0x91,0x79)


// CMytts3DlgAutoProxy 消息处理程序
