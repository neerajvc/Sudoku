//Major Project 1
//Neeraj Chand
/*
The following sudoku puzzle will give the user 2 options. 
Option 1 will display a sudoku with some prefilled values, and ask the user to play.
It will validate if the user selects a cell with a prefilled value that cannot be changed and it will alert the 
user to select another cell. Once the correct cell is selected, it will proceed with validating the value as per 
rules of the sudoku game.
Option 2 will be for a randomly generated 9x9 puzzle. It will ask the user if he or she wants to play and easy or a hard puzzle
and it will prefill the number of sqaures accordingly. (I am assuming that an easy game has more prefilled squares.)
All code in this project is original, and I tried to do it to the best of my ability, including a portion of the extra credit.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void display(int[][9], int, int);
void input(int[][9], int[][9]);
int validateInput(int[][9], int, int, int);
void reset(int[][9], int[][9]);
void randomGenerate(int[][9]);

int main()
{
int puzzle[9][9]={{1,2,3, 4,9,7, 8,6,5},
                  {4,5,9, 0,0,0, 0,0,0},
                  {6,7,8, 0,0,0, 0,0,0},
                  {3,0,0, 0,1,0, 0,0,0},
                  {2,0,0, 0,0,0, 0,0,0},
                  {9,0,0, 0,0,5, 0,0,0},
                  {8,0,0, 0,0,0, 0,0,0},
                  {7,0,0, 0,0,0, 0,0,0},
                  {5,0,0, 9,0,0, 0,0,0}};
/*Creating a reset copy for both options: fixed sudoku puzzle and a randomly generated sudoku puzzle.
There are two purposes for the reset copy. Firstly, they provide a copy to check against fixed inputs,
and secondly they can be called to reset the puzzle to its default values.
*/
int orgCopy[9][9];
int resetCopy[9][9];
int r,c;
int choice;
for(r=0;r<9;r++)
{
	for(c=0;c<9;c++)
		{if(puzzle[r][c] != 0){ 
		orgCopy[r][c] = puzzle[r][c];}
	else{
		orgCopy[r][c] = 0;}	
	}
}
//The program starts calling for user inputs from here.
do
{
		printf("\n\n============================================\n");
        printf("\033[22;32mTHE PROGRAM OFFERS THE FOLLOWING CHOICES:\033[0m\n");
        printf("============================================\n");
        printf("Option 1: Play the game with a pre-filled array.\n");
        printf("Option 2: Play a randomly generated 9x9 sudoku game.\n");
		printf("============================================\n");
     	printf("Please enter you choice. (NOTE: To quit the program please enter a choice outside the range.)\n");
		scanf(" %d", &choice);
		
	switch(choice)
	{
	case 1:
		printf("\n\n\033[22;32mThis is the puzzle to start with. Note it has some prefilled values\033[0m");
		printf("\033[22;32m and it won't let you change those.\033[0m\n"); 
        printf("\033[22;32mPlease begin by selecting a row and column to input a value.\033[0m\n");
		display(puzzle,9,9);
		for(r=0;r<9;r++)
			{
			for (c=0;c<9;c++)
        		if (puzzle[r][c] == 0){
        			input(orgCopy, puzzle);
					}
			}
			break;
	case 2:
		printf("\n\n\033[22;32mThis is the puzzle to start with. Note it has some prefilled values\033[0m");
		printf("\033[22;32m and it won't let you change those.\033[0m\n"); 
        printf("\033[22;32m------------------------------------------------------------------------------------------\033[0m\n");
		randomGenerate(puzzle);
		for(r=0;r<9;r++)
			{
			for (c=0;c<9;c++)
        		if (puzzle[r][c] == 0){
        			input(resetCopy, puzzle);
					}
			}
			break;
	}
}
while ((choice >= 1) && (choice <= 2));
if ((choice<1) || (choice>2)){
	printf("\nThe choice you entered is '%d':\n", choice);
	printf("\033[22;31mProgram will quit now!\033[0m\n");
	}
return 0;
}

/*****************************************************/
//This function displays the array
/*****************************************************/
 void display(int puzzle[][9],int r, int c)
 {
 int i, j;
 printf("-------------------------------\n");
     for (i=0; i<r; i++) //row
     {  
		 printf("|");
         for (j=0;j<c; j++) //column
         {
          printf(" %d ", puzzle[i][j]);
          if (((j+1)%3)==0)
             {
             printf("|");
			 }
		}
		printf("\n");
		if (((i+1)%3) == 0) {
		printf("-------------------------------\n");}
	}	
}

