#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h> 


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
int grid_land[20][10];
int grid_moving[20][10];
int grid_temp[20][10];

int shape1[4][8] = {{0,1,0,0,
		1,1,1,0},
		{1,0,1,1,
		 1,0,0,0},
		{1,1,1,0,
		0,1,0,0},
		{0,1,1,1,
		0,1,0,0}};
int shape2[4][8] = {{2,0,0,0,
		2,2,2,0},
		{2,2,2,0,
		 2,0,0,0},
		{2,2,2,0,
		 0,0,2,0},
	  {0,2,0,2,
	   2,2,0,0}};
int shape3[4][8] = {{0,0,3,0,
			3,3,3,0},
			{3,0,3,0,
			 3,3,0,0},
			{3,3,3,0,
			 3,0,0,0},
		  {3,3,0,3,
		   0,3,0,0}};
int shape4[2][8] = {{4,4,0,0,
		   0,4,4,0},
		  {0,4,4,4,
		   4,0,0,0}};
int shape5[2][8] = {{0,5,5,0,
		5,5,0,0},
		{5,0,5,5,
		 0,5,0,0}};
int shape6[2][8] = {{6,6,6,6,
			0,0,0,0},
			{6,0,6,0,
			6,0,6,0}};
int shape7[8] = {7,7,0,0,
		 7,7,0,0};

int block_index = 0; 

int vertCheck = 0; 
int curBlock[8] = {0,0,0,0,
		0,0,0,0 };
char input;
int point=10;

int rotCounter;

static void initialize_grids()
{
	int i,j;
	for (i = 0; i < 20; i ++) {
		for (j = 0;j < 10;j++) {
			grid[i][j]=0;
			grid_moving[i][j]=0;
			grid_land[i][j]=0;
		}
	}
}

// static void grid_land_Default()
// {
// 	for (i = 0; i < 20; i ++) {
// 		for (j = 0;j < 10;j++) {
// 			if (j == 0 || j == 9) {
// 				grid_land[i][j] = 9;
// 			}
// 			else if (i== 0 || i == 19) {
// 				grid_land[i][j] = 9;
// 			}
// 		}
// 	}	
// }


static void drawGrid(	)
{
	int i,j;
	for (i = 0; i < 20; i ++) {
		for (j = 0;j < 10;j++) {
			if (grid[i][j] > 0) {
				printf("*");
			}
			else printf(" ");
		}
		printf("\n");
	}
	
}

static void drawShape(int shape[8]) {
	grid_moving[1][3] = shape[0];
	grid_moving[1][4] = shape[1];
	grid_moving[1][5] = shape[2];
	grid_moving[1][6] = shape[3];
	grid_moving[2][3] = shape[4];
	grid_moving[2][4] = shape[5];
	grid_moving[2][5] = shape[6];
	grid_moving[2][6] = shape[7];	
	
	return;	
}

static void copyShape(int *ptr)
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			grid_temp[i][j]=0;
		}
	}
	if(rotCounter == 0 || rotCounter ==2)
	{
		grid_temp[ptr[0]][ptr[1]]=grid_moving[ptr[0]][ptr[1]];
		grid_temp[ptr[0]][ptr[1]+1]=grid_moving[ptr[0]][ptr[1]+1];
		grid_temp[ptr[0]][ptr[1]+2]=grid_moving[ptr[0]][ptr[1]+2];
		grid_temp[ptr[0]][ptr[1]+3]=grid_moving[ptr[0]][ptr[1]+3];
		grid_temp[ptr[0]+1][ptr[1]]=grid_moving[ptr[0]+1][ptr[1]];
		grid_temp[ptr[0]+1][ptr[1]+1]=grid_moving[ptr[0]+1][ptr[1]+1];
		grid_temp[ptr[0]+1][ptr[1]+2]=grid_moving[ptr[0]+1][ptr[1]+2];
		grid_temp[ptr[0]+1][ptr[1]+3]=grid_moving[ptr[0]+1][ptr[1]+3];
	}
	else
	{
		grid_temp[ptr[0]-3][ptr[1]]=grid_moving[ptr[0]-3][ptr[1]];
		grid_temp[ptr[0]-3][ptr[1]+1]=grid_moving[ptr[0]-3][ptr[1]+1];
		grid_temp[ptr[0]-2][ptr[1]]=grid_moving[ptr[0]-2][ptr[1]];
		grid_temp[ptr[0]-2][ptr[1]+1]=grid_moving[ptr[0]-2][ptr[1]+1];
		grid_temp[ptr[0]-1][ptr[1]]=grid_moving[ptr[0]-1][ptr[1]];
		grid_temp[ptr[0]-1][ptr[1]+1]=grid_moving[ptr[0]-1][ptr[1]+1];
		grid_temp[ptr[0]][ptr[1]]=grid_moving[ptr[0]][ptr[1]];
		grid_temp[ptr[0]][ptr[1]+1]=grid_moving[ptr[0]][ptr[1]+1];
		grid_temp[ptr[0]+1][ptr[1]]=grid_moving[ptr[0]+1][ptr[1]];
		grid_temp[ptr[0]+1][ptr[1]+1]=grid_moving[ptr[0]+1][ptr[1]+1];
	}
}

