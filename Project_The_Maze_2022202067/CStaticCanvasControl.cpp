// CStaticCanvasControl.cpp: 구현 파일
//

#include "pch.h"
#include "Project_The_Maze_2022202067.h"
#include "CStaticCanvasControl.h"


// CStaticCanvasControl

IMPLEMENT_DYNAMIC(CStaticCanvasControl, CStatic)

CStaticCanvasControl::CStaticCanvasControl()
	: m_white_brush(RGB(255, 255, 255))
	, m_black_pen(PS_SOLID, 2, RGB(0, 0, 0))
	, m_white_pen(PS_SOLID, 2, RGB(255, 255, 255))
	, m_purple_pen(PS_SOLID, 2, RGB(102, 102, 255))
	, m_purple_brush(RGB(102, 102, 255))
	, m_blue_pen(PS_SOLID,2,RGB(0,0,255))
	, m_blue_brush(RGB(0,0,255))
	, m_red_pen(PS_SOLID, 2, RGB(255, 0, 0))
	, m_red_brush(RGB(255, 0, 0))
	, m_yellow_pen(PS_SOLID, 2, RGB(255, 255, 102))
	, m_yellow_brush(RGB(255, 255, 102))
	, m_red_dot_x(-1)
	, m_red_dot_y(-1)
	, m_blue_dot_x(-1)
	, m_blue_dot_y(-1)
{

}

CStaticCanvasControl::~CStaticCanvasControl()
{
}


