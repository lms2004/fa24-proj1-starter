#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t *state, unsigned int snum);
static char next_square(game_state_t *state, unsigned int snum);
static void update_tail(game_state_t *state, unsigned int snum);
static void update_head(game_state_t *state, unsigned int snum);

/* Task 1 */
game_state_t *create_default_state() {
  game_state_t* game = (game_state_t*)malloc(sizeof(game_state_t));
  unsigned int  gameCol= 20;
  game->num_rows = 18;

  game->board = (char**)malloc(game->num_rows*sizeof(char*));
  for(int i = 0;i < game->num_rows;i++){
    game->board[i] = (char*)malloc((gameCol+1) * sizeof(char));
  }

  game->num_snakes = 1;

  game->snakes = (snake_t*)malloc(sizeof(snake_t));
  game->snakes->head_row = 2;
  game->snakes->head_col = 4;

  game->snakes->tail_row = 2;
  game->snakes->tail_col = 2;
  game->snakes->live = true;

  // board
  for(int i = 0;i < game->num_rows;i++){
    game->board[i][0] = '#';
    game->board[i][gameCol - 1] = '#';

    game->board[i][gameCol] = '\0';

    char a = (i == 0 || i == game->num_rows - 1)?'#':' ';
    for(int j = 1;j < gameCol - 1;j++){
      game->board[i][j] = a;
    }
  }

  game->board[2][4] = 'D';        // head
  game->board[2][3] = '>';        // body
  game->board[2][2] = 'd';        // tail

  game->board[2][9] = '*';        // apple
  return game;
}

/* Task 2 */
void free_state(game_state_t *state) {
  for(int i = 0;i < state->num_rows;i++){
    free(state->board[i]);
  }
  free(state->board);
  
  free(state->snakes);
  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp) {
  for(int i = 0;i < state->num_rows;i++){
    fprintf(fp,"%s\n",state->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t *state, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t *state, unsigned int row, unsigned int col) { return state->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t *state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  switch(c){
    case 'w':
    case 'a':
    case 's':
    case 'd': return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  switch(c){
    case 'W':
    case 'A':
    case 'S':
    case 'D':
    case 'x':     return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
    switch(c){
      // head
      case 'W':
      case 'A':
      case 'S':
      case 'D':
      case 'x':   
      
      // body
      case '<':
      case '>':
      case '^':
      case 'v':

      // tail
      case 'w':
      case 'a':
      case 's':
      case 'd':  return true;
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  switch (c) {
    case '^': return 'w';
    case '>': return 'd';
    case 'v': return 's';
    case '<': return 'a';
    default: return '?'; // 如果输入不在预期范围内，返回 '?' 表示未知
  }
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  switch (c) {
      case 'W': return '^'; // 蛇头向上，身体箭头向上
      case 'A': return '<'; // 蛇头向左，身体箭头向左
      case 'S': return 'v'; // 蛇头向下，身体箭头向下
      case 'D': return '>'; // 蛇头向右，身体箭头向右
      default: return '?';  // 对于不是蛇头的字符，返回未定义值 '?'
  }
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  switch(c){
    case 'v':
    case 's':
    case 'S': return cur_row + 1;
    case '^':
    case 'w':
    case 'W': return cur_row - 1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  switch(c){
    case '>':
    case 'd':
    case 'D': return cur_col + 1;
    case '<':
    case 'a':
    case 'A': return cur_col - 1;
  }
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. 
  
  Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t *state, unsigned int snum) {
  snake_t gSnake = state->snakes[snum];
  char** board = state->board;

  unsigned int hRow = gSnake.head_row;
  unsigned int hCol = gSnake.head_col;
  switch(head_to_body(board[hRow][hCol])){
      case '^': return board[hRow - 1][hCol]; // 蛇头向上，身体箭头向上
      case '<': return board[hRow][hCol - 1]; // 蛇头向左，身体箭头向左
      case 'v': return board[hRow + 1][hCol]; // 蛇头向下，身体箭头向下
      case '>': return board[hRow][hCol + 1]; // 蛇头向右，身体箭头向右
  }

  return '?';
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state)) {
  // TODO: Implement this function.
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  // TODO: Implement this function.
  return NULL;
}

/* Task 5.2 */
game_state_t *load_board(FILE *fp) {
  // TODO: Implement this function.
  return NULL;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t *state, unsigned int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state) {
  // TODO: Implement this function.
  return NULL;
}