static void eraseShape(int *ptr)
{
	int i,j;
	for (i = 0; i < 20; i ++) {
		for (j = 0;j < 10;j++) {
			grid_moving[i][j] =0;
		}
	}
}


static void land_fix()
{
	int i,j;
	for (i = 0; i < 20; i ++) {
		for (j = 0;j < 10;j++) {
			if(grid_moving[i][j]>0)
			{
				grid_land[i][j]=grid_moving[i][j];
			}
		}
	}
}

static int * moveShape(int shape[8], int * ptr, int * still_moving) {

	//erase the old shape
	//eraseShape(ptr);	
	//draw the new shape
	if(block_index ==1)
	{
		if(rotCounter==1)
		{
			if (grid_land[ptr[0]+1][ptr[1]]==0 && grid_land[ptr[0]][ptr[1]+1]==0 && grid_land[ptr[0]][ptr[1]]==0&& grid_land[ptr[0]-1][ptr[1]]==0 && ptr[0]+1!=20) 
			{
				eraseShape(ptr);
				grid_moving[ptr[0]-1][ptr[1]] = shape1[1][0];
				//grid_moving[ptr[0]-1][ptr[1]+1] = shape1[1][1];
				grid_moving[ptr[0]][ptr[1]] = shape1[1][2];
				grid_moving[ptr[0]][ptr[1]+1] = shape1[1][3];
				grid_moving[ptr[0]+1][ptr[1]] = shape1[1][4];
				//grid_moving[ptr[0]+1][ptr[1]+1] = shape1[1][5];
				//grid[ptr[0]+2][ptr[1]] = shape1[1][6];
				//grid[ptr[0]+2][ptr[1]+1] = shape1[1][7];
			}
			else still_moving[0] = 0;
			
		}
		else if(rotCounter ==2)
		{
			if (grid_land[ptr[0]+1][ptr[1]] == 0 && grid_land[ptr[0]+1][ptr[1]+2] == 0&& grid_land[ptr[0]+1][ptr[1]+1] == 0  && grid_land[ptr[0]+2][ptr[1]+1] == 0 && ptr[0]+2!=20)
			 {
					eraseShape(ptr);
					grid_moving[ptr[0]+1][ptr[1]] = shape1[2][0];
					grid_moving[ptr[0]+1][ptr[1]+1] = shape1[2][1];
					grid_moving[ptr[0]+1][ptr[1]+2] = shape1[2][2];
					//grid_moving[ptr[0]+1][ptr[1]+3] = shape1[2][3];
					//grid_moving[ptr[0]+2][ptr[1]] = shape1[2][4];
					grid_moving[ptr[0]+2][ptr[1]+1] = shape1[2][5];
					//grid_moving[ptr[0]+2][ptr[1]+2] = shape1[2][6];
					//grid_moving[ptr[0]+2][ptr[1]+3] = shape1[2][7];
			}
			else still_moving[0] = 0;
		}
		else if(rotCounter ==3){
			if (grid_land[ptr[0]-1][ptr[1]+1]==0 && grid_land[ptr[0]][ptr[1]]==0 && grid_land[ptr[0]][ptr[1]+1]==0 && grid_land[ptr[0]+1][ptr[1]+1]==0 && ptr[0]+1!=20) 
			{
				eraseShape(ptr);
				//grid_moving[ptr[0]-1][ptr[1]] = shape1[3][0];
				grid_moving[ptr[0]-1][ptr[1]+1] = shape1[3][1];
				grid_moving[ptr[0]][ptr[1]] = shape1[3][2];
				grid_moving[ptr[0]][ptr[1]+1] = shape1[3][3];
				//grid_moving[ptr[0]+1][ptr[1]] = shape1[3][4];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape1[3][5];
				// grid[ptr[0]+2][ptr[1]] = shape1[3][6];
				// grid[ptr[0]+2][ptr[1]+1] = shape1[3][7];
			}
			else still_moving[0] = 0;
		}
		else{
			if (grid_land[ptr[0]+1][ptr[1]+1] == 0 && grid_land[ptr[0]+2][ptr[1]] == 0 && grid_land[ptr[0]+2][ptr[1]+1] == 0 && grid_land[ptr[0]+2][ptr[1]+2] == 0 && ptr[0]+1!=19)
			{
				eraseShape(ptr);
				//grid_moving[ptr[0]+1][ptr[1]] = shape1[0][0];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape1[0][1];
				//grid_moving[ptr[0]+1][ptr[1]+2] = shape1[0][2];
				//grid_moving[ptr[0]+1][ptr[1]+3] = shape1[0][3];
				grid_moving[ptr[0]+2][ptr[1]] = shape1[0][4];
				grid_moving[ptr[0]+2][ptr[1]+1] = shape1[0][5];
				grid_moving[ptr[0]+2][ptr[1]+2] = shape1[0][6];
				//grid_moving[ptr[0]+2][ptr[1]+3] = shape1[0][7];
				rotCounter =0;
			}
			else still_moving[0] = 0;
		}
	}
	if(block_index ==2)
	{
		if(rotCounter==1)
		{
			if ( grid_land[ptr[0]-1][ptr[1]]==0  && grid_land[ptr[0]-1][ptr[1]+1]==0  && grid_land[ptr[0]][ptr[1]]==0 &&grid_land[ptr[0]+1][ptr[1]]==0 && ptr[0]+1!=20) 
			{
				eraseShape(ptr);
				grid_moving[ptr[0]-1][ptr[1]] = shape2[1][0];
				grid_moving[ptr[0]-1][ptr[1]+1] = shape2[1][1];
				grid_moving[ptr[0]][ptr[1]] = shape2[1][2];
				//grid_moving[ptr[0]][ptr[1]+1] = shape2[1][3];
				grid_moving[ptr[0]+1][ptr[1]] = shape2[1][4];
				//grid_moving[ptr[0]+1][ptr[1]+1] = shape2[1][5];
				// grid[ptr[0]+2][ptr[1]] = shape2[1][6];
				// grid[ptr[0]+2][ptr[1]+1] = shape2[1][7];
			}
			else still_moving[0] = 0;
		}
		else if(rotCounter ==2)
		{
			if (grid_land[ptr[0]+1][ptr[1]]==0 && grid_land[ptr[0]+1][ptr[1]+1]==0 && grid_land[ptr[0]+1][ptr[1]+2]==0 &&grid_land[ptr[0]+2][ptr[1]+2]==0 && ptr[0]+1!=19) 
			{

				eraseShape(ptr);
				grid_moving[ptr[0]+1][ptr[1]] = shape2[2][0];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape2[2][1];
				grid_moving[ptr[0]+1][ptr[1]+2] = shape2[2][2];
				//grid_moving[ptr[0]+1][ptr[1]+3] = shape2[2][3];
				//grid_moving[ptr[0]+2][ptr[1]] = shape2[2][4];
				//grid_moving[ptr[0]+2][ptr[1]+1] = shape2[2][5];
				grid_moving[ptr[0]+2][ptr[1]+2] = shape2[2][6];
				//grid_moving[ptr[0]+2][ptr[1]+3] = shape2[2][7];
			}
			else still_moving[0] = 0;
		}
		else if(rotCounter ==3){
			if (grid_land[ptr[0]-1][ptr[1]+1] == 0 && grid_land[ptr[0]][ptr[1]+1] == 0 && grid_land[ptr[0]+1][ptr[1]] == 0 && grid_land[ptr[0]+1][ptr[1]+1] == 0&& ptr[0]+1!=20) 
			{
				eraseShape(ptr);
				//grid_moving[ptr[0]-1][ptr[1]] = shape2[3][0];
				grid_moving[ptr[0]-1][ptr[1]+1] = shape2[3][1];
				//grid_moving[ptr[0]][ptr[1]] = shape2[3][2];
				grid_moving[ptr[0]][ptr[1]+1] = shape2[3][3];
				grid_moving[ptr[0]+1][ptr[1]] = shape2[3][4];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape2[3][5];
				// grid[ptr[0]+2][ptr[1]] = shape2[3][6];
				// grid[ptr[0]+2][ptr[1]+1] = shape2[3][7];
			}
			else still_moving[0] = 0;
		}
		else{
			if (grid_land[ptr[0]+1][ptr[1]] == 0 && grid_land[ptr[0]+2][ptr[1]] == 0 && grid_land[ptr[0]+2][ptr[1]+1] == 0 && grid_land[ptr[0]+2][ptr[1]+2] == 0&& ptr[0]+1!=19) 
			{
				eraseShape(ptr);
				grid_moving[ptr[0]+1][ptr[1]] = shape2[0][0];
				//grid_moving[ptr[0]+1][ptr[1]+1] = shape2[0][1];
				//grid_moving[ptr[0]+1][ptr[1]+2] = shape2[0][2];
				//grid_moving[ptr[0]+1][ptr[1]+3] = shape2[0][3];
				grid_moving[ptr[0]+2][ptr[1]] = shape2[0][4];
				grid_moving[ptr[0]+2][ptr[1]+1] = shape2[0][5];
				grid_moving[ptr[0]+2][ptr[1]+2] = shape2[0][6];
				//grid[ptr[0]+2][ptr[1]+3] = shape2[0][7];
				rotCounter =0;
			}
			else still_moving[0] = 0;
		}
	}
	if( block_index == 3)
	{
		if(rotCounter==1)
		{
			if (grid_land[ptr[0]-1][ptr[1]] == 0 &&grid_land[ptr[0]][ptr[1]] == 0 && grid_land[ptr[0]+1][ptr[1]] == 0 && grid_land[ptr[0]+1][ptr[1]+1] == 0&& ptr[0]+1!=20) 
			{
				eraseShape(ptr);
				grid_moving[ptr[0]-1][ptr[1]] = shape3[1][0];
				//grid_moving[ptr[0]-1][ptr[1]+1] = shape3[1][1];
				grid_moving[ptr[0]][ptr[1]] = shape3[1][2];
				//grid_moving[ptr[0]][ptr[1]+1] = shape3[1][3];
				grid_moving[ptr[0]+1][ptr[1]] = shape3[1][4];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape3[1][5];
				// grid[ptr[0]+2][ptr[1]] = shape2[1][6];
				// grid[ptr[0]+2][ptr[1]+1] = shape2[1][7];
			}
			else still_moving[0] = 0;
		}
		else if(rotCounter ==2)
		{
			if ( grid_land[ptr[0]+1][ptr[1]]==0&& grid_land[ptr[0]+1][ptr[1]+1] == 0 && grid_land[ptr[0]+1][ptr[1]+2]  == 0 && grid_land[ptr[0]+2][ptr[1]]==0 && ptr[0]+1!=19)
			 {
				eraseShape(ptr);
				grid_moving[ptr[0]+1][ptr[1]] = shape3[2][0];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape3[2][1];
				grid_moving[ptr[0]+1][ptr[1]+2] = shape3[2][2];
				//grid_moving[ptr[0]+1][ptr[1]+3] = shape3[2][3];
				grid_moving[ptr[0]+2][ptr[1]] = shape3[2][4];
				//grid_moving[ptr[0]+2][ptr[1]+1] = shape3[2][5];
				//grid_moving[ptr[0]+2][ptr[1]+2] = shape3[2][6];
				//grid_moving[ptr[0]+2][ptr[1]+3] = shape3[2][7];
			}
			else still_moving[0] = 0;
		}
		else if(rotCounter ==3){
			if ( grid_land[ptr[0]-1][ptr[1]] == 0&& grid_land[ptr[0]-1][ptr[1]+1]== 0 && grid_land[ptr[0]][ptr[1]+1] == 0 && grid_land[ptr[0]+1][ptr[1]+1] == 0&& ptr[0]+1!=20) 
			{
				eraseShape(ptr);
				grid_moving[ptr[0]-1][ptr[1]] = shape3[3][0];
				grid_moving[ptr[0]-1][ptr[1]+1] = shape3[3][1];
				//grid_moving[ptr[0]][ptr[1]] = shape3[3][2];
				grid_moving[ptr[0]][ptr[1]+1] = shape3[3][3];
				//grid_moving[ptr[0]+1][ptr[1]] = shape3[3][4];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape3[3][5];
				// grid_moving[ptr[0]+2][ptr[1]] = shape3[3][6];
				// grid_moving[ptr[0]+2][ptr[1]+1] = shape3[3][7];
			}
			else still_moving[0] = 0;
		}
		else{
			if (grid_land[ptr[0]+1][ptr[1]+2] == 0 &&grid_land[ptr[0]+2][ptr[1]] == 0 && grid_land[ptr[0]+2][ptr[1]+1] == 0 && grid_land[ptr[0]+2][ptr[1]+2] == 0&& ptr[0]+1!=19) 
			{
				eraseShape(ptr);
				//grid_moving[ptr[0]+1][ptr[1]] = shape3[0][0];
				//grid_moving[ptr[0]+1][ptr[1]+1] = shape3[0][1];
				grid_moving[ptr[0]+1][ptr[1]+2] = shape3[0][2];
				//grid_moving[ptr[0]+1][ptr[1]+3] = shape3[0][3];
				grid_moving[ptr[0]+2][ptr[1]] = shape3[0][4];
				grid_moving[ptr[0]+2][ptr[1]+1] = shape3[0][5];
				grid_moving[ptr[0]+2][ptr[1]+2] = shape3[0][6];
				//grid[ptr[0]+2][ptr[1]+3] = shape3[0][7];
				rotCounter =0;
			}
			else still_moving[0] = 0;
		}
	}
	if(block_index == 4)
	{
			if(rotCounter==1)
		{
			if (grid_land[ptr[0]-1][ptr[1]+1] == 0 && grid_land[ptr[0]][ptr[1]] == 0&& grid_land[ptr[0]][ptr[1]+1]==0 && grid_land[ptr[0]+1][ptr[1]] == 0&& ptr[0]+1!=20) 
			{
				eraseShape(ptr);
				//grid_moving[ptr[0]-1][ptr[1]] = shape4[1][0];
				grid_moving[ptr[0]-1][ptr[1]+1] = shape4[1][1];
				grid_moving[ptr[0]][ptr[1]] = shape4[1][2];
				grid_moving[ptr[0]][ptr[1]+1] = shape4[1][3];
				grid_moving[ptr[0]+1][ptr[1]] = shape4[1][4];
				//grid_moving[ptr[0]+1][ptr[1]+1] = shape4[1][5];
				//grid_moving[ptr[0]+2][ptr[1]] = shape4[1][6];
				//grid_moving[ptr[0]+2][ptr[1]+1] = shape4[1][7];
			}
			else still_moving[0] = 0;
		}
		else 
		{
			if (grid_land[ptr[0]+1][ptr[1]] == 0 && grid_land[ptr[0]+2][ptr[1]+1] == 0 && grid_land[ptr[0]+2][ptr[1]+1] == 0&& grid_land[ptr[0]+2][ptr[1]+2] == 0&& ptr[0]+1!=19)
			 {
					eraseShape(ptr);
					grid_moving[ptr[0]+1][ptr[1]] = shape4[0][0];
					grid_moving[ptr[0]+1][ptr[1]+1] = shape4[0][1];
					//grid_moving[ptr[0]+1][ptr[1]+2] = shape4[0][2];
					//grid_moving[ptr[0]+1][ptr[1]+3] = shape4[0][3];
					//grid_moving[ptr[0]+2][ptr[1]] = shape4[0][4];
					grid_moving[ptr[0]+2][ptr[1]+1] = shape4[0][5];
					grid_moving[ptr[0]+2][ptr[1]+2] = shape4[0][6];
					//grid_moving[ptr[0]+2][ptr[1]+3] = shape4[0][7];
					rotCounter =0;
			}
			else still_moving[0] = 0;
		}
	}
	if(block_index ==5)
	{
		if(rotCounter==1)
		{
			if (grid_land[ptr[0]-1][ptr[1]] == 0 && grid_land[ptr[0]][ptr[1]] == 0 && grid_land[ptr[0]][ptr[1]+1]==0 && grid_land[ptr[0]+1][ptr[1]+1] == 0&& ptr[0]+1!=20) {
				eraseShape(ptr);
				grid_moving[ptr[0]-1][ptr[1]] = shape5[1][0];
				//grid_moving[ptr[0]-1][ptr[1]+1] = shape5[1][1];
				grid_moving[ptr[0]][ptr[1]] = shape5[1][2];
				grid_moving[ptr[0]][ptr[1]+1] = shape5[1][3];
				//grid_moving[ptr[0]+1][ptr[1]] = shape5[1][4];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape5[1][5];
				//grid_moving[ptr[0]+2][ptr[1]] = shape5[1][6];
				//grid_moving[ptr[0]+2][ptr[1]+1] = shape5[1][7];
			}
			else still_moving[0] = 0;
		}
		else 
		{
			if (grid_land[ptr[0]+2][ptr[1]] == 0 && grid_land[ptr[0]+2][ptr[1]+1] == 0 && grid_land[ptr[0]+1][ptr[1]+1]==0 && grid_land[ptr[0]+1][ptr[1]+2]==0 && ptr[0]+1!=19) {
				eraseShape(ptr);
				//grid_moving[ptr[0]+1][ptr[1]] = shape5[0][0];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape5[0][1];
				grid_moving[ptr[0]+1][ptr[1]+2] = shape5[0][2];
				//grid_moving[ptr[0]+1][ptr[1]+3] = shape5[0][3];
				grid_moving[ptr[0]+2][ptr[1]] = shape5[0][4];
				grid_moving[ptr[0]+2][ptr[1]+1] = shape5[0][5];
				//grid_moving[ptr[0]+2][ptr[1]+2] = shape5[0][6];
				//grid_moving[ptr[0]+2][ptr[1]+3] = shape5[0][7];
				rotCounter =0;
			}
			else still_moving[0] = 0;
		}
	}
	if(block_index == 6)
	{
		if(rotCounter==1)
		{
			if (grid_land[ptr[0]-1][ptr[1]] == 0 &&grid_land[ptr[0]][ptr[1]] == 0 &&grid_land[ptr[0]+1][ptr[1]] == 0 &&grid_land[ptr[0]+2][ptr[1]] == 0 && ptr[0]+1!=19 ) {
				eraseShape(ptr);
				grid_moving[ptr[0]-1][ptr[1]] = shape6[1][0];
				//grid_moving[ptr[0]-1][ptr[1]+1] = shape6[1][1];
				grid_moving[ptr[0]][ptr[1]] = shape6[1][2];
				//grid_moving[ptr[0]][ptr[1]+1] = shape6[1][3];
				grid_moving[ptr[0]+1][ptr[1]] = shape6[1][4];
				//grid_moving[ptr[0]+1][ptr[1]+1] = shape6[1][5];
				grid_moving[ptr[0]+2][ptr[1]] = shape6[1][6];
				//grid_moving[ptr[0]+2][ptr[1]+1] = shape6[1][7];
			}
			else still_moving[0] = 0;
		}
		else 
		{
			if (grid_land[ptr[0]+1][ptr[1]] == 0 && grid_land[ptr[0]+1][ptr[1]+1] == 0 && grid_land[ptr[0]+1][ptr[1]+2] == 0 && grid_land[ptr[0]+1][ptr[1]+3] == 0&& ptr[0]+1!=20) {
				eraseShape(ptr);
				grid_moving[ptr[0]+1][ptr[1]] = shape6[0][0];
				grid_moving[ptr[0]+1][ptr[1]+1] = shape6[0][1];
				grid_moving[ptr[0]+1][ptr[1]+2] = shape6[0][2];
				grid_moving[ptr[0]+1][ptr[1]+3] = shape6[0][3];
				//grid_moving[ptr[0]+2][ptr[1]] = shape6[0][4];
				//grid_moving[ptr[0]+2][ptr[1]+1] = shape6[0][5];
				//grid_moving[ptr[0]+2][ptr[1]+2] = shape6[0][6];
				//grid_moving[ptr[0]+2][ptr[1]+3] = shape6[0][7];
				rotCounter =0;
			}
			else still_moving[0] = 0;
		}
	}
	if(block_index == 7)
	{
		if (grid_land[ptr[0]+1][ptr[1]] == 0 && grid_land[ptr[0]+1][ptr[1]+1] == 0 && grid_land[ptr[0]+2][ptr[1]] == 0 && grid_land[ptr[0]+2][ptr[1]+1] == 0 && ptr[0]+1!=19) {
			eraseShape(ptr);
			grid_moving[ptr[0]+1][ptr[1]] = shape7[0];
			grid_moving[ptr[0]+1][ptr[1]+1] = shape7[1];
			//grid_moving[ptr[0]+1][ptr[1]+2] = shape7[2];
			//grid_moving[ptr[0]+1][ptr[1]+3] = shape7[3];
			grid_moving[ptr[0]+2][ptr[1]] = shape7[4];
			grid_moving[ptr[0]+2][ptr[1]+1] = shape7[5];
			//grid_moving[ptr[0]+2][ptr[1]+2] = shape7[6];
			//grid_moving[ptr[0]+2][ptr[1]+3] = shape7[7];
			rotCounter =0;
		}
		else still_moving[0] = 0;
	}


		printf("%x\n",ptr[0]);
		printf("%x\n",ptr[1]);


		if (still_moving) ptr[0] = ptr[0]+1;
		return ptr;
		
}

