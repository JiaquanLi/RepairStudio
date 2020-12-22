// XLAutomation.h: interface for the CXLAutomation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XLAUTOMATION_H__E020CE95_7428_4BEF_A24C_48CE9323C450__INCLUDED_)
#define AFX_XLAUTOMATION_H__E020CE95_7428_4BEF_A24C_48CE9323C450__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_DISP_ARGS 10
#define DISPARG_NOFREEVARIANT 0x01
#define DISP_FREEARGS 0x02
#define DISP_NOSHOWEXCEPTIONS 0x03
#define xlWorksheet -4167
#define xlRows 1
#define xlColumns 2
#define xlNormal -4143
#define xlMinimized -4140
#define xlMaximized -4137
#define xlUp -4162 /*Up*/
#define xlDown -4121 /*Down*/
#define xlToLeft -4159 /*To left*/
#define xlToRight -4161 /*To right*/
#define xlReadOnly 3 /*Read only*/
#define xlReadWrite 2 /*Read/write*/

#define xl3DArea -4098 3D /*Area.*/
#define xl3DAreaStacked 78 /*3D Stacked Area.*/
#define xl3DAreaStacked100 79 /*100% Stacked Area.*/
#define xl3DBarClustered 60 /*3D Clustered Bar.*/
#define xl3DBarStacked 61 /*3D Stacked Bar.*/
#define xl3DBarStacked100 62 /*3D % Stacked Bar.*/
#define xl3DColumn -4100 /*3D Column.*/
#define xl3DColumnClustered 54 /*3D Clustered Column.*/
#define xl3DColumnStacked 55 /*3D Stacked Column.*/ 
#define xl3DColumnStacked100 56 /*3D 100% Stacked Column.*/
#define xl3DLine -4101 /*3D Line.*/
#define xl3DPie -4102 /*3D Pie.*/
#define xl3DPieExploded 70 /*Exploded 3D Pie.*/
#define xlArea 1 /*Area*/
#define xlAreaStacked 76 /*Stacked Area.*/
#define xlAreaStacked100 77 /*100% Stacked Area.*/
#define xlBarClustered 57 /*Clustered Bar.*/
#define xlBarOfPie 71 /*Bar of Pie.*/
#define xlBarStacked 58 /*Stacked Bar.*/
#define xlBarStacked100 59 /*100% Stacked Bar.*/
#define xlBubble 15 /*Bubble.*/
#define xlBubble3DEffect 87 /*Bubble with 3D effects.*/
#define xlColumnClustered 51 /*Clustered Column.*/
#define xlColumnStacked 52 /*Stacked Column.*/
#define xlColumnStacked100 53 /*100% Stacked Column.*/
#define xlConeBarClustered 102 /*Clustered Cone Bar.*/
#define xlConeBarStacked 103 /*Stacked Cone Bar.*/
#define xlConeBarStacked100 104 /*100% Stacked Cone Bar.*/
#define xlConeCol 105 /*3D Cone Column.*/
#define xlConeColClustered 99 /*Clustered Cone Column.*/
#define xlConeColStacked 100 /*Stacked Cone Column.*/
#define xlConeColStacked100 101 /*100% Stacked Cone Column.*/
#define xlCylinderBarClustered 95 /*Clustered Cylinder Bar.*/
#define xlCylinderBarStacked 96 /*Stacked Cylinder Bar.*/
#define xlCylinderBarStacked100 97 /*100% Stacked Cylinder Bar.*/
#define xlCylinderCol 98 /*3D Cylinder Column.*/
#define xlCylinderColClustered 92 /*Clustered Cone Column.*/
#define xlCylinderColStacked 93 /*Stacked Cone Column.*/
#define xlCylinderColStacked100 94 /*100% Stacked Cylinder Column.*/
#define xlDoughnut -4120 /*Doughnut.*/
#define xlDoughnutExploded 80 /*Exploded Doughnut.*/
#define xlLine 4 /*Line.*/
#define xlLineMarkers 65 /*Line with Markers.*/
#define xlLineMarkersStacked 66 /*Stacked Line with Markers.*/
#define xlLineMarkersStacked100 67 /*100% Stacked Line with Markers.*/
#define xlLineStacked 63 /*Stacked Line.*/
#define xlLineStacked100 64 /*100% Stacked Line.*/
#define xlPie 5 /*Pie.*/
#define xlPieExploded 69 /*Exploded Pie.*/
#define xlPieOfPie 68 /*Pie of Pie.*/
#define xlPyramidBarClustered 109 /*Clustered Pyramid Bar.*/
#define xlPyramidBarStacked 110 /*Stacked Pyramid Bar.*/
#define xlPyramidBarStacked100 111 /*100% Stacked Pyramid Bar.*/
#define xlPyramidCol 112 /*3D Pyramid Column.*/
#define xlPyramidColClustered 106 /*Clustered Pyramid Column.*/
#define xlPyramidColStacked 107 /*Stacked Pyramid Column.*/
#define xlPyramidColStacked100 108 /*100% Stacked Pyramid Column.*/
#define xlRadar -4151 /*Radar.*/
#define xlRadarFilled 82 /*Filled Radar.*/
#define xlRadarMarkers 81 /*Radar with Data Markers.*/
#define xlStockHLC 88 /*High-Low-Close.*/
#define xlStockOHLC 89 /*Open-High-Low-Close.*/
#define xlStockVHLC 90 /*Volume-High-Low-Close.*/
#define xlStockVOHLC 91 /*Volume-Open-High-Low-Close.*/
#define xlSurface 83 3D /*Surface.*/
#define xlSurfaceTopView 85 /*Surface (Top View).*/
#define xlSurfaceTopViewWireframe 86 /*Surface (Top View wireframe).*/
#define xlSurfaceWireframe 84 /*3D Surface (wireframe).*/
#define xlXYScatter -4169 /*Scatter.*/
#define xlXYScatterLines 74 /*Scatter with Lines.*/
#define xlXYScatterLinesNoMarkers 75 /*Scatter with Lines and No Data Markers.*/
#define xlXYScatterSmooth 72 /*Scatter with Smoothed Lines.*/
#define xlXYScatterSmoothNoMarkers 73 /*Scatter with Smoothed Lines and No Data Markers.*/

