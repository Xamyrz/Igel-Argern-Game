/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLUE) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

char* colour_to_string(enum color col) {
    if(col == PINK) return "Pink";
    if(col == RED) return "Red";
    if(col == BLUE) return "Blue";
    if(col == GREEN) return "Green";
    if(col == ORANGE) return "Orange";
    if(col == YELLOW) return "Yellow";
    return NULL;
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}



void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
    int row;
    struct token *token;

    // Loop 4 times, once per token
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < numPlayers; j++) {
            print_board(board);
            display_message(players[j], "In which row would you like to place your token?");
            scanf("%d", &row);
            while(row > 5 || row <0){
                print_board(board);
                display_message(players[j], "Row number is out of bounds! Please try again.");
                display_message(players[j], "In which row would you like to place your token?");
                scanf("%d", &row);
            }
            token = malloc(sizeof(token));
            token->col = players[j].col;
            token->id = players[j].col*10+i; // Assigns a unique id to each token for comparison. The id is formed from the player's colour and the numbered token that is placed. (1-4)
            add_token_to_square(&board[row][0], token);
        }
    }

}


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    //TO BE IMPLEMENTED
}


//dice roll function which creates a random number from 1 to 6 and returns the result
int dice_roll(){
    int dice = rand()%5+1;

    return dice;
}

void display_message(player player, char message[]){
    char *colour = colour_to_string(player.col);
    if(colour == NULL) {
        printf("Player %d: %s\n", player.player_id, message);
    } else {
        printf("Player %d [%s]: %s\n", player.player_id, colour, message);
    }
}

// Square management functions
void add_token_to_square(square *sq, token *tok) {
    if(sq->stack == NULL) {
        sq->stack = tok;
    } else {
        token *curr = sq->stack;
        while(curr->next != NULL)
            curr = curr->next;

        curr->next = tok;
    }
}

void remove_token_from_square(square *sq, token *tok) {
    token *prev = sq->stack;
    token *following;
    while(prev->next->id != tok->id && prev != NULL) {
        prev = prev->next;
    }

    if(prev == NULL) {
        // TODO: Implement behaviour for it not being found in the square's stack
    }

    following = prev->next->next;

    prev->next = following; // Skip over the token in the stack to detach it
    tok->next = NULL; // Detatch "following" from the stack of the now detatched token
}

void move_token(square *from, square *to, token *tok) {
    remove_token_from_square(from, tok);
    add_token_to_square(to, tok);
}