static void addGrid()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<10;j++)
		{
			
			if(grid_moving[i][j]>0 && grid_land[i][j] ==0)
			{
				grid[i][j] = grid_moving[i][j];
			}
			else if(grid_moving[i][j]==0 && grid_land[i][j] >0)
			{
				grid[i][j] = grid_land[i][j];
			}
			else if(grid_moving[i][j]==0 && grid_land[i][j] ==0)
			{
				grid[i][j] = 0;
			}
		}
	}
}



static int checkMoveLeft(int *ptr)
{
	if(rotCounter==0 || rotCounter ==2)
	{
		if(grid_land[ptr[0]][ptr[1]-1]==0 && grid_land[ptr[0]+1][ptr[1]-1]==0 )
		{
			return 0; 
		}
		else if(((grid_land[ptr[0]][ptr[1]-1]==0 && grid_moving[ptr[0]][ptr[1]-1]>0)&&(grid_land[ptr[0]+1][ptr[1]-1]>0 && grid_moving[ptr[0]+1][ptr[1]-1]==0)) || ((grid_land[ptr[0]][ptr[1]-1]>0 && grid_moving[ptr[0]][ptr[1]]==0) && ((grid_land[ptr[0]][ptr[1]-1]==0 && grid_moving[ptr[0]][ptr[1]]>0))))
		{
			return 0;
		}
	}
	else if(rotCounter ==1 || rotCounter ==3)
	{
		if(block_index == 6)
		{
			if(grid_land[ptr[0]-1][ptr[1]]==0 && grid_land[ptr[0]][ptr[1]]==0 && grid_land[ptr[0]+1][ptr[1]]==0 && grid_land[ptr[0]+2][ptr[1]]==0)
			{
				return 0;
			}
		}
		else 
		{
			if(grid_land[ptr[0]][ptr[1]-1]==0 && grid_land[ptr[0]+1][ptr[1]-1]==0 && grid_land[ptr[0]+2][ptr[1]-1]==0  )
			{
				return 0; 
			}
			else if(((grid_land[ptr[0]-1][ptr[1]-1]+grid_moving[ptr[0]-1][ptr[1]] == grid_land[ptr[0]-1][ptr[1]-1])||(grid_land[ptr[0]-1][ptr[1]-1]+grid_moving[ptr[0]-1][ptr[1]] == grid_moving[ptr[0]-1][ptr[1]])) 
				&& ((grid_land[ptr[0]][ptr[1]-1]+grid_moving[ptr[0]][ptr[1]] == grid_land[ptr[0]][ptr[1]-1])||(grid_land[ptr[0]][ptr[1]-1]+grid_moving[ptr[0]][ptr[1]] == grid_moving[ptr[0]][ptr[1]]))
				&&((grid_land[ptr[0]+1][ptr[1]-1]+grid_moving[ptr[0]+1][ptr[1]] == grid_land[ptr[0]+1][ptr[1]-1])||(grid_land[ptr[0]+1][ptr[1]-1]+grid_moving[ptr[0]+1][ptr[1]] == grid_moving[ptr[0]+1][ptr[1]])))
			{
				return 0;
			}
		}
	}
	return 1;
}