BEGIN_MESSAGE_MAP(CStaticCanvasControl, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CStaticCanvasControl 메시지 처리기




void CStaticCanvasControl::OnPaint()
{
	//흰색으로 채우기
	CPaintDC dc(this);
	GetClientRect(m_rect_window);
	dc.FillRect(&m_rect_window, &m_white_brush);
}

//미로 그리기 함수
void CStaticCanvasControl::DrawMaze(int row, int col, char** map)
{
	//화면 초기화
	Invalidate();

	//객체의 dc객체 생성
	CPaintDC dc(this);

	//더블 버퍼링 구현을 위한 메모리 DC, 기존 dc 복사하여 생성
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	//창 크기 정보를 변수에 저장
	GetClientRect(m_rect_window);

	//메모리 dc에 미로를 그릴 비트맵 객체 생성
	CBitmap bitmap;

	//창 크기만큼 비트맵 생성
	bitmap.CreateCompatibleBitmap(&dc, m_rect_window.Width(), m_rect_window.Height());

	//미로 한칸의 크기 설정
	m_unit_size = min((m_rect_window.Width()-12)/col, (m_rect_window.Height()-12)/row);

	//미로 전체 크기 저장
	m_maze_height = m_unit_size * row;
	m_maze_width = m_unit_size * col;

	//캔버스 상에서 미로 그림의 시작 위치
	x_start = (m_rect_window.Width() - m_maze_width) / 2;
	y_start = (m_rect_window.Height() - m_maze_height) / 2;

	//메모리dc로 비트맵 선택
	memDC.SelectObject(&bitmap);
	
	//메모리dc에 흰색 채우기
	memDC.FillRect(&m_rect_window, &m_white_brush);
	
	//미로 배열 전체를 탐색하며 미로 그리기
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			//기본 설정
			memDC.SelectObject(&m_black_pen);
			memDC.SelectObject(&m_white_brush);

			//탐색한 경로이면 보라색 브러쉬
			if (map[2 * i + 1][2 * j + 1] == '*'||map[2 * i + 1][2 * j + 1] == '+')
				memDC.SelectObject(&m_purple_brush);

			//검은 테두리, 흰 배경 or 보라 배경 사각형 그리기
			memDC.Rectangle(x_start + j * m_unit_size, y_start + i * m_unit_size, x_start + (j + 1) * m_unit_size, y_start + (i + 1) * m_unit_size);
			
			//위쪽이 뚫린 경우
			if (map[2 * i][2 * j + 1] != '#') {
				if (map[2 * i + 1][2 * j + 1] == '*' || map[2 * i + 1][2 * j + 1] == '+') {		//해당 좌표가 탐색된 곳인 경우 보라색으로 위쪽 벽 덧칠
					memDC.SelectObject(&m_purple_pen);
					memDC.Rectangle(x_start + j * m_unit_size + 2, y_start + i * m_unit_size, x_start + (j + 1) * m_unit_size - 2, y_start + i * m_unit_size + 2);

					if (map[2 * i + 1][2 * j + 1] == '+' && map[2 * i][2 * j + 1] == '+') {		//최단경로가 위쪽인 경우 빨간색 선을 그림
						memDC.SelectObject(&m_red_brush);
						memDC.SelectObject(&m_red_pen);
						memDC.Rectangle(x_start + j * m_unit_size + (m_unit_size / 2) - 2, y_start + i * m_unit_size, x_start + j * m_unit_size + (m_unit_size / 2) + 2, y_start + i * m_unit_size + (m_unit_size / 2) + 2);
					}
				}
				else if (map[2 * i + 1][2 * j + 1] == ' ') {	//그 외 흰색으로 위쪽 벽 덧칠
					memDC.SelectObject(&m_white_pen);
					memDC.Rectangle(x_start + j * m_unit_size + 2, y_start + i * m_unit_size, x_start + (j + 1) * m_unit_size - 2, y_start + i * m_unit_size + 2);
				}
				
			}

			//아래쪽이 뚫린 경우
			if (map[2 * i + 2][2 * j + 1] != '#') {
				if (map[2 * i + 1][2 * j + 1] == '*' || map[2 * i + 1][2 * j + 1] == '+') {		//해당 좌표가 탐색된 곳인 경우 보라색으로 아래쪽 벽 덧칠
					memDC.SelectObject(&m_purple_pen);
					memDC.Rectangle(x_start + j * m_unit_size + 2, y_start + (i + 1) * m_unit_size - 2, x_start + (j + 1) * m_unit_size - 2, y_start + (i + 1) * m_unit_size);
					
					if (map[2 * i + 1][2 * j + 1] == '+' && map[2 * i + 2][2 * j + 1] == '+') {		//최단경로가 아래쪽인 경우 빨간색 선을 그림
						memDC.SelectObject(&m_red_brush);
						memDC.SelectObject(&m_red_pen);
						memDC.Rectangle(x_start + j * m_unit_size + (m_unit_size / 2) - 2, y_start + i * m_unit_size + (m_unit_size / 2) - 2, x_start + j * m_unit_size + (m_unit_size / 2) + 2, y_start + (i + 1) * m_unit_size);
					}
				}
				else if (map[2 * i + 1][2 * j + 1] == ' ') {	//그 외 흰색으로 아래쪽 벽 덧칠
					memDC.SelectObject(&m_white_pen);
					memDC.Rectangle(x_start + j * m_unit_size + 2, y_start + (i + 1) * m_unit_size - 2, x_start + (j + 1) * m_unit_size - 2, y_start + (i + 1) * m_unit_size);
				}
				
			}

			//왼쪽이 뚫린 경우
			if (map[2 * i + 1][2 * j] != '#') {
				if (map[2 * i + 1][2 * j + 1] == '*' || map[2 * i + 1][2 * j + 1] == '+') {		//해당 좌표가 탐색된 곳인 경우 보라색으로 왼쪽 벽 덧칠
					memDC.SelectObject(&m_purple_pen);
					memDC.Rectangle(x_start + j * m_unit_size, y_start + i * m_unit_size + 2, x_start + j * m_unit_size + 2, y_start + (i + 1) * m_unit_size - 2);
					
					if (map[2 * i + 1][2 * j + 1] == '+' && map[2 * i + 1][2 * j] == '+') {		//최단경로가 왼쪽인 경우 빨간색 선을 그림
						memDC.SelectObject(&m_red_brush);
						memDC.SelectObject(&m_red_pen);
						memDC.Rectangle(x_start + j * m_unit_size, y_start + i * m_unit_size + (m_unit_size / 2) - 2, x_start + j * m_unit_size + (m_unit_size / 2) + 2, y_start + i * m_unit_size + (m_unit_size / 2) + 2);
					}
				}
				else if (map[2 * i + 1][2 * j + 1] == ' ') {	//그 외 흰색으로 왼쪽 벽 덧칠
					memDC.SelectObject(&m_white_pen);
					memDC.Rectangle(x_start + j * m_unit_size, y_start + i * m_unit_size + 2, x_start + j * m_unit_size + 2, y_start + (i + 1) * m_unit_size - 2);
				}
				
			}

			//오른쪽이 뚫린 경우
			if (map[2 * i + 1][2 * j + 2] != '#') {
				if (map[2 * i + 1][2 * j + 1] == '*'|| map[2 * i + 1][2 * j + 1] == '+') {		//해당 좌표가 탐색된 곳인 경우 보라색으로 오른쪽 벽 덧칠
					memDC.SelectObject(&m_purple_pen);
					memDC.Rectangle(x_start + (j + 1) * m_unit_size - 2, y_start + i * m_unit_size + 2, x_start + (j + 1) * m_unit_size, y_start + (i + 1) * m_unit_size - 2);
					
					if (map[2 * i + 1][2 * j + 1] == '+' && map[2 * i + 1][2 * j + 2] == '+') {		//최단경로가 오른쪽인 경우 빨간색 선을 그림
						memDC.SelectObject(&m_red_brush);
						memDC.SelectObject(&m_red_pen);
						memDC.Rectangle(x_start + j * m_unit_size + (m_unit_size / 2) - 2, y_start + i * m_unit_size + (m_unit_size / 2) - 2, x_start + (j + 1) * m_unit_size, y_start + i * m_unit_size + (m_unit_size / 2) + 2);
					}
				}
				else if (map[2 * i + 1][2 * j + 1] == ' ') {	//그 외 흰색으로 오른쪽 벽 덧칠
					memDC.SelectObject(&m_white_pen);
					memDC.Rectangle(x_start + (j + 1) * m_unit_size - 2, y_start + i * m_unit_size + 2, x_start + (j + 1) * m_unit_size, y_start + (i + 1) * m_unit_size - 2);
				}
				
			}

			//출발점인 경우 빨간 점 그리기
			if (i == m_red_dot_y && j == m_red_dot_x) {
				memDC.SelectObject(&m_red_pen);
				memDC.SelectObject(&m_red_brush);
				memDC.Ellipse(x_start + j * m_unit_size + 2, y_start + i * m_unit_size + 2, x_start + (j + 1) * m_unit_size - 2, y_start + (i + 1) * m_unit_size - 2);

			}

			//도착점인 경우 파란 점 그리기
			if (i == m_blue_dot_y && j == m_blue_dot_x) {
				memDC.SelectObject(&m_blue_pen);
				memDC.SelectObject(&m_blue_brush);
				memDC.Ellipse(x_start + j * m_unit_size + 2, y_start + i * m_unit_size + 2, x_start + (j + 1) * m_unit_size - 2, y_start + (i + 1) * m_unit_size - 2);

			}
		}
	}

	//메모리dc의 비트맵을 캔버스 컨트롤 dc에 복사
	dc.BitBlt(0, 0, m_rect_window.Width(), m_rect_window.Height(), &memDC, 0, 0, SRCCOPY);

	//비트맵 객체 삭제
	bitmap.DeleteObject();

	//dc해제
	ReleaseDC(&dc);
	ReleaseDC(&memDC);

	//창 업데이트
	UpdateWindow();
}

