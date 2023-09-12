
// Project_The_Maze_2022202067Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project_The_Maze_2022202067.h"
#include "Project_The_Maze_2022202067Dlg.h"
#include "afxdialogex.h"
#include <random>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CProjectTheMaze2022202067Dlg 대화 상자



CProjectTheMaze2022202067Dlg::CProjectTheMaze2022202067Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_THE_MAZE_2022202067_DIALOG, pParent)
	, m_row_value(0)
	, m_col_value(0)
	, m_animate_generate(FALSE)
	, m_radio_dfs(FALSE)
	, m_animate_solve(FALSE)
	, m_map(0)
	, m_map_copy(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectTheMaze2022202067Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CANVAS, m_static_canvas_control);
	DDX_Text(pDX, IDC_EDIT_ROW, m_row_value);
	DDX_Text(pDX, IDC_EDIT_COL, m_col_value);
	DDX_Check(pDX, IDC_CHECK_GEN_ANIMATE, m_animate_generate);
	DDX_Radio(pDX, IDC_RADIO_DFS, m_radio_dfs);
	DDX_Check(pDX, IDC_CHECK_SOLVE_ANIMATE, m_animate_solve);
	DDX_Control(pDX, IDC_BUTTON3, m_button_exit);
}

BEGIN_MESSAGE_MAP(CProjectTheMaze2022202067Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProjectTheMaze2022202067Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CProjectTheMaze2022202067Dlg::OnBnClickedButton2)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_BUTTON3, &CProjectTheMaze2022202067Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CProjectTheMaze2022202067Dlg 메시지 처리기

BOOL CProjectTheMaze2022202067Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	srand((unsigned int)time(NULL));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProjectTheMaze2022202067Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CProjectTheMaze2022202067Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CProjectTheMaze2022202067Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Generate 버튼 클릭 시 실행
void CProjectTheMaze2022202067Dlg::OnBnClickedButton1()
{
	//사용자가 입력한 행,열 값 업데이트
	UpdateData(TRUE);

	//출발점, 도착점 초기화
	m_static_canvas_control.m_red_dot_x = -1;
	m_static_canvas_control.m_red_dot_y = -1;
	m_static_canvas_control.m_blue_dot_x = -1;
	m_static_canvas_control.m_blue_dot_y = -1;

	//미로 관련 이차원 배열 메모리 존재시 해제 후 재할당
	if (m_map) {
		delete[] m_map[0];
		delete[] m_map;
		m_map = 0;
	}
	if (m_visited) {
		delete[] m_visited[0];
		delete[] m_visited;
		m_visited = 0;
	}
	m_map = new char* [2 * m_row_value + 1];
	m_visited = new bool* [m_row_value];
	m_map[0] = new char[(2 * m_col_value + 1) * (2 * m_row_value + 1)];
	m_visited[0] = new bool[m_row_value * m_col_value];

	for (int i = 1; i < m_row_value; i++) {
		m_visited[i] = m_visited[i - 1] + m_col_value;
	}
	for (int i = 1; i < 2 * m_row_value + 1; i++) {
		m_map[i] = m_map[i - 1] + (2 * m_col_value + 1);
	}

	//미로 관련 이차원 배열 초기화
	memset(m_map[0], '#', (2 * m_col_value + 1) * (2 * m_row_value + 1));
	memset(m_visited[0], false, m_row_value * m_col_value);

	//미로 생성 시작점 rand함수로 무작위 선택
	int randn = rand() % m_row_value;
	int randm = rand() % m_col_value;

	//미로 생성 함수 실행
	MakeMaze(randn, randm, 0);
	
	//여러 번 풀이가 가능하게 만들기 위한 미로 복사본 이차원 배열 재할당, 복사
	if (m_map_copy) {
		delete[] m_map_copy[0];
		delete[] m_map_copy;
		m_map_copy = 0;
	}
	m_map_copy = new char* [2 * m_row_value + 1];
	m_map_copy[0] = new char[(2 * m_col_value + 1) * (2 * m_row_value + 1)];
	for (int i = 1; i < 2 * m_row_value + 1; i++) {
		m_map_copy[i] = m_map_copy[i - 1] + (2 * m_col_value + 1);
	}
	memcpy(m_map_copy[0], m_map[0], (2 * m_col_value + 1) * (2 * m_row_value + 1));

	//캔버스 컨트롤의 미로 그리기 함수 실행
	m_static_canvas_control.DrawMaze(m_row_value, m_col_value,m_map);
}