static int moveLeft(int shape[8],int * ptr) {

	//erase the old shape
	if ((ptr[1] - 1) >=0) 
		{
			if(!checkMoveLeft(ptr))
			{
				eraseShape(ptr);
				ptr[1] = ptr[1] - 1;
			}
		}
	else if ((ptr[1] - 1) == 0) {
		if (shape[0] == 0 && shape[4] == 0)
		{
			if(!checkMoveLeft(ptr))
			{
				eraseShape(ptr);
				ptr[1] = ptr[1] - 1;
			}
		}
	}
	return ptr[1];
}
static int checkMoveRight()
{

}

static int moveRight(int shape[8],int * ptr) {
if(rotCounter == 0||rotCounter==2)
	{
		if(ptr[1]+4 < 10)
		{
			if(grid_land[ptr[0]][ptr[1]+4] == 0 && grid_land[ptr[0]+1][ptr[1]+4]==0)
			{
				ptr[1] = ptr[1] + 1;
			}
		}
		else
		{
			if(ptr[1]+4 == 10)
			{
				if(grid_land[ptr[0]][ptr[1]+3] == 0 && grid_land[ptr[0]+1][ptr[1]+3]==0)
				{
					if(shape[3] == 0 && shape[7] == 0)
					{
						ptr[1] = ptr[1] + 1;
					}
				}
			}
			else if(ptr[1]+4 == 11)
			{
				if(block_index == 7)
				{
					if(grid_land[ptr[0]][ptr[1]+2] == 0 && grid_land[ptr[0]+1][ptr[1]+2]==0)
					{
						ptr[1] = ptr[1] + 1;
					}
				}
			}
		}
	}
	else 
	{
		if(ptr[1]+2 < 10)
		{
			if(grid_land[ptr[0]][ptr[1]+2] == 0 && grid_land[ptr[0]+1][ptr[1]+2]==0 && grid_land[ptr[0]+2][ptr[1]+2] == 0 && grid_land[ptr[0]+3][ptr[1]+2]==0)
			{
				ptr[1] = ptr[1] + 1;
			}
		}
		else
		{
			if(ptr[1]+2 == 10)
			{
				if(grid_land[ptr[0]][ptr[1]+1] == 0 && grid_land[ptr[0]+1][ptr[1]+1]==0 && grid_land[ptr[0]+1][ptr[1]+2] == 0 && grid_land[ptr[0]+3][ptr[1]+1]==0)
				{
					if(block_index == 6)
					{
						ptr[1] = ptr[1] + 1;
					}
				}
			}
		}
	}









	// 	if ((ptr[1] + 4) <= 9) 
	// 	{
	// 		if(grid_land[ptr[0]][ptr[1]+4] == 0 && grid_land[ptr[0]+1][ptr[1]+4])==0
	// 		{
	// 			//eraseShape(ptr);
	// 			ptr[1] = ptr[1] + 1;
	// 		}
	// 	}
	// 	//bounds check to the right.
	// 	else if ((ptr[1] + 4) == 10) {
	// 		if (shape[3] == 0 && shape[7] == 0)
	// 		{
	// 			if(grid_land[ptr[0]+3][ptr[1]+3] == 0 && grid_land[ptr[0]+3][ptr[1]+3])
	// 			{
	// 				//eraseShape(ptr);
	// 				ptr[1] = ptr[1] + 1;
	// 			}
	// 		}
	// 		if(block_index==7)
	// 		{
	// 			if(grid_land[ptr[0]][ptr[1]+1] == 0)
	// 			{
	// 				//eraseShape(ptr);
	// 				ptr[1] = ptr[1] + 1;
	// 			}
	// 		}
	// 	}
	// }
	// else
	// {
	// 	if ((ptr[1] + 2) < 10) 
	// 	{
	// 		if(grid_land[ptr[0]][ptr[1]+1] == 0)
	// 		{
	// 			//eraseShape(ptr);
	// 			ptr[1] = ptr[1] + 1;
	// 		}
	// 	}
	// 	//bounds check to the right.
	// 	else if ((ptr[1] + 2) == 10) {
	// 		if (shape[3] == 0 && shape[7] == 0) 
	// 		{
	// 			if(grid_land[ptr[0]][ptr[1]+1] == 0)
	// 			{
	// 				//eraseShape(ptr);
	// 				ptr[1] = ptr[1] + 1;
	// 			}
	// 		}
	// 	}
	// }

	return ptr[1];

}

