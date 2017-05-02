#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int grid[20][10];

<<<<<<< HEAD
int shape1[8] = {0,1,0,0,
		 1,1,1,0};
int shape2[8] = {1,1,0,0,
		 0,1,1,0};
int shape3[8] = {0,0,0,0,
		 1,1,1,1};

int i,j;
int vertCheck = 0; 
int curBlock[8] = {0,0,0,0,
									0,0,0,0 };
=======
int shape1[4][8] = {{0,1,0,0,
		1,1,1,0},
		{1,0,1,1,
		 1,0,0,0},
		{1,1,1,0,
		0,1,0,0},
		{0,1,1,1,
		0,1,0,0}};
int shape2[4][8] = {{1,0,0,0,
		1,1,1,0},
		{1,1,1,0,
		 1,0,0,0},
		{1,1,1,0,
		 0,0,1,0},
	  {0,1,0,1,
	   1,1,0,0}};
int shape3[4][8] = {{0,0,1,0,
			1,1,1,0},
			{1,0,1,0,
			 1,1,0,0},
			{1,1,1,0,
			 1,0,0,0},
		  {1,1,0,1,
		   0,1,0,0}};
int shape4[2][8] = {{1,1,0,0,
		   0,1,1,0},
		  {0,1,1,1,
		   1,0,0,0}};
int shape5[2][8] = {{0,1,1,0,
		1,1,0,0},
		{1,0,1,1,
		 0,1,0,0}};
int shape6[2][8] = {{1,1,1,1,
			0,0,0,0},
			{1,0,1,0,
			1,0,1,0}};
int shape7[8] = {1,1,0,0,
		 1,1,0,0};

int block_index = 0; 
int i,j;
int vertCheck = 0; 
int curBlock[8] = {0,0,0,0,
		0,0,0,0 };
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
char input;

int rotCounter;
static void drawGrid(int grid[20][10]) {
	
for (i = 0; i < 20; i ++) {
	for (j = 0;j < 10;j++) {
		if (j == 0 || j == 9) {
			grid[i][j] = 1;
		}
		else if (i== 0 || i == 19) {
			grid[i][j] = 1;
		}
	}
}

for (i = 0; i < 20; i ++) {
	for (j = 0;j < 10;j++) {
		if (grid[i][j] == 1) {
			printf("*");
		}
		else printf(" ");
	}
	printf("\n");
}
	
}

static void drawShape(int shape[8]) {
	grid[1][3] = shape[0];
	grid[1][4] = shape[1];
	grid[1][5] = shape[2];
	grid[1][6] = shape[3];
	grid[2][3] = shape[4];
	grid[2][4] = shape[5];
	grid[2][5] = shape[6];
	grid[2][6] = shape[7];	
	
	return;	
}

