
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
using namespace std;


// CMytts3Dlg 对话框


IMPLEMENT_DYNAMIC(CMytts3Dlg, CDialog);

CMytts3Dlg::CMytts3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MYTTS3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
	
	//初始状态的语言不是暂停的，所以是false
	pause = false;


	//初始化TTS
	if (FAILED(::CoInitialize(NULL)))
		MessageBox(_T("语音初始化失败，请重新启动或检查配置。"), _T("WARNING FROM wxy"), 0);
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (!SUCCEEDED(hr))
		return;

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
	DDX_Control(pDX, IDC_EDIT2, show_name);
	DDX_Control(pDX, IDC_LIST4, picklist);
	DDX_Control(pDX, IDC_EDIT3, picktimes);
	DDX_Control(pDX, IDC_SLIDER1, slider_volume);
	DDX_Control(pDX, IDC_SLIDER2, slider_speed);
}

BEGIN_MESSAGE_MAP(CMytts3Dlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMytts3Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMytts3Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMytts3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CMytts3Dlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMytts3Dlg::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT2, &CMytts3Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMytts3Dlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST4, &CMytts3Dlg::OnLbnSelchangeList4)
	ON_MESSAGE(WM_YOU_CAN_PICK, &CMytts3Dlg::Youcanpick)
	ON_BN_CLICKED(IDC_BUTTON5, &CMytts3Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT3, &CMytts3Dlg::OnEnChangeEdit3)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CMytts3Dlg::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CMytts3Dlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMytts3Dlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMytts3Dlg::OnBnClickedButton4)
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

	m_editFont.CreatePointFont(240, L"宋体");
	show_name.SetFont(&m_editFont);

	slider_volume.SetRange(0, 100);
	slider_speed.SetRange(0, 10);

	CWnd* stop_resume = GetDlgItem(IDC_BUTTON5);
	stop_resume->EnableWindow(false);

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
	::CoUninitialize();
	pVoice = NULL;
	if (CanExit())
		CDialog::OnClose();
}

void CMytts3Dlg::OnOK()
{
	//if (CanExit())
	//	CDialog::OnOK();
	HWND hWnd = ::GetFocus(); 
	int iID = ::GetDlgCtrlID(hWnd);
	if (iID == IDC_EDIT1)
	{
		OnBnClickedButton2();
	}
}

void CMytts3Dlg::OnCancel()
{
	::CoUninitialize();
	pVoice = NULL;
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CMytts3Dlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	
	::CoUninitialize();
	pVoice = NULL;
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
	CFileDialog filewindow(TRUE, _T("文本文件(*.txt)|*.txt||"), NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL, 0, 0, 0);
	
	
	if (IDOK != filewindow.DoModal())
		return;
	// 打开成功！
	MessageBox(_T("you open the file window."), _T("You click this."), MB_OK);
	CString openfilename = filewindow.GetPathName();

	// 帮助用来添加utf-8内容。
	//setlocale(LC_CTYPE, "chs");
	CString tan = getUtf8File(openfilename);
	//namelist.AddString(tan);
	MessageBox(tan, _T("添加成功2！"), MB_OK);
	UpdateWindow();

	//按换行符将CString每段分开。
	while (TRUE)
	{
		int index = tan.Find(_T("\r\n"));
		if (index == -1)
		{
			namelist.AddString(tan);
			break;
		}
		namelist.AddString(tan.Left(index));
		tan = tan.Right(tan.GetLength() - index - 1);
	}
	//这里是失败案例。
	/*
	CStdioFile txtfile;
	txtfile.Open(openfilename, CFile::modeRead);
	CString name_to_add;
	while (txtfile.ReadString(name_to_add)) {
		//ReadStringCharToUnicode(name_to_add);

		namelist.AddString(name_to_add);
		MessageBox(name_to_add, _T("添加成功2！"), MB_OK);
		UpdateWindow();
	}
	*/
}


void CMytts3Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* name;
	name = (CEdit *)GetDlgItem(IDC_EDIT1);
	CString str;
	name->GetWindowText(str);
	if (str.GetLength() != 0) {
		namelist.AddString(str);
		MessageBox(str, _T("添加成功！"), MB_OK);
	}
	name->SetWindowText(L"");
	UpdateWindow();

}



