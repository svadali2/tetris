#include <stdio.h>
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

int shape1[4][8] = {{0,1,0,0,
		 							1,1,1,0},
		 							{1,0,1,1,
		 							 1,0,0,0},
		 							{1,1,1,0,
		 							0,1,0,0},
		 							{0,1,1,1,
		 							0,1,0,0}};
int shape2[8] = {1,1,0,0,
		 0,1,1,0};
int shape3[8] = {0,0,0,0,
		 1,1,1,1};
int block_index = 0; 
int i,j;
int vertCheck = 0; 
int curBlock[8] = {0,0,0,0,
									0,0,0,0 };
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

static int * moveShape(int shape[8], int * ptr) {

	//erase the old shape
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



	//draw the new shape
	if(rotCounter==1)
	{
		grid[ptr[0]-2][ptr[1]] = shape1[1][0];
		grid[ptr[0]-2][ptr[1]+1] = shape1[1][1];
		grid[ptr[0]-1][ptr[1]] = shape1[1][2];
		grid[ptr[0]-1][ptr[1]+1] = shape1[1][3];
		grid[ptr[0]][ptr[1]] = shape1[1][4];
		grid[ptr[0]][ptr[1]+1] = shape1[1][5];
		grid[ptr[0]+1][ptr[1]] = shape1[1][6];
		grid[ptr[0]+1][ptr[1]+1] = shape1[1][7];
	}
	else if(rotCounter ==2)
	{
		grid[ptr[0]+1][ptr[1]] = shape1[2][0];
		grid[ptr[0]+1][ptr[1]+1] = shape1[2][1];
		grid[ptr[0]+1][ptr[1]+2] = shape1[2][2];
		grid[ptr[0]+1][ptr[1]+3] = shape1[2][3];
		grid[ptr[0]+2][ptr[1]] = shape1[2][4];
		grid[ptr[0]+2][ptr[1]+1] = shape1[2][5];
		grid[ptr[0]+2][ptr[1]+2] = shape1[2][6];
		grid[ptr[0]+2][ptr[1]+3] = shape1[2][7];
	}
	else if(rotCounter ==3){
		grid[ptr[0]-2][ptr[1]] = shape1[3][0];
		grid[ptr[0]-2][ptr[1]+1] = shape1[3][1];
		grid[ptr[0]-1][ptr[1]] = shape1[3][2];
		grid[ptr[0]-1][ptr[1]+1] = shape1[3][3];
		grid[ptr[0]][ptr[1]] = shape1[3][4];
		grid[ptr[0]][ptr[1]+1] = shape1[3][5];
		grid[ptr[0]+1][ptr[1]] = shape1[3][6];
		grid[ptr[0]+1][ptr[1]+1] = shape1[3][7];
	}
	else{
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

	//printf("%x\n",ptr[0]);
	//printf("%x\n",ptr[1]);


	ptr[0] = ptr[0]+1;
	return ptr;
	
}



static int checkBounds(int * ptr) {
	if (ptr[0] == 19) return 1;
	else return 0;
}

static int moveLeft(int shape[8],int * ptr) {

	//erase the old shape
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

	if ((ptr[1] - 1) >=1) ptr[1] = ptr[1] - 1;
	else if ((ptr[1] - 1) == 0) {
		if (shape[0] == 0 && shape[4] == 0) ptr[1] = ptr[1] - 1;
	}
	return ptr[1];
}

static int moveRight(int shape[8],int * ptr) {

	//erase the old shape
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
	}
	return ptr[1];
}

static int moveDown(int shape[8],int * ptr) {
	
	//erase the old shape
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
	if ((ptr[0] + 1) <= 19) ptr[0] = ptr[0] + 1;
	//printf("%x\n",ptr[0]);
	//printf("%x\n",ptr[1]);
	return ptr[0];
	
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

	if(rotCounter == 1){
		ptr[0] = ptr[0];
	}
	else if(rotCounter ==2){
		ptr[0] = ptr[0]-3;
	}
	else if(rotCounter == 3){
		ptr[0] = ptr[0];
	}
	else if(rotCounter ==4){
		ptr[0] = ptr[0]-3;
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
	char temp[3];
	
	int start_pt[2] = {1,3};
	
	int * start_ptr = start_pt;
	copyBlock(shape1[0],curBlock);
	block_index =1;
	drawShape(curBlock);
	drawGrid(grid);

	rotCounter = 0;
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
			}
		}

		start_ptr = moveShape(curBlock,start_ptr);
		drawGrid(grid);
	}
	return 0;
}



