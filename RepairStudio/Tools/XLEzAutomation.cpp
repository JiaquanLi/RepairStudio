// EzAutomation.cpp: implementation of the CXLEzAutomation class.
//This wrapper classe is provided for easy access to basic automation  
//methods of the CXLAutoimation.
//Only very basic set of methods is provided here.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XLEzAutomation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//

//////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////
CXLEzAutomation::CXLEzAutomation()
{
	//Starts Excel with bVisible = TRUE and creates empty worksheet 
	m_pXLServer = new CXLAutomation;
}

CXLEzAutomation::CXLEzAutomation(BOOL bVisible)
{
	//Can be used to start Excel in background (bVisible = FALSE)
	m_pXLServer = new CXLAutomation(bVisible);
}

CXLEzAutomation::~CXLEzAutomation()
{
	if(NULL != m_pXLServer)
		delete m_pXLServer;
}

BOOL CXLEzAutomation::StartExcel(BOOL bVisible)
{
	if(! m_pXLServer)
	{
		m_pXLServer = new CXLAutomation(bVisible);
		return TRUE;
	}

	return FALSE;	// file is already open !
}

void CXLEzAutomation::StopExcel()
{
	if(m_pXLServer)
	{
		//ReleaseExcel();
		delete m_pXLServer;
	}
	m_pXLServer = NULL;
}
//Create XY plot of the type xlXYScatterLinesNoMarkers
BOOL CXLEzAutomation::CreateXYChart(int nYColumn)
{
	return m_pXLServer->CreateXYChart(nYColumn);
}
//Force update data source range . If new data points have been added to
//the data source, these points will be added to the plot.
//Default assumes data are placed in A and B columns of the Excel worksheet.
BOOL CXLEzAutomation::UpdateXYChart(int nYColumn)
{
	return m_pXLServer->UpdatePlotRange(nYColumn);
}
// If nXRow is 0 and nYRow is 0 then UpdateXYChart get the original rows number
BOOL CXLEzAutomation::UpdateXYChart(int nX1Column,int nY1Column,int nXRow/* = 0*/,int nYRow/* = 0*/)
{
	return m_pXLServer->UpdatePlotRange(nX1Column,nY1Column,nXRow,nYRow);
}
//Use clipboard to export szDataCollection to Excel worksheet
BOOL CXLEzAutomation::ExportCString(CString szDataCollection)
{
	return m_pXLServer->PasteStringToWorksheet(szDataCollection);
}
//Set cell value: Worksheet.Cells(nColumn, nRow).Value = szValue
BOOL CXLEzAutomation::SetCellValue(int nRow, int nColumn, CString szValue)
{
	BOOL bResult;
	bResult = m_pXLServer->SetCellsValueToString((double) nColumn, (double)nRow, szValue);

	return bResult;
}
//Quit Excel
BOOL CXLEzAutomation::ReleaseExcel()
{
	return m_pXLServer->ReleaseExcel();
}
//Delete line from worksheet
BOOL CXLEzAutomation::DeleteRow(int nRow)
{
	return m_pXLServer->DeleteRow(nRow);
}
//Save workbook as Excel file
BOOL CXLEzAutomation::SaveFileAs(CString szFileName, CString szPassword/* = _T("")*/, CString szWritePassword/* = _T("")*/, BOOL bReadOnly/* = FALSE*/, BOOL bBackUp/* = FALSE*/)
{
	return m_pXLServer->SaveAs(szFileName, xlNormal, szPassword, szWritePassword, bReadOnly, bBackUp);
}
//Returns Worksheet.Cells(nColumn, nRow).Value
CString CXLEzAutomation::GetCellValue(int nColumn, int nRow)
{
	return m_pXLServer->GetCellValueCString(nColumn, nRow);
}
//Insert picture from file. Position it at (Column, Row) on the worksheet. 
//The method resizes the picture to 50% of the original size (see 0.5, 0.5)
BOOL CXLEzAutomation::InsertPictureFromFile(CString szFileName, int nColumn, int nRow)
{
	return m_pXLServer->InsertPictureToWorksheet(szFileName, nColumn, nRow, 0.5, 0.5);
}
//Insert picture which was previously placed on clipboard
//Does not resize picture (see 0.0, 0.0)
BOOL CXLEzAutomation::InsertPictureFromClipboard(int nColumn, int nRow)
{
	return m_pXLServer->InsertPictureToWorksheet(NULL, nColumn, nRow, 0.0, 0.0);
}
//Place image to clipboard using XLAutomation method
BOOL CXLEzAutomation::PlacePictureToClipboard(BYTE *pImage)
{
	return m_pXLServer->PlaceImageToClipboard(pImage);
}
//Open Excell file
BOOL CXLEzAutomation::OpenExcelFile(CString szFileName)
{
	return m_pXLServer->OpenExcelFile(szFileName);
}
//Insert picture from buffer. If pImage = NULL, the picture from clipboard will be inserted.
//The picture is placed at (Column, Row) on worksheet
//The picture can be resized in % of its original size
//by specifying dXScale and dYScale
//If no resize is needed, make dXScal = 0.0 and dYScale = 0.0 
BOOL CXLEzAutomation::InsertPictureFromBuffer(BYTE *pImage, int nColumn, int nRow, double dXScale, double dYScale)
{
	return m_pXLServer->InsertPictureToWorksheet(pImage, nColumn, nRow, dXScale, dYScale);
}

