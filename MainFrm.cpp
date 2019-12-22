
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Style.h"

#include "MainFrm.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_TEST, &CMainFrame::OnTest)
	ON_COMMAND(IDM_VIEW_NEWTOOLBAR, &CMainFrame::OnViewNewtoolbar)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_NEWTOOLBAR, &CMainFrame::OnUpdateViewNewtoolbar)

	ON_MESSAGE(UM_PROGRESS,OnProgress)
	ON_WM_PAINT()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	IDS_TIMER,
	IDS_PROGRESS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

extern CStyleApp theApp;
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

	//SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);

	SetClassLong(m_hWnd, GCL_HICON, (LONG)LoadIcon(NULL, IDI_ERROR));


	m_hIcons[0] = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	m_hIcons[1] = LoadIcon(theApp.m_hInstance, MAKEINTRESOURCE(IDI_ICON2));
	m_hIcons[2] = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3));

	SetClassLong(m_hWnd, GCL_HICON, (LONG)m_hIcons[0]);

	SetTimer(1, 1000, NULL);



	if (!m_newToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS  | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || !m_newToolBar.LoadToolBar(IDR_TOOLBAR1)) {
	
		TRACE("fAILED TO CREATE TOOLBAR\n");
		return -1;

	}
	m_newToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_newToolBar);



	//m_progress.Create(WS_CHILD | WS_VISIBLE, CRect(100, 100, 120,200), this, 123);

	//PostMessage(UM_PROGRESS);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式


	//cs.cx = 600;
	//cs.cy = 400;

	//cs.lpszName = L"daidai";
	//cs.style = WS_OVERLAPPEDWINDOW;
	//利用mfc提供的函数来新生成一个窗口类，因为提供了默认参数，所以有些不需要设置的参数可以不设置，比较方便
	//cs.lpszClass = AfxRegisterWndClass( CS_HREDRAW | CS_VREDRAW, 0, 0, LoadIcon(NULL, IDI_WARNING));
	
	
	return TRUE;
} 

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{

	static int index = 0;
	SetClassLong(m_hWnd, GCL_HICON, (LONG)m_hIcons[index]);
	index = ++index % 3;


	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%H:%M:%S");
	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	m_wndStatusBar.SetPaneInfo(1, IDS_TIMER, SBPS_NORMAL, sz.cx);
	m_wndStatusBar.SetPaneText(1, str);


	m_progress.StepIt();
	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnTest()
{

	MessageBox(L"test");

}


void CMainFrame::OnViewNewtoolbar()
{

	//if (m_newToolBar.IsWindowVisible()) {
	//	m_newToolBar.ShowWindow(SW_HIDE);
	//}
	//else {
	//	m_newToolBar.ShowWindow(SW_SHOW);
	//}
	//RecalcLayout();
	//DockControlBar(&m_newToolBar);

	ShowControlBar(&m_newToolBar, !m_newToolBar.IsWindowVisible(), FALSE);
}


void CMainFrame::OnUpdateViewNewtoolbar(CCmdUI* pCmdUI)
{

	pCmdUI->SetCheck(m_newToolBar.IsWindowVisible());

}


LRESULT CMainFrame::OnProgress(WPARAM wParam, LPARAM lParam) {
	return 0;


}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFrameWnd::OnPaint()
	


	CRect rect;
	m_wndStatusBar.GetItemRect(2, &rect);
	if (!m_progress.m_hWnd)
	{
		m_progress.Create(WS_CHILD | WS_VISIBLE, rect, &m_wndStatusBar, 123);

	}
	else
	{
		m_progress.MoveWindow(rect);
	}
	m_progress.SetPos(50);
	  
}
