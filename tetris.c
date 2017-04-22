#include <stdio.h>

int grid[20][10];

int shape1[8] = {0,1,0,0,
		 1,1,1,0};
int shape2[8] = {1,1,0,0,
		 0,1,1,0};
int shape3[8] = {0,0,0,0,
		 1,1,1,1};

int i,j;

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
	grid[ptr[0]][ptr[1]] = 0;
	grid[ptr[0]][ptr[1]+1] = 0;
	grid[ptr[0]][ptr[1]+2] = 0;
	grid[ptr[0]][ptr[1]+3] = 0;
	grid[ptr[0]+1][ptr[1]] = 0;
	grid[ptr[0]+1][ptr[1]+1] = 0;
	grid[ptr[0]+1][ptr[1]+2] = 0;
	grid[ptr[0]+1][ptr[1]+3] = 0;

	//draw the new shape
	grid[ptr[0]+1][ptr[1]] = shape[0];
	grid[ptr[0]+1][ptr[1]+1] = shape[1];
	grid[ptr[0]+1][ptr[1]+2] = shape[2];
	grid[ptr[0]+1][ptr[1]+3] = shape[3];
	grid[ptr[0]+2][ptr[1]] = shape[4];
	grid[ptr[0]+2][ptr[1]+1] = shape[5];
	grid[ptr[0]+2][ptr[1]+2] = shape[6];
	grid[ptr[0]+2][ptr[1]+3] = shape[7];
	
	ptr[0] = ptr[0]+1;
	return ptr;
	
}

static int checkBounds(int * ptr) {
	if (ptr[0] == 17) return 1;
	else return 0;
}


int main() {
	
	drawGrid(grid);		//draw initial grid
	
	int start_pt[2] = {1,3};
	
	int * start_ptr = start_pt;
	
	drawShape(shape1);
	drawGrid(grid);

	while(!checkBounds(start_ptr)){
		for (i = 0; i < 500000000;i++);
		start_ptr = moveShape(shape1,start_ptr);
		drawGrid(grid);
	}
	return 0;
}