static int checkMoveDown(int *ptr)
{
	if(rotCounter==0 || rotCounter ==2)
	{
		if(grid_land[ptr[0]+2][ptr[1]]==0 && grid_land[ptr[0]+2][ptr[1]+1]==0 && grid_land[ptr[0]+2][ptr[1]+2]==0 && grid_land[ptr[0]+2][ptr[1]+3]==0)
		{
			return 0; 
		}
		else if(grid_land[ptr[0]+2][ptr[1]]==0 && grid_land[ptr[0]+2][ptr[1]+1]==0 && grid_land[ptr[0]+2][ptr[1]+2]==0 && block_index!=6)
		{
			return 0;
		}
		else if(grid_land[ptr[0]+2][ptr[1]]==0 && grid_land[ptr[0]+2][ptr[1]+1]==0 && block_index==7)
		{
			return 0; 
		}
	}
	else if(rotCounter ==1 || rotCounter ==3)
	{
		if(block_index == 6)
		{
			if(grid_land[ptr[0]+2][ptr[1]]==0)
			{
				return 0;
			}
		}
		else 
		{
			if(grid_land[ptr[0]][ptr[1]-1]==0 && grid_land[ptr[0]+1][ptr[1]-1]==0 && grid_land[ptr[0]+2][ptr[1]-1]==0  )
			{
				return 0; 
			}
			else if(((grid_land[ptr[0]-1][ptr[1]-1]+grid_moving[ptr[0]-1][ptr[1]] == grid_land[ptr[0]-1][ptr[1]-1])||(grid_land[ptr[0]-1][ptr[1]-1]+grid_moving[ptr[0]-1][ptr[1]] == grid_moving[ptr[0]-1][ptr[1]])) 
				&& ((grid_land[ptr[0]][ptr[1]-1]+grid_moving[ptr[0]][ptr[1]] == grid_land[ptr[0]][ptr[1]-1])||(grid_land[ptr[0]][ptr[1]-1]+grid_moving[ptr[0]][ptr[1]] == grid_moving[ptr[0]][ptr[1]]))
				&&((grid_land[ptr[0]+1][ptr[1]-1]+grid_moving[ptr[0]+1][ptr[1]] == grid_land[ptr[0]+1][ptr[1]-1])||(grid_land[ptr[0]+1][ptr[1]-1]+grid_moving[ptr[0]+1][ptr[1]] == grid_moving[ptr[0]+1][ptr[1]])))
			{
				return 0;
			}
		}
	}
	return 1;
}
static int moveDown(int shape[8],int * ptr,int grid[20][10]) {
	
	//erase the old shape
	//eraseShape(ptr);
	if ((ptr[0] + 1) <= 16) {
		// if(!checkMoveDown(ptr))
		// {
			eraseShape(ptr);
			ptr[0] = ptr[0] + 1;
		// }
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
		grid_moving[ptr[0]][ptr[1]] = 0;
		grid_moving[ptr[0]][ptr[1]+1] = 0;
		grid_moving[ptr[0]][ptr[1]+2] = 0;
		grid_moving[ptr[0]][ptr[1]+3] = 0;
		grid_moving[ptr[0]+1][ptr[1]] = 0;
		grid_moving[ptr[0]+1][ptr[1]+1] = 0;
		grid_moving[ptr[0]+1][ptr[1]+2] = 0;
		grid_moving[ptr[0]+1][ptr[1]+3] = 0;
	}
	else {
		grid_moving[ptr[0]-3][ptr[1]] = 0;
		grid_moving[ptr[0]-3][ptr[1]+1] = 0;
		grid_moving[ptr[0]-2][ptr[1]] = 0;
		grid_moving[ptr[0]-2][ptr[1]+1] = 0;
		grid_moving[ptr[0]-1][ptr[1]] = 0;
		grid_moving[ptr[0]-1][ptr[1]+1] = 0;
		grid_moving[ptr[0]][ptr[1]] = 0;
		grid_moving[ptr[0]][ptr[1]+1] = 0;
		grid_moving[ptr[0]+1][ptr[1]] = 0;
		grid_moving[ptr[0]+1][ptr[1]+1] = 0;
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
	int randNum;
		randNum = rand()%7;
	//randNum = 6;
	//randNum = 5;
		printf("%d\n",randNum );

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

static int checkBounds(int * ptr) {
	if(rotCounter ==1 || rotCounter ==3)
	{
		if(block_index == 6)
		{
			if(ptr[0]==17) return 1;
		}
		else{
			if(ptr[0] ==18) return 1;
		}
	}
	else{
		if(block_index == 6)
		{
			if(ptr[0]==18) return 1;
		}
		else{
			if (ptr[0] == 17) return 1;
		}
	}
	 return 0;
}

static int checkEndGame(int grid[20][10], int still_moving) {
	int i,j;
	for (i = 0; i < 20; i++) {
		if ((grid[0][i] > 0 )&& (still_moving ==0)) return 1;
	}
	
	 return 0;
}

static void rowDown(int row_index)
{
	int i,j;
	while(row_index>0)
	{ 
		printf("%d\n",row_index);
		for(j=0;j<10;j++)
		{
			grid_land[row_index][j] = grid_land[row_index-1][j];
		}
		row_index--;
	}
	for(j=0;j<10;j++)
		{
			grid_land[0][j] = 0;
		}
}

static void PointAdd()
{
	point +=10;
}
static void deletionFilledRows()
{
	int i,j;
	for(i=0;i<20;i++)
	{
		//printf("%d\n",i);
		int count_filled = 0;
		for(j=0;j<10;j++)
		{
			if(grid_land[i][j]>0)
			{
				count_filled ++ ;
			}
		}
		if(count_filled == 10)
		{
			//printf("%d\n",i);
			PointAdd();
			rowDown(i);
		}
	}
}

	
int main() {

	initialize_grids();
	//grid_land_Default();
	//draw initial grid
	addGrid();
	drawGrid();
	int check[8];

	int hello;
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
	
	int still_moving = 1;
	int first_line = 0;
	
	int random_num;

	int * start_ptr = start_pt;
	int * first_row = check;
	int * stl_mov_ptr = &still_moving;

	srand ( time(NULL) );
	randomShape();
	drawShape(curBlock);
	addGrid();
	drawGrid();
	int i,j;

	rotCounter = 0;
	while(1){
	for (i = 0; i < 500000000;i++);
		if (still_moving){			
			if (kbhit()) {
					if(!checkBounds(start_ptr) && !checkMoveDown(start_ptr))
					{
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
							if(!checkMoveDown(start_ptr))
							{
								start_ptr[0] = moveDown(curBlock,start_ptr,grid);
							}
						
						//printf("after:%d\n",start_ptr[0]);
					}
				}
			}
			
			start_ptr = moveShape(curBlock,start_ptr,stl_mov_ptr);
			addGrid();
			drawGrid();
			printf("%d\n",still_moving);
		}
		else {
			land_fix();

			eraseShape(start_ptr);
			deletionFilledRows();

			addGrid();

			for(i=0;i<20;i++)
			{
				for(j=0;j<10;j++)
				{
					printf("%d",grid[i][j]);
					if(j==9)
						printf("\n");
				}
			}
			
			int endGame = checkEndGame(grid,still_moving);
			if (endGame) break;
			start_pt[0] =1;
			start_pt[1] = 3;
			//drawGrid();
			
			randomShape();
			drawShape(curBlock);
			addGrid();
			drawGrid();
			still_moving = 1;
			rotCounter=0;
			
		}
		//printf("still:%d\n",still_moving);
	}
	return 0;
}
