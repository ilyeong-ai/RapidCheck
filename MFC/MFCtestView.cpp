
// MFCtestView.cpp : CMFCtestView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCtest.h"
#endif

#include "MFCtestDoc.h"
#include "MFCtestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCtestView

IMPLEMENT_DYNCREATE(CMFCtestView, CView)

BEGIN_MESSAGE_MAP(CMFCtestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCtestView 생성/소멸

CMFCtestView::CMFCtestView()
{
	// TODO: 여기에 생성 코드를 추가합니다.


}

CMFCtestView::~CMFCtestView()
{
}

BOOL CMFCtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCtestView 그리기

//void CMFCtestView::OnDraw(CDC* pDC)
void CMFCtestView::OnDraw(CDC* /*pDC*/)
{
	/*
	CMFCtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i, dan;
    CString str;

    for (dan = 2; dan <= 9; dan++)
    {
        for (i = 1; i <= 2; i++)
        {
            str.Format(_T("%dx%d=%d"), dan, i, dan * i);
            pDC->TextOut((dan - 2) * 70 + 20, 20 * i, str);
        }
    }
	str.Format(_T("test %d"), 31);
	pDC->TextOut(100, 180, str); //x,y 좌표, 출력할 문자
	*/
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCtestView 인쇄

BOOL CMFCtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCtestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCtestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCtestView 진단

#ifdef _DEBUG
void CMFCtestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCtestDoc* CMFCtestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCtestDoc)));
	return (CMFCtestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCtestView 메시지 처리기

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')
void CMFCtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	FILE* fp = NULL;
	fopen_s(&fp, "screen.bmp", "rb");
	if (!fp)
		return;

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	// BITMAPFILEHEADER 읽기
	if (fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, fp) != 1) {
		fclose(fp);
		return;
	}

	// BMP 파일임을 나타내는 'BM' 마커가 있는지 확인
	if (bmfh.bfType != DIB_HEADER_MARKER) {
		fclose(fp);
		return;
	}

	// BITMAPINFOHEADER 읽기
	if (fread(&bmih, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
		fclose(fp);
		return;
	}

	LONG nWidth = bmih.biWidth;
	LONG nHeight = bmih.biHeight;
	WORD nBitCount = bmih.biBitCount;

	DWORD dwWidthStep = (DWORD)((nWidth * nBitCount / 8 + 3) & ~3);
	DWORD dwSizeImage = nHeight * dwWidthStep;

	// DIB 구조 전체 크기 계산 (BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터)
	DWORD dwDibSize;
	if (nBitCount == 24)
		dwDibSize = sizeof(BITMAPINFOHEADER)+dwSizeImage;
	else
		dwDibSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* (1 << nBitCount) + dwSizeImage;

	// 파일로부터 DIB 구조를 읽어서 저장할 메모리 공간 할당
	BYTE* pDib = new BYTE[dwDibSize];

	if (pDib == NULL)
	{
		fclose(fp);
		return;
	}

	// 파일로부터 Packed-DIB 크기만큼을 읽기
	fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
	if (fread(pDib, sizeof(BYTE), dwDibSize, fp) != dwDibSize)
	{
		delete[] pDib;
		pDib = NULL;
		fclose(fp);
		return;
	}

	// 픽셀 데이터 시작 위치 계산
	LPVOID lpvBits;
	if (nBitCount == 24)
		lpvBits = pDib + sizeof(BITMAPINFOHEADER);
	else
		lpvBits = pDib + sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* (1 << nBitCount);

	// DIB 화면 출력
	CClientDC dc(this);
	::SetDIBitsToDevice(dc.m_hDC, point.x, point.y, nWidth, nHeight, 0, 0, 0,
		nHeight, lpvBits, (BITMAPINFO*)pDib, DIB_RGB_COLORS);

	// 메모리 해제 및 파일 닫기
	delete[] pDib;
	fclose(fp);

	CView::OnLButtonDown(nFlags, point);
}
