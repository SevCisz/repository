#include <locale>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

void setColor(char* printChar, int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cbInfo;
	GetConsoleScreenBufferInfo(hConsole, &cbInfo);
	int originalColor = cbInfo.wAttributes;

	SetConsoleTextAttribute(hConsole, color);
	printf("%s", printChar);
	SetConsoleTextAttribute(hConsole, originalColor);
}

struct fieldChess
{
	//color w/g DOS
	int color;
	//Nazwa figury
	char value;
	//Czy to miejsce to figura czy pusto
	bool isEmpty;
	//Czy jest zaznaczony
	bool selected;
};

fieldChess** initTable() {

	fieldChess** tab1;
	tab1 = (struct fieldChess**) malloc(8 * sizeof(struct fieldChess*));
	
	for (int i = 0; i < 8; i++)
		tab1[i] = (struct fieldChess*)malloc(8 * sizeof(struct fieldChess));

	//Czyszczenie szachownicy z losowych znaków w pamięci
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			tab1[i][j].color = 0;
			tab1[i][j].value = ' ';
			tab1[i][j].isEmpty = false;
			tab1[i][j].selected = false;
		}
	}

	//Umieszczenie czarnych figur
	tab1[0][0].value = 'W';
	tab1[0][1].value = 'K';
	tab1[0][2].value = 'S';
	tab1[0][3].value = 'Q';
	tab1[0][4].value = 'H';
	tab1[0][5].value = 'S';
	tab1[0][6].value = 'K';
	tab1[0][7].value = 'W';

	tab1[0][0].color = 0;
	tab1[0][1].color = 0;
	tab1[0][2].color = 0;
	tab1[0][3].color = 0;
	tab1[0][4].color = 0;
	tab1[0][5].color = 0;
	tab1[0][6].color = 0;
	tab1[0][7].color = 0;

	tab1[0][0].isEmpty = false;
	tab1[0][1].isEmpty = false;
	tab1[0][2].isEmpty = false;
	tab1[0][3].isEmpty = false;
	tab1[0][4].isEmpty = false;
	tab1[0][5].isEmpty = false;
	tab1[0][6].isEmpty = false;
	tab1[0][7].isEmpty = false;

	//Umieszczenie czarnych pionków
	for (int i = 0; i < 8; i++)
	{
		tab1[1][i].color = 0;
		tab1[1][i].value = 'P';
		tab1[1][i].isEmpty = false;
	}
	//======================================================

	//Umieszczenie białych figur
	tab1[7][0].value = 'W';
	tab1[7][1].value = 'K';
	tab1[7][2].value = 'S';
	tab1[7][3].value = 'Q';
	tab1[7][4].value = 'H';
	tab1[7][5].value = 'S';
	tab1[7][6].value = 'K';
	tab1[7][7].value = 'W';

	tab1[7][0].color = 13;
	tab1[7][1].color = 13;
	tab1[7][2].color = 13;
	tab1[7][3].color = 13;
	tab1[7][4].color = 13;
	tab1[7][5].color = 13;
	tab1[7][6].color = 13;
	tab1[7][7].color = 13;

	tab1[7][0].isEmpty = false;
	tab1[7][1].isEmpty = false;
	tab1[7][2].isEmpty = false;
	tab1[7][3].isEmpty = false;
	tab1[7][4].isEmpty = false;
	tab1[7][5].isEmpty = false;
	tab1[7][6].isEmpty = false;
	tab1[7][7].isEmpty = false;

	//Umieszczenie białych pionków
	for (int i = 0; i < 8; i++)
	{
		tab1[6][i].color = 13;
		tab1[6][i].value = 'P';
		tab1[6][i].isEmpty = false;
	}

	return tab1;
}

void printTable(fieldChess** tab1, char selectedX, int selectedY) {
	int labelA[] = { 8,7,6,5,4,3,2,1};
	int selX = 8 - (selectedX - 97);
	int selY = 8 - (selectedY );
	
	for (int i = 0; i < 8; ++i)
	{
		//Opis pionowy w/g odwróconej tablicy numerków
		printf("%d", labelA[i]);
		for (int j = 0; j < 8; ++j)
		{
			//Czy selected ? - jeśli tak to kwadrat na zielono !
			if (selY == i && selX == j) {
				setColor(&tab1[i][j].value, 10 << 4 | 1);
			}
			//Jeśli nie jest selected, to rysuj szachownicę biało-szarą
			else {
				if ((i % 2) == 0)
				{
					if ((j % 2) == 0) {
						setColor(&tab1[i][j].value, 15 << 4 | tab1[i][j].color);
					}
					else {
						setColor(&tab1[i][j].value, 7 << 4 | tab1[i][j].color);
					}
				}
				else
				{
					if ((j % 2) == 0) {
						setColor(&tab1[i][j].value, 7 << 4 | tab1[i][j].color);
					}
					else {
						setColor(&tab1[i][j].value, 15 << 4 | tab1[i][j].color);
					}
				}

			}
		}
		printf("\n");
	}

	//Opis poziomy
	printf(" ABCDEFGH");
}