BOOL CXLEzAutomation::Create3YChart(int nX1Column,int nY1Column)
{
	return m_pXLServer->Create3YChart(nX1Column,nY1Column);
}

BOOL CXLEzAutomation::ActiveChartNewSeries(long nXC1, long nXR1, long nXC2, long nXR2, long nYC1, long nYR1, long nYC2, long nYR2, LPCTSTR lpszSerieName/* = NULL*/)
{
	return m_pXLServer->ActiveChartNewSeries(nXC1, nXR1, nXC2, nXR2, nYC1, nYR1, nYC2, nYR2, lpszSerieName);
}

BOOL CXLEzAutomation::InsertRow(int nRow)
{
	return m_pXLServer->InsertRow(nRow);
}

BOOL CXLEzAutomation::SetWorksheetTitle(CString sTitle)
{
	return m_pXLServer->SetWorksheetTitle(sTitle);
}

BOOL CXLEzAutomation::SetChartTitle(CString sTitle)
{
	return m_pXLServer->SetChartTitle(sTitle);
}

int CXLEzAutomation::AddNewWorkSheet()
{
	return m_pXLServer->AddNewWorkSheet();
}

int CXLEzAutomation::GetWorksheetsCount()
{
	return m_pXLServer->GetWorksheetsCount();
}

int CXLEzAutomation::GetChartsCount()
{
	return m_pXLServer->GetChartsCount();
}

BOOL CXLEzAutomation::SetActiveWorksheet(int nWorksheet)
{
	return m_pXLServer->SetActiveWorksheet(nWorksheet);
}

BOOL CXLEzAutomation::SetActiveChart(int nChart)
{
	return m_pXLServer->SetActiveChart(nChart);
}

BOOL CXLEzAutomation::SetFontSize(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd, int nFontSize)
{
	return m_pXLServer->SetFontSize(nColumnStart, nRowStart, nColumnEnd, nRowEnd, nFontSize);
}

BOOL CXLEzAutomation::SetFontBold(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd, BOOL bBold)
{
	return m_pXLServer->SetFontBold(nColumnStart, nRowStart, nColumnEnd, nRowEnd, bBold);
}

BOOL CXLEzAutomation::MergeCells(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd)
{
	return m_pXLServer->MergeCells(nColumnStart, nRowStart, nColumnEnd, nRowEnd);
}

BOOL CXLEzAutomation::SetAxesTitle(CString szXTitle, CString szYTitle)
{
	return m_pXLServer->SetAxesTitle(szXTitle, szYTitle);
}