//DFS기반 미로 생성 함수
void CProjectTheMaze2022202067Dlg::MakeMaze(int n, int m, int p_dir)
{
	//중복 탐색 방지를 위한 방문 여부 확인 이차원배열, 현재 좌표 방문 표시
	m_visited[n][m] = true;

	//미로 이차원 배열의 현재 좌표에 공백을 저장하여 길 표시
	m_map[2 * n + 1][2 * m + 1] = ' ';

	//애니메이션 활성화 시에만 현재까지의 미로 그리기, 20ms 지연
	if (m_animate_generate) {
		m_static_canvas_control.DrawMaze(m_row_value, m_col_value, m_map);
		Sleep(50);
	}

	//현재 좌표에서 진행 가능한 방향이 있는지 표시하는 flag
	bool flag = 1;

	//현재 좌표에서 진행 가능한 방향이 없어질 때까지 반복
	while (flag) {
		//일단 진행 불가능 표시
		flag = 0;

		//네 방향(위쪽부터 시계방향) 진행 가능 여부 확인
		for (int i = 0; i < 4; i++) {
			int n_n = n + dn[i];
			int n_m = m + dm[i];
			if (0 <= n_n && n_n < m_row_value && 0 <= n_m && n_m < m_col_value) {
				//다음 좌표에 방문하지 않았으면 flag = 1
				if (!m_visited[n + dn[i]][m + dm[i]]) {
					flag = 1;
				}
			}
		}

		//탐색 방향 변수, 현재 보고있는 방향에서 좌회전, 직진, 우회전 지정
		int dir;

		//rand함수로 방향 랜덤 지정
		dir = (rand() % 3) - 1;

		//이전 방향을 더하여 현재 진행 방향 설정
		dir += p_dir;

		//방향이 범위를 벗어나는것을 방지
		if (dir > 3)
			dir -= 4;
		if (dir < 0)
			dir += 4;

		//해당 방향의 다음 좌표가 방문 가능할 때 다음 좌표로 가능 통로 좌표에 공백 저장, 재귀함수로 다음 좌표에서 재탐색
		if (0 <= n + dn[dir] && n + dn[dir] < m_row_value && 0 <= m + dm[dir] && m + dm[dir] < m_col_value) {
			if (!m_visited[n + dn[dir]][m + dm[dir]]) {
				m_map[2 * n + 1 + dn[dir]][2 * m + 1+dm[dir]] = ' ';
				MakeMaze(n + dn[dir], m + dm[dir], dir);
			}
		}
	}
}

//미로풀이(BFS)
void CProjectTheMaze2022202067Dlg::SolvingBFS()
{
	Queue* del;
	Queue* ptr = new Queue;
	Queue* tail, * head;
	tail = head = ptr;

	//출발점을 큐에 저장
	ptr->xpos = m_static_canvas_control.m_red_dot_x;
	ptr->ypos = m_static_canvas_control.m_red_dot_y;
	ptr->next = NULL;

	//큐가 빌 때까지 반복
	while (head) {

		//큐에서 좌표 불러오기
		int q_x = head->xpos;
		int q_y = head->ypos;

		//현재 좌표에 *을 저장하여 탐색한 좌표임을 표시
		m_map[2 * q_y + 1][2 * q_x + 1] = '*';

		//Solve 애니메이션 활성화 시 미로 그리기
		if (m_animate_solve) {
			m_static_canvas_control.DrawMaze(m_row_value,m_col_value,m_map);
			Sleep(50);
		}

		//현재 좌표가 도착점이면 함수 종료
		if (q_x == m_static_canvas_control.m_blue_dot_x && q_y == m_static_canvas_control.m_blue_dot_y) {
			return;
		}
		del = head;
		head = head->next;
		delete del;

		//네 방향(위쪽부터 시계방향)탐색
		for (int i = 0; i < 4; i++) {
			int n_x = q_x + dm[i];
			int n_y = q_y + dn[i];

			//다음 좌표가 공백(길)일 때 다음 좌표를 큐에 저장, 다음 좌표로 가는 통로에 * 저장
			if (0 <= n_x && n_x < m_col_value && 0 <= n_y && n_y < m_row_value) {
				if (m_map[2 * q_y + 1 + dn[i]][2 * q_x + 1 + dm[i]] == ' ') {
					ptr = new Queue;
					ptr->xpos = n_x;
					ptr->ypos = n_y;
					ptr->next = 0;
					if (head) {
						tail->next = ptr;
						tail = ptr;
					}
					else {
						head = tail = ptr;
					}

					m_map[2 * q_y + 1 + dn[i]][2 * q_x + 1 + dm[i]] = '*';
				}
			}
		}
	}
}

