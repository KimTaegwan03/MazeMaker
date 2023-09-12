
// Project_The_Maze_2022202067Dlg.h: 헤더 파일
//

#pragma once
#include "CStaticCanvasControl.h"

// CProjectTheMaze2022202067Dlg 대화 상자
class CProjectTheMaze2022202067Dlg : public CDialogEx
{
// 생성입니다.
public:
	CProjectTheMaze2022202067Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_THE_MAZE_2022202067_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStaticCanvasControl m_static_canvas_control;
	int m_row_value;
	int m_col_value;
	BOOL m_animate_generate;
	BOOL m_radio_dfs;
	BOOL m_animate_solve;
	afx_msg void OnBnClickedButton1();
	void MakeMaze(int n, int m, int p_dir);
	int SolvingDFS(int px, int py);
	int WayToDest(int px, int py);
	void SolvingBFS();

	int m_prev_i;
	int m_prev_j;

private:
	char** m_map;
	char** m_map_copy;
	bool** m_visited;
	int dm[4] = { 0,1,0,-1 };  //위 오 아 왼
	int dn[4] = { -1,0,1,0 };

	int m_red_dot_x;
	int m_red_dot_y;

	int m_blue_dot_x;
	int m_blue_dot_y;

	typedef struct Queue {
		int xpos;
		int ypos;
		Queue* next;
	}Queue;

public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	CButton m_button_exit;
	afx_msg void OnBnClickedButton3();
};
