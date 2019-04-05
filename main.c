/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: lpasqua
 *
 * Created on 06 March 2019, 12:11
 */

#include "game_init.h"
#include "game_logic.h"
#include <time.h>
#include <stdlib.h>


int sample_players(player *players, int num) {
    for(int i=0; i<num; i++) {
        player p = {.col = i, .player_id = i+1};
        players[i] = p;
    }

    return num;
}

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));

    //the board is defined as a 2-Dimensional array of squares
    square board[NUM_ROWS][NUM_COLUMNS];
    
    //an array containing the players (MAX 6 players)
    player players[6];
    
    //the number of players
    int numPlayers = 0;
    
    //creates the squares of the board
    initialize_board(board);
    
    //prints the board
    print_board(board);
    
    //creates the players
    numPlayers = initialize_players(players);
    //numPlayers = sample_players(players, 6);

    //asks each player to place their tokens
    //on the first column of the board
    place_tokens(board, players, numPlayers);
    
    
    //manages the turns of the game and identifies a winner
    play_game(board, players, numPlayers);
    
    return 0;
    
    

}