void CMytts3Dlg::ReadStringCharToUnicode(CString& str)
{
	char* szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
	memset(szBuf, '\0', str.GetLength());

	int i;
	for (i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

	int nLen;
	WCHAR* ptch;
	CString strOut;
	if (szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
	ptch = new WCHAR[nLen];
	memset(ptch, '\0', nLen);
	MultiByteToWideChar(CP_ACP, 0, szBuf, -1, ptch, nLen);
	str.Format(_T("%s"), ptch);

	if (NULL != ptch)
		delete[] ptch;
	ptch = NULL;

	if (NULL != szBuf)
		delete[]szBuf;
	szBuf = NULL;
	return;
}


//此处参考 https://blog.csdn.net/beyondlpf/article/details/7161976
CString CMytts3Dlg::getUtf8File(CString filename)
{
	CFile file;
	if (! file.Open(filename, CFile::modeRead | CFile::typeBinary))
		return NULL;

	// 判断有无utf-8标志头。如果有的话就先读掉，没有的话得重新回到起点。
	BYTE head[3];
	file.Read(head, 3);
	if (!(head[0] == 0xEF && head[1] == 0xBB && head[2] == 0xBF))
		file.SeekToBegin();

	//先将文本内容按照字节一个个读进来，然后后面再处理。
	ULONGLONG FileSize = file.GetLength();
	char* pContent = (char*)calloc(FileSize + 1,1);
	file.Read(pContent, FileSize);

	//从多字节转换成宽字节，之前的UTF-8是三个字节，这里变成两个字节。
	int n = MultiByteToWideChar(CP_UTF8, 0, pContent, FileSize + 1, NULL, 0);
	wchar_t* pWideChar = (wchar_t*)calloc(n + 1, sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, pContent, FileSize + 1, pWideChar, n);
	CString strFile = CString(pWideChar);

	//释放空间
	file.Close();
	free(pContent);
	free(pWideChar);

	return strFile;
}

void CMytts3Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	HWND hWnd = ::GetFocus();
	int iID = ::GetDlgCtrlID(hWnd);
	if (iID == IDC_EDIT1)
	{
		CMytts3Dlg::OnOK();
		return;
	}
	char num[20];

	//关闭本按钮
	CWnd* this_wind = GetDlgItem(IDOK);
	this_wind->EnableWindow(false);
	//关闭reset按钮
	CWnd* reset = GetDlgItem(IDC_BUTTON1);
	reset->EnableWindow(false);
	
	UINT x = GetDlgItemInt(IDC_EDIT3, 0, 0);
	if (x == 0)
		x = 1;

	UINT total = namelist.GetCount();
	if (total < x)
		x = total;

	ps = (struct pick_struct*)malloc(sizeof(struct pick_struct));
	ps->dlg = this;
	ps->times = x;
	m_hThread = CreateThread(0, 0, ThreadProc, ps, 0, 0);
	CloseHandle(m_hThread);
	
}


void CMytts3Dlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	namelist.DeleteString(namelist.GetCurSel());
	UpdateWindow();
}


void CMytts3Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

LRESULT CMytts3Dlg::Youcanpick(WPARAM wParam, LPARAM lParam)
{
	Do_pick();
	return LRESULT();
}


void CMytts3Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//这个函数是用来将框全部清空的。

	show_name.SetWindowText(L"");
	picktimes.SetWindowText(L"");
	editname.SetWindowText(L"");
	namelist.ResetContent();
	picklist.ResetContent();
	slider_volume.SetPos(0);
	slider_speed.SetPos(0);
	UpdateWindow();
}


void CMytts3Dlg::OnLbnSelchangeList4()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CMytts3Dlg::OnBnClickedButton5()
{
	//添加一个bool变量，用来控制是暂停还是回复。
	if(pause == false)
		pVoice->Pause();
	else
		pVoice->Resume();
	
	pause ^= true; // 0和1互换。
}


void CMytts3Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码

}


void CMytts3Dlg::Do_pick() {
	/*这个函数里，我们每点击一次，就要将一个Cstring挪到
	我们的中间框里，把它朗读出来。并把它加入右边框。*/

	// 首先获取列表总数。
	long total = namelist.GetCount();
	if (total == 0) {
		MessageBox(_T("名单里没有能抽的了！"), NULL, 0);
		return;
	}

	UINT i;

	// 随机抽取一个CString
	srand(time(NULL));
	i = rand() % total;
	CString get_chouqu;
	namelist.GetText(i, get_chouqu);

	namelist.DeleteString(i);
	//MessageBox(get_chouqu, NULL, 0);

	UpdateWindow();

	//更新中间框内容
	UpdateData(TRUE);
	show_name.Clear();
	show_name.SetSel(0, -1);
	show_name.ReplaceSel(get_chouqu);
	UpdateData(FALSE);

	//朗读名字
	pVoice->Speak(get_chouqu,SPF_ASYNC, NULL);
	pVoice->WaitUntilDone(INFINITY);
	picklist.AddString(get_chouqu);
	UpdateWindow();
}




