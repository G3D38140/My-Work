
// SUDOKUDlg.cpp : fichier d'impl�mentation
//

#include "stdafx.h"
#include "SUDOKU.h"
#include "SUDOKUDlg.h"
#include "afxdialogex.h"
#include "Solution.h"
#include "Calcul_temps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int grid[MAX][MAX];

// bo�te de dialogue CSUDOKUDlg

CSUDOKUDlg::CSUDOKUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSUDOKUDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//  Value_IDC_EDIT1 = 0;
}

void CSUDOKUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSUDOKUDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSUDOKUDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSUDOKUDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CSUDOKUDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSUDOKUDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// gestionnaires de messages pour CSUDOKUDlg

BOOL CSUDOKUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	EnableToolTips();

	// D�finir l'ic�ne de cette bo�te de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fen�tre principale de l'application n'est pas une bo�te de dialogue
	SetIcon(m_hIcon, TRUE);			// D�finir une grande ic�ne
	
	// TODO: ajoutez ici une initialisation suppl�mentaire
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	::SetDlgItemTextW(m_hWnd, IDC_STATIC,_T(""));
	return TRUE;  // retourne TRUE, sauf si vous avez d�fini le focus sur un contr�le
}

// Si vous ajoutez un bouton R�duire � votre bo�te de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'ic�ne.  Pour les applications MFC utilisant le mod�le Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CSUDOKUDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de p�riph�rique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'ic�ne dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'ic�ne
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le syst�me appelle cette fonction pour obtenir le curseur � afficher lorsque l'utilisateur fait glisser
//  la fen�tre r�duite.
HCURSOR CSUDOKUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSUDOKUDlg::OnBnClickedOk()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contr�le


	// Solution
	 pt_solution = new Solution(m_hWnd);

	if (pt_solution->Charger_valeur_saisie(m_hWnd) == TRUE)
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->SetWindowTextW(_T("Fin"));
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
	
	if (pt_solution != 0)
	{
		delete pt_solution;
	}
}


void CSUDOKUDlg::OnBnClickedCancel()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contr�le


	// Cancel

	CDialogEx::OnCancel();
}


void CSUDOKUDlg::OnBnClickedButton1()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contr�le

	// Raz

	int z = 0;
	CString Chaine(_T(""));

	for (int row = 0; row < MAX; row++)
	{
		for (int col = 0; col < MAX; col++)
		{
			::SetDlgItemTextW(m_hWnd, (IDC_EDIT1 + z), (LPWSTR)Chaine.GetBuffer());
			// grid[row,col] = 0; // a voir
			z++;
		}
	}

	GetDlgItem(IDOK)->EnableWindow(TRUE);
	::SetDlgItemTextW(m_hWnd, IDC_STATIC, _T(""));

}


void CSUDOKUDlg::OnBnClickedButton2()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contr�le
	// Load a file


	CString Chaine(_T(""));
	int z = 0;

	pt_solution = new Solution(m_hWnd);

	for (int row = 0; row < MAX; row++)
	{
		for (int col = 0; col < MAX; col++)
		{
			::SetDlgItemTextW(m_hWnd, (IDC_EDIT1 + z), (LPWSTR)Chaine.GetBuffer());
			z++;
		}
	}

	if (pt_solution->Charger_From_a_File(m_hWnd) == TRUE)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDCANCEL)->SetWindowTextW(_T("Fin"));
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}

	if (pt_solution != 0)
	{
		delete pt_solution;
	}
}
