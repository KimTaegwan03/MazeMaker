#pragma once


// CStaticCanvasControl

class CStaticCanvasControl : public CStatic
{
	DECLARE_DYNAMIC(CStaticCanvasControl)

public:
	CStaticCanvasControl();
	virtual ~CStaticCanvasControl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void DrawMaze(int row, int col, char** map);
	CRect m_rect_window;
	CBrush m_white_brush;
	CPen m_white_pen;
	CPen m_blue_pen;
	CBrush m_blue_brush;
	CPen m_purple_pen;
	CBrush m_purple_brush;
	CPen m_red_pen;
	CBrush m_red_brush;
	CPen m_black_pen;
	CPen m_yellow_pen;
	CBrush m_yellow_brush;

	int x_start;
	int y_start;
	int m_maze_width;
	int m_maze_height;

	int m_base_size;
	int m_unit_size;

	int m_red_dot_x;
	int m_red_dot_y;

	int m_blue_dot_x;
	int m_blue_dot_y;


	void PaintYellow(int i, int j, int prev_i, int prev_j, char** map);

};


