#include "GameOfLife.h"


/*
Just a beautiful pattern from an attempt to make a circle
Returns a boolean array, true: cell alive, false: cell not alive 
*/
boolp initBeautifulPattern() {
	int i = 0, j = 0, middle = GRID_SIZE / 2, radius = GRID_SIZE / 4;
	boolp result = malloc(sizeof(bool) * GRID_SIZE * GRID_SIZE);
	int k = 0;

	for (i = 0; i < GRID_SIZE; i++) {
		for (j = 0; j < GRID_SIZE; j++) {
			if (middle - radius == i || middle + radius == i || middle + radius == j || middle - radius == j)
				result[i*GRID_SIZE + j] = true;
			else
				result[i*GRID_SIZE + j] = false;
		}
	}
	return result;
}

/*
Init a circle 
Return array of booleans indicating a live cell if true
*/
boolp initCircle() {
	int y = 0, x = 0, middle = GRID_SIZE / 2, radius = GRID_SIZE / 4;
	boolp result = malloc(sizeof(bool) * GRID_SIZE * GRID_SIZE);
	int k = 0;

	for (y = 0; y < GRID_SIZE; y++) {
		for (x = 0; x < GRID_SIZE; x++) {
			/* Check if point in circle (in constraints of radius)*/
			if (((x + k) == middle || (x - k) == middle) && y > middle - radius && y < middle + radius) {
				result[y*GRID_SIZE + x] = true;
				result[y*GRID_SIZE + (++x)] = true;
			}
			else 
				result[y*GRID_SIZE + x] = false;
		}
		if (y > (middle - radius) && y < middle) /* Above middle of circle */
			k++;
		else if (y >= middle && y <=(middle + radius)) /* Below middle of circle */
			k--;
	}
	return result;
}

/*
Constructs points to be considered as alive during
init of pattern
*/
sp constructLivePointsStruct(int wanted){
	int size_y = SIZEY(wanted), size_x = SIZEY(wanted);
	p insert_points = malloc(sizeof(point) * size_y * size_x);
	sp ret = malloc(sizeof(struc));
	
	int y = 0, x = 0;
	int alive_counter = 0;
	for(y = 0; y < size_y; y++){
		for (x = 0; x < size_x; x++){
			// tell whether alive during to figure pattern
			if(GET_IS_ALIVE(wanted,y,x)){
				point insert;
				insert.y = y;
				insert.x = x;
				insert_points[alive_counter] = insert;
				alive_counter++;
			}
		}
	}

	ret->points = insert_points;
	ret->size = alive_counter;
	return ret;
}

void freePattern(sp to_free){
	free(to_free->points);
	free(to_free);
}

/*
Uses
*/
boolp initWantedPattern(int wanted){
	int i = 0;
	point initial_start;
	initial_start.x = GRID_SIZE/2;
	initial_start.y = GRID_SIZE/2;
	sp pattern = constructLivePointsStruct(wanted);
	boolp result = malloc(sizeof(bool) * GRID_SIZE * GRID_SIZE); 

	for (i = 0;i < GRID_SIZE * GRID_SIZE;i++) 
		result[i] = false;
	for (i = 0; i < pattern->size;i++ ){
		result[(initial_start.y + pattern->points[i].y) * GRID_SIZE + initial_start.x + pattern->points[i].x ] = true;
	}
	freePattern(pattern);
	return result;
}


void printPattern(boolp result) {
	int i = 0, j = 0;
	// Print the result string
	for (i = 0; i < GRID_SIZE; i++) {
		for (j = 0; j < GRID_SIZE; j++) {
			if (result[i*GRID_SIZE + j])
				printf("* ");
			else printf("  ");
		}
		puts("");
	}

}

boolp copyPattern(boolp dst, boolp src, int size) {
	int i = 0;
	for (; i < size; i++) {
		dst[i] = src[i];
	}
	return dst;
}

int getNeighbor(boolp pattern, int y, int x, int dy, int dx, int size) {
	// Check if in constraints of frame
	if (y - dy < 0 || y + dy > size || x - dx < 0 || x + dx > size)  // Out of the grid
		return 0;
	return pattern[(y + dy) * GRID_SIZE + dx + x];
}

int isAlive(boolp pattern, int y, int x, int size) {
	return getNeighbor(pattern,y, x, 0, 0, size);
}

/*
Checks if cell has to be alive according to the rules about alive neighnors of cell:
4 and above cell dies from overpopulation
0,1 dies from loneliness
2,3 live cell stays alive 
3 dead cell becomes alive (from birth)
*/
bool beAlive(boolp pattern, int y, int x, int size) {
	int i = 0, j = 0;

	int is_alive = isAlive(pattern, y, x, size);

	int top_left = getNeighbor(pattern, y, x, -1, -1, size);
	int top_right = getNeighbor(pattern, y, x, -1, 1, size);

	int top = getNeighbor(pattern, y, x, -1, 0, size);
	int down = getNeighbor(pattern, y, x, 1, 0, size);

	int down_right = getNeighbor(pattern, y, x, 1, 1, size);
	int down_left = getNeighbor(pattern, y, x, 1, -1, size);

	int left = getNeighbor(pattern, y, x, 0, -1, size);
	int right = getNeighbor(pattern, y, x, 0, 1, size);

	int alive_neighbors = top + down + top_left + top_right + down_right + down_left + left + right;
	
	if (alive_neighbors < 2 || alive_neighbors > 3) return false;
	else if (!is_alive && alive_neighbors == 2)
		return false;
	return true;
}

/*
Makes one move for all cells of pattern according to the rules of life
*/
boolp changePattern(boolp pattern, int size) {
	int i = 0, j = 0;
	// According to rules can't change pattern explicitly on the loop
	boolp result = malloc(sizeof(bool) * size * size );
	
	for (i; i < size; i++) {
		for (j = 0; j < size; j++) {
			result[i*size + j] = beAlive(pattern, i, j, size);
		}
	}
	// After all moves calculated apply changes
	copyPattern(pattern, result, size * size);
	free(result);
	return pattern;
}

void delay(int time_limit)
{
	// Stroing start time
	clock_t start_time = clock();

	// looping till required time is not acheived
	while (clock() < start_time + time_limit)
		;
}

void start_game() {
	int i = 0, max_times = 50;
	//boolp result = initPattern();
	//boolp result = initCircle();
	boolp result = initWantedPattern(PULSAR);

	for (i = 0; i < max_times; i++) {
		printPattern(result);
		puts("");
		result = changePattern(result, GRID_SIZE);
		
		delay(500000);
	}

	free(result);
}

void mainGameOfLifeLoop() {
	start_game();
}

int main(){
	mainGameOfLifeLoop();
}