#pragma once
#include "time.h"
#include "resource.h"

#define MAX 9
#define MIN 3

class Solution 

{
public:
	Solution();
	Solution(HWND Curent_windows);
	virtual ~Solution();

	BOOL Charger_valeur_saisie(HWND Curent_windows);
	int Charger_From_a_File(HWND Curent_windows);

private:
	 
	void  Raz();
	BOOL  Check_input_grid();
	BOOL  Check_input_rows();
	BOOL  Check_input_a_row(int row);
	BOOL  Check_input_columns();
	BOOL  Check_input_a_column(int col);
	BOOL  Check_input_sub_squares();
	BOOL  Check_input_a_sub_square(int sub_square);
	void  Trans_sub_square(char buffer[], int sub_square);
	void  Resolve();
	BOOL  Free_cell_for_number(int number, int row, int col);
	void  Trans_sub_square_of_cell(char buffer[], int row, int col);
	BOOL  Finished_grid();
	void  Display_grille(HWND Curent_windows);
	void  Print();
	void  Charge_tableau_relation();
	void  Definition_limite(HWND Curent_windows);
	CString Current_Dir();
	BOOL  Save_Load_Data();
	BOOL  Save_File(LPTSTR File);
	BOOL  Open_File(LPTSTR File);
	BOOL  WriteFile(FILE* _File);
	CString Folder();
	CString Sepcial_Folder(int _directory_resquest);
	void  Dur_Dur();
	void  Conversion(CString chaine);
	void  Affiche_Synchro(unsigned long long __Time);
	int   tableau_de_saisie[81] = { 0 };
	
	HWND Save_Curent_windows;
	int g_test_counter;
	CString pszSource;
	FILE *pt_fichier;
	CString Start_Time, End_Time;

};