//마우스 호버링 시 배경 색이 바뀌는 것을 구현한 함수
void CStaticCanvasControl::PaintYellow(int i, int j,int prev_i,int prev_j, char** map)
{
	//화면 초기화
	Invalidate();

	//객체의 dc객체 생성
	CPaintDC dc(this);

	//더블 버퍼링 구현을 위한 메모리 DC, 기존 dc 복사하여 생성
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	//메모리dc 펜,브러쉬 설정
	memDC.SelectObject(&m_black_pen);
	memDC.SelectObject(&m_white_brush);

	//메모리 dc에 미로르 그릴 비트맵 객체 생성
	CBitmap bitmap;

	//창 크기만큼 비트맵 생성
	bitmap.CreateCompatibleBitmap(&dc, x_start + m_maze_width, y_start + m_maze_height);

	//메모리dc로 비트맵 선택
	memDC.SelectObject(&bitmap);

	//-----이전 위치 복구 알고리즘 구간 시작-----

	//기존 미로 그림 복사
	memDC.BitBlt(0, 0, x_start + m_maze_width, y_start + m_maze_height, &dc, 0, 0, SRCCOPY);

	//탐색한 위치일 때 보라색 브러쉬, 그 외 기본 흰색 브러쉬
	if (map[2 * prev_i + 1][2 * prev_j + 1] == '*' || map[2 * prev_i + 1][2 * prev_j + 1] == '+')
		memDC.SelectObject(&m_purple_brush);

	//이전 위치에 흰색(보라색)배경의 사각형 그리기
	memDC.Rectangle(x_start + prev_j * m_unit_size, y_start + prev_i * m_unit_size, x_start + (prev_j + 1) * m_unit_size, y_start + (prev_i + 1) * m_unit_size);

	//이하 네 방향과 출발점 도착점의 과정은 위 DrawMaze의 함수와 동일
	if (map[2 * prev_i][2 * prev_j + 1] != '#') {
		if (map[2 * prev_i + 1][2 * prev_j + 1] == '*' || map[2 * prev_i + 1][2 * prev_j + 1] == '+') {
			memDC.SelectObject(&m_purple_pen);
			memDC.Rectangle(x_start + prev_j * m_unit_size + 2, y_start + prev_i * m_unit_size, x_start + (prev_j + 1) * m_unit_size - 2, y_start + prev_i * m_unit_size + 2);
			if (map[2 * prev_i + 1][2 * prev_j + 1] == '+' && map[2 * prev_i][2 * prev_j + 1] == '+') {
				memDC.SelectObject(&m_red_brush);
				memDC.SelectObject(&m_red_pen);
				memDC.Rectangle(x_start + prev_j * m_unit_size + (m_unit_size / 2) - 2, y_start + prev_i * m_unit_size, x_start + prev_j * m_unit_size + (m_unit_size / 2) + 2, y_start + prev_i * m_unit_size + (m_unit_size / 2) + 2);
			}
		}
		else if (map[2 * prev_i + 1][2 * prev_j + 1] == ' ') {
			memDC.SelectObject(&m_white_pen);
			memDC.Rectangle(x_start + prev_j * m_unit_size + 2, y_start + prev_i * m_unit_size, x_start + (prev_j + 1) * m_unit_size - 2, y_start + prev_i * m_unit_size + 2);
		}

	}
	if (map[2 * prev_i + 2][2 * prev_j + 1] != '#') {
		if (map[2 * prev_i + 1][2 * prev_j + 1] == '*' || map[2 * prev_i + 1][2 * prev_j + 1] == '+') {
			memDC.SelectObject(&m_purple_pen);
			memDC.Rectangle(x_start + prev_j * m_unit_size + 2, y_start + (prev_i + 1) * m_unit_size - 2, x_start + (prev_j + 1) * m_unit_size - 2, y_start + (prev_i + 1) * m_unit_size);
			if (map[2 * prev_i + 1][2 * prev_j + 1] == '+' && map[2 * prev_i + 2][2 * prev_j + 1] == '+') {
				memDC.SelectObject(&m_red_brush);
				memDC.SelectObject(&m_red_pen);
				memDC.Rectangle(x_start + prev_j * m_unit_size + (m_unit_size / 2) - 2, y_start + prev_i * m_unit_size + (m_unit_size / 2) - 2, x_start + prev_j * m_unit_size + (m_unit_size / 2) + 2, y_start + (prev_i + 1) * m_unit_size);
			}
		}
		else if (map[2 * prev_i + 1][2 * prev_j + 1] == ' ') {
			memDC.SelectObject(&m_white_pen);
			memDC.Rectangle(x_start + prev_j * m_unit_size + 2, y_start + (prev_i + 1) * m_unit_size - 2, x_start + (prev_j + 1) * m_unit_size - 2, y_start + (prev_i + 1) * m_unit_size);
		}

	}
	if (map[2 * prev_i + 1][2 * prev_j] != '#') {
		if (map[2 * prev_i + 1][2 * prev_j + 1] == '*' || map[2 * prev_i + 1][2 * prev_j + 1] == '+') {
			memDC.SelectObject(&m_purple_pen);
			memDC.Rectangle(x_start + prev_j * m_unit_size, y_start + prev_i * m_unit_size + 2, x_start + prev_j * m_unit_size + 2, y_start + (prev_i + 1) * m_unit_size - 2);
			if (map[2 * prev_i + 1][2 * prev_j + 1] == '+' && map[2 * prev_i + 1][2 * prev_j] == '+') {
				memDC.SelectObject(&m_red_brush);
				memDC.SelectObject(&m_red_pen);
				memDC.Rectangle(x_start + prev_j * m_unit_size, y_start + prev_i * m_unit_size + (m_unit_size / 2) - 2, x_start + prev_j * m_unit_size + (m_unit_size / 2) + 2, y_start + prev_i * m_unit_size + (m_unit_size / 2) + 2);
			}
		}
		else if (map[2 * prev_i + 1][2 * prev_j + 1] == ' ') {
			memDC.SelectObject(&m_white_pen);
			memDC.Rectangle(x_start + prev_j * m_unit_size, y_start + prev_i * m_unit_size + 2, x_start + prev_j * m_unit_size + 2, y_start + (prev_i + 1) * m_unit_size - 2);
		}

	}
	if (map[2 * prev_i + 1][2 * prev_j + 2] != '#') {
		if (map[2 * prev_i + 1][2 * prev_j + 1] == '*' || map[2 * prev_i + 1][2 * prev_j + 1] == '+') {
			memDC.SelectObject(&m_purple_pen);
			memDC.Rectangle(x_start + (prev_j + 1) * m_unit_size - 2, y_start + prev_i * m_unit_size + 2, x_start + (prev_j + 1) * m_unit_size, y_start + (prev_i + 1) * m_unit_size - 2);
			if (map[2 * prev_i + 1][2 * prev_j + 1] == '+' && map[2 * prev_i + 1][2 * prev_j + 2] == '+') {
				memDC.SelectObject(&m_red_brush);
				memDC.SelectObject(&m_red_pen);
				memDC.Rectangle(x_start + prev_j * m_unit_size + (m_unit_size / 2) - 2, y_start + prev_i * m_unit_size + (m_unit_size / 2) - 2, x_start + (prev_j + 1) * m_unit_size, y_start + prev_i * m_unit_size + (m_unit_size / 2) + 2);
			}
		}
		else if (map[2 * prev_i + 1][2 * prev_j + 1] == ' ') {
			memDC.SelectObject(&m_white_pen);
			memDC.Rectangle(x_start + (prev_j + 1) * m_unit_size - 2, y_start + prev_i * m_unit_size + 2, x_start + (prev_j + 1) * m_unit_size, y_start + (prev_i + 1) * m_unit_size - 2);
		}

	}
	
	if (prev_i == m_red_dot_y && prev_j == m_red_dot_x) {
		memDC.SelectObject(&m_red_pen);
		memDC.SelectObject(&m_red_brush);
		memDC.Ellipse(x_start + prev_j * m_unit_size + 2, y_start + prev_i * m_unit_size + 2, x_start + (prev_j + 1) * m_unit_size - 2, y_start + (prev_i + 1) * m_unit_size - 2);

	}
	if (prev_i == m_blue_dot_y && prev_j == m_blue_dot_x) {
		memDC.SelectObject(&m_blue_pen);
		memDC.SelectObject(&m_blue_brush);
		memDC.Ellipse(x_start + prev_j * m_unit_size + 2, y_start + prev_i * m_unit_size + 2, x_start + (prev_j + 1) * m_unit_size - 2, y_start + (prev_i + 1) * m_unit_size - 2);

	}


	//-----현재 위치 노란 배경 알고리즘 구간 시작-----

	//검은펜, 노란브러쉬 설정
	memDC.SelectObject(&m_black_pen);
	memDC.SelectObject(&m_yellow_brush);

	//검은 테두리, 노란 배경 직사각형 그리기
	memDC.Rectangle(x_start + j * m_unit_size, y_start + i * m_unit_size, x_start + (j + 1) * m_unit_size, y_start + (i + 1) * m_unit_size);

	//위쪽 벽이 뚫인 경우 위쪽 벽에 노란색 덧칠
	if (map[2*i][2*j+1] != '#') {
		memDC.SelectObject(&m_yellow_pen);
		memDC.Rectangle(x_start + j * m_unit_size + 2, y_start + i * m_unit_size, x_start + (j + 1) * m_unit_size - 2, y_start + i * m_unit_size + 2);
	}

	//아래쪽 벽이 뚫린 경우 아래쪽 벽에 노란색 덧칠
	if (map[2*i + 2][2*j+1] != '#') {
		memDC.SelectObject(&m_yellow_pen);
		memDC.Rectangle(x_start + j * m_unit_size + 2, y_start + (i + 1) * m_unit_size - 2, x_start + (j + 1) * m_unit_size - 2, y_start + (i + 1) * m_unit_size);
	}

	//왼쪽 벽이 뚫린 경우 왼쪽 벽에 노란색 덧칠
	if (map[2*i+1][2*j] != '#') {
		memDC.SelectObject(&m_yellow_pen);
		memDC.Rectangle(x_start + j * m_unit_size, y_start + i * m_unit_size + 2, x_start + j * m_unit_size + 2, y_start + (i + 1) * m_unit_size - 2);
	}

	//오른쪽 벽이 뚫린 경우 오른쪽 벽에 노란색 덧칠
	if (map[2*i+1][2*j + 2] != '#') {
		memDC.SelectObject(&m_yellow_pen);
		memDC.Rectangle(x_start + (j + 1) * m_unit_size - 2, y_start + i * m_unit_size + 2, x_start + (j + 1) * m_unit_size, y_start + (i + 1) * m_unit_size - 2);
	}

	//출발점 위치일 경우 빨간 점 그리기
	if (i == m_red_dot_y && j == m_red_dot_x) {
		memDC.SelectObject(&m_red_pen);
		memDC.SelectObject(&m_red_brush);
		memDC.Ellipse(x_start + j * m_unit_size + 2, y_start + i * m_unit_size + 2, x_start + (j + 1) * m_unit_size - 2, y_start + (i + 1) * m_unit_size - 2);

	}

	//도착점 위치일 경우 파란 점 그리기
	if (i == m_blue_dot_y && j == m_blue_dot_x) {
		memDC.SelectObject(&m_blue_pen);
		memDC.SelectObject(&m_blue_brush);
		memDC.Ellipse(x_start + j * m_unit_size + 2, y_start + i * m_unit_size + 2, x_start + (j + 1) * m_unit_size - 2, y_start + (i + 1) * m_unit_size - 2);

	}

	//메모리dc의 비트맵을 dc에 옮겨 그리기
	dc.BitBlt(0, 0, x_start + m_maze_width, y_start + m_maze_height, &memDC, 0, 0, SRCCOPY);

	//비트맵 객체 삭제
	bitmap.DeleteObject();

	//dc해제
	ReleaseDC(&dc);
	ReleaseDC(&memDC);

	//창 업데이트
	UpdateWindow();
}