
// DlgProxy.h: 头文件
//

#pragma once

class CMytts3Dlg;


// CMytts3DlgAutoProxy 命令目标

class CMytts3DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMytts3DlgAutoProxy)

	CMytts3DlgAutoProxy();           // 动态创建所使用的受保护的构造函数

// 特性
public:
	CMytts3Dlg* m_pDialog;

// 操作
public:

// 重写
	public:
	virtual void OnFinalRelease();

// 实现
protected:
	virtual ~CMytts3DlgAutoProxy();

	// 生成的消息映射函数

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMytts3DlgAutoProxy)

	// 生成的 OLE 调度映射函数

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