//미로풀이(DFS) 겸 최단경로
int CProjectTheMaze2022202067Dlg::SolvingDFS(int px, int py)
{
	//현재 좌표가 도착점이면 현재 좌표에 +를 저장하여 최단경로임을 표시, 1 반환
	if (px == 2* m_static_canvas_control.m_blue_dot_x+1 && py == 2* m_static_canvas_control.m_blue_dot_y+1) {
		m_map[py][px] = '+';
		return 1;
	}

	//현재 좌표를 탐색했다는 표시로 * 저장
	m_map[py][px] = '*';

	//애니메이션
	if (m_animate_solve) {
		m_static_canvas_control.DrawMaze(m_row_value, m_col_value, m_map);
		Sleep(50);
	}

	//네 방향 탐색
	for (int i = 0; i < 4; i++) {
		int n_x = px + dm[i];
		int n_y = py + dn[i];

		//다음 좌표가 공백(길)일 때 해당 통로에 * 저장
		if (0 <= n_x && n_x < 2 * m_col_value + 1 && 0 <= n_y && n_y < 2 * m_row_value + 1) {
			if (m_map[n_y][n_x] == ' ') {
				m_map[n_y][n_x] = '*';

				//if문의 조건에 재귀함수를 넣어 1이 반환 될 때 똑같이 1을 반환하도록 구현 -> 최단경로일 때만 실행됨
				if (SolvingDFS(n_x + dm[i], n_y + dn[i])) {

					//최단경로에 + 저장
					m_map[py][px] = '+';
					m_map[n_y][n_x] = '+';
					return 1;
				}
			}
		}
	}
	return 0;
}

//최단경로 탐색(DFS)
int CProjectTheMaze2022202067Dlg::WayToDest(int px, int py)
{
	//현재 좌표 
	m_visited[(py - 1) / 2][(px - 1) / 2] = true;
	if (px == 2*m_static_canvas_control.m_blue_dot_x+1 && py == 2* m_static_canvas_control.m_blue_dot_y+1) {
		m_map[py][px] = '+';
		return 1;
	}

	//네 방향 탐색
	for (int i = 0; i < 4; i++) {
		int n_x = px + dm[i];
		int n_y = py + dn[i];
		if (0 <= n_x && n_x < 2 * m_col_value + 1 && 0 <= n_y && n_y < 2 * m_row_value + 1) {

			//다음 좌표가 BFS풀이로 탐색한 경로이면서 최단경로 탐색에서 방문하지 않은 좌표일 때
			if ((m_map[n_y][n_x] == '*') && !m_visited[(py - 1) / 2 + dn[i]][(px - 1) / 2 + dm[i]]) {

				//if문의 조건에 재귀함수를 넣어 1이 반환 될 때 똑같이 1을 반환하도록 구현 -> 최단경로일 때만 실행됨
				if (WayToDest(n_x + dm[i], n_y + dn[i])) {
					m_map[py][px] = '+';
					m_map[n_y][n_x] = '+';
					return 1;
				}
			}
		}
	}
	return 0;
}

//Solve 버튼 클릭 시 실행
void CProjectTheMaze2022202067Dlg::OnBnClickedButton2()
{
	//사용자 입력 데이터 업데이트
	UpdateData(TRUE);

	//탐색되지않은 미로 배열(복사한 미로)을 원래 미로에 복사
	if (m_map) {
		memcpy(m_map[0], m_map_copy[0], (2 * m_col_value + 1) * (2 * m_row_value + 1));
	}

	//캔버스 객체의 출발점, 도착점 변수 초기화
	m_red_dot_x = m_static_canvas_control.m_red_dot_x;
	m_red_dot_y = m_static_canvas_control.m_red_dot_y;
	m_blue_dot_x = m_static_canvas_control.m_blue_dot_x;
	m_blue_dot_y = m_static_canvas_control.m_blue_dot_y;

	//출발점과 도착점이 설정되어 있을 때만 풀이
	if (m_red_dot_x >= 0 && m_blue_dot_x >= 0 && m_map) {

		//DFS 라디오버튼 활성화 시 DFS로 풀이
		if (!m_radio_dfs)
			SolvingDFS(2 * m_red_dot_x + 1, 2 * m_red_dot_y + 1);

		else {	//BFS로 풀이, 최단경로는 최단경로 함수를 사용하여 따로 표시
			SolvingBFS();
			memset(m_visited[0], 0, m_col_value * m_row_value);
			WayToDest(2 * m_red_dot_x + 1, 2 * m_red_dot_y + 1);
		}

		//미로 그리기
		m_static_canvas_control.DrawMaze(m_row_value, m_col_value, m_map);
	}
}