class CXLAutomation
{
public:
	int CountDataRows();
	int CountDataLines();
	int AddNewWorkSheet();
	int GetChartsCount();
	int GetWorksheetsCount();
	BOOL EnableAlert(BOOL bShowAlert);
	BOOL Sort(long lColumnStart, long lRowStart, long lColumnEnd, long lRowEnd, long lColumnSort);
	BOOL FindInRange(long lColumnStart, long lRowStart, long lColumnEnd, long lRowEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell);
	BOOL FindInRows(long lRowStart, long lRowEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell);
	BOOL FindInColumns(long lColumnStart, long lColumnEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell);
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
	BOOL SetChartTitle(CString sTitle);
	BOOL SetWorksheetTitle(CString sTitle);
	BOOL InsertRow(int nRow);
	BOOL ActiveChartNewSeries(long nXC1, long nXR1, long nXC2, long nXR2, long nYC1, long nYR1, long nYC2, long nYR2, LPCTSTR lpszSerieName = NULL);
	BOOL Create3YChart(int nX1Column,int nY1Column);
	BOOL OpenExcelFile(CString szFileName);
	BOOL InsertPictureToWorksheet(BYTE* pImage, int nColumn, int nRow, double dPicWidth, double dPicHeight);
	BOOL InsertPictureToWorksheet(CString szFileName, int nColumn, int nRow, double dPicWidth, double dPicHeight);
	BOOL PlaceImageToClipboard(BYTE* pImage);
	CString GetCellValueCString(int nColumn, int nRow);
	BOOL SaveAs(CString szFileName, int nFileFormat, CString szPassword, CString szWritePassword, BOOL bReadOnly, BOOL bBackUp);
	BOOL DeleteRow(long fRow);
	BOOL ReleaseExcel();
	BOOL CreateWorkSheet();
	BOOL PasteStringToWorksheet(CString pDataBuffer);
	BOOL UpdatePlotRange(int nYColumn);
	BOOL UpdatePlotRange(int nXColumn,int nYColumn,int nXRow = 0,int nYRow = 0);
	BOOL AddArgumentCStringArray(LPOLESTR lpszArgName,WORD wFlags, LPOLESTR* paszStrings, int iCount);
	BOOL SetRangeValueDouble(LPOLESTR lpszRef, double d);
	BOOL CreateXYChart(int nYColumn);
	BOOL SetCellsValueToString(double fColumn, double fRow, CString szStr);
	BOOL AddArgumentOLEString(LPOLESTR lpszArgName, WORD wFlags, LPOLESTR lpsz);
	BOOL AddArgumentCString(LPOLESTR lpszArgName, WORD wFlags, CString szStr);
	BOOL AddArgumentDouble(LPOLESTR lpszArgName, WORD wFlags, double d);
	BOOL AddArgumentBool(LPOLESTR lpszArgName, WORD wFlags, BOOL b);
	BOOL AddArgumentInt2(LPOLESTR lpszArgName, WORD wFlags, int i);
	BOOL AddArgumentDispatch(LPOLESTR lpszArgName, WORD wFlags, IDispatch* pdisp);
	void AddArgumentCommon(LPOLESTR lpszArgName, WORD wFlags, VARTYPE vt);
	BOOL InitOLE();
	CXLAutomation();
	CXLAutomation::CXLAutomation(BOOL bVisible);
	virtual ~CXLAutomation();

public:
	int	m_nChartType;

protected:
	void ClearAllArgs();
	void ReleaseDispatch();
	BOOL SetExcelVisible(BOOL bVisible);
	void ClearVariant(VARIANTARG* pvarg);
	void ReleaseVariant(VARIANTARG* pvarg);
	BOOL GetCellRange(VARIANTARG* pvargSelection, long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd);
	void ShowException(LPOLESTR szMember, HRESULT hr, EXCEPINFO* pexcep, unsigned int uiArgErr);

	int			m_iArgCount;
	int			m_iNamedArgCount;
	VARIANTARG	m_aVargs[MAX_DISP_ARGS];
	DISPID		m_aDispIds[MAX_DISP_ARGS + 1];		// one extra for the member name
	LPOLESTR	m_alpszArgNames[MAX_DISP_ARGS + 1];	// used to hold the argnames for GetIDs
	WORD		m_awFlags[MAX_DISP_ARGS];

	BOOL ExlInvoke(IDispatch* pdisp, LPOLESTR szMember, VARIANTARG* pvargReturn,WORD wInvokeAction, WORD wFlags);
	IDispatch* m_pdispExcelApp;
	IDispatch* m_pdispWorkbook;
	IDispatch* m_pdispWorksheet;
	IDispatch* m_pdispActiveWorksheet;
	IDispatch* m_pdispActiveChart;
	BOOL StartExcel();
};

#endif // !defined(AFX_XLAUTOMATION_H__E020CE95_7428_4BEF_A24C_48CE9323C450__INCLUDED_)
