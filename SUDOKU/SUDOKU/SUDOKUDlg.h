
// SUDOKUDlg.h : fichier d'en-tête
//

#pragma once


// boîte de dialogue CSUDOKUDlg
class CSUDOKUDlg : public CDialogEx
{
// Construction
public:
	CSUDOKUDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
	enum { IDD = IDD_SUDOKU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:	

	Solution *pt_solution = nullptr;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