//마우스 움직일 때마다 실행 ( 마우스 호버링 )
void CProjectTheMaze2022202067Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//미로가 생성되어 있고, 마우스가 미로 위에 위치할 때만 실행
	if (m_map) {
		if (m_static_canvas_control.y_start + 12 <= point.y && point.y < m_static_canvas_control.y_start + m_static_canvas_control.m_maze_height + 12
			&& m_static_canvas_control.x_start + 175 <= point.x && point.x < m_static_canvas_control.x_start + m_static_canvas_control.m_maze_width + 175) {

			//현재 마우스의 좌표를 미로의 방 위치로 변환
			int i = ((point.y - 12 - m_static_canvas_control.y_start) / m_static_canvas_control.m_unit_size);
			int j = ((point.x - 175 - m_static_canvas_control.x_start) / m_static_canvas_control.m_unit_size);

			//캔버스 컨트롤의 PaintYellow함수를 사용하여 i행 j열 위치에 노란 배경 그리기, 이전 위치는 원래대로 복구
			m_static_canvas_control.PaintYellow(i, j, m_prev_i, m_prev_j ,m_map);

			//이전 위치를 현재 위치로 저장
			m_prev_i = i;
			m_prev_j = j;
		}

		//마우스가 미로를 벗어날 때 원상태로 복구하기 위한 조건( 미로보다 살짝 큰 범위 )
		else if (m_static_canvas_control.y_start + 2 <= point.y && point.y < m_static_canvas_control.y_start + m_static_canvas_control.m_maze_height + 22
			&& m_static_canvas_control.x_start + 165 <= point.x && point.x < m_static_canvas_control.x_start + m_static_canvas_control.m_maze_width + 185)
			//미로 그리기
			m_static_canvas_control.DrawMaze(m_row_value, m_col_value, m_map);
	}
		CDialogEx::OnMouseMove(nFlags, point);
}

//마우스 왼쪽 클릭 시 실행
void CProjectTheMaze2022202067Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//마우스 클릭 위치가 미로 내부일 때
	if (m_static_canvas_control.y_start + 12 <= point.y && point.y < m_static_canvas_control.y_start + m_static_canvas_control.m_maze_height + 12 &&
		m_static_canvas_control.x_start + 175 <= point.x && point.x < m_static_canvas_control.x_start + m_static_canvas_control.m_maze_width + 175) {
		
		//출발점 재설정 시 탐색한 미로 초기화
		memcpy(m_map[0], m_map_copy[0], (2 * m_col_value + 1) * (2 * m_row_value + 1));
		
		//마우스 클릭 좌표를 미로 내부의 위치로 변환, 출발점으로 저장
		m_static_canvas_control.m_red_dot_y = ((point.y - 12 - m_static_canvas_control.y_start) / m_static_canvas_control.m_unit_size);
		m_static_canvas_control.m_red_dot_x = ((point.x - 175 - m_static_canvas_control.x_start) / m_static_canvas_control.m_unit_size);

		//미로 그리기
		m_static_canvas_control.DrawMaze(m_row_value,m_col_value,m_map);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

//마우스 오른쪽 클릭 시 실행
void CProjectTheMaze2022202067Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	//마우스 클릭 위치가 미로 내부일 때
	if (m_static_canvas_control.y_start + 12 <= point.y && point.y < m_static_canvas_control.y_start + m_static_canvas_control.m_maze_height + 12 &&
		m_static_canvas_control.x_start + 175 <= point.x && point.x < m_static_canvas_control.x_start + m_static_canvas_control.m_maze_width + 175) {
		
		//도착점 재설정 시 탐색한 미로 초기화
		memcpy(m_map[0], m_map_copy[0], (2 * m_col_value + 1) * (2 * m_row_value + 1));
		
		//마우스 클릭 좌표를 미로 내부의 위치로 변환, 도착점으로 저장
		m_static_canvas_control.m_blue_dot_y = ((point.y - 12 - m_static_canvas_control.y_start) / m_static_canvas_control.m_unit_size);
		m_static_canvas_control.m_blue_dot_x = ((point.x - 175 - m_static_canvas_control.x_start) / m_static_canvas_control.m_unit_size);

		//미로 그리기
		m_static_canvas_control.DrawMaze(m_row_value, m_col_value, m_map);
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

//창 크기 변환 시 실행
void CProjectTheMaze2022202067Dlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	//캔버스 크기 조정
	m_static_canvas_control.MoveWindow(175, 12, (pRect->right - pRect->left - 199), (pRect->bottom - pRect->top - 60));

	//exit버튼 위치 조정
	m_button_exit.MoveWindow(33, pRect->bottom - pRect->top -90, 108, 24);

	//미로 존재 시 미로 다시 그리기
	if (m_map) {

		m_static_canvas_control.DrawMaze(m_row_value, m_col_value, m_map);
	}
}

//exit버튼 클릭 시 실행
void CProjectTheMaze2022202067Dlg::OnBnClickedButton3()
{

	//동적 할당 메모리 할당 해제
	if (m_map) {
		delete[] m_map[0];
		delete[] m_map;
		m_map = 0;
	}
	if (m_map_copy) {
		delete[] m_map_copy[0];
		delete[] m_map_copy;
		m_map_copy = 0;
	}
	if (m_visited) {
		delete[] m_visited[0];
		delete[] m_visited;
		m_visited = 0;
	}

	//종료 메시지 전송
	SendMessage(WM_CLOSE, 0, 0);
	
}