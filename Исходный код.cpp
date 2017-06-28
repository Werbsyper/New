#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <Windows.h>
#define N 15

int Search();
void Generation();
void Input();
int vaves(int*);
int path(int,int);

int last_vave=1, size, field[N][N]={0}, finish[2], field_2[N][N]={0};


int main()
{
	int  choose, res;	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_ALL, "rus");
	printf("Условные обозначения:\n");
	printf("0-Пустая ячейка\n-1-Шарик\n-255-Начало пути\n-256-Конец пути\n");
	printf("Координаты ячеек нумеруются следующим образом:\nПервая координата-строка\nВторая координата-столбец\nНумерация начинается с нуля");
	puts("\nКак создать поле?\n 1-Сгенерировать\n 2-Ввод\n");
	printf("Выберите способ создания поля:");
	scanf("%i",&choose);
	while(choose!=1&&choose!=2){
	printf("Некорректно, введите заново:");
	scanf("%i",&choose);}
	switch(choose){
	case 1:Generation();break;
	case 2:Input();break;}
	res=Search();
	if(res==1){
		printf("Такой путь построить невозможно!\n");
		return 0;}
	puts("Кратчайший путь построен!");
	printf("Длинна данного пути: %i",last_vave+1);
	for(int i=0;i<size;i++){
		printf("\n");
		for(int j=0;j<size;j++){
			if(field_2[i][j]>0||field_2[i][j]==-255||field_2[i][j]==-256){
			SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 10));
			printf(" %4i",field_2[i][j]);
			SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 7));}
			else
			printf(" %4i",field_2[i][j]);}}
	puts("");
	return 0;
}
void Generation()
{
	int flag=0;
	srand(time(NULL));
	printf("Введите длинну стороны поля(2-15):");
	scanf("%i",&size);
	while(size<=1||size>15){
		printf("Ошибка, введите корректную  длинну стороны поля(2-15):");
		scanf("%i",&size);}
	for(int i=0;i<size;i=i++){
		for(int j=0;j<size;j=j++){
			field[i][j]=rand()%2-1;
		}}
	puts("Сгенерированое поле:");
	for(int i=0;i<size;i++){
		printf("\n");
		for(int j=0;j<size;j++){
			printf(" %3i",field[i][j]);}}
	printf("\n");
}
void Input()
{
	int chosen[2];
	printf("Введите длинну стороны поля(2-15):");
	scanf("%i",&size);
	while(size<=1||size>15){
		printf("Ошибка, введите корректную  длинну стороны поля(2-15):");
		scanf("%i",&size);}
	while(1){
		printf("\nВведите координаты ячейки поля в которую необходимо положить шарик\n(конец ввода -1):");
		scanf("%i%i",&chosen[0],&chosen[1]);
		while(chosen[0]>=size||chosen[1]>=size){
			printf("Некорректная координата, введите корректную:");
			scanf("%i%i",&chosen[0],&chosen[1]);}
		if(chosen[0]==-1||chosen[1]==-1){
			puts("Вы завершили ввод, конечный вариант поля:");
			for(int i=0;i<size;i++){
				printf("\n");
				for(int j=0;j<size;j++){
					printf(" %3i",field[i][j]);}}
			printf("\n");
			break;}
		field[chosen[0]][chosen[1]]=-1;
		puts("Созданое  поле:");
		for(int i=0;i<size;i++){
				printf("\n");
				for(int j=0;j<size;j++){
					printf(" %3i",field[i][j]);}}}
		
}
int Search()
{
	int  work_position1[2], work_position2[2], res;
	printf("\nВиберите шарик для перемещения:");
	scanf("%i%i",&work_position1[0],&work_position1[1]);
	while(field[work_position1[0]][work_position1[1]]!=-1){
		printf("В данной ячейке нет шарика, выберите другую:");
		scanf("%i%i",&work_position1[0],&work_position1[1]);}
	printf("\nВиберите ячеку, куда необходимо переместить:");
	scanf("%i%i",&work_position2[0],&work_position2[1]);
	while(field[work_position2[0]][work_position2[1]]!=0){
		printf("Данная ячейка недоступна, выберите другую:");
		scanf("%i%i",&work_position2[0],&work_position2[1]);}
	field[work_position1[0]][work_position1[1]]=-255;
	field[work_position2[0]][work_position2[1]]=-256;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			field_2[i][j]=field[i][j];}}
	vaves(work_position1);
   res=path(work_position2[0],work_position2[1]);
   if(res==0)
	   return 0;
   else return 1;
}
int vaves(int* start)
{
		if(*start-1>=0&&field[*start-1][*(start+1)]!=-1){
				field[*start-1][*(start+1)]=1;}
		if(*start+1<size&&field[*start+1][*(start+1)]!=-1){
				field[*start+1][*(start+1)]=1;}
		if(*(start+1)-1>=0&&field[*start][*(start+1)-1]!=-1){
				field[*start][*(start+1)-1]=1;}
		if(*(start+1)+1<size&&field[*start][*(start+1)+1]!=-1){
				field[*start][*(start+1)+1]=1;}
for(int k=0;k<size*size/2;k++){
	for(int i=0;i<size;i=i++){
		for(int j=0;j<size;j=j++){
			if(field[i][j]==last_vave&& i-1>=0&&field[i-1][j]==0){
				field[i-1][j]=last_vave+1;}
			else if(field[i-1][j]==-256&&field[i][j]==last_vave){
				finish[0]=i-1;
				finish[1]=j;
				return 0;}
			if(field[i][j]==last_vave&& i+1<size&&field[i+1][j]==0){
				field[i+1][j]=last_vave+1;}
			else if(field[i+1][j]==-256&&field[i][j]==last_vave){
				finish[0]=i+1;
				finish[1]=j;
				return 0;}
			if(field[i][j]==last_vave&& j-1>=0&&field[i][j-1]==0){
				field[i][j-1]=last_vave+1;}
			else if(field[i][j-1]==-256&&field[i][j]==last_vave){
				finish[0]=i;
				finish[1]=j-1;
				return 0;}
			if(field[i][j]==last_vave&& j+1<size&&field[i][j+1]==0){
				field[i][j+1]=last_vave+1;}
			else if(field[i][j+1]==-256&&field[i][j]==last_vave){
				finish[0]=i;
				finish[1]=j+1;
				return 0;}}}
				last_vave++; }
		return 0;
}

