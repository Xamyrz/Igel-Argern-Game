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
    int num_tokens_placed = 0;
    int rows_placed_in[] = {0,0,0,0,0,0}; // Array to keep track of number of tokens in each row

    // Loop 4 times, once per token
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < numPlayers; j++) {
            print_board(board);
            display_message(players[j], "In which row would you like to place your token?");
            scanf("%d", &row);

            while(row > 5 || row <0 || rows_placed_in[row] > num_tokens_placed/NUM_ROWS){
                print_board(board);
                display_message(players[j], "Row number is out of bounds or contains too many tokens! Please try again.");
                display_message(players[j], "In which row would you like to place your token?");
                scanf("%d", &row);
            }

            token = malloc(sizeof(struct token));
            token->col = players[j].col;
            token->next = NULL;
            token->id = players[j].col*10+i; // Assigns a unique id to each token for comparison. The id is formed from the player's colour and the numbered token that is placed. (1-4)
            add_token_to_square(&board[row][0], token);
            rows_placed_in[row]++;
            num_tokens_placed++;
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
    int dice_roll;
    int curr_player = 0;
    int winner;

    do {
        printf("NEW ROUND\n");
        print_board(board);
        dice_roll = roll_dice();
        printf("%d has been rolled\n", dice_roll);
        side_step(board, players[curr_player]);
        print_board(board);
        forward_step(board, players[curr_player], dice_roll);

        curr_player++;
        if(curr_player == numPlayers)
            curr_player = 0; //Wrap back around once curr_player reaches the max

        winner = has_any_player_won(players, numPlayers);
    } while (winner == -1);
}


//dice roll function which creates a random number from 1 to 6 and returns the result
int roll_dice() {
    int dice = rand()%5;

    return dice;
}

void display_message(player player, char message[]){
    char *colour = colour_to_string(player.col);
    if(colour == NULL) {
        printf("Player %d: %s\n", player.player_id, message);
    }else{
        printf("%s [%s]: %s\n", player.playername, colour, message);
    }
}

// Square management functions
void add_token_to_square(square *sq, token *tok) {
    if(sq->stack == NULL) {
        sq->stack = tok;
    } else {
        token *prev = sq->stack;
        sq->stack = tok;
        tok->next = prev;
    }
}

void pop_from_top_of_square(square *sq) {
    sq->stack = sq->stack->next;
}

void move_token(square *from, square *to, token *tok) {
    pop_from_top_of_square(from);
    printf("Popped from stack!\n");
    add_token_to_square(to, tok);
    printf("Added to square\n");
}

int can_move_from_cell(square board[NUM_ROWS][NUM_COLUMNS], int row, int column) {
    if(board[row][column].type == NORMAL)
        return 1;

    // Checks all preceding columns to check if they contain a token, if they do, return 0
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < (column - 1); j++) {
            if(board[row][column].stack != NULL)
                return 0;
        }
    }

    // By this stage we've verified that all preceding columns don't contain a token, so we can safely return 1
    return 1;
}

int has_any_player_won(player players[], int num_players) {
    for(int i = 0; i < num_players; i++) {
        if(players[i].num_tokens_at_end == 3)
            return i;
    }

    return -1;
}

void side_step(square board[NUM_ROWS][NUM_COLUMNS], player player) {
    char c;
    int row, column;
    display_message(player, "Would you like to move one of your tokens?");
    printf("Enter y for yes, else for no\n");
    scanf(" %c", &c);

    if(c == 'y' || c == 'Y') {
        display_message(player, "Please enter the token you wish to move in the following form: \"[row], [column]\"");
        scanf(" %d, %d", &row, &column);

        while(row < 0 || row > NUM_ROWS || column < 0 || column > NUM_COLUMNS) {
            display_message(player, "Invalid co-ordinate, please try again.");
            scanf(" %d, %d", &row, &column);
        }

        token *tok = board[row][column].stack;

        if(tok == NULL) {
            display_message(player, "No token in that square.");
            side_step(board, player); // Send it back to the function again
            return; // Return once that function returns to avoid duplication of work
        }

        if(tok->col != player.col) {
            display_message(player, "Token belongs to another player");
            side_step(board, player); // Send it back to the function again
            return; // Return once that function returns to avoid duplication of work
        }

        if(!can_move_from_cell(board, row, column)) {
            display_message(player, "Token cannot be moved due to it being in an obstacle");
            side_step(board, player); // Send it back to the function again
            return; // Return once that function returns to avoid duplication of work
        }

        display_message(player, "Would you like to move the token up or down?\n Enter u for up or d for down.");
        scanf(" %c", &c);

        while(c != 'u' && c != 'd') {
            display_message(player, "Invalid choice, please enter either u or d.");
            scanf(" %c", &c);
        }

        if(c == 'u') {
            if(row != 0) {
                // If u was entered move the token up, assuming this doesn't move it out of bounds
                move_token(&board[row][column], &board[row - 1][column], tok);
            } else {
                display_message(player, "Move would send token out of bounds");
                side_step(board, player); // Send it back to the function again
                return; // Return once that function returns to avoid duplication of work
            }
        } else {
            if(row != NUM_ROWS) {
                // If u was entered move the token up, assuming this doesn't move it out of bounds
                move_token(&board[row][column], &board[row + 1][column], tok);
            } else {
                display_message(player, "Move would send token out of bounds");
                side_step(board, player); // Send it back to the function again
                return; // Return once that function returns to avoid duplication of work
            }
        }
    }
}

void forward_step(square board[NUM_ROWS][NUM_COLUMNS], player player, int roll){
    int count = 0;
    for(int i=0; i<9;i++){
        if(board[roll][i].stack == NULL){
            count++;
        }
    }
    if(count == 0){
        display_message(player, "Unfortunately there are no tokens in that column");
        return;
    }
    char *message = malloc(sizeof(char) * 56);
    int column;
    sprintf(message, "Please select a column from row %d to move token forward", roll);
    display_message(player, message);
    scanf(" %d", &column);
    while(board[roll][column].stack == NULL){
        display_message(player, "Unfortunately there is no token in that column \n please re-enter column");
        scanf(" %d", &column);
    }
    if(!can_move_from_cell(board, roll, column)) {
        display_message(player, "Token cannot be moved due to it being in an obstacle");
        forward_step(board, player, roll); // Send it back to the function again
        return; // Return once that function returns to avoid duplication of work
    }
    printf("column: %d roll: %d", column, roll);
    move_token(&board[roll][column], &board[roll][column + 1], board[roll][column].stack);
}