
#pragma once
#include "stdafx.h"
#include "time.h"
#include "resource.h"
#include "Calcul_temps.h"
#include "Solution.h"

#pragma warning(disable: 4996)


#pragma comment(linker, "/STACK:2000000")
#pragma comment(linker, "/HEAP:2000000")

int grid[MAX][MAX];

Solution::Solution()
{
}

void Solution::Charge_tableau_relation()
{
	for (int i = 0; i < (sizeof(tableau_de_saisie) / sizeof(int)); i++)
	{
		tableau_de_saisie[i] = (IDC_EDIT1 + i);
	}
}

void Solution::Definition_limite(HWND Curent_windows)
{
	CEdit *pt_edit_combo;

	for (int i = 0; i <(sizeof(tableau_de_saisie) / sizeof(int)); i++)
	{
		pt_edit_combo = (CEdit *)GetDlgItem(Save_Curent_windows, tableau_de_saisie[i]);
		ASSERT(IsWindow((HWND)pt_edit_combo) != 0);
		::SendMessage((HWND)pt_edit_combo, EM_SETLIMITTEXT, 1, 0);
	}
}


BOOL Solution::Open_File(LPTSTR File)
{
	CString OpenFilter;
	CString local_File(File);

	OpenFilter = "Text File (*.txt)|*.txt|";
	OpenFilter += "All Files (*.*)|*.*||";

	CFileDialog FileOpenDialog(
		TRUE,
		NULL,
		local_File,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
		OpenFilter,                       // filter
		AfxGetMainWnd());               // the parent window 
	CString result = Current_Dir();

	FileOpenDialog.m_ofn.lpstrInitialDir = result;

	FileOpenDialog.m_ofn.lpstrTitle = _T("Sudoku File");

	if (FileOpenDialog.DoModal() == IDOK)
	{
		pszSource = FileOpenDialog.m_ofn.lpstrFile;
		return TRUE;
	}

	return FALSE;

}

BOOL Solution::Save_File(LPTSTR File)
{
	CString OpenFilter;
	CString local_File(File);

	OpenFilter = "Text File (*.txt)|*.txt|";
	OpenFilter += "All Files (*.*)|*.*||";

	CFileDialog FileOpenDialog(
		FALSE,
		NULL,
		local_File,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
		OpenFilter,                       // filter
		AfxGetMainWnd());               // the parent window 

	CString result = Current_Dir();

	FileOpenDialog.m_ofn.lpstrInitialDir = result;

	FileOpenDialog.m_ofn.lpstrTitle = _T("Sudoku File");

	if (FileOpenDialog.DoModal() == IDOK)
	{
		pszSource = FileOpenDialog.m_ofn.lpstrFile;
		return TRUE;
	}

	return FALSE;

}


CString Solution::Current_Dir()
{
	CString Chaine;

	::GetCurrentDirectory(MAX_PATH, Chaine.GetBuffer(MAX_PATH));
	Chaine.ReleaseBuffer();
	return (Chaine);

}

int  Solution::Charger_From_a_File(HWND Curent_windows)
{
	int result = TRUE;
	int valeur = 0;
	FILE *pt_fichier;
	char buffer[MAX_PATH];

	// mise à zéro de la grille d'origine
	Raz();
	Charge_tableau_relation();
	Definition_limite(Curent_windows);

	if (Open_File(_T("Sudoku_input.txt")) == TRUE)
	{

	 pt_fichier = _wfopen(pszSource.GetBuffer(), _T("rt"));

	 if (pt_fichier != 0)
	  {
	
	   for (int row = 0; row < MAX; row++)
	    {

		fgets(&buffer[0], MAX_PATH, pt_fichier);

		for (int data = 0; data < MAX; data++)
		  {
			
			valeur = atoi(&buffer[data * 2]);
			if (valeur > 0)
			{
			grid[row][data] = valeur;
			}
			else
			{
			 grid[row][data] = 0;
			}
		  }

	    }

	   fclose(pt_fichier);

	  }
	 else
	 {
		 result = FALSE;
	 }

	}

	// On vérifie le grille 
	if (!Check_input_grid())
	{
		result = FALSE;
	}

	::SetDlgItemTextW(Save_Curent_windows, IDC_STATIC, _T(""));
	// Et on Affiche
	Display_grille(Curent_windows);
	
	return result;

}

