#include <iostream>

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

float** mallocArray(float** mas)
{
	mas = (float**)malloc(sizeof(float*));
	if (mas == NULL)
	{
		printf("Неудалось выделить память!");
		exit(1);
	}
	return mas;
}
float** reallocArray(float** mas, int rows)
{
	mas = (float**)realloc(mas, sizeof(float*) * (rows + 1));
	if (mas == NULL)
	{
		printf("Неудалось выделить память!");
		exit(1);
	}
	mas[rows] = NULL;
	return mas;
}
void mallocArrayForArray(float** mas, int rows, int cols)
{
	mas[rows] = (float*)malloc(sizeof(float) * (cols + 1));
	if (mas[rows] == NULL)
	{
		printf("Неудалось выделить память!");
		exit(1);
	}
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
	printf("\n");
}

void fillArrayRandomly(float** mas)
{
	int cols;
	for (int rows = 0; mas[rows] != NULL; rows++)
	{
		cols = scanColsSize();	
		mallocArrayForArray(mas, rows, cols);

		for (int col = 0; mas[rows][col] != NULL; col++)
			mas[rows][col] = (rand() % 2001 - 1000.0) / 10;
	}
}

float** fillArrayFromTxtFile(float** mas, char* filename)
{
	FILE* f;
	if (fopen_s(&f, filename, "r") != NULL)
		exit(1);

	int rows = 0, cols = 0;
	int pos = ftell(f);
	while (!feof(f))
	{
		char currentChar = fgetc(f);
		if (currentChar == '.')
			cols++;
		if (currentChar == '\n')
		{
			mas = reallocArray(mas, rows + 1);
			mas[rows] = (float*)malloc(sizeof(float) * (cols + 1));

			fseek(f, pos, SEEK_SET);
			for (int col = 0; col < cols; col++)
				fscanf_s(f, "%f", &mas[rows][col]);
			fscanf_s(f, "\n");
			pos = ftell(f);

			mas[rows][cols] = NULL;
			cols = 0;
			rows++;
		}
	}
	fclose(f);

	return mas;
}

float** fillArrayFromBinFile(float** mas, char* filename)
{
	FILE* f;
	if (fopen_s(&f, filename, "rb") != NULL)
		exit(1);

	int rows = 0, cols = 0;
	mas = reallocArray(mas, rows);
	float value;
	while (!feof(f))
	{
		fread(&value, sizeof(float), 1, f);
		if (value == NULL)
		{
			rows++;
			mas = reallocArray(mas, rows);
			cols = 0;
		}
		else
		{
			mas[rows] = (float*)realloc(mas[rows], sizeof(float) * (cols + 2));
			mas[rows][cols++] = value;
			mas[rows][cols] = NULL;
		}
	}
	return mas;
}

void writeArrayToTxtFile(float** mas, char* filename)
{
	FILE* f;
	if (fopen_s(&f, filename, "w") != NULL)
		exit(1);

	for (int row = 0; mas[row] != NULL; row++)
	{
		for (int col = 0; mas[row][col] != NULL; col++)
			fprintf(f, "%6.1f", mas[row][col]);
		fprintf(f, "\n");
	}
}

void writeArrayToBinFile(float** mas, char* filename)
{
	FILE* f;
	if (fopen_s(&f, filename, "wb") != NULL)
		exit(1);
	
	for (int row = 0; mas[row] != NULL; row++)
	{
		int col = 0;
		while (mas[row][col] != NULL)
			fwrite(&mas[row][col++], sizeof(float), 1, f);
		fwrite(&mas[row][col], sizeof(float), 1, f);
	}
}

int main()
{
	system("chcp 1251"); system("cls");
	srand(time(NULL));

	float** mas = NULL;
	mas = mallocArray(mas);
	char filenameTxt[] = "1.txt";
	char filenameBin[] = "2.bin";

	switch (askUserScan())
	{
	case 1:
	{
		int rows = scanRowsSize();
		mas = reallocArray(mas, rows);
		fillArrayRandomly(mas);
		break;
	}
	case 2:
	{
		mas = fillArrayFromTxtFile(mas, filenameTxt);
		break;
	}
	case 3:
	{
		mas = fillArrayFromBinFile(mas, filenameBin);
		break;
	}
	}

	printArray(mas);

	switch (askUserSave())
	{
	case 1:
		writeArrayToTxtFile(mas, filenameTxt);
		break;
	case 2:
		writeArrayToBinFile(mas, filenameBin);
		break;
	}

	freeArray(mas);

	return 0;
}