/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
        }
    }
}
    
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){

    //declares playernum variable
    int playernum;

    int colour_taken[] = {0,0,0,0,0,0};

    //prompts user to enter amount of players
    printf("How many players are going to play? \n");
    scanf("%d", &playernum);

    //display error message when playernum is less than 2 or greater than 6 and ask again
    while(playernum > 6 || playernum < 2){
        printf("ERROR: You have entered more than 6 or less than 2 players. \n");
        printf("How many players are going to play? \n");
        scanf("%d", &playernum);
    }

    //loop playernum times
    for(int i = 1; i<=playernum; i++) {

        //assigns an id to a player
        players[i-1].player_id = i;

        //prompt a user to enter their name
        display_message(players[i-1], "Enter your name");
        scanf("%s",players[i-1].playername);

        //prompt a user to enter a colour
        display_message(players[i-1], "Please select a colour");
        printf("1)Red \n2)Blue \n3)Green \n4)Yellow \n5)Pink \n6)Orange \n");
        int colour;
        scanf("%d", &colour);

        //checks if value in the colour_taken is 1, if it is ask the user to input colour again
        while(colour_taken[colour-1] == 1){
            display_message(players[i-1], "You have selected a colour which is already taken");
            display_message(players[i-1], "Please select a colour");
            printf("1)Red \n2)Blue \n3)Green \n4)Yellow \n5)Pink \n6)Orange \n");
            scanf("%d", &colour);
        }

        //if the colour id is greater than 6 or less than 1 then display the error and prompt the user again.
        while(colour > 6 || colour < 1){
            display_message(players[i-1], "You entered an invalid colour! Please try again.");
            display_message(players[i-1], "Please select a colour");
            printf("1)Red \n2)Blue \n3)Green \n4)Yellow \n5)Pink \n6)Orange \n");
            scanf("%d", &colour);
        }

        //sets the value of colour_taken[colour -1] to 1 when it's free to use.
        colour_taken[colour-1] = 1;

        //sets the players colour
        players[i-1].col = colour - 1;
        players[i-1].num_tokens_at_end = 0;
    }
        return playernum;
}
    
   
     