void Solution::Dur_Dur()
{

	Calcul_temps * pt_temps = new Calcul_temps;
	pt_temps->Start_time();

	Resolve();

	pt_temps->Stop_time();
	Affiche_Synchro( pt_temps->Read_time());

	delete pt_temps;

}

void Solution::Affiche_Synchro(uint64_t __Time)
{	
	CString Affiche = _T("");
	if (__Time > 0)
	{
		Affiche.Format(_T("Temps de résolution: %ld ms"), (long) __Time);
	}
	else
	{
		Affiche = _T("Temps de résolution < 1 ms");
	}
	
	::SetDlgItemTextW(Save_Curent_windows, IDC_STATIC3, (LPWSTR)Affiche.GetBuffer());
	
	// AfxMessageBox(Affiche, MB_OK);
}


CString Solution::Sepcial_Folder(int _directory_resquest)
{
	TCHAR szPath[MAX_PATH];

	SHGetFolderPath(NULL, _directory_resquest, NULL, 0, szPath);

	CString chaine(szPath);
	return (chaine);

}

CString Solution::Folder()
{
	CString Back_slash = _T("\\");
	CString Output_diectory = Sepcial_Folder(CSIDL_PERSONAL) + Back_slash;
	return (Output_diectory);
}

void  Solution::Print()
{

	fprintf(pt_fichier, "Nombre d'essais : %d\n\n", g_test_counter);
	CString chaine;
	chaine.Format(_T("Nombre d'essais : %d"),g_test_counter);

	// IDC_STATIC
	::SetDlgItemTextW(Save_Curent_windows, IDC_STATIC, (LPWSTR)chaine.GetBuffer()); 

	for (int row = 0; row < MAX; row++)
	{
		for (int col = 0; col < MAX; col++)
		{

			fprintf(pt_fichier, "%d ", grid[row][col]);

		}

		fprintf(pt_fichier, "\n");
	}

	fprintf(pt_fichier, "\n\n\n");
}



Solution::Solution(HWND Curent_windows)
{		

	// Sauvegarde de la fentre d'appel
	Save_Curent_windows = Curent_windows;
	ASSERT(Curent_windows != 0);

	CString Out_dir = Folder() + "resultat_grille_Sudoku.txt"; // là là
	pt_fichier = _wfopen(Out_dir, _T("w+t"));

	// Charge le tableau de relation 
	Charge_tableau_relation();
	
	// Définition des limtes etc...
	Definition_limite(Curent_windows);
	g_test_counter = 0;


}

Solution::~Solution()
{

	fclose(pt_fichier);

}

BOOL  Solution::Charger_valeur_saisie(HWND Curent_windows)
{
	BOOL result = TRUE;
	int  z = 0;
	int valeur_lue= 0;
	char Car_courr = 0x00;
	CString Valeur;

	ASSERT(IsWindow(Curent_windows) != 0);

	// mise à zéro de la grille d'origine
	Raz();

	for (int row = 0; row < MAX; row++)
	{
		for (int col = 0; col < MAX; col++)
		{
		  ::GetDlgItemTextW(Curent_windows,tableau_de_saisie[z], (LPWSTR)Valeur.GetBuffer(255),255);
		  Valeur.ReleaseBuffer();
		  valeur_lue = 0;
		  valeur_lue = atoi((char *)Valeur.GetBuffer());	
		  z++;
		  if ( (valeur_lue >= 1) && (valeur_lue < 10 )   )
		  {

		    grid[row][col] = valeur_lue;

		  }
		  else
		  {
			  grid[row][col] = 0;

		  }
		}
	}

	// Savegarde de la configuration d'origine
	// 
	Save_Load_Data();

	// On vérifie le grille 
	 if (!Check_input_grid())
	 {
		result = FALSE;
	  }
	
	 // Allez on bosse dur
	 Dur_Dur();

	 Print();

	// Et on Affiche
	 Display_grille(Curent_windows);

	 return result;
}