static void eraseShape(int *ptr)
{
	if(rotCounter == 0 || rotCounter ==2)
	{
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}
	else
	{
		//grid[ptr[0]-3][ptr[1]] = 0;
		//grid[ptr[0]-3][ptr[1]+1] = 0;
		grid[ptr[0]-2][ptr[1]] = 0;
		grid[ptr[0]-2][ptr[1]+1] = 0;
		grid[ptr[0]-1][ptr[1]] = 0;
		grid[ptr[0]-1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
	}
}
static int * moveShape(int shape[8], int * ptr, int * still_moving) {

	//erase the old shape
<<<<<<< HEAD
	if(vertCheck==1)
	{
		grid[ptr[0]-3][ptr[1]] = 0;
		grid[ptr[0]-3][ptr[1]+1] = 0;
		grid[ptr[0]-2][ptr[1]] = 0;
		grid[ptr[0]-2][ptr[1]+1] = 0;
		grid[ptr[0]-1][ptr[1]] = 0;
		grid[ptr[0]-1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;

	}
	else {
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}


	//draw the new shape
	if(vertCheck)
	{
		grid[ptr[0]-2][ptr[1]] = shape[4];
		grid[ptr[0]-2][ptr[1]+1] = shape[0];
		grid[ptr[0]-1][ptr[1]] = shape[5];
		grid[ptr[0]-1][ptr[1]+1] = shape[1];
		grid[ptr[0]][ptr[1]] = shape[6];
		grid[ptr[0]][ptr[1]+1] = shape[2];
		grid[ptr[0]+1][ptr[1]] = shape[7];
		grid[ptr[0]+1][ptr[1]+1] = shape[3];
	}
	else{
		grid[ptr[0]+1][ptr[1]] = shape[0];
		grid[ptr[0]+1][ptr[1]+1] = shape[1];
		grid[ptr[0]+1][ptr[1]+2] = shape[2];
		grid[ptr[0]+1][ptr[1]+3] = shape[3];
		grid[ptr[0]+2][ptr[1]] = shape[4];
		grid[ptr[0]+2][ptr[1]+1] = shape[5];
		grid[ptr[0]+2][ptr[1]+2] = shape[6];
		grid[ptr[0]+2][ptr[1]+3] = shape[7];
	}
=======
	//eraseShape(ptr);	



	//draw the new shape
if(block_index ==1)
{
	if(rotCounter==1)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape1[1][0];
			grid[ptr[0]-1][ptr[1]+1] = shape1[1][1];
			grid[ptr[0]][ptr[1]] = shape1[1][2];
			grid[ptr[0]][ptr[1]+1] = shape1[1][3];
			grid[ptr[0]+1][ptr[1]] = shape1[1][4];
			grid[ptr[0]+1][ptr[1]+1] = shape1[1][5];
			grid[ptr[0]+2][ptr[1]] = shape1[1][6];
			grid[ptr[0]+2][ptr[1]+1] = shape1[1][7];
		}
		else still_moving[0] = 0;
		
	}
	else if(rotCounter ==2)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape1[2][0];
			grid[ptr[0]+1][ptr[1]+1] = shape1[2][1];
			grid[ptr[0]+1][ptr[1]+2] = shape1[2][2];
			grid[ptr[0]+1][ptr[1]+3] = shape1[2][3];
			grid[ptr[0]+2][ptr[1]] = shape1[2][4];
			grid[ptr[0]+2][ptr[1]+1] = shape1[2][5];
			grid[ptr[0]+2][ptr[1]+2] = shape1[2][6];
			grid[ptr[0]+2][ptr[1]+3] = shape1[2][7];
		}
		else still_moving[0] = 0;
	}
	else if(rotCounter ==3){
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape1[3][0];
			grid[ptr[0]-1][ptr[1]+1] = shape1[3][1];
			grid[ptr[0]][ptr[1]] = shape1[3][2];
			grid[ptr[0]][ptr[1]+1] = shape1[3][3];
			grid[ptr[0]+1][ptr[1]] = shape1[3][4];
			grid[ptr[0]+1][ptr[1]+1] = shape1[3][5];
			grid[ptr[0]+2][ptr[1]] = shape1[3][6];
			grid[ptr[0]+2][ptr[1]+1] = shape1[3][7];
		}
		else still_moving[0] = 0;
	}
	else{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape1[0][0];
			grid[ptr[0]+1][ptr[1]+1] = shape1[0][1];
			grid[ptr[0]+1][ptr[1]+2] = shape1[0][2];
			grid[ptr[0]+1][ptr[1]+3] = shape1[0][3];
			grid[ptr[0]+2][ptr[1]] = shape1[0][4];
			grid[ptr[0]+2][ptr[1]+1] = shape1[0][5];
			grid[ptr[0]+2][ptr[1]+2] = shape1[0][6];
			grid[ptr[0]+2][ptr[1]+3] = shape1[0][7];
			rotCounter =0;
		}
		else still_moving[0] = 0;
	}
}
if(block_index ==2)
{
	if(rotCounter==1)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape2[1][0];
			grid[ptr[0]-1][ptr[1]+1] = shape2[1][1];
			grid[ptr[0]][ptr[1]] = shape2[1][2];
			grid[ptr[0]][ptr[1]+1] = shape2[1][3];
			grid[ptr[0]+1][ptr[1]] = shape2[1][4];
			grid[ptr[0]+1][ptr[1]+1] = shape2[1][5];
			grid[ptr[0]+2][ptr[1]] = shape2[1][6];
			grid[ptr[0]+2][ptr[1]+1] = shape2[1][7];
		}
		else still_moving[0] = 0;
	}
	else if(rotCounter ==2)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape2[2][0];
			grid[ptr[0]+1][ptr[1]+1] = shape2[2][1];
			grid[ptr[0]+1][ptr[1]+2] = shape2[2][2];
			grid[ptr[0]+1][ptr[1]+3] = shape2[2][3];
			grid[ptr[0]+2][ptr[1]] = shape2[2][4];
			grid[ptr[0]+2][ptr[1]+1] = shape2[2][5];
			grid[ptr[0]+2][ptr[1]+2] = shape2[2][6];
			grid[ptr[0]+2][ptr[1]+3] = shape2[2][7];
		}
		else still_moving[0] = 0;
	}
	else if(rotCounter ==3){
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape2[3][0];
			grid[ptr[0]-1][ptr[1]+1] = shape2[3][1];
			grid[ptr[0]][ptr[1]] = shape2[3][2];
			grid[ptr[0]][ptr[1]+1] = shape2[3][3];
			grid[ptr[0]+1][ptr[1]] = shape2[3][4];
			grid[ptr[0]+1][ptr[1]+1] = shape2[3][5];
			grid[ptr[0]+2][ptr[1]] = shape2[3][6];
			grid[ptr[0]+2][ptr[1]+1] = shape2[3][7];
		}
		else still_moving[0] = 0;
	}
	else{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape2[0][0];
			grid[ptr[0]+1][ptr[1]+1] = shape2[0][1];
			grid[ptr[0]+1][ptr[1]+2] = shape2[0][2];
			grid[ptr[0]+1][ptr[1]+3] = shape2[0][3];
			grid[ptr[0]+2][ptr[1]] = shape2[0][4];
			grid[ptr[0]+2][ptr[1]+1] = shape2[0][5];
			grid[ptr[0]+2][ptr[1]+2] = shape2[0][6];
			grid[ptr[0]+2][ptr[1]+3] = shape2[0][7];
			rotCounter =0;
		}
		else still_moving[0] = 0;
	}
}
if( block_index == 3)
{
	if(rotCounter==1)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape2[1][0];
			grid[ptr[0]-1][ptr[1]+1] = shape2[1][1];
			grid[ptr[0]][ptr[1]] = shape2[1][2];
			grid[ptr[0]][ptr[1]+1] = shape2[1][3];
			grid[ptr[0]+1][ptr[1]] = shape2[1][4];
			grid[ptr[0]+1][ptr[1]+1] = shape2[1][5];
			grid[ptr[0]+2][ptr[1]] = shape2[1][6];
			grid[ptr[0]+2][ptr[1]+1] = shape2[1][7];
		}
		else still_moving[0] = 0;
	}
	else if(rotCounter ==2)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape3[2][0];
			grid[ptr[0]+1][ptr[1]+1] = shape3[2][1];
			grid[ptr[0]+1][ptr[1]+2] = shape3[2][2];
			grid[ptr[0]+1][ptr[1]+3] = shape3[2][3];
			grid[ptr[0]+2][ptr[1]] = shape3[2][4];
			grid[ptr[0]+2][ptr[1]+1] = shape3[2][5];
			grid[ptr[0]+2][ptr[1]+2] = shape3[2][6];
			grid[ptr[0]+2][ptr[1]+3] = shape3[2][7];
		}
		else still_moving[0] = 0;
	}
	else if(rotCounter ==3){
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape3[3][0];
			grid[ptr[0]-1][ptr[1]+1] = shape3[3][1];
			grid[ptr[0]][ptr[1]] = shape3[3][2];
			grid[ptr[0]][ptr[1]+1] = shape3[3][3];
			grid[ptr[0]+1][ptr[1]] = shape3[3][4];
			grid[ptr[0]+1][ptr[1]+1] = shape3[3][5];
			grid[ptr[0]+2][ptr[1]] = shape3[3][6];
			grid[ptr[0]+2][ptr[1]+1] = shape3[3][7];
		}
		else still_moving[0] = 0;
	}
	else{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape3[0][0];
			grid[ptr[0]+1][ptr[1]+1] = shape3[0][1];
			grid[ptr[0]+1][ptr[1]+2] = shape3[0][2];
			grid[ptr[0]+1][ptr[1]+3] = shape3[0][3];
			grid[ptr[0]+2][ptr[1]] = shape3[0][4];
			grid[ptr[0]+2][ptr[1]+1] = shape3[0][5];
			grid[ptr[0]+2][ptr[1]+2] = shape3[0][6];
			grid[ptr[0]+2][ptr[1]+3] = shape3[0][7];
			rotCounter =0;
		}
		else still_moving[0] = 0;
	}
}
if(block_index == 4)
{
		if(rotCounter==1)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape4[1][0];
			grid[ptr[0]-1][ptr[1]+1] = shape4[1][1];
			grid[ptr[0]][ptr[1]] = shape4[1][2];
			grid[ptr[0]][ptr[1]+1] = shape4[1][3];
			grid[ptr[0]+1][ptr[1]] = shape4[1][4];
			grid[ptr[0]+1][ptr[1]+1] = shape4[1][5];
			grid[ptr[0]+2][ptr[1]] = shape4[1][6];
			grid[ptr[0]+2][ptr[1]+1] = shape4[1][7];
		}
		else still_moving[0] = 0;
	}
	else 
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape4[0][0];
			grid[ptr[0]+1][ptr[1]+1] = shape4[0][1];
			grid[ptr[0]+1][ptr[1]+2] = shape4[0][2];
			grid[ptr[0]+1][ptr[1]+3] = shape4[0][3];
			grid[ptr[0]+2][ptr[1]] = shape4[0][4];
			grid[ptr[0]+2][ptr[1]+1] = shape4[0][5];
			grid[ptr[0]+2][ptr[1]+2] = shape4[0][6];
			grid[ptr[0]+2][ptr[1]+3] = shape4[0][7];
			rotCounter =0;
		}
		else still_moving[0] = 0;
	}
}
if(block_index ==5)
{
	if(rotCounter==1)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape5[1][0];
			grid[ptr[0]-1][ptr[1]+1] = shape5[1][1];
			grid[ptr[0]][ptr[1]] = shape5[1][2];
			grid[ptr[0]][ptr[1]+1] = shape5[1][3];
			grid[ptr[0]+1][ptr[1]] = shape5[1][4];
			grid[ptr[0]+1][ptr[1]+1] = shape5[1][5];
			grid[ptr[0]+2][ptr[1]] = shape5[1][6];
			grid[ptr[0]+2][ptr[1]+1] = shape5[1][7];
		}
		else still_moving[0] = 0;
	}
	else 
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape5[0][0];
			grid[ptr[0]+1][ptr[1]+1] = shape5[0][1];
			grid[ptr[0]+1][ptr[1]+2] = shape5[0][2];
			grid[ptr[0]+1][ptr[1]+3] = shape5[0][3];
			grid[ptr[0]+2][ptr[1]] = shape5[0][4];
			grid[ptr[0]+2][ptr[1]+1] = shape5[0][5];
			grid[ptr[0]+2][ptr[1]+2] = shape5[0][6];
			grid[ptr[0]+2][ptr[1]+3] = shape5[0][7];
			rotCounter =0;
		}
		else still_moving[0] = 0;
	}
}
if(block_index == 6)
{
	if(rotCounter==1)
	{
		if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0) {
		eraseShape(ptr);
			grid[ptr[0]-1][ptr[1]] = shape6[1][0];
			grid[ptr[0]-1][ptr[1]+1] = shape6[1][1];
			grid[ptr[0]][ptr[1]] = shape6[1][2];
			grid[ptr[0]][ptr[1]+1] = shape6[1][3];
			grid[ptr[0]+1][ptr[1]] = shape6[1][4];
			grid[ptr[0]+1][ptr[1]+1] = shape6[1][5];
			grid[ptr[0]+2][ptr[1]] = shape6[1][6];
			grid[ptr[0]+2][ptr[1]+1] = shape6[1][7];
		}
		else still_moving[0] = 0;
	}
	else 
	{
		if (grid[ptr[0]+1][ptr[1]] == 0 && grid[ptr[0]+1][ptr[1]+1] == 0 && grid[ptr[0]+1][ptr[1]+2] == 0 && grid[ptr[0]+1][ptr[1]+3] == 0) {
		eraseShape(ptr);
			grid[ptr[0]+1][ptr[1]] = shape6[0][0];
			grid[ptr[0]+1][ptr[1]+1] = shape6[0][1];
			grid[ptr[0]+1][ptr[1]+2] = shape6[0][2];
			grid[ptr[0]+1][ptr[1]+3] = shape6[0][3];
			grid[ptr[0]+2][ptr[1]] = shape6[0][4];
			grid[ptr[0]+2][ptr[1]+1] = shape6[0][5];
			grid[ptr[0]+2][ptr[1]+2] = shape6[0][6];
			grid[ptr[0]+2][ptr[1]+3] = shape6[0][7];
			rotCounter =0;
		}
		else still_moving[0] = 0;
	}
}
if(block_index == 7)
{
	if (grid[ptr[0]+2][ptr[1]] == 0 && grid[ptr[0]+2][ptr[1]+1] == 0 && grid[ptr[0]+2][ptr[1]+2] == 0 && grid[ptr[0]+2][ptr[1]+3] == 0) {
	eraseShape(ptr);
		grid[ptr[0]+1][ptr[1]] = shape7[0];
		grid[ptr[0]+1][ptr[1]+1] = shape7[1];
		grid[ptr[0]+1][ptr[1]+2] = shape7[2];
		grid[ptr[0]+1][ptr[1]+3] = shape7[3];
		grid[ptr[0]+2][ptr[1]] = shape7[4];
		grid[ptr[0]+2][ptr[1]+1] = shape7[5];
		grid[ptr[0]+2][ptr[1]+2] = shape7[6];
		grid[ptr[0]+2][ptr[1]+3] = shape7[7];
		rotCounter =0;
	}
	else still_moving[0] = 0;
}

