// Refactored Tic Tac Toe

#include <stdio.h>
#include <string.h>

char choice_XorO;
char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void reset_board()
{
  for (int i = 0; i < 9; i++)
    board[i] = ' ';
}

void move_X(char m)
{
  board[m - '1'] = 'X';
}

void move_O(char m)
{
  board[m - '1'] = 'O';
}

void new_board()
{
  printf("\n %c | %c | %c \n", board[0], board[1], board[2]);
  printf("___|___|___\n");
  printf(" %c | %c | %c \n", board[3], board[4], board[5]);
  printf("___|___|___\n");
  printf(" %c | %c | %c \n", board[6], board[7], board[8]);
  printf("   |   |   \n");
}

char default_mode()
{
  for (int i = 0; i < 9; i++)
  {
    if (board[i] == ' ')
      return i + '1';
  }
  return '0';
}

int win_check()
{
  int lines[8][3] = {
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
      {0, 3, 6},
      {1, 4, 7},
      {2, 5, 8}, // columns
      {0, 4, 8},
      {2, 4, 6} // diagonals
  };
  for (int i = 0; i < 8; i++)
  {
    if (board[lines[i][0]] == 'X' && board[lines[i][1]] == 'X' && board[lines[i][2]] == 'X')
      return 1;
    if (board[lines[i][0]] == 'O' && board[lines[i][1]] == 'O' && board[lines[i][2]] == 'O')
      return 2;
  }
  return 0;
}

int kill_prog()
{
  int win = win_check();
  if (win == 1)
  {
    if (choice_XorO == '1')
      printf("\nYou Win! \nThanks for playing!\n");
    else
      printf("\nComputer Wins. \nTry again!\n");
    return 1;
  }
  if (win == 2)
  {
    if (choice_XorO == '2')
      printf("\nYou Win! \nThanks for playing!\n");
    else
      printf("\nComputer Wins. \nTry again!\n");
    return 1;
  }
  return 0;
}

char find_third(char symbol)
{
  int lines[8][3] = {
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
  for (int i = 0; i < 8; i++)
  {
    int count = 0;
    char empty_pos = '0';
    for (int j = 0; j < 3; j++)
    {
      if (board[lines[i][j]] == symbol)
        count++;
      if (board[lines[i][j]] == ' ')
        empty_pos = lines[i][j] + '1';
    }
    if (count == 2 && empty_pos != '0')
      return empty_pos;
  }
  return '0';
}

char find_third_O()
{
  return find_third('O');
}

char find_third_X()
{
  return find_third('X');
}

char get_move()
{
  char input[2];
  scanf(" %s", input);
  while ((strlen(input) != 1) || !(input[0] == '1' || input[0] == '2' || input[0] == '3' || input[0] == '4' ||
                                   input[0] == '5' || input[0] == '6' || input[0] == '7' || input[0] == '8' || input[0] == '9'))
  {
    printf("\nInvalid entry. Please choose a number between 1 and 9: ");
    scanf("%s", input);
  }
  return input[0];
}

int main()
{
  char play_again;
  do
  {
    reset_board();
    char game_mode_input[2];
    printf("Welcome to Tic Tac Toe!\n");
    printf("\nPress 1 for single player mode and 2 for two player mode: ");
    scanf("%s", game_mode_input);
    while ((strlen(game_mode_input) != 1) || !(game_mode_input[0] == '1' || game_mode_input[0] == '2'))
    {
      printf("\nInvalid entry. Please enter 1 for single player mode and 2 for two player mode: ");
      scanf("%s", game_mode_input);
    }
    char game_mode = game_mode_input[0];

    if (game_mode == '1')
    {
      char choice_input[2];
      printf("\nSingle player mode. Can you beat the computer?...\n");
      printf("\nX's go first. Would you like to be X's or O's? \n");
      printf("\nPress 1 to be X's and 2 to be O's: ");
      scanf("%s", choice_input);
      while ((strlen(choice_input) != 1) || !(choice_input[0] == '1' || choice_input[0] == '2'))
      {
        printf("\nInvalid entry. Please press 1 to be X's and 2 to be O's: ");
        scanf("%s", choice_input);
      }
      choice_XorO = choice_input[0];

      printf("\n 1 | 2 | 3 \n___|___|___\n 4 | 5 | 6 \n___|___|___\n 7 | 8 | 9 \n   |   |   \n");
      printf("\nPlease use above diagram to enter your moves.\n");

      char player_symbol = (choice_XorO == '1') ? 'X' : 'O';
      char computer_symbol = (choice_XorO == '1') ? 'O' : 'X';
      void (*player_move_func)(char) = (choice_XorO == '1') ? move_X : move_O;
      void (*computer_move_func)(char) = (choice_XorO == '1') ? move_O : move_X;
      char (*find_third_player)(void) = (choice_XorO == '1') ? find_third_X : find_third_O;
      char (*find_third_computer)(void) = (choice_XorO == '1') ? find_third_O : find_third_X;

      if (choice_XorO == '2')
      {
        computer_move_func('5');
        new_board();
      }

      for (int turn = 0; turn < 5; turn++)
      {
        printf("\nEnter move %d: ", turn + 1);
        char move = get_move();
        while (board[move - '1'] != ' ')
        {
          printf("That spot is already taken. Please pick a unique move. ");
          move = get_move();
        }
        player_move_func(move);
        new_board();
        if (kill_prog() == 1)
          break;

        if (turn == 4)
        {
          printf("\nTied Game. Try again!\n");
          break;
        }

        // Computer move
        char computer_move = find_third_computer();
        if (computer_move == '0')
          computer_move = find_third_player();
        if (computer_move == '0')
          computer_move = default_mode();
        computer_move_func(computer_move);
        new_board();
        if (kill_prog() == 1)
          break;
      }
    }
    else
    {
      // Two player mode
      printf("\nWelcome to two player mode. \n");
      printf("\nPlayer 1 will be X's and Player 2 will be O's. \n");
      printf("\n 1 | 2 | 3 \n___|___|___\n 4 | 5 | 6 \n___|___|___\n 7 | 8 | 9 \n   |   |   \n");
      printf("\nPlease use above diagram to enter your moves.\n");

      for (int turn = 0; turn < 5; turn++)
      {
        // Player 1 move
        printf("\nEnter move Player 1: ");
        char move = get_move();
        while (board[move - '1'] != ' ')
        {
          printf("That spot is already taken. Please pick a unique move. ");
          move = get_move();
        }
        move_X(move);
        new_board();
        if (win_check() == 1)
        {
          printf("\nPlayer 1 wins! \n");
          break;
        }

        if (turn == 4)
        {
          printf("\nTied game. \nThanks for playing! Don't forget to check out single player mode! \n");
          break;
        }

        // Player 2 move
        printf("\nEnter move Player 2: ");
        move = get_move();
        while (board[move - '1'] != ' ')
        {
          printf("That spot is already taken. Please pick a unique move. ");
          move = get_move();
        }
        move_O(move);
        new_board();
        if (win_check() == 2)
        {
          printf("\nPlayer 2 wins! \n");
          break;
        }
      }
    }

    printf("\nPlay again? (y/n): ");
    scanf(" %c", &play_again);
  } while (play_again == 'y' || play_again == 'Y');

  return 0;
}