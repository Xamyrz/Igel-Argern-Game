/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
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

    int playernum;
    printf("How many players are going to play? \n");
    scanf("%d", &playernum);
    while(playernum > 6 || playernum < 2){
        printf("ERROR: You have entered more than 6 or less than 2 players. \n");
        printf("How many players are going to play? \n");
        scanf("%d", &playernum);
    }

    for(int i = 1; i<=playernum; i++) {
        players[i].player_id = i;
        printf("Please enter the colour for Player %d \n", players[i].player_id);
        printf("1)Red \n2)Blue \n3)Green \n4)Yellow \n5)Pink \n6)Orange \n");
        int colour;
        scanf("%d", &colour);
        while(colour > 6 || colour < 1){
            printf("ERROR: You have entered a non existant color id.");
            printf("Please enter the colour for Player %d \n", players[i].player_id);
            printf("1)Red \n2)Blue \n3)Green \n4)Yellow \n5)Pink \n6)Orange \n");
            scanf("%d", &colour);
            players[i].col = colour - 1;
        }
    }
        return playernum;
    }
    
   
     

