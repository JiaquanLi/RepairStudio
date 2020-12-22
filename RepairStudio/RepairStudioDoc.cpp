// RepairStudioDoc.cpp : implementation of the CRepairStudioDoc class
//

#include "stdafx.h"
#include "RepairStudio.h"

#include "RepairStudioDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRepairStudioDoc

IMPLEMENT_DYNCREATE(CRepairStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CRepairStudioDoc, CDocument)
END_MESSAGE_MAP()


// CRepairStudioDoc construction/destruction

CRepairStudioDoc::CRepairStudioDoc()
{
	// TODO: add one-time construction code here

}

CRepairStudioDoc::~CRepairStudioDoc()
{
}

BOOL CRepairStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRepairStudioDoc serialization

void CRepairStudioDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CRepairStudioDoc diagnostics

#ifdef _DEBUG
void CRepairStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRepairStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRepairStudioDoc commands
