#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int grid[20][12];

int shape1[8] = {0,1,0,0,
		 1,1,1,0};
int shape2[8] = {1,1,0,0,
		 0,1,1,0};
int shape3[8] = {0,0,0,0,
		 1,1,1,1};

int i,j;

static void drawGrid(int grid[20][12]) {
	
for (i = 0; i < 20; i ++) {
	for (j = 0;j < 12;j++) {
		if (j == 0 || j == 11) {
			grid[i][j] = 1;
		}
		else if (i== 0 || i == 19) {
			grid[i][j] = 1;
		}
	}
}

for (i = 0; i < 20; i ++) {
	for (j = 0;j < 12;j++) {
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

static int * moveShape(int shape[8], int * ptr, char c) {

	//erase the old shape
	grid[ptr[0]][ptr[1]] = 0;
	grid[ptr[0]][ptr[1]+1] = 0;
	grid[ptr[0]][ptr[1]+2] = 0;
	grid[ptr[0]][ptr[1]+3] = 0;
	grid[ptr[0]+1][ptr[1]] = 0;
	grid[ptr[0]+1][ptr[1]+1] = 0;
	grid[ptr[0]+1][ptr[1]+2] = 0;
	grid[ptr[0]+1][ptr[1]+3] = 0;


	int rows,cols;
    char buf[200];
    char garbage[2];
    int move_success = 0;

    
    switch ( c ) 
    {
    case 'w':
        grid[ptr[0]+1][ptr[1]] = shape[0];
				grid[ptr[0]+1][ptr[1]+1] = shape[1];
				grid[ptr[0]+1][ptr[1]+2] = shape[2];
				grid[ptr[0]+1][ptr[1]+3] = shape[3];
				grid[ptr[0]+2][ptr[1]] = shape[4];
				grid[ptr[0]+2][ptr[1]+1] = shape[5];
				grid[ptr[0]+2][ptr[1]+2] = shape[6];
				grid[ptr[0]+2][ptr[1]+3] = shape[7];
        break;
    case 'a':
    	if(ptr[1]>0){
	      grid[ptr[0]+1][ptr[1]-1] = shape[0];
				grid[ptr[0]+1][ptr[1]] = shape[1];
				grid[ptr[0]+1][ptr[1]+1] = shape[2];
				grid[ptr[0]+1][ptr[1]+2] = shape[3];
				grid[ptr[0]+2][ptr[1]-1] = shape[4];
				grid[ptr[0]+2][ptr[1]] = shape[5];
				grid[ptr[0]+2][ptr[1]+1] = shape[6];
				grid[ptr[0]+2][ptr[1]+2] = shape[7];
			}
        break;
    case 's':
        grid[ptr[0]+1][ptr[1]] = shape[0];
				grid[ptr[0]+1][ptr[1]+1] = shape[1];
				grid[ptr[0]+1][ptr[1]+2] = shape[2];
				grid[ptr[0]+1][ptr[1]+3] = shape[3];
				grid[ptr[0]+2][ptr[1]] = shape[4];
				grid[ptr[0]+2][ptr[1]+1] = shape[5];
				grid[ptr[0]+2][ptr[1]+2] = shape[6];
				grid[ptr[0]+2][ptr[1]+3] = shape[7];
        break;
    case 'd':
        if(ptr[1]+4<12){
	      grid[ptr[0]+1][ptr[1]+1] = shape[0];
				grid[ptr[0]+1][ptr[1]+2] = shape[1];
				grid[ptr[0]+1][ptr[1]+3] = shape[2];
				grid[ptr[0]+1][ptr[1]+4] = shape[3];
				grid[ptr[0]+2][ptr[1]+1] = shape[4];
				grid[ptr[0]+2][ptr[1]+2] = shape[5];
				grid[ptr[0]+2][ptr[1]+3] = shape[6];
				grid[ptr[0]+2][ptr[1]+4] = shape[7];
			}
        break;

        
    default: //any other input
        //printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    	grid[ptr[0]+1][ptr[1]] = shape[0];
			grid[ptr[0]+1][ptr[1]+1] = shape[1];
			grid[ptr[0]+1][ptr[1]+2] = shape[2];
			grid[ptr[0]+1][ptr[1]+3] = shape[3];
			grid[ptr[0]+2][ptr[1]] = shape[4];
			grid[ptr[0]+2][ptr[1]+1] = shape[5];
			grid[ptr[0]+2][ptr[1]+2] = shape[6];
			grid[ptr[0]+2][ptr[1]+3] = shape[7];
			break;
    }

	ptr[0] = ptr[0]+1;
	return ptr;
	
}

static int checkBounds(int * ptr) {
	if (ptr[0] == 17) return 1;
	else return 0;
}


static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}



int main() {
	
	drawGrid(grid);		//draw initial grid
	
	int start_pt[2] = {1,3};
	
	int * start_ptr = start_pt;
	
	drawShape(shape1);
	drawGrid(grid);
	char c;
	while(!checkBounds(start_ptr)){
		for (i = 0; i < 500000000;i++);
		c = getch();
		printf("character : %c\n",c);
		start_ptr = moveShape(shape1,start_ptr,c);
		drawGrid(grid);
	}
	return 0;
}