BOOL Solution::Save_Load_Data()
{

	if (Save_File(_T("Sudoku_imput.txt")) == TRUE)
	{
		FILE* pt_Out;

		pt_Out = _wfopen(pszSource.GetBuffer(), _T("wt"));
		if (pt_Out != 0)
		{ 
		 WriteFile(pt_Out);
		 fclose(pt_Out);
		 return (TRUE);
		}
	}
	return (FALSE);
}

BOOL Solution::WriteFile(FILE* _File)
{

	for (int row = 0; row < MAX; row++)
	{
		for (int col = 0; col < MAX; col++)
		{

			fprintf(_File, "%d ", grid[row][col]);

		}

		fprintf(_File, "\n");
	}

	fprintf(_File, "\n");
	return (TRUE);
}


void Solution::Display_grille(HWND Curent_windows)
{	
	int z = 0;
	CString Chaine;

	ASSERT(IsWindow(Curent_windows) != 0);

	for (int row = 0; row < MAX; row++)
	{
		for (int col = 0; col < MAX; col++)
		{
			Chaine.Format(_T("%d"), grid[row][col]);
			if (grid[row][col] > 0)
			{		
			 ::SetDlgItemTextW(Curent_windows, tableau_de_saisie[z], (LPWSTR)Chaine.GetBuffer());
			}else
			{
			 ::SetDlgItemTextW(Curent_windows, tableau_de_saisie[z],_T(""));
			}
			z++;
		}
	}

}

BOOL Solution::Check_input_grid()
{
	/* Check whether any duplicate throughout the grid. */
	int result = TRUE;

	if (!Check_input_rows()) result = FALSE;
	if (!Check_input_columns()) result = FALSE;
	if (!Check_input_sub_squares()) result = FALSE;

	return result;
}

BOOL Solution::Check_input_rows()
{
	/* Checks if no duplicate into the rows. */
	int row;

	int result = TRUE;
	for (row = 0; row < MAX; row++)
	{
		if (!Check_input_a_row(row))
		{
			result = FALSE;
			break;
		}
	}/* end for */

	return result;
}

BOOL Solution::Check_input_a_row(int row)
{
	/* Checks if no duplicate into the row. */
	int i, j;

	for (i = 0; i < MAX - 1; i++)
	{
		if (grid[row][i] == 0) continue;
		for (j = i + 1; j < MAX; j++) {
			if (grid[row][i] == grid[row][j])
			{

				CString chaine;
				chaine.Format(_T("Erreur ligne %d: nombre egaux"), row + 1);
				AfxMessageBox(chaine,MB_OK);
				return FALSE;

			}/* end if */
		}/* end for j */
	}/* end for i */

	return TRUE;
}

BOOL Solution::Check_input_columns()
{
	/* Checks if no duplicate into the columns. */
	int col;
	int result = TRUE;

	for (col = 0; col < MAX; col++)
	{

		if (!Check_input_a_column(col))
		{
			result = FALSE;
			break;
		}

	}/* end for */

	return result;
}

BOOL Solution::Check_input_a_column(int col)
{
	/* Checks if no duplicate into the column. */
	int i, j;
	for (i = 0; i < MAX - 1; i++)
	{
		if (grid[i][col] == 0) continue;

		for (j = i + 1; j < MAX; j++)
		{

			if (grid[i][col] == grid[j][col])
			{

				CString chaine;
				chaine.Format(_T("Erreur colonne %d: nombre egaux"),col + 1);
				AfxMessageBox(chaine, MB_OK);
				return FALSE;

			}/* end if */
		}/* end for j */
	}/* end for i */

	return TRUE;
}

BOOL Solution::Check_input_sub_squares()
{
	/* Checks if no duplicate into the sub-squares of 3 x 3. */
	int sub_square;
	int result = TRUE;

	for (sub_square = 0; sub_square < MAX; sub_square++)
	{

		if (!Check_input_a_sub_square(sub_square))
		{ 
			result = FALSE;
			break;
		}
	}/* end for */
	return result;
}

BOOL Solution::Check_input_a_sub_square(int sub_square)
{
	/* Checks if no duplicate into the sub-square of 3 x 3. */
	char buffer[MAX + 10];
	int i, j;

	Trans_sub_square(buffer, sub_square);

	for (i = 0; i < MAX - 1; i++)
	{
		if (buffer[i] == 0) continue;

		for (j = i + 1; j < MAX; j++)
		{
			if (buffer[i] == buffer[j])
			{
				CString chaine;
				chaine.Format(_T("Erreur sous carré %d: nombre egaux"), sub_square + 1);
				AfxMessageBox(chaine, MB_OK);
				return FALSE;

			}/* end if */
		}/* end for j */
	}/* end for i */

	return TRUE;
}

