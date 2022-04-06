#include <iostream>

//#define TERMINAL_VALUE -1
//
//struct RaggedArray
//{
//	int** data = NULL;
//	int rows = NULL;
//};
//
//int askUserScan()
//{
//	int choice = 0;
//	do {
//		printf("Введите способ записи:\n1 - заполнить массив рандомно\n2 - заполнить массив из файла txt\n3 - заполнить массив из файла bin\nВыбор:");
//		scanf_s("%d", &choice);
//	} while (choice > 3 || choice < 1);
//	return choice;
//}
//int askUserSave()
//{
//	int choice = 0;
//	do {
//		printf("Введите способ сохранения:\n1 - в файл txt\n2 - в файл bin\nВыбор:");
//		scanf_s("%d", &choice);
//	} while (choice > 2 || choice < 1);
//	return choice;
//}
//
//int scanRowsSize()
//{
//	int choice = 0;
//	do {
//		printf("Введите количество строк [0;1000]:\n");
//		scanf_s("%d", &choice);
//	} while (choice > 1000 || choice < 0);
//	return choice;
//}
//int scanColsSize()
//{
//	int choice = 0;
//	static int counter = 0;
//	counter++;
//	do {
//		printf("№%d - ", counter);
//		scanf_s("%d", &choice);
//	} while (choice > 1000 || choice < 0);
//	return choice;
//}
//
//int** allocateMas(RaggedArray mas)
//{
//	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
//	printf("Введите количество столбцов [0;1000]:\n");
//	for (int i = 0; i < mas.rows; i++)
//	{
//		int cols = scanColsSize();
//		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
//		for (int j = 0; j < cols; j++)
//			mas.data[i][j] = 0;
//		mas.data[i][cols] = TERMINAL_VALUE;
//	}
//	return mas.data;
//}
//
//void fillMasRandom(RaggedArray mas)
//{
//	for (int i = 0; i < mas.rows; i++)
//		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
//			mas.data[i][j] = rand() % 100;
//}
//
//void outputMasToScreen(RaggedArray mas)
//{
//	printf("\n");
//	for (int i = 0; i < mas.rows; i++)
//	{
//		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
//			printf("%5d", mas.data[i][j]);
//		printf("\n");
//	}
//	printf("\n");
//}
//
//void fillMasFromTxtFile(const char* filename, RaggedArray mas)
//{
//	int cols;
//	FILE* f;
//	if (fopen_s(&f, filename, "r") != 0)
//		exit(1);
//
//	fscanf_s(f, "%d", &mas.rows);
//	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
//	for (int i = 0; i < mas.rows; i++)
//	{
//		fscanf_s(f, "%d", &cols);
//		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
//		mas.data[i][cols] = TERMINAL_VALUE;
//	}
//	for (int i = 0; i < mas.rows; i++)
//		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
//			fscanf_s(f, "%d", &mas.data[i][j]);
//
//	outputMasToScreen(mas);
//	
//	fclose(f);
//}
//
////void fillMasFromBinFile(const char* filename, RaggedArray mas, int& cols)
////{
////
////}
//
//
////void writeMasToTxtFile(const char* filename, RaggedArray mas)
////{
////	FILE* f;
////	if (fopen_s(&f, filename, "w") != 0)
////		exit(1);
////
////	fprintf_s(f, "%d ", cols);
////
////	for (int i = 0; i < mas.rows; i++)
////		for (int j = 0; mas.data[i][j] != TERMINAL_VALUE; j++)
////			fscanf_s(f, "%d", &mas.data[i][j]);
////
////	fclose(f);
////}
//
//void freeMas(RaggedArray mas)
//{
//	for (int i = 0; i < mas.rows; i++)
//		free(mas.data[i]);
//	free(mas.data);
//}
//
//int main()
//{
//	//3. Массив представляется указателем на вектор указателей на строки.Количество строк определяется терминальным символом.
//	//Количество элементов строки определяется терминальным символом. Память выделяется одним блоком.
//	system("chcp 1251");
//	srand(time(0));
//
//	RaggedArray mas;
//
//	switch (askUserScan())
//	{
//	case 1:
//	{
//		mas.rows = scanRowsSize();
//		mas.data = allocateMas(mas);
//		fillMasRandom(mas);
//		outputMasToScreen(mas);
//		break;
//	}
//	case 2:
//		fillMasFromTxtFile("1.txt", mas);
//		break;
//	case 3:
//		break;
//	}
//
//	switch (askUserSave())
//	{
//	case 1:
//	{
//		//writeMasToTxtFile("1.txt", mas);
//		break;
//	}
//	case 2:
//
//		break;
//	}
//
//	freeMas(mas);
//
//	return 0;
//}

/*Задание:
Массив представляется указателем на вектор указателей на строки.
Количество строк определяется терминальным символом.
Количество элементов строки определяется терминальным символом.
Память выделяется одним блоком.*/

int askUserScan()
{
	int choice = 0;
	do {
		printf("Введите способ записи:\n1 - заполнить массив рандомно\n2 - заполнить массив из файла txt\n3 - заполнить массив из файла bin\nВыбор:");
		scanf_s("%d", &choice);
	} while (choice > 3 || choice < 1);
	return choice;
}
int askUserSave()
{
	int choice = 0;
	do {
		printf("Введите способ сохранения:\n1 - в файл txt\n2 - в файл bin\nВыбор:");
		scanf_s("%d", &choice);
	} while (choice > 2 || choice < 1);
	return choice;
}

float** mallocArray(float** mas, int rows)
{
	mas = (float**)malloc(sizeof(float*) * (rows + 1));
	mas[rows] = NULL;
	return mas;
}
void mallocArrayForArray(float** mas, int rows, int cols)
{
	mas[rows] = (float*)malloc(sizeof(float) * (cols + 1));
	mas[rows][cols] = NULL;
}
void freeArray(float** mas)
{
	for (int rows = 0; mas[rows] != NULL; rows++)
		free(mas[rows]);
	free(mas);
}

int scanRowsSize()
{
	int choice = 0;
	do {
		printf("Введите количество строк [0;1000]:\n");
		scanf_s("%d", &choice);
	} while (choice > 1000 || choice < 0);
	return choice;
}
int scanColsSize()
{
	int choice = 0;
	static int counter = 0;
	counter++;
	do {
		printf("№%d - ", counter);
		scanf_s("%d", &choice);
	} while (choice > 1000 || choice < 0);
	return choice;
}

void printArray(float** mas)
{
	printf("\nМассив:\n");
	for (int rows = 0; mas[rows]!=NULL; rows++)
	{
		for (int col = 0; mas[rows][col] != NULL; col++)
			printf("%6.1f", mas[rows][col]);
		printf("\n");
	}
}

void fillArrayRandomly(float** mas)
{
	int cols;
	for (int rows = 0;mas[rows]!=NULL;rows++)
	{
		cols = scanColsSize();	
		mallocArrayForArray(mas, rows, cols);

		for (int col = 0; mas[rows][col] != NULL; col++)
			mas[rows][col] = (rand() % 2001 - 1000.0) / 10;
	}
}

int main()
{
	system("chcp 1251"); system("cls");
	srand(time(NULL));

	float** mas = NULL;

	switch (askUserScan())
	{
	case 1:
	{
		int rows = scanRowsSize();
		mas = mallocArray(mas, rows);
		fillArrayRandomly(mas);

		break;
	}
	}

	printArray(mas);



	return 0;
}

