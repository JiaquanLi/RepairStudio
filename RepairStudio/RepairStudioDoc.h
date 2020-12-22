// RepairStudioDoc.h : interface of the CRepairStudioDoc class
//


#pragma once


class CRepairStudioDoc : public CDocument
{
protected: // create from serialization only
	CRepairStudioDoc();
	DECLARE_DYNCREATE(CRepairStudioDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CRepairStudioDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