void Solution::Trans_sub_square(char buffer[], int sub_square)
{
	/* Transfer the sub-square of 3 x 3 into a one-dimensional array. */
	int i, j, x, y, z;

	x = (((sub_square) % MIN)*MIN);
	y = (((sub_square + MIN) / MIN)*MIN) - MIN;
	z = 0;

	for (j = y; j < y + MIN; j++)
	{

		for (i = x; i < x + MIN; i++)
		{

			buffer[z++] = grid[j][i];

		}/* end for i */

	}/* end for j */
}

void Solution::Raz()
{

  // Mise à zéro de la grille
  for (int row = 0; row < MAX; row++)
  {
	  for (int col = 0; col < MAX; col++)
	  {
		  grid[row][col] = 0;
	  }
  }
  ::SetDlgItemTextW(Save_Curent_windows, IDC_STATIC, _T(""));
}

void Solution::Resolve()
{
	
	/* Attention, recursive function... */
	int row = 0;
	int col = 0;
	int number = 0;
	int buffer_number = 0 ;

	for (row = 0; row < MAX; row++)
	{
		for (col = 0; col < MAX; col++)
		{
			if (grid[row][col]) continue;

			for (number = 1; number <= MAX; number++)
			{

				if (!Free_cell_for_number(number, row, col)) continue;
				buffer_number = grid[row][col]; 
				g_test_counter++;
				grid[row][col] = number;
				Resolve();
				if (Finished_grid() == TRUE ) return;
				/* To see all the solutions of the grids with multiple solutions,
				switch the line above as a comment and remove the comment command
				of the line below.
				*/
				grid[row][col] = buffer_number;

			}/* end for number */
			return;

		}/* end for col */
	}/* end for row */

	return;

}


void Solution::Conversion(CString chaine)
{
	const size_t newsizew = (chaine.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, chaine, _TRUNCATE);
	fprintf(pt_fichier, "%s\n", nstringw);
	delete nstringw;

}

BOOL Solution::Free_cell_for_number(int number, int row, int col)
{
	/* Test if the number is already in the line, or the column,
	or the sub-square of 3 X 3 afferent at the cell pointed to by line and column. */

	char buffer[MAX + 20] = { 0 };
	int i= 0;

	/* If the number is used in the line return FALSE */
	for (i = 0; i < MAX; i++)

	{
		if (grid[row][i] == number) return(FALSE); /* If the number is used in the column return FALSE */
	}

	for (i = 0; i < MAX; i++)
	{
		if (grid[i][col] == number) return(FALSE); /* If the number is used in the sub-square of 3 X 3 return FALSE */
	}

	Trans_sub_square_of_cell(buffer, row, col);

	for (i = 0; i < MAX; i++)
	{
		if (buffer[i] == number) return (FALSE);   /* whereby the number is available for the cell, return TRUE. */
	}
	return(TRUE);
}

void Solution::Trans_sub_square_of_cell(char buffer[], int row, int col)
/* Transfer the sub-square of 3 x 3 of the cell into a one-dimensional array. */
{
	int i, j, k = 0;

	while ((row % MIN) != 0) row--;
	while ((col % MIN) != 0) col--;

	k = 0;

	for (j = row; j < row + MIN; j++)
	{

		for (i = col; i < col + MIN; i++)
		{

			buffer[++k] = grid[j][i];

		}/* end for i */

	}/* end for j */

}/* end trans_sub_square_of_cell */

BOOL Solution::Finished_grid()
/* Test if the grid is finished. Return TRUE if grid completed, otherwise return FALSE.
Begins with the end of the grid, this one being completed by its beginning. */
{
	int row, col = 0;

	for (row = MAX - 1; row >= 0; row--)
	{

		for (col = MAX - 1; col >= 0; col--)
		{

			if (grid[row][col] == 0)
			{
				return FALSE;
			}

		}/* end for col */
	}/* end for row */

	return TRUE;
}