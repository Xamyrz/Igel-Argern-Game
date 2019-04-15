
/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);



/* 
 *  * Manages the logic of the game
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players 
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

/**
 * Converts a colour enum to a string representing the colour
 * @param col The colour to convert
 * @return A string representation of the colour.
 * E.g. RED will return "Red"
 */
char* colour_to_string(enum color col);

int dice_roll();

void display_message(player player, char message[]);

/**
 * Adds a token to a square's stack
 * @param sq The square to be added to
 * @param tok The token involved
 */
void add_token_to_square(square *sq, token *tok);

/**
 * Removes a token from a square's stack
 * @param sq The square to be affected
 * @param tok The token to be removed
 */
void pop_from_top_of_square(square *sq);

/**
 * Moves a token from one square to another
 * @param from The square to move the token from
 * @param to The square to move the token to
 * @param tok The token to be moved
 */
void move_token(square *from, square *to, token *tok);

/**
 * To be called during the forward stepping period of the game
 */
void side_step(square board[NUM_ROWS][NUM_COLUMNS], player player);

/**
 * To be called during the side stepping period of the game
 */
void forward_step();

/**
 * Checks if a token is legally allowed to move from its current position
 * @return 1 if cell is not an obstacle or all other tokens have caught up, 0 otherwise
 */
int can_move_from_cell(square board[NUM_ROWS][NUM_COLUMNS], int row, int column);

/**
 * Checks if any player has won the game yet
 * @param players[] The array of players in the game
 * @param num_players The number of initialised players in the game
 * @return The player that has won, if no player won then the function returns -1
 */
int has_any_player_won(player players[], int num_players);