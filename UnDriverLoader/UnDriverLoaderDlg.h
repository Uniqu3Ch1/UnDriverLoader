
// UnDriverLoaderDlg.h: 头文件
//

#pragma once


// CUnDriverLoaderDlg 对话框
class CUnDriverLoaderDlg : public CDialogEx
{
// 构造
public:
	CUnDriverLoaderDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNDRIVERLOADER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	CString strDriverPath;
	CString strDriverName;
	DriverHelp m_DriverHelp;
	CMFCEditBrowseCtrl m_EditBrowse;
	enum class m_Status{ Success, Fail };
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void LogMessage(m_Status status, CString msg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegister();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedUnload();
	afx_msg void OnEnChangeMfceditbrowse();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