int path(int fin0,int fin1)
{
	int way[200][2], cur[2], min_x, min_y, flag=0;
	cur[0]=fin0;
	cur[1]=fin1;
	field[fin0][fin1]=256;
	if(fin0>=0&&field[fin0-1][fin1]<1)
		flag++;
	if(fin0<size&&field[fin0+1][fin1]<1)
		flag++;
	if(fin1>=0&&field[fin0][fin1-1]<1)
		flag++;
	if(fin1<size&&field[fin0][fin1+1]<1)
		flag++;
	if(flag==4)
		return 1;
	for(int i=0;;i++){
		if(field[cur[0]][cur[1]]>field[cur[0]-1][cur[1]]&&field[cur[0]-1][cur[1]]>0){	
			min_y=cur[0]-1;
			min_x=cur[1];
			}
		else if(field[cur[0]-1][cur[1]]==-255)
			break;
		if(field[cur[0]][cur[1]]>field[cur[0]+1][cur[1]]&&field[cur[0]+1][cur[1]]>0){
			min_y=cur[0]+1;
			min_x=cur[1];}
		else if(field[cur[0]+1][cur[1]]==-255)
			break;
		if(field[cur[0]][cur[1]]>field[cur[0]][cur[1]-1]&&field[cur[0]][cur[1]-1]>0){
			min_y=cur[0];
			min_x=cur[1]-1;}
		else if(field[cur[0]][cur[1]-1]==-255)
			break;
		if(field[cur[0]][cur[1]]>field[cur[0]][cur[1]+1]&&field[cur[0]][cur[1]+1]>0){
			min_y=cur[0];
			min_x=cur[1]+1;}
		else if(field[cur[0]][cur[1]+1]==-255)
			break;
		way[i][0]=min_y;
		way[i][1]=min_x;
		cur[0]=min_y;
		cur[1]=min_x;
	}
		for(int k=0;k<last_vave;k++){
			field_2[way[k][0]][way[k][1]]=field[way[k][0]][way[k][1]];}
		return 0;
}

