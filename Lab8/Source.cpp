#include<iostream>

/*Задание:
Массив представляется указателем на вектор указателей на строки.
Количество строк определяется терминальным символом.
Количество элементов строки определяется терминальным символом.
Память выделяется одним блоком.*/

struct RaggedArray
{
	int** data = NULL;
};

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
		printf("Введите способ сохранения:\n1 - в файл txt\n2 - в файл bin\n3 - выйти\nВыбор:");
		scanf_s("%d", &choice);
	} while (choice > 3 || choice < 1);
	return choice;
}

int scanRowsSize()
{
	int choice = 0;
	do {
		printf("Введите количество строк (0;1000]:\n");
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

int** allocateArray(RaggedArray mas)
{
	int rows = scanRowsSize();
	mas.data = (int**)malloc(sizeof(int*) * (rows + 1));
	mas.data[rows] = NULL;

	printf("Введите количество столбцов (0;1000]:\n");
	for (int i = 0; mas.data[i] != NULL; i++)
	{
		int cols = scanColsSize();
		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		mas.data[i][cols] = NULL;
	}
	return mas.data;
}

void fillArrayRandom(RaggedArray mas)
{
	for (int i = 0; mas.data[i] != NULL; i++)
		for (int j = 0; mas.data[i][j] != NULL; j++)
			mas.data[i][j] = rand() % 501;
}

void fillArrayFromTxtFile(const char* filename, RaggedArray& mas)
{
	int rows = 0, cols = 0;

	FILE* f;
	if (fopen_s(&f, filename, "r") != 0) exit(1);

	fscanf_s(f, "%d", &rows);
	mas.data = (int**)malloc(sizeof(int*) * (rows + 1));
	mas.data[rows] = NULL;

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		fscanf_s(f, "%d", &cols);

		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		mas.data[i][cols] = NULL;

		for (int j = 0; mas.data[i][j] != NULL; j++)
			fscanf_s(f, "%d", &mas.data[i][j]);
	}

	fclose(f);
}

void writeArrayToTxtFile(const char* filename, RaggedArray mas)
{
	FILE* f;
	if (fopen_s(&f, filename, "w") != 0) exit(1);

	int rows = 0;
	while (mas.data[rows] != NULL) rows++;

	fprintf(f, "%d\n", rows);

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		int cols = 0;
		while (mas.data[i][cols] != NULL) cols++;
		fprintf(f, "%d ", cols);
		for (int j = 0; mas.data[i][j] != NULL; j++)
			fprintf(f, "%d ", mas.data[i][j]);
		fprintf(f, "\n");
	}

	fclose(f);
}

void fillArrayFromBinFile(const char* filename, RaggedArray& mas)
{
	int rows = 0, cols = 0;

	FILE* f;
	if (fopen_s(&f, filename, "rb") != 0) exit(1);

	fread(&rows, sizeof(int), 1, f);
	mas.data = (int**)malloc(sizeof(int*) * (rows + 1));
	mas.data[rows] = NULL;

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		fread(&cols, sizeof(int), 1, f);
		mas.data[i] = (int*)malloc(sizeof(int) * (cols + 1));
		mas.data[i][cols] = NULL;

		fread(mas.data[i], sizeof(int), cols, f);
	}

	fclose(f);
}

void writeArrayToBinFile(const char* filename, RaggedArray mas)
{
	int rows = 0;
	FILE* f;
	if (fopen_s(&f, filename, "wb") != 0) exit(1);

	while (mas.data[rows] != NULL) rows++;

	fwrite(&rows, sizeof(int), 1, f);

	for (int i = 0; mas.data[i] != NULL; i++)
	{
		int cols = 0;
		while (mas.data[i][cols] != NULL) cols++;
		fwrite(&cols, sizeof(int), 1, f);
		fwrite(mas.data[i], sizeof(int), cols, f);
	}

	fclose(f);
}

void outputArrayToScreen(RaggedArray mas)
{
	printf("\n");
	for (int i = 0; mas.data[i] != NULL; i++)
	{
		for (int j = 0; mas.data[i][j] != NULL; j++)
			printf("%5d", mas.data[i][j]);
		printf("\n");
	}
	printf("\n");
}

void freeArray(RaggedArray mas)
{
	for (int i = 0; mas.data[i] != NULL; i++)
		free(mas.data[i]);
	free(mas.data);
}

int main()
{
	system("chcp 1251"); system("cls");
	srand(time(0));

	RaggedArray mas;
	
	char filenameTxt[] = "1.txt";
	char filenameBin[] = "2.bin";

	switch (askUserScan())
	{
	case 1:
		mas.data = allocateArray(mas);
		fillArrayRandom(mas);
		break;
	case 2:
		fillArrayFromTxtFile(filenameTxt, mas);
		break;
	case 3:
		fillArrayFromBinFile(filenameBin, mas);
		break;
	}

	outputArrayToScreen(mas);

	switch (askUserSave())
	{
	case 1:
		writeArrayToTxtFile(filenameTxt, mas);
		break;
	case 2:
		writeArrayToBinFile(filenameBin, mas);
		break;
	case 3:
		exit(0);
	}

	freeArray(mas);

	return 0;
}