BOOL CXLEzAutomation::AddErrorBar(long nPlusColm, long nPlusRowStart, long nPlusRowEnd, long nMinusColm, long nMinusRowStart, long nMinusRowEnd)
{
	return m_pXLServer->AddErrorBar(nPlusColm, nPlusRowStart, nPlusRowEnd, nMinusColm, nMinusRowStart, nMinusRowEnd);
}

BOOL CXLEzAutomation::ImportDataFromTextFile(CString szFileName)
{
	return m_pXLServer->ImportDataFromTextFile(szFileName);
}

BOOL CXLEzAutomation::CountDataCells(int nResultColumn)
{
	return m_pXLServer->CountDataCells(nResultColumn);
}

BOOL CXLEzAutomation::SetTickSpacing(int nLabelSpacing, int nMarkSpacing)
{
	return m_pXLServer->SetTickSpacing(nLabelSpacing, nMarkSpacing);
}

CString CXLEzAutomation::GetWorksheetName(int nWorksheet)
{
	return m_pXLServer->GetWorksheetName(nWorksheet);
}

BOOL CXLEzAutomation::EnableAlert(BOOL bShowAlert)
{
	return m_pXLServer->EnableAlert(bShowAlert);
}

int CXLEzAutomation::CountDataLines()
{
	return m_pXLServer->CountDataLines();
}

int CXLEzAutomation::CountDataRows()
{
	return m_pXLServer->CountDataRows();
}

BOOL CXLEzAutomation::FormatCell(int nRow, int nColumn, CString szFormat)
{
	return m_pXLServer->FormatCell(nRow, nColumn, szFormat);
}

BOOL CXLEzAutomation::SetCellColor(int nRow, int nColumn, int nColorIndex)
{
	return m_pXLServer->SetCellColor(nRow, nColumn, nColorIndex);
}

BOOL CXLEzAutomation::SetCellBackgroundTransparent(long nRow, long nColumn)
{
	return m_pXLServer->SetCellBackgroundTransparent(nRow, nColumn);
}

BOOL CXLEzAutomation::CutAndPasteCellRange(long nColumnStart, long nRowStart, long nColumnEnd, long nRowEnd, long nColumnStart1, long nRowStart1, long nColumnEnd1, long nRowEnd1)
{
	return m_pXLServer->CutAndPasteCellRange(nColumnStart, nRowStart, nColumnEnd, nRowEnd, nColumnStart1, nRowStart1, nColumnEnd1, nRowEnd1);
}

BOOL CXLEzAutomation::ClearCell(int nColumn, int nRow)
{
	return m_pXLServer->ClearCell(nColumn, nRow);
}

BOOL CXLEzAutomation::Sort(long lColumnStart, long lRowStart, long lColumnEnd, long lRowEnd, long lColumnSort)
{
	return m_pXLServer->Sort(lColumnStart, lRowStart, lColumnEnd, lRowEnd, lColumnSort);
}

BOOL CXLEzAutomation::FindInRange(long lColumnStart, long lRowStart, long lColumnEnd, long lRowEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell)
{
	return m_pXLServer->FindInRange(lColumnStart, lRowStart, lColumnEnd, lRowEnd, sArgument, piColumnOfFoundCell, piRowOfFoundCell);
}

BOOL CXLEzAutomation::FindInRows(long lRowStart, long lRowEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell)
{
	return m_pXLServer->FindInRows(lRowStart, lRowEnd, sArgument, piColumnOfFoundCell, piRowOfFoundCell);
}

BOOL CXLEzAutomation::FindInColumns(long lColumnStart, long lColumnEnd, CString sArgument, int* piColumnOfFoundCell, int* piRowOfFoundCell)
{
	return m_pXLServer->FindInColumns(lColumnStart, lColumnEnd, sArgument, piColumnOfFoundCell, piRowOfFoundCell);
}