/*******************************************************
This is the function that calls the inputs and starts the validating process.
It checks the user selection against the reset copy of the puzzle, and alerts the user
which cells cannot be changed.
It checks  inputs for row, column and checks it against the elements in the row,
checks it against the elements in the column, and it also checks against the elements
int the 9x9 box by calling the validateInput function.
*****************************************************/

void input(int orgCopy[][9], int puzzle[][9])
{
	int a, b, i, value;
	char ans;
	printf("Please select a row between 1-9: ");
	scanf("%d", &a);
	printf("Please select a column between 1-9: ");
	scanf("%d", &b);
	if (orgCopy[a-1][b-1] != 0) 
		printf("\033[22;31mThis is a fixed field. Please select another cell.\033[0m\n");
	else{
		printf("\033[01;32mYour valid numbers for this cell include:\033[0m ");
		for (i=1;i<10;i++){
		if (validateInput(puzzle, a-1, b-1, i)){
			printf("\033[01;32m%d\033[0m ",i);}}
		printf("\n");
	    printf("Please enter a value: ");
		scanf("%d", &value);
			if (validateInput(puzzle, a-1, b-1, value))
				{
				puzzle[a-1][b-1] = value;
				display(puzzle,9,9);
				}
			else
				printf("\033[22;31mThis number is not a valid selection.\033[0m\n");
		}
return;
}

/*******************************************************
This is the validate function that checks the elements against all the elements
in the corresponding row, column and the 9x9 box.
*****************************************************/
int validateInput(int puzzle[][9], int r, int c, int value)
{
int rowStart = (r/3)*3;
int colStart = (c/3)*3;
int i,j;
	for (i=0;i<9;i++)
	{
		if (puzzle[r][i] == value) return 0;
		if (puzzle[i][c] == value) return 0;
		if (puzzle[rowStart + (i%3)][colStart + (i/3)] == value) return 0;
	}
return 1;
}
/*******************************************************
This function resets the puzzle to its default version.
This partcular reset function is for Option 1: Play a prefilled sudoku.
I havent called this function anywhere in my code though as I was trying to think how I could best call it.
Suppose the user is in the middle of the puzzle, and wants to call quits and reset it, he will have to exit the 
current loop and then call for a reset of the function. There are many options where I could include this but none
of them I liked the best and so I left it. I have to work on it and find an optimal way to call this function.
*****************************************************/

void reset(int puzzle[][9], int orgCopy[][9])
{
int i,j;
	for(i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
		{
  		puzzle[i][j] = orgCopy[i][j];
		}
	}
}
/*******************************************************
This is the function to generate the random sudoku puzzle. Using the best of my knowledge, I tried to do something original.
I used the assumption that at a very basic level, an easy 9x9 sudoku puzzle has at least about 25 squares prefilled and a hard 
9x9 puzzle may have between 17-24 squares filled.
My logic was as follows: so suppose I want an easy puzzle I need at least 25 random inputs for puzzle[i][j]. henece I need at
least 25 values for number, i and j. I also had to account for the fact that the some of the randomly generated values may not
satisfy the validation check and so if the user calls for an easy value, the number is set to 45 for easy and that can be adjusted, 
so that at least 25 of the sets of i,j and number meet the validation check requirements and thus the randomly generated puzzle
has at least 25 prefilled values.
I am also creating a reset copy in this function for the randomly generated puzzle.
*****************************************************/

void randomGenerate(int puzzle[][9])
{
int i,j,rowIndex, columnIndex, value, level, num;
//initializes the puzzle to zero
 for (i=0;i<9;i++){
     for (j=0;j<9;j++){
         puzzle[i][j] = 0;
         }
     }
//ask the user to choose game difficulty
printf("\033[22;32mEnter difficulty level for a 9x9 sudoku puzzle by either entering '1' for easy and '2' for difficult.\033[0m\n");
printf("\033[22;32mHINT: An easy game may have approximately 25 prefilled values.\033[0m\n");
printf("\033[22;32mA harder puzzle may have between approx 17 prefilled values.\033[0m \n");
printf("Please enter your choice of level '1' or '2': ");
scanf("%d", &level);
srand(time(NULL));

 if(level == 1){num = 45;}
     else {num = 35;}

 for (i=0; i<num; i++)
     {
     value = rand()%10;
     rowIndex = rand()%10;
     columnIndex = rand()%10;

     if(validateInput(puzzle, i, j, value)){
         puzzle[rowIndex][columnIndex]=value;}
     }
 	printf("Your puzzle is:\n ");
 	display(puzzle,9,9);
 //Creating a reset copy of the puzzle
 int resetCopy[9][9];
 int r,c;
 for (r=0;r<9;r++)
    {
         for (c=0;c<9;c++){
         resetCopy[r][c] = puzzle[r][c];
    	}
	}
}
/********************************************************/