>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034

	//printf("%x\n",ptr[0]);
	//printf("%x\n",ptr[1]);


<<<<<<< HEAD
	ptr[0] = ptr[0]+1;
=======
	if (still_moving) ptr[0] = ptr[0]+1;
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
	return ptr;
	
}




static int moveLeft(int shape[8],int * ptr) {

	//erase the old shape
<<<<<<< HEAD
	if(vertCheck==1)
	{
		grid[ptr[0]-2][ptr[1]] = 0;
		grid[ptr[0]-2][ptr[1]+1] = 0;
		grid[ptr[0]-1][ptr[1]] = 0;
		grid[ptr[0]-1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}
	else{
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}
=======
	eraseShape(ptr);
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034

	if ((ptr[1] - 1) >=1) ptr[1] = ptr[1] - 1;
	else if ((ptr[1] - 1) == 0) {
		if (shape[0] == 0 && shape[4] == 0) ptr[1] = ptr[1] - 1;
	}
	return ptr[1];
}

static int moveRight(int shape[8],int * ptr) {

	//erase the old shape
<<<<<<< HEAD
	if(vertCheck==1)
	{
		grid[ptr[0]-2][ptr[1]] = 0;
		grid[ptr[0]-2][ptr[1]+1] = 0;
		grid[ptr[0]-1][ptr[1]] = 0;
		grid[ptr[0]-1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}
	else{
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}

	if ((ptr[1] + 5) <= 9) ptr[1] = ptr[1] + 1;
	//bounds check to the right.
	else if ((ptr[1] + 5) == 10) {
		if (shape[3] == 0 && shape[7] == 0) ptr[1] = ptr[1]+1;
=======
	eraseShape(ptr);
	if(rotCounter == 0||rotCounter==2)
	{
		if ((ptr[1] + 5) <= 9) ptr[1] = ptr[1] + 1;
		//bounds check to the right.
		else if ((ptr[1] + 5) == 10) {
			if (shape[3] == 0 && shape[7] == 0) ptr[1] = ptr[1]+1;
		}
	}
	else
	{
		if ((ptr[1] + 3) <= 9) ptr[1] = ptr[1] + 1;
		//bounds check to the right.
		else if ((ptr[1] + 3) == 10) {
			if (shape[3] == 0 && shape[7] == 0) ptr[1] = ptr[1]+1;
		}
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
	}

	return ptr[1];
}

static int moveDown(int shape[8],int * ptr,int grid[20][10]) {
	
	//erase the old shape
<<<<<<< HEAD
	if(vertCheck ==1 )
	{
		grid[ptr[0]-2][ptr[1]] = 0;
		grid[ptr[0]-2][ptr[1]+1] = 0;
		grid[ptr[0]-1][ptr[1]] = 0;
		grid[ptr[0]-1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
=======
	//eraseShape(ptr);
	if ((ptr[0] + 1) <= 16 && grid[ptr[0]+3][ptr[1]] != 1 && grid[ptr[0]+3][ptr[1]+1] != 1) {
		eraseShape(ptr);
		ptr[0] = ptr[0] + 1;
		}
	/*if (grid[ptr[0]+1][ptr[1]] != 1 && (ptr[0] + 2) < 17) {
		//printf("grid:%d\n",grid[ptr[0]+1][ptr[1]]);
		ptr[0] = ptr[0] + 1;
	}*/
	
	//printf("%x\n",ptr[0]);
	//printf("%x\n",ptr[1]);
	return ptr[0];
	
}

static int rotate(int shape[8],int*ptr){
		if(rotCounter == 1 || rotCounter ==3)
		{
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}
	else {
<<<<<<< HEAD
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;
	}	
	if ((ptr[0] + 1) <= 19) ptr[0] = ptr[0] + 1;
	//printf("%x\n",ptr[0]);
	//printf("%x\n",ptr[1]);
=======
		grid[ptr[0]-2][ptr[1]] = 0;
		grid[ptr[0]-2][ptr[1]+1] = 0;
		grid[ptr[0]-1][ptr[1]] = 0;
		grid[ptr[0]-1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		//grid[ptr[0]+2][ptr[1]] = 0;
		//grid[ptr[0]+2][ptr[1]+1] = 0;
		}		

	if(rotCounter == 1){
		ptr[0] = ptr[0]-1;
	}
	else if(rotCounter ==2){
		ptr[0] = ptr[0]-2;
	}
	else if(rotCounter == 3){
		ptr[0] = ptr[0]-1;
	}
	else {
		ptr[0] = ptr[0]-2;
	}

	if ((ptr[0] + 1) <= 19) ptr[0] = ptr[0] + 1;

>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
	return ptr[0];
}



void copyBlock(int inBlock[8],int outBlock[8]){
	int count;
	for(count = 0; count< 8; count++)
	{
		outBlock[count] = inBlock[count];
	}
}

static void randomShape(){
	int randNum = rand() % 7;

	switch(randNum){
		case 0:
			copyBlock(shape1[0],curBlock);
			block_index =1;
			break;
		case 1:
			copyBlock(shape2[0],curBlock);
			block_index =2;
			break;
		case 2:
			copyBlock(shape3[0],curBlock);
			block_index =3;
			break;
		case 3:
			copyBlock(shape4[0],curBlock);
			block_index =4;
			break;
		case 4:
			copyBlock(shape5[0],curBlock);
			block_index =5;
			break;
		case 5:
			copyBlock(shape6[0],curBlock);
			block_index =6;
			break;
		case 6:
			copyBlock(shape7,curBlock);
			block_index =7;
			break;
		default:
			copyBlock(shape1[0],curBlock);
			block_index =1;
			break;
	}

	//return resultShape;
}

static int checkBounds(int grid[20][10]) {
	
	for (i = 1; i < 9; i++) {
		if (grid[1][i] == 1) return 1;
	}
	
	 return 0;
}

static int rotate(int shape[8],int*ptr){
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]+2] = 0;
		grid[ptr[0]][ptr[1]+3] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]+2] = 0;
		grid[ptr[0]+1][ptr[1]+3] = 0;

		grid[ptr[0]-2][ptr[1]] = 0;
		grid[ptr[0]-2][ptr[1]+1] = 0;
		grid[ptr[0]-1][ptr[1]] = 0;
		grid[ptr[0]-1][ptr[1]+1] = 0;
		grid[ptr[0]][ptr[1]] = 0;
		grid[ptr[0]][ptr[1]+1] = 0;
		grid[ptr[0]+1][ptr[1]] = 0;
		grid[ptr[0]+1][ptr[1]+1] = 0;
		grid[ptr[0]+2][ptr[1]] = 0;
		grid[ptr[0]+2][ptr[1]+1] = 0;		

	if(rotCounter > 0){
		vertCheck =1;
	}
	if ((ptr[0] + 1) <= 19) ptr[0] = ptr[0] + 1;
	return ptr[0];
}
//
// int* randomShape(){
// 	int randNum = rand()%7;
// 	int * resultShape;
// 	switch(randNum){
// 		case 0:
// 			resultShape = shape1[0];
// 			break;
// 		case 1:
// 			resultShape = shape2[0];
// 			break;
// 		case 2:
// 			resultShape = shape3[0];
// 			break;
// 		case 3:
// 			resultShape = shape4[0];
// 			break;
// 		case 4:
// 			resultShape = shape5[0];
// 			break;
// 		case 5:
// 			resultShape = shape6[0];
// 			break;
// 		case 6:
// 			resultShape = shape7[0];
// 			break;
// 		default:
// 			resultShape = shape1[0];
// 			break;
// 	}

// 	return resultShape;
// }

void copyBlock(int inBlock[8],int outBlock[8]){
	int count;
	for(count = 0; count< 8; count++)
	{
		outBlock[count] = inBlock[count];
	}
}

int main() {
	
	drawGrid(grid);		//draw initial grid
	int check[8];

	
	check[0] = grid[1][1];
	check[1] = grid[1][2];
	check[2] = grid[1][3];
	check[3] = grid[1][4];
	check[4] = grid[1][5];
	check[5] = grid[1][6];
	check[6] = grid[1][7];
	check[0] = grid[1][8];
	
	
	int start_pt[2] = {1,3};
	int check_pt[2] = {0,0};
	
<<<<<<< HEAD
	int * start_ptr = start_pt;
	copyBlock(shape1,curBlock);
=======
	int still_moving = 1;
	int first_line = 0;
	
	int random_num;

	int * start_ptr = start_pt;
	int * first_row = check;
	int * stl_mov_ptr = &still_moving;
	randomShape();
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
	drawShape(curBlock);
	drawGrid(grid);

	rotCounter = 0;
<<<<<<< HEAD
	while(!checkBounds(start_ptr)){
		for (i = 0; i < 500000000;i++);
		if (kbhit()) {
			input = getchar();
			if (input == 'a') {
				//move left
				start_ptr[1] = moveLeft(curBlock,start_ptr);
			}
			else if (input == 'd') {
				start_ptr[1] = moveRight(curBlock,start_ptr);
			}
			else if (input == 'w') {
				rotCounter++;
				start_ptr[0] = rotate(curBlock,start_ptr);
			}
			else if (input == 's') {
				start_ptr[0] = moveDown(curBlock,start_ptr);
=======
	while(1){
	for (i = 0; i < 500000000;i++);
		if (still_moving){			
			if (kbhit()) {
				input = getchar();
				if (input == 'a') {
					//move left
					start_ptr[1] = moveLeft(curBlock,start_ptr);
				}
				else if (input == 'd') {
					//move right
					start_ptr[1] = moveRight(curBlock,start_ptr);
				}
				else if (input == 'w') {
					//rotate
					rotCounter++;
					start_ptr[0] = rotate(curBlock,start_ptr);
				}
				else if (input == 's') {
					//move down
					//printf("before:%d\n",start_ptr[0]);
					start_ptr[0] = moveDown(curBlock,start_ptr,grid);
					//printf("after:%d\n",start_ptr[0]);
				}
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
			}
			
			start_ptr = moveShape(curBlock,start_ptr,stl_mov_ptr);
			drawGrid(grid);
		}
		else {
			int endGame = checkBounds(grid);
			if (endGame) break;
			start_pt[0] =1;
			start_pt[1] = 3;
			drawGrid(grid);
			eraseShape(start_ptr);
			randomShape();
			drawShape(curBlock);
			still_moving = 1;
			
		}
<<<<<<< HEAD

		start_ptr = moveShape(curBlock,start_ptr);
		drawGrid(grid);
=======
		//printf("still:%d\n",still_moving);
>>>>>>> 622dd9e7d8b135676dea9541398505cb25e11034
	}
	return 0;
}
