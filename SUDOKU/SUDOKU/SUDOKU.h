
// SUDOKU.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux
#include "Solution.h"

// CSUDOKUApp :
// Consultez SUDOKU.cpp pour l'implémentation de cette classe
//

class CSUDOKUApp : public CWinApp
{
public:
	CSUDOKUApp();


// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CSUDOKUApp theApp;