
// MFCApplication2Dlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CMFCApplication2Dlg 對話方塊



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, txt);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 訊息處理常式

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include "ftl/ftl.h"

void update_message() {
	MSG message;
	while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&message);
		::DispatchMessage(&message);
	}
}

CString printBufferData(u32 lba, u8* writeBuf, u8* readBuf) {
	
	CString strText;
	strText.AppendFormat("lba = %d\n", lba);
	char buffer[16];
	strText += "\n";

	strText += "writeBuf: ";
	sprintf_s(buffer, sizeof(buffer), "%02X", writeBuf[0]);
	strText += buffer;
	strText += " ";
	strText += "\n";

	strText += "readBuf: ";
	sprintf_s(buffer, sizeof(buffer), "%02X", readBuf[0]);
	strText += buffer;
	strText += " ";
	strText += "\n";

	return strText;
}
bool m_onClose = false;
void CMFCApplication2Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	u8 writeBuf[SECTOR_SIZE];
	u8 readBuf[SECTOR_SIZE];
	CString msg;
	for (u32 lba = 0; lba < (2 * 1024); lba++) {
		update_message();

		if (m_onClose) {
			return;
		}

		u8 len = 1;
		memset(writeBuf, lba, sizeof(u8) * SECTOR_SIZE);

		lbaWrite(lba, len, writeBuf);
		lbaRead(lba, len, readBuf);

		int res = memcmp(writeBuf, readBuf, sizeof(writeBuf));

		if (res != 0) {
			MessageBox("error");
		}

		msg = printBufferData(lba, writeBuf, readBuf) + "\r\n";
		//txt.SetWindowTextA(msg); 
		
		//用 append 的方式，加訊息到 editbox 的尾端
		int nLength = txt.GetWindowTextLength();
		// put the selection at the end of text
		txt.SetSel(nLength, nLength);
		// replace the selection
		txt.ReplaceSel(msg);

		//讓 dialog 可以自由移動
		UpdateWindow();

	
	}
	MessageBox("finish");
}


void CMFCApplication2Dlg::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CDialogEx::OnClose();
	m_onClose = true;
}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}