//这里的s是用来提取我们的参数的，一个是执行次数，一个是窗体对象指针。
DWORD WINAPI ThreadProc(LPVOID lpParam) {
	struct pick_struct* s;
	s = (pick_struct*)lpParam;
	
	int adj = s->dlg->slider_speed.GetPos();

	CWnd* pick = s->dlg->GetDlgItem(IDOK);
	CWnd* reset = s->dlg->GetDlgItem(IDC_BUTTON1);
	CWnd* stop_resume = s->dlg->GetDlgItem(IDC_BUTTON5);

	stop_resume->EnableWindow(true);

	for (unsigned int i = 0; i < (s->times); i++)
	{
		::PostMessage(s->dlg->m_hWnd, WM_YOU_CAN_PICK, 0, 0);
		Sleep(2000-adj*130);
		while (1) {
			if (s->dlg->pause == 1) {
				Sleep(20);
			}
			else {
				break;
			}
		}
	}

	
	pick->EnableWindow(true);
	reset->EnableWindow(true);
	stop_resume->EnableWindow(false);
	
	return 1;
}

void CMytts3Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMytts3Dlg::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	pVoice->SetRate(slider_speed.GetPos()-5);
}


void CMytts3Dlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	pVoice->SetVolume(slider_volume.GetPos());
}

char* CreateUTF8TextInitWithString(CString strValue) {
	char* buffer = NULL;
	int  length;

#ifdef _UNICODE  
	length = WideCharToMultiByte(CP_UTF8, 0, strValue, -1, NULL, 0, NULL, NULL);
#else  
	return NULL;
#endif  
	if (length <= 0)
	{
		return NULL;
	}

	buffer = new char[length];
	if (buffer == NULL)
	{
		return NULL;
	}

	ZeroMemory(buffer, length);

#ifdef _UNICODE  
	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, buffer, length, NULL, NULL);
#else  
	strcpy_s(buffer, length, strValue);
#endif  

	return buffer;
}

void CMytts3Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int len = picklist.GetCount();
	if (len == 0) {
		MessageBox(_T("现在表单是空的，导出不了！"), _T("You used a button."), 0);
		return;
	}


	CFileDialog filewindow(FALSE, _T("文本文件(*.txt)|*.txt||"), L"test.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, 0, 0, 0);

	if (IDOK != filewindow.DoModal())
		return;
	// 打开成功！
	CString filename = filewindow.GetPathName();
	CFile file;
	if (!file.Open(filename, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary))
		return;


	int flag = 0;
	while (picklist.GetCount() > 0) {
		CString get_chouqu;
		picklist.GetText(0, get_chouqu);
		picklist.DeleteString(0);

		UpdateWindow();
		char* input;
		input = CreateUTF8TextInitWithString(get_chouqu);

		UINT len = WideCharToMultiByte(CP_UTF8, 0, get_chouqu, -1, NULL, 0, NULL, NULL);
		if ( flag == 0) {
			if (input[0] == '\n')
			{
				input++;
				len--;
			}
		}
		else if (flag == 1) {
			if (input[0] == '\n')
			{
				file.Write("\r", 1);
			}
			else
				file.Write("\r\n", 2);
		}
		

		//先将文本内容按照字节一个个读进来，然后后面再处理。
		//ULONGLONG FileSize = file.GetLength();
		//char* pContent = (char*)calloc(FileSize + 1, 1);
		file.Write(input, len-1);
		
		flag = 1;
	}
	file.Close();

}


char* CMytts3Dlg::CreateUTF8TextInitWithString(CString strValue)
{
	char* buffer = NULL;
	int  length;

#ifdef _UNICODE  
	length = WideCharToMultiByte(CP_UTF8, 0, strValue, -1, NULL, 0, NULL, NULL);
#else  
	return NULL;
#endif  
	if (length <= 0)
	{
		return NULL;
	}

	buffer = new char[length];
	if (buffer == NULL)
	{
		return NULL;
	}

	ZeroMemory(buffer, length);

#ifdef _UNICODE  
	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, buffer, length, NULL, NULL);
#else  
	strcpy_s(buffer, length, strValue);
#endif  

	return buffer;
}