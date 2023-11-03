#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <string.h>   
#define MAX_BUFFER 256
#define MAX_ARRAY_SIZE 20000

//STRUCT FOR REVIEW
int number_comparisons = 0;
int number_swaps = 0;

//DECLARATION
int next_field( FILE *f, char *buf, int max );

typedef struct Game {
    char name[MAX_BUFFER];
    char platform[MAX_BUFFER];
    int score;
    int year;
} Game;

//ARRAY OF GAMES

Game GameArray[MAX_ARRAY_SIZE];

//CSV PARSER
void ReadtoArr(FILE *f, Game * game){
    char buf[MAX_BUFFER];
    next_field(f, buf, MAX_BUFFER);
    strcpy(game->name, buf);
    //printf(" %s ", game->name);
    next_field(f, buf, MAX_BUFFER);
    strcpy(game->platform, buf);
    next_field(f, buf, MAX_BUFFER);
    game->score = atoi(buf);
    next_field(f, buf, MAX_BUFFER);
    game->year = atoi(buf);
}

void insertionSort(Game arr[], int size) 
{ 
  //TODO
  for(int i = 0; i < size; i++){
    Game curr = arr[i]; //VALUE OF CURRENT ITEM
    int prev = i - 1; //INDEX OF PREV ITEM
    int sentinel = 0;
    number_comparisons++;
    number_comparisons++;
    //printf("running");
    if (prev >= 0 && arr[prev].score > curr.score){
      sentinel = 1;
    }
    while (sentinel == 1){
      number_comparisons++;
      number_comparisons++;
      arr[prev + 1] = arr[prev]; //bring the bigger num forward
      number_swaps++;
      prev = prev - 1;//so we can compare the num before for if bigger?
      if (prev >= 0 && arr[prev].score > curr.score){
        sentinel = 1;
      }
      else{
        sentinel = 0;
      }
    }
    arr[prev + 1] = curr; // So now, we have assigned the curr val to its required pos
  }
  
}


int next_field( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

int parser ( int argc, char *argv[] ) {
	FILE *f;		
	char buffer[MAX_BUFFER];

	// Users must pass the name of the input file through the command line. Make sure
	// that we got an input file. If not, print a message telling the user how to use
	// the program and quit
	if( argc < 2 ) { 
		printf("usage: csv FILE\n"); 
		return EXIT_FAILURE; 
	}

	// Try to open the input file. If there is a problem, report failure and quit
	f = fopen(argv[1], "r");
	if(!f) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}
    int row = 0;
	while( !next_field(f, buffer, MAX_BUFFER) ); // discard the header
	// Now read and print records until the end of the file
	while(!feof(f)) {
        ReadtoArr(f, &GameArray[row]);
        //printf("running");
		//printf("%s%c\n", buffer, ((eor)? '\n':' '));  // double newline if eor is not 0
        row++;
	}
	// Always remember to close the file
	fclose(f);
	return row;
}
void print(Game arr[], int max){
    for(int i = 0; i < 10; i++){
        printf("%s   %d\n", arr[i].name, arr[i].score);
    }
}

int main(int argc, char *argv[] ){
    int rows = parser(argc, argv);
    //printf("%d", rows);
    //TESTING 
    insertionSort(GameArray, rows);
    print(GameArray, rows);    
}