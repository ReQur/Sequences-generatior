#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>


using namespace std;

void Selected_Text(const string word, bool flag)
{
	if (flag)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((4 << 5) | 15));
		cout << word;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	}
	else
		cout << word;
}

void switchsel(int& select, int& inf, int n)
{
	switch (_getch())
	{
	case 72:
		select--;
		if (select < 0) select = select + n;
		break;

	case 80:
		select++;
		if (select > n - 1) select = select - n;
		break;

	case 75:
		select--;
		if (select < 0) select = select + n;
		break;

	case 77:
		select++;
		if (select > n - 1) select = select - n;
		break;

	case 224:
		break;

	case 13:
		inf = 0;
		break;
	case 32:
		inf = 0;
		break;

	case 27:
		exit(0);
	default:
		cout << "wrong" << endl;
		break;
	}
}


int Selection(const string * word, int n, string quest)
{
	int i = 0, select = 0, inf = 1;


	while (inf)
	{
		system("cls");
		if (!quest.empty()) cout << quest << endl;
		for (i = 0; i < n; i++) { Selected_Text(word[i], i == select); cout << "\n"; }
		switchsel(select, inf, n);
	}

	return select;
}
