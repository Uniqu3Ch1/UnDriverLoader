﻿
// UnDriverLoaderDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "UnDriverLoader.h"
#include "UnDriverLoaderDlg.h"
#include "afxdialogex.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnDriverLoaderDlg 对话框



CUnDriverLoaderDlg::CUnDriverLoaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNDRIVERLOADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DriverHelp = DriverHelp();
}

void CUnDriverLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUnDriverLoaderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDRegister, &CUnDriverLoaderDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDRun, &CUnDriverLoaderDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDStop, &CUnDriverLoaderDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDUnload, &CUnDriverLoaderDlg::OnBnClickedUnload)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE, &CUnDriverLoaderDlg::OnEnChangeMfceditbrowse)
	ON_WM_DROPFILES()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUnDriverLoaderDlg 消息处理程序

BOOL CUnDriverLoaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUnDriverLoaderDlg::OnPaint()
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
HCURSOR CUnDriverLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUnDriverLoaderDlg::OnBnClickedRegister()
{
	GetDlgItemText(IDC_MFCEDITBROWSE, strDriverPath);
	GetDlgItemText(IDC_ServiceName, strDriverName);
	m_DriverHelp.setName(strDriverName);
	m_DriverHelp.setPath(strDriverPath);
	if (m_DriverHelp.RegisterDriver())
	{
		LogMessage(m_Status::Success, _T("服务注册成功！"));
		return;
	}
	LogMessage(m_Status::Fail, _T("服务注册失败！"));
	
}


void CUnDriverLoaderDlg::OnBnClickedRun()
{
	GetDlgItemText(IDC_MFCEDITBROWSE, strDriverPath);
	GetDlgItemText(IDC_ServiceName, strDriverName);
	m_DriverHelp.setName(strDriverName);
	m_DriverHelp.setPath(strDriverPath);
	if (m_DriverHelp.RunDriver())
	{
		LogMessage(m_Status::Success, _T("服务运行成功！"));
		return;
	}
	LogMessage(m_Status::Fail, _T("服务运行失败！"));
}


void CUnDriverLoaderDlg::OnBnClickedStop()
{
	GetDlgItemText(IDC_MFCEDITBROWSE, strDriverPath);
	GetDlgItemText(IDC_ServiceName, strDriverName);
	m_DriverHelp.setName(strDriverName);
	m_DriverHelp.setPath(strDriverPath);
	if (m_DriverHelp.StopDriver())
	{
		LogMessage(m_Status::Success, _T("服务停止成功！"));
		return;
	}
	LogMessage(m_Status::Fail, _T("服务停止失败！"));
}


void CUnDriverLoaderDlg::OnBnClickedUnload()
{
	GetDlgItemText(IDC_MFCEDITBROWSE, strDriverPath);
	GetDlgItemText(IDC_ServiceName, strDriverName);
	m_DriverHelp.setName(strDriverName);
	m_DriverHelp.setPath(strDriverPath);
	if (m_DriverHelp.UnRegisterDriver())
	{
		LogMessage(m_Status::Success, _T("服务卸载成功！"));
		return;
	}
	LogMessage(m_Status::Fail, _T("服务卸载失败！"));
}







void CUnDriverLoaderDlg::OnEnChangeMfceditbrowse()
{
	CString gap("\\");
	CEdit* name;
	CStringArray items;

	GetDlgItemText(IDC_MFCEDITBROWSE, strDriverPath);
	SplitStr(strDriverPath, gap, items);
	INT_PTR num = items.GetCount();
	strDriverName = items.GetAt(num-1);
	name = (CEdit*)GetDlgItem(IDC_ServiceName);
	name->SetWindowTextW(strDriverName.AllocSysString());
	
}


void CUnDriverLoaderDlg::OnDropFiles(HDROP hDropInfo)
{

	CString gap("\\");
	CStringArray items;
	CEdit* name;
	CMFCEditBrowseCtrl* path;

	wchar_t pFilePath[256] = { 0 };
	DragQueryFile(hDropInfo, 0, pFilePath, 256);
	strDriverPath.Format(_T("%s"), pFilePath);
	SplitStr(strDriverPath, gap, items);
	INT_PTR num = items.GetCount();
	strDriverName = items.GetAt(num - 1);
	path = (CMFCEditBrowseCtrl*)GetDlgItem(IDC_MFCEDITBROWSE);
	name = (CEdit*)GetDlgItem(IDC_ServiceName);
	path->SetWindowTextW(strDriverPath.AllocSysString());
	name->SetWindowTextW(strDriverName.AllocSysString());
	UpdateData(false);
	CDialogEx::OnDropFiles(hDropInfo);
}


void CUnDriverLoaderDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CWnd* pWnd = GetDlgItem(IDC_STATIC);
	if (pWnd->GetSafeHwnd())
	{
		
		pWnd->MoveWindow(15, 15, cx - 30, cy - 30);
	}

	// TODO: 在此处添加消息处理程序代码
}

void CUnDriverLoaderDlg::LogMessage(m_Status status, CString msg) {
	LPVOID lpmsg;
	DWORD err = GetLastError();

	switch (status)
	{
	case CUnDriverLoaderDlg::m_Status::Success:
		MessageBoxW(msg, _T("提示"), MB_OK | MB_ICONINFORMATION);
		break;
	case CUnDriverLoaderDlg::m_Status::Fail:
		
		if (
			FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			err,
			LANG_SYSTEM_DEFAULT,
			(LPTSTR) &lpmsg,
			0,
			NULL) == 0
			)
		{
			MessageBoxW(_T("错误消息解析失败，请重试！"), _T("提示"), MB_OK | MB_ICONINFORMATION);
			break;
		}// msg error

		MessageBoxW(msg + (LPTSTR)lpmsg, _T("提示"), MB_OK | MB_ICONINFORMATION);
		LocalFree(lpmsg);
		break;
	default:
		break;
	}
	return;
}
