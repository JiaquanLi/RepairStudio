// EzAutomation.h: interface for the CXLEzAutomation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EzAutomation_H__D140B9A3_1995_40AC_8E6D_8F23A95A63A2__INCLUDED_)
#define AFX_EzAutomation_H__D140B9A3_1995_40AC_8E6D_8F23A95A63A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XLAutomation.h"
#define xlNormal -4143

class CXLEzAutomation
{
public:

	enum ChartType
	{
		XL3DArea					= -4098,
		XL3DAreaStacked				= 78,
		XL3DBarClustered			= 60,
		XL3DBarStacked				= 61,
		XL3DBarStacked100			= 62,
		XL3DColumn					= -4100,
		XL3DColumnClustered			= 54,
		XL3DColumnStacked			= 55,
		XL3DColumnStacked100		= 56,
		XL3DLine					= -4101,
		XL3DPie						= -4102,
		XL3DPieExploded				= 70,
		XLArea						= 1,
		XLAreaStacked				= 76,
		XLAreaStacked100			= 77,
		XLBarClustered				= 57,
		XLBarOfPie					= 71,
		XLBarStacked				= 58,
		XLBarStacked100				= 59,
		XLBubble					= 15,
		XLBubble3DEffect			= 87,
		XLColumnClustered			= 51,
		XLColumnStacked				= 52,
		XLColumnStacked100			= 53,
		XLConeBarClustered			= 102,
		XLConeBarStacked			= 103,
		XLConeBarStacked100			= 104,
		XLConeCol					= 105,
		XLConeColClustered			= 99,
		XLConeColStacked			= 100,
		XLConeColStacked100			= 101,
		XLCylinderBarClustered		= 95,
		XLCylinderBarStacked		= 96,
		XLCylinderBarStacked100		= 97,
		XLCylinderCol				= 98,
		XLCylinderColClustered		= 92,
		XLCylinderColStacked		= 93,
		XLCylinderColStacked100		= 94,
		XLDoughnut					= -4120,
		XLDoughnutExploded			= 80,
		XLLine						= 4,
		XLLineMarkers				= 65,
		XLLineMarkersStacked		= 66,
		XLLineMarkersStacked100		= 67,
		XLLineStacked				= 63,
		XLLineStacked100			= 64,
		XLPie						= 5,
		XLPieExploded				= 69,
		XLPieOfPie					= 68,
		XLPyramidBarClustered		= 109,
		XLPyramidBarStacked			= 110,
		XLPyramidBarStacked100		= 111,
		XLPyramidCol				= 112,
		XLPyramidColClustered		= 106,
		XLPyramidColStacked			= 107,
		XLPyramidColStacked100		= 108,
		XLRadar						= -4151,
		XLRadarFilled				= 82,
		XLRadarMarkers				= 81,
		XLStockHLC					= 88,
		XLStockOHLC					= 89,
		XLStockVHLC					= 90,
		XLStockVOHLC				= 91,
		XLSurface					= 83,
		XLSurfaceTopView			= 85,
		XLSurfaceTopViewWireframe	= 86,
		XLSurfaceWireframe			= 84,
		XLXYScatter					= -4169,
		XLXYScatterLines			= 74,
		XLXYScatterLinesNoMarkers	= 75,
		XLXYScatterSmooth			= 72,
		XLXYScatterSmoothNoMarkers	= 73
	};

public:
	int CountDataRows();
	int CountDataLines();
	int AddNewWorkSheet();
	int GetChartsCount();
	int GetWorksheetsCount();
	BOOL InsertRow(int nRow);
	BOOL EnableAlert(BOOL bShowAlert);
	BOOL SetChartTitle(CString sTitle);
	BOOL SetWorksheetTitle(CString sTitle);
	BOOL Sort(long lColumnStart, long lRowStart, long lColumnEnd, long lRowEnd, long lColumnSort);
	BOOL FindInRange(long lColumnStart, long lRowStart, long lColumnEnd, long lRowEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell);
	BOOL FindInRows(long lRowStart, long lRowEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell);
	BOOL FindInColumns(long lColumnStart, long lColumnEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell);
	void SetChartType(ChartType Type){m_pXLServer->m_nChartType = Type;}
	BOOL SetCellBackgroundTransparent(long nRow, long nColumn);
	BOOL CutAndPasteCellRange(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd, long nColumnStart1, long nRowStart1, long nColumnEnd1, long nRowEnd1);
	BOOL ClearCell(int nColumn, int nRow);
	BOOL SetCellColor(int nRow, int nColumn, int nColorIndex);
	BOOL FormatCell(int nRow, int nColumn, CString szFormat);
	CString GetWorksheetName(int nWorksheet);
	BOOL SetTickSpacing(int nLabelSpacing, int nMarkSpacing);
	int CountDataCells(int nResultColumn);
	BOOL ImportDataFromTextFile(CString szFileName);
	BOOL AddErrorBar(long nPlusColm, long nPlusRowStart, long nPlusRowEnd, long nMinusColm, long nMinusRowStart, long nMinusRowEnd);
	BOOL SetAxesTitle(CString szXTitle, CString szYTitle);
	BOOL MergeCells(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd);
	BOOL SetFontBold(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd, BOOL bBold);
	BOOL SetFontSize(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd, int nFontSize);
	BOOL SetActiveWorksheet(int nWorksheet);
	BOOL SetActiveChart(int nChart);
	BOOL ActiveChartNewSeries(long nXC1, long nXR1, long nXC2, long nXR2, long nYC1, long nYR1, long nYC2, long nYR2, LPCTSTR lpszSerieName = NULL);
	BOOL Create3YChart(int nX1Column,int nY1Column);
	BOOL InsertPictureFromBuffer(BYTE* pImage, int nColumn, int nRow, double dXScale, double dYScale);
	BOOL OpenExcelFile(CString szFileName);
	BOOL PlacePictureToClipboard(BYTE* pImage);
	BOOL InsertPictureFromClipboard(int nColumn, int nRow);
	BOOL InsertPictureFromFile(CString szFileName, int nColumn, int nRow);
	CString GetCellValue(int nColumn, int nRow);
	BOOL SaveFileAs(CString szFileName, CString szPassword = _T(""), CString szWritePassword = _T(""), BOOL bReadOnly = FALSE, BOOL bBackUp = FALSE);
	BOOL DeleteRow(int nRow);
	BOOL ReleaseExcel();
	BOOL SetCellValue(int nRow, int nColumn, CString szValue);
	BOOL ExportCString(CString szDataCollection);
	BOOL UpdateXYChart(int nX1Column,int nY1Column,int nXRow = 0,int nYRow = 0);
	BOOL UpdateXYChart(int nYColumn);
	BOOL CreateXYChart(int nYColumn);
	BOOL StartExcel(BOOL bVisible);
	void StopExcel();	// A B - for ability to close the Excel process without destroying the object
	CXLEzAutomation();
	CXLEzAutomation(BOOL bVisible);
	virtual ~CXLEzAutomation();

protected:
	CXLAutomation* m_pXLServer;
};

#endif // !defined(AFX_EzAutomation_H__D140B9A3_1995_40AC_8E6D_8F23A95A63A2__INCLUDED_)
