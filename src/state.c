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
    game->board[i] = (char*)malloc((gameCol+2) * sizeof(char));
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

    game->board[i][gameCol] = '\n';
    game->board[i][gameCol + 1] = '\0';

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
    if (state == NULL) return;

    // 释放 board 数组中的每一行
    if (state->board != NULL) {
        for (int i = 0; i < state->num_rows; i++) {
            if (state->board[i] != NULL) {
                free(state->board[i]);
                state->board[i] = NULL;  // 避免重复释放
            }
        }
        free(state->board);
        state->board = NULL;
    }

    // 释放 snakes 数组
    if (state->snakes != NULL) {
        free(state->snakes);
        state->snakes = NULL;
    }
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp) {
  for(int i = 0;i < state->num_rows;i++){
    fprintf(fp,"%s",state->board[i]);
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
  char c = board[hRow][hCol];

  return board[get_next_row(hRow, c)][get_next_col(hCol, c)];
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t *state, unsigned int snum) {
  char** board = state->board;

  unsigned int row = state->snakes[snum].head_row;
  unsigned int col = state->snakes[snum].head_col;
    
  char c = board[row][col];
  unsigned int nextRow = get_next_row(row, c);
  unsigned int nextCol = get_next_col(col, c);

  board[nextRow][nextCol] = board[row][col];
  board[row][col] = head_to_body(c);

  state->snakes[snum].head_row = nextRow;
  state->snakes[snum].head_col = nextCol;

  return;
}

static void update_head_hasfruit(game_state_t *state, unsigned int snum) {
  char** board = state->board;

  unsigned int row = state->snakes[snum].head_row;
  unsigned int col = state->snakes[snum].head_col;
    
  char c = board[row][col];
  unsigned int nextRow = get_next_row(row, c);
  unsigned int nextCol = get_next_col(col, c);

  board[row][col] = head_to_body(c);
  board[nextRow][nextCol] = c;

  state->snakes[snum].head_row = nextRow;
  state->snakes[snum].head_col = nextCol;

  return;
}


static void update_head_dead(game_state_t *state, unsigned int snum) {
  char** board = state->board;

  unsigned int row = state->snakes[snum].head_row;
  unsigned int col = state->snakes[snum].head_col;

  board[row][col] = 'x';

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
  char** board = state->board;

  unsigned int row = state->snakes[snum].tail_row;
  unsigned int col = state->snakes[snum].tail_col;
    
  char c = board[row][col];
  unsigned int nextRow = get_next_row(row, c);
  unsigned int nextCol = get_next_col(col, c);

  board[nextRow][nextCol] = body_to_tail(board[nextRow][nextCol]);
  board[row][col] = ' ';

  state->snakes[snum].tail_row = nextRow;
  state->snakes[snum].tail_col = nextCol;

  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state)) {


  snake_t* snake = state->snakes;

  for(unsigned int i = 0;i < state->num_snakes;i++){
      char c =next_square(state, i);
      if(is_snake(c) || c == '#'){
          update_head_dead(state, i);
          snake[i].live = false;
      }else if(c == '*'){
          update_head_hasfruit(state, i);
          add_food(state);
      }else{
          update_head(state, i);  
          update_tail(state, i);      
      }
      
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {

  char buffer[1024];
  unsigned int capacity = 8 * 1024;
  unsigned int len = 0;

  char* line = (char*)malloc(capacity * sizeof(char));
  if (line != NULL) {
    memset(line, 0, capacity);  // 将所有字节设置为 '\0'
  }
  
  while(fgets(buffer, sizeof(buffer), fp) != NULL){
    size_t Bufferlen = strlen(buffer);
    len += Bufferlen;
    if(len >= capacity){
      capacity *= 2;
      line = (char*)realloc(line, capacity * sizeof(char));
    }

    if(buffer[Bufferlen - 1] == '\n'){
      strcat(line, buffer);
      break;
    }else{
      strncat(line, buffer, Bufferlen);
    }
  }
  if(len == 0){
    return NULL;
  }
  line = (char*)realloc(line, (len+1) * sizeof(char));
  return line;
}

/* Task 5.2 */
game_state_t *load_board(FILE *fp) {
  game_state_t * game = (game_state_t *)malloc(sizeof(game_state_t));
  unsigned int capacity = 10;
  game->board =  (char**)malloc(capacity * sizeof(char*));
  unsigned int row = 0;
  while((game->board[row] = read_line(fp))){
      row++;
      if(row == capacity){
          capacity *= 2;
          game->board =  (char**)realloc(game->board, capacity * sizeof(char*));
      }
  }

  game->board =  (char**)realloc(game->board, row * sizeof(char*));
  game->snakes = (snake_t *)malloc(sizeof(snake_t));
  game->num_rows = row;
  return game;
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
  unsigned int NextRow = state->snakes[snum].tail_row;
  unsigned int NextCol = state->snakes[snum].tail_col;
  char** board = state->board;

  char next = board[NextRow][NextCol];

  while(!is_head(next)){
    NextRow = get_next_row(NextRow, next);
    NextCol = get_next_col(NextCol, next);
    next = board[NextRow][NextCol];
  }
  state->snakes[snum].head_row = NextRow;
  state->snakes[snum].head_col = NextCol;
  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state) {
  unsigned int capacity = 5;
  state->snakes = (snake_t*)malloc(capacity * sizeof(snake_t));
  unsigned int snakenum = 0;
  char** board = state->board;
  
  for(unsigned int i = 0;i < state->num_rows;i++){
    for(unsigned int j = 0;j < strlen(board[i]) - 1;j++){
      if(is_tail(board[i][j])){
        if(capacity == snakenum){
          capacity *= 2;
          state->snakes = (snake_t*)realloc(state->snakes, capacity * sizeof(snake_t));
        }
        state->snakes[snakenum].live = true;
        state->snakes[snakenum].tail_row = i;
        state->snakes[snakenum].tail_col = j;
        find_head(state, snakenum);
        snakenum++;
      }
    }
  }
  state->snakes = (snake_t*)realloc(state->snakes,snakenum  * sizeof(snake_t));
  state->num_snakes = snakenum;
  return state;
}