bool CanGo(fieldChess** tab1, char startPosX, int startPosY, char destPosX, int destPosY) {
	
	int labelA[] = { 8,7,6,5,4,3,2,1 };
	int startX = 8 - (startPosX - 97);
	int startY = 8 - (startPosY);

	int destX = 8 - (destPosX - 97);
	int destY = 8 - (destPosY);

	bool results = false;

	//Czy to pionek chce ruszyć ?
	if (tab1[startY][startX].value == 'P')
	{
		//Czy 1 krok spełniony ponieważ pionki ruszają do góry ?
		if (startX == destX)
		{
			//Czy to jest skok o 1 pole
			if ((startY - 1) == destY)
			{
				//TAK
				return true;
			}
			//Czy to jest skok o 2 pola
			else if((startY + 2 == destY) && destY < 3) {
				//NIE
				//Czy pomiędzy skokiem o 2 pola jest miejsce zajęte
				if (tab1[destY+1][destX].isEmpty)
				{
					return false;
				}

			}
			else {
				return false;
			}
		}
	}
	else {
		//Brak obsługi
	}
}

fieldChess** move(fieldChess** tab1, char startPosX, int startPosY, char destPosX, int destPosY) {
	int startX = 8 - (startPosX - 97);
	int startY = 8 - (startPosY);

	int destX = 8 - (destPosX - 97);
	int destY = 8 - (destPosY);
	
	tab1[destY][destX].color = tab1[startY][startX].color;
	tab1[destY][destX].value = tab1[startY][startX].value;
	tab1[destY][destX].isEmpty = tab1[startY][startX].isEmpty;
	tab1[destY][destX].selected = tab1[startY][startX].selected;

	tab1[startY][startX].value = ' ';
	tab1[startY][startX].selected = false;
	tab1[startY][startX].color = 0;

	return tab1;
}


int main()
{
	setlocale(LC_ALL, "");
	struct fieldChess** tableMap = initTable();
	printTable(tableMap, ' ', 0);
	printf("\n\n");

	Beep(750, 300);

	//unsigned char b, f;

	//for (b = 0; b < 16; b++)
	//{
	//	for (f = 0; f < 16; f++)
	//	{
	//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), b << 4 | f);
	//		printf("%.2X", b << 4 | f);
	//	}
	//	printf("\n");
	//}

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

	char startPosX = ' ';
	int startPosY = 0;

	char destPosX = ' ';
	int destPosY = 0;

	printf("Podaj pozycję X pionka, którym chcesz ruszyć: ");
	scanf_s("%c", &startPosX);
	printf("Podaj pozycję Y pionka, którym chcesz ruszyć: ");
	scanf_s("%d", &startPosY);

	system("@cls||clear");
	printTable(tableMap, startPosX, startPosY);
	printf("\n\n");

	Beep(300, 200);

	//Myk aby wyczyścic bufor, ponieważ pamięta jakieś znaki CR lub LF po ostatnio wprowadzonej cyfrze
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}

	printf("Podaj pozycję X docelowego ruchu: ");
	scanf_s("%c", &destPosX);
	printf("Podaj pozycję Y docelowego ruchu: ");
	scanf_s("%d", &destPosY);

	system("@cls||clear");
	printTable(tableMap, destPosX, destPosY);
	printf("\n\n");

	Beep(750, 200);
	Sleep(1);
	Beep(750, 200);
	
	Sleep(1);
	system("@cls||clear");
	printTable(tableMap, ' ', 0);
	printf("\n\n");

	while ((c = getchar()) != '\n' && c != EOF) {}


	if (CanGo(tableMap, startPosX, startPosY, destPosX, destPosY)) {
		system("@cls||clear");
		printTable(move(tableMap, startPosX, startPosY, destPosX, destPosY), destPosX, destPosY);
	}
	else {
		setColor((char*)"Ruch niedozwolony !", 10 << 4 | 1);
	}

	free(tableMap);

	return 0;
}
