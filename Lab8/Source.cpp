#include <iostream>

#define TERMINAL_VALUE -1

struct RaggedArray
{
	int** data = NULL;
	int rows = NULL;
};

int askUserScan()
{
	int choise = 0;
	do {
		printf("Введите способ записи:\n1 - заполнить массив рандомно\n2 - заполнить массив из файла txt\n3 - заполнить массив из файла bin\nВыбор:");
		scanf_s("%d", &choise);
	} while (choise > 3 || choise < 1);
	return choise;
}
int askUserPrint()
{
	int choise = 0;
	do {
		printf("Введите способ вывода:\n1 - в консоль\n2 - в файл txt\n3 - в файл bin\nВыбор:");
		scanf_s("%d", &choise);
	} while (choise > 3 || choise < 1);
	return choise;
}

int scanRowsSize()
{
	int choise = 0;
	do {
		printf("Введите количество строк [0;1000]:\n");
		scanf_s("%d", &choise);
	} while (choise > 1000 || choise < 0);
	return choise;
}
int scanColsSize()
{
	int choise = 0;
	static int counter = 0;
	counter++;
	do {
		printf("№%d - ", counter);
		scanf_s("%d", &choise);
	} while (choise > 1000 || choise < 0);
	return choise;
}

int** allocateMas(RaggedArray mas)
{
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	printf("Введите количество столбцов [0;1000]:\n");
	for (int i = 0; i < mas.rows; i++)
	{
		int cols = scanColsSize();
		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		for (int j = 0; j < cols; j++)
			mas.data[i][j] = 0;
		mas.data[i][cols] = TERMINAL_VALUE;
	}
	return mas.data;
}

void fillMasRandom(RaggedArray mas)
{
	for (int i = 0; i < mas.rows; i++)
		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
			mas.data[i][j] = rand() % 100;
}

void fillMasFromTxtFile(const char* filename, RaggedArray mas, int& cols)
{
	FILE* f;
	if (fopen_s(&f, filename, "r") != 0)
		exit(1);

	fscanf_s(f, "%d\n", &mas.rows);
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	for (int i = 0; i < mas.rows; i++)
	{
		fscanf_s(f, "%d", &cols);
		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		for (int j = 0; j < cols; j++)
			mas.data[i][j] = 0;
		mas.data[i][cols] = TERMINAL_VALUE;
	}
	for (int i = 0; i < mas.rows; i++)
		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
			fscanf_s(f, "%d ", &mas.data[i][j]);

	printf("\n");
	for (int i = 0; i < mas.rows; i++)
	{
		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
			printf("%5d", mas.data[i][j]);
		printf("\n");
	}

	fclose(f);
}

//void fillMasFromBinFile(const char* filename, RaggedArray mas, int& cols)
//{
//
//}

void outputMasToScreen(RaggedArray mas)
{
	printf("\n");
	for (int i = 0; i < mas.rows; i++)
	{
		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
			printf("%5d", mas.data[i][j]);
		printf("\n");
	}
}

//void writeMasToTxtFile(const char* filename, RaggedArray mas, int cols)
//{
//	FILE* f;
//	if (fopen_s(&f, filename, "w") != 0)
//		exit(1);
//
//	fprintf_s(f, "%d", cols);
//
//
//	fclose(f);
//}

void freeMas(RaggedArray mas)
{
	for (int i = 0; i < mas.rows; i++)
		free(mas.data[i]);
	free(mas.data);
}

int main()
{
	//3. Массив представляется указателем на вектор указателей на строки.Количество строк определяется терминальным символом.
	//Количество элементов строки определяется терминальным символом. Память выделяется одним блоком.
	system("chcp 1251");
	srand(time(0));

	RaggedArray mas;

	switch (askUserScan())
	{
	case 1:
	{
		mas.rows = scanRowsSize();
		mas.data = allocateMas(mas);
		fillMasRandom(mas);
		break;
	}
	case 2:
	{
		int cols;
		fillMasFromTxtFile("1.txt", mas, cols);
		break;
	}
	case 3:
		break;
	}

	switch (askUserPrint())
	{
	case 1:
		outputMasToScreen(mas);
		break;
	case 2:
		int cols;
		//writeMasToTxtFile("1.txt", mas, cols);
		break;
	}

	freeMas(mas);

	return 0;
}