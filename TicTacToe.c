// Tic Tac Toe game with single and two player modes
// Fun fact: There are 255,168 possible games of Tic Tac Toe!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char choice_XorO;
char position_one = ' ', position_two = ' ', position_three = ' ', position_four = ' ', position_five = ' ', position_six = ' ', position_seven = ' ', position_eight = ' ', position_nine = ' ';
int invalid_entry_count = 0;

void move_X(char);                          // applies X's
void move_O(char);                          // applies O's
void new_board();                           // shows updated game
char default_mode();                        // computer's default mode of playing like you read a book
int win_check();                            // checks to see if either side has won
int kill_prog();                            // terminates program if someone has won
char find_third_O();                        // finds winning move for O's
char find_third_X();                        // finds winning move for X's
int invalid_entry_police(char string[255]); // ensures entry is 1 character and a number between 1 and 9

int main()
{
    int duplicate_entry_count = 0;
    char game_mode;
    char player_move_one, player_move_two, player_move_three, player_move_four, player_move_five;
    char computer_move_one, computer_move_two, computer_move_three, computer_move_four, computer_move_five;
    char Choice_XorO[255];
    char Game_mode[255];
    char Move_1[20];
    char Move_2[20];
    char Move_3[20];
    char Move_4[20];
    char Move_5[20];

    printf("Welcome to Tic Tac Toe!\n");
    printf("\nPress 1 for single player mode and 2 for two player mode: ");
    scanf(" %s", Game_mode);
    for (int game_mode_chance = 1; ((strlen(Game_mode) != 1) || !(Game_mode[0] == '1' || Game_mode[0] == '2')) && game_mode_chance < 3; game_mode_chance++)
    {
        printf("\nInvalid entry. Please enter 1 for single player mode and 2 for two player mode: ");
        scanf("%s", Game_mode);
    }

    if ((strlen(Game_mode) != 1) || !(Game_mode[0] == '1' || Game_mode[0] == '2'))
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        game_mode = Game_mode[0];
    if (game_mode == '1')
    {
        printf("\nSingle player mode. Can you beat the computer?...\n");
        printf("\nX's go first. Would you like to be X's or O's? \n");
        printf("\nPress 1 to be X's and 2 to be O's: ");
        scanf(" %s", Choice_XorO);
        for (int choice_XorO_chance = 1; ((strlen(Choice_XorO) != 1) || !(Choice_XorO[0] == '1' || Choice_XorO[0] == '2')) && choice_XorO_chance < 3; choice_XorO_chance++)
        {
            printf("\nInvalid entry. Please press 1 to be X's and 2 to be O's: ");
            scanf("%s", Choice_XorO);
        }

        if ((strlen(Choice_XorO) != 1) || !(Choice_XorO[0] == '1' || Choice_XorO[0] == '2'))
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            choice_XorO = Choice_XorO[0];
        printf("\n 1 | 2 | 3 \n");
        printf("___|___|___\n");
        printf(" 4 | 5 | 6 \n");
        printf("___|___|___\n");
        printf(" 7 | 8 | 9 \n");
        printf("   |   |   \n");
        // a | b | c
        //___|___|___
        // d | e | f  the real table
        //___|___|___
        // g | h | i
        //   |   |
        printf("\nPlease use above diagram to enter your moves.\n");

        if (choice_XorO == '2') //  computer's first move if it is X's
        {
            computer_move_one = '5';
            move_X(computer_move_one);
            new_board();
        }

        // printf("computer_move_one: %c\n", computer_move_one);

        printf("\nEnter move 1: "); // player move 1
        scanf(" %s", Move_1);
        if (invalid_entry_police(Move_1) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_move_one = Move_1[0];
        for (int s = 0; player_move_one == computer_move_one && s < 2; s++)
        {
            duplicate_entry_count++;
            if (duplicate_entry_count >= 3)
                break;
            printf("That spot is already taken. Please pick a unique move. ");
            scanf(" %s", Move_1);
            if (invalid_entry_police(Move_1) == 1)
            {
                printf("\nYou had your chance. Program terminated. \n");
                return 0;
            }
            else
                player_move_one = Move_1[0];
        }
        if (player_move_one == computer_move_one || duplicate_entry_count >= 3)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        if (choice_XorO == '1')
            move_X(player_move_one);
        else if (choice_XorO == '2')
            move_O(player_move_one);
        new_board();

        if (choice_XorO == '1')
        { //  computer move 2 if X's and move 1 if O's
            if (player_move_one != '5')
                computer_move_two = '5';
            else
                computer_move_two = default_mode();
        }
        if (choice_XorO == '2')
        {
            if (player_move_one == '1')
                computer_move_two = '9';
            else
                computer_move_two = default_mode();
            move_X(computer_move_two);
        }
        else if (choice_XorO == '1')
            move_O(computer_move_two);
        new_board();
        if (win_check() == 2)
        {
            if (choice_XorO == '2')
            {
                printf("You Win! \nThanks for playing!\n");
                return 0;
            }
            else if (choice_XorO == '1')
            {
                printf("\nComputer Wins. \nTry again!\n");
                return 0;
            }
        }

        printf("\nEnter move 2: "); // player move 2
        scanf(" %s", Move_2);
        if (invalid_entry_police(Move_2) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_move_two = Move_2[0];
        for (int t = 0; (((player_move_two == computer_move_one) || (player_move_two == computer_move_two) || (player_move_two == player_move_one)) && (t < 2)); t++)
        {
            duplicate_entry_count++;
            if (duplicate_entry_count >= 3)
                break;
            printf("That spot is already taken. Please pick a unique move. ");
            scanf(" %s", Move_2);
            if (invalid_entry_police(Move_2) == 1)
            {
                printf("\nYou had your chance. Program terminated. \n");
                return 0;
            }
            else
                player_move_two = Move_2[0];
        }
        if ((player_move_two == computer_move_one) || (player_move_two == computer_move_two) || (player_move_two == player_move_one) || (duplicate_entry_count >= 3))
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        if (choice_XorO == '1')
            move_X(player_move_two);
        else if (choice_XorO == '2')
            move_O(player_move_two);
        new_board();

        computer_move_three = find_third_X(); //  computer move 3 if X's and move 2 if O's
        if (computer_move_three == '0')
            computer_move_three = find_third_O();
        if (choice_XorO == '2' && computer_move_three == '0')
        {
            if (computer_move_two == '1')
            {
                if (position_three == ' ')
                    computer_move_three = '3';
                if (position_seven == ' ' && player_move_one != '4' && player_move_one != '9')
                    computer_move_three = '7';
                if (player_move_one == '9' && player_move_two == '2')
                    computer_move_three = '7';
            }
            if (player_move_one == '1' && computer_move_two == '9')
            {
                if (player_move_two == '6')
                    computer_move_three = '8';
                if (player_move_two == '8')
                    computer_move_three = '6';
            }
        }
        if (computer_move_three == '0' && choice_XorO == '1')
        {
            if (player_move_one == '2')
            {
                if (player_move_two == '4')
                    computer_move_three = '1';
                if (player_move_two == '6')
                    computer_move_three = '3';
            }
            if (player_move_one == '4')
            {
                if (player_move_two == '2')
                    computer_move_three = '1';
                if (player_move_two == '8')
                    computer_move_three = '7';
            }
            if (player_move_one == '6')
            {
                if (player_move_two == '2')
                    computer_move_three = '3';
                if (player_move_two == '8')
                    computer_move_three = '9';
            }
            if (player_move_one == '8')
            {
                if (player_move_two == '4')
                    computer_move_three = '7';
                if (player_move_two == '6')
                    computer_move_three = '9';
            }
            if (position_five == 'X' && position_nine == 'X')
                computer_move_three = '3';
            if (position_three == 'X' && position_eight == 'X')
                computer_move_three = '9';
            if (position_three == 'X' && position_four == 'X')
                computer_move_three = '1';
            if (position_three == 'X' && position_seven == 'X')
                computer_move_three = '6';
            if (position_one == 'X' && position_eight == 'X')
                computer_move_three = '7';
            if (position_one == 'X' && position_eight == 'X')
                computer_move_three = '7';
            if (position_one == 'X' && position_nine == 'X')
                computer_move_three = '2';
            if (position_nine == 'X' && position_one == 'X')
                computer_move_three = '2';
            if (position_nine == 'X' && position_two == 'X')
                computer_move_three = '3';
            if (position_nine == 'X' && position_four == 'X')
                computer_move_three = '7';
            if (position_three == 'X' && position_seven == 'X')
                computer_move_three = '6';
            if (position_six == 'X' && position_seven == 'X')
                computer_move_three = '9';
            if (position_two == 'X' && position_seven == 'X')
                computer_move_three = '3';
        }
        if (computer_move_three == '0')
            computer_move_three = default_mode();
        if (choice_XorO == '2')
            move_X(computer_move_three);
        else if (choice_XorO == '1')
            move_O(computer_move_three);
        new_board();
        if (kill_prog() == 1)
            return 0;

        printf("\n 1 | 2 | 3 \n");
        printf("___|___|___\n");
        printf(" 4 | 5 | 6 \n");
        printf("___|___|___\n");
        printf(" 7 | 8 | 9 \n");
        printf("   |   |   \n");

        printf("\nEnter move 3: "); // player move 3
        scanf(" %s", Move_3);
        if (invalid_entry_police(Move_3) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_move_three = Move_3[0];
        for (int u = 0; (((player_move_three == computer_move_one) || (player_move_three == computer_move_two) || (player_move_three == computer_move_three) || (player_move_three == player_move_one) || (player_move_three == player_move_two)) && (u < 2)); u++)
        {
            duplicate_entry_count++;
            if (duplicate_entry_count >= 3)
                break;
            printf("That spot is already taken. Please pick a unique move. ");
            scanf(" %s", Move_3);
            if (invalid_entry_police(Move_3) == 1)
            {
                printf("\nYou had your chance. Program terminated. \n");
                return 0;
            }
            else
                player_move_three = Move_3[0];
        }
        if ((player_move_three == computer_move_one) || (player_move_three == computer_move_two) || (player_move_three == computer_move_three) || (player_move_three == player_move_one) || (player_move_three == player_move_two) || (duplicate_entry_count >= 3))
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        if (choice_XorO == '1')
            move_X(player_move_three);
        else if (choice_XorO == '2')
            move_O(player_move_three);
        new_board();
        if (kill_prog() == 1)
            return 0;

        if (choice_XorO == '1') //  computer move 4 if X's and move 3 if O's
        {
            computer_move_four = find_third_O();
            if (computer_move_four == '0')
                computer_move_four = find_third_X();
            if ((computer_move_four == '0') && position_one == 'X' && position_six == 'X' && position_eight == 'X')
                computer_move_four = '7';
            if (computer_move_four == '0')
                computer_move_four = default_mode();
            move_O(computer_move_four);
        }
        if (choice_XorO == '2')
        {
            computer_move_four = find_third_X();
            if (computer_move_four == '0')
                computer_move_four = find_third_O();
            if (computer_move_four == '0')
                computer_move_four = default_mode();
            move_X(computer_move_four);
        }
        new_board();
        if (kill_prog() == 1)
            return 0;

        printf("\nEnter move 4: "); // player move 4
        scanf(" %s", Move_4);
        if (invalid_entry_police(Move_4) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_move_four = Move_4[0];
        for (int v = 0; ((player_move_four == computer_move_one) || (player_move_four == computer_move_two) || (player_move_four == computer_move_three) || (player_move_four == computer_move_four) || (player_move_four == player_move_one) || (player_move_four == player_move_two) || (player_move_four == player_move_three)) && v < 2; v++)
        {
            duplicate_entry_count++;
            if (duplicate_entry_count >= 3)
                break;
            printf("That spot is already taken. Please pick a unique move. ");
            scanf(" %s", Move_4);
            if (invalid_entry_police(Move_4) == 1)
            {
                printf("\nYou had your chance. Program terminated. \n");
                return 0;
            }
            else
                player_move_four = Move_4[0];
        }
        if ((player_move_four == computer_move_one) || (player_move_four == computer_move_two) || (player_move_four == computer_move_three) || (player_move_four == computer_move_four) || (player_move_four == player_move_one) || (player_move_four == player_move_two) || (player_move_four == player_move_three) || (duplicate_entry_count >= 3))
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        if (choice_XorO == '1')
            move_X(player_move_four);
        else if (choice_XorO == '2')
            move_O(player_move_four);
        new_board();
        if (kill_prog() == 1)
            return 0;

        if (choice_XorO == '1') //  computer move 5 if X's and move 4 if O's (final move)
        {
            computer_move_five = find_third_O();
            if (computer_move_five == '0')
                computer_move_five = find_third_X();
            if (computer_move_five == '0')
                computer_move_five = default_mode();
            move_O(computer_move_five);
        }
        if (choice_XorO == '2')
        {
            computer_move_five = find_third_X();
            if (computer_move_five == '0')
                computer_move_five = find_third_O();
            if (computer_move_five == '0')
                computer_move_five = default_mode();
            move_X(computer_move_five);
        }
        new_board();
        if (kill_prog() == 1)
            return 0;
        if ((win_check() != 1) && (choice_XorO == '2'))
        {
            printf("\nTied Game. Try again!\n");
            return 0;
        }

        printf("\n 1 | 2 | 3 \n");
        printf("___|___|___\n");
        printf(" 4 | 5 | 6 \n");
        printf("___|___|___\n");
        printf(" 7 | 8 | 9 \n");
        printf("   |   |   \n");

        printf("\nEnter move 5: "); // player move 5 (final move)
        scanf(" %s", Move_5);
        if (invalid_entry_police(Move_5) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_move_five = Move_5[0];
        for (int w = 0; ((player_move_five == computer_move_one) || (player_move_five == computer_move_two) || (player_move_five == computer_move_three) || (player_move_five == computer_move_four) ||
                         (player_move_five == player_move_one) || (player_move_five == player_move_two) || (player_move_five == player_move_three) || (player_move_five == player_move_four)) &&
                        w < 2;
             w++)
        {
            duplicate_entry_count++;
            if (duplicate_entry_count >= 3)
                break;
            printf("That spot is already taken. Please pick a unique move. ");
            scanf(" %s", Move_5);
            if (invalid_entry_police(Move_5) == 1)
            {
                printf("\nYou had your chance. Program terminated. \n");
                return 0;
            }
            else
                player_move_five = Move_5[0];
        }
        if ((player_move_five == computer_move_one) || (player_move_five == computer_move_two) || (player_move_five == computer_move_three) || (player_move_five == computer_move_four) ||
            (player_move_five == player_move_one) || (player_move_five == player_move_two) || (player_move_five == player_move_three) || (player_move_five == player_move_four) || (duplicate_entry_count >= 3))
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        if (choice_XorO == '1')
            move_X(player_move_five);
        else if (choice_XorO == '2')
            move_O(player_move_five);
        new_board();
        if (kill_prog() == 1)
            return 0;
        if (win_check() != 1)
        {
            printf("\nTied Game. Try again!\n");
            return 0;
        }
    }
    invalid_entry_count = 0;
    duplicate_entry_count = 0;
    char P1mv1[255], P1mv2[255], P1mv3[255], P1mv4[255], P1mv5[255];
    char P2mv1[255], P2mv2[255], P2mv3[255], P2mv4[255];
    char player_one_move_one, player_one_move_two, player_one_move_three, player_one_move_four, player_one_move_five;
    char player_two_move_one, player_two_move_two, player_two_move_three, player_two_move_four;
    printf("\nWelcome to two player mode. \n");
    printf("\nPlayer 1 will be X's and Player 2 will be O's. \n");
    printf("\nPlease use above diagram to enter your moves.\n");
    printf("\n 1 | 2 | 3 \n");
    printf("___|___|___\n");
    printf(" 4 | 5 | 6 \n");
    printf("___|___|___\n");
    printf(" 7 | 8 | 9 \n");
    printf("   |   |   \n");

    printf("\nEnter move Player 1: "); // Player 1 move 1
    scanf("%s", P1mv1);
    if (invalid_entry_police(P1mv1) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_one_move_one = *P1mv1;

    move_X(player_one_move_one);
    new_board();

    printf("\nEnter move Player 2: "); // Player 2 move 1
    scanf("%s", P2mv1);
    if (invalid_entry_police(P2mv1) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_two_move_one = *P2mv1;

    for (int S = 0; player_two_move_one == player_one_move_one && S < 2; S++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv1);
        if (invalid_entry_police(P2mv1) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_two_move_one = *P2mv1;
    }

    move_O(player_two_move_one);
    new_board();

    printf("\nEnter move Player 1: "); // Player 1 move 2
    scanf("%s", P1mv2);
    if (invalid_entry_police(P1mv2) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_one_move_two = *P1mv2;
    for (int T = 0; (player_one_move_two == player_one_move_one || player_one_move_two == player_two_move_one) && T < 2; T++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv2);
        if (invalid_entry_police(P1mv2) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_one_move_two = *P1mv2;
    }
    if (player_one_move_two == player_one_move_one || player_one_move_two == player_two_move_one)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    move_X(player_one_move_two);
    new_board();

    printf("\n 1 | 2 | 3 \n");
    printf("___|___|___\n");
    printf(" 4 | 5 | 6 \n");
    printf("___|___|___\n");
    printf(" 7 | 8 | 9 \n");
    printf("   |   |   \n");

    printf("\nEnter move Player 2: "); // Player 2 move 2
    scanf("%s", P2mv2);
    if (invalid_entry_police(P2mv2) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_two_move_two = *P2mv2;

    for (int U = 0; (player_two_move_two == player_one_move_one || player_two_move_two == player_one_move_two || player_two_move_two == player_two_move_one) && U < 2; U++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv2);
        if (invalid_entry_police(P2mv2) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_two_move_two = *P2mv2;
    }
    if (player_two_move_two == player_one_move_one || player_two_move_two == player_one_move_two || player_two_move_two == player_two_move_one)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    move_O(player_two_move_two);
    new_board();

    printf("\nEnter move Player 1: "); // Player 1 move 3
    scanf("%s", P1mv3);
    if (invalid_entry_police(P1mv3) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_one_move_three = *P1mv3;
    for (int V = 0; (player_one_move_three == player_one_move_one || player_one_move_three == player_one_move_two || player_one_move_three == player_two_move_one || player_one_move_three == player_two_move_two) && V < 2; V++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv3);
        if (invalid_entry_police(P1mv3) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_one_move_three = *P1mv3;
    }
    if (player_one_move_three == player_one_move_one || player_one_move_three == player_one_move_two || player_one_move_three == player_two_move_one || player_one_move_three == player_two_move_two)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    move_X(player_one_move_three);
    new_board();
    if (win_check() == 1)
    {
        printf("\nPlayer 1 wins! \n");
        return 0;
    }

    printf("\nEnter move Player 2: "); // Player 2 move 3
    scanf("%s", P2mv3);
    if (invalid_entry_police(P2mv3) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_two_move_three = *P2mv3;

    for (int W = 0; (player_two_move_three == player_one_move_one || player_two_move_three == player_one_move_two || player_two_move_three == player_one_move_three ||
                     player_two_move_three == player_two_move_one || player_two_move_three == player_two_move_two) &&
                    W < 2;
         W++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv3);
        if (invalid_entry_police(P2mv3) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_two_move_three = *P2mv3;
    }
    if (player_two_move_three == player_one_move_one || player_two_move_three == player_one_move_two || player_two_move_three == player_one_move_three ||
        player_two_move_three == player_two_move_one || player_two_move_three == player_two_move_two)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    move_O(player_two_move_three);
    new_board();
    if (win_check() == 2)
    {
        printf("\nPlayer 2 wins! \n");
        return 0;
    }

    printf("\n 1 | 2 | 3 \n");
    printf("___|___|___\n");
    printf(" 4 | 5 | 6 \n");
    printf("___|___|___\n");
    printf(" 7 | 8 | 9 \n");
    printf("   |   |   \n");

    printf("\nEnter move Player 1: "); // Player 1 move 4
    scanf("%s", P1mv4);
    if (invalid_entry_police(P1mv4) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_one_move_four = *P1mv4;
    for (int X = 0; (player_one_move_four == player_one_move_one || player_one_move_four == player_one_move_two || player_one_move_four == player_two_move_three ||
                     player_one_move_four == player_two_move_one || player_one_move_four == player_two_move_two || player_one_move_four == player_two_move_three) &&
                    X < 2;
         X++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv4);
        if (invalid_entry_police(P1mv4) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_one_move_four = *P1mv4;
    }
    if (player_one_move_four == player_one_move_one || player_one_move_four == player_one_move_two || player_one_move_four == player_two_move_three ||
        player_one_move_four == player_two_move_one || player_one_move_four == player_two_move_two || player_one_move_four == player_two_move_three)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    move_X(player_one_move_four);
    new_board();
    if (win_check() == 1)
    {
        printf("\nPlayer 1 wins! \n");
        return 0;
    }

    printf("\nEnter move Player 2: "); // Player 2 move 4
    scanf("%s", P2mv4);
    if (invalid_entry_police(P2mv4) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_two_move_four = *P2mv4;

    for (int Y = 0; (player_two_move_four == player_one_move_one || player_two_move_four == player_one_move_two || player_two_move_four == player_one_move_three || player_two_move_four == player_one_move_four ||
                     player_two_move_four == player_two_move_one || player_two_move_four == player_two_move_two || player_two_move_four == player_two_move_three) &&
                    Y < 2;
         Y++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv4);
        if (invalid_entry_police(P2mv4) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_two_move_four = *P2mv4;
    }
    if (player_two_move_four == player_one_move_one || player_two_move_four == player_one_move_two || player_two_move_four == player_one_move_three || player_two_move_four == player_one_move_four ||
        player_two_move_four == player_two_move_one || player_two_move_four == player_two_move_two || player_two_move_four == player_two_move_three)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    move_O(player_two_move_four);
    new_board();
    if (win_check() == 2)
    {
        printf("\nPlayer 2 wins! \n");
        return 0;
    }

    printf("\nEnter move Player 1: "); // Player 1 move 5
    scanf("%s", P1mv5);
    if (invalid_entry_police(P1mv5) == 1)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else
        player_one_move_five = *P1mv5;
    for (int Z = 0; (player_one_move_five == player_one_move_one || player_one_move_five == player_one_move_two || player_one_move_five == player_one_move_three || player_one_move_five == player_one_move_four ||
                     player_one_move_five == player_two_move_one || player_one_move_five == player_two_move_two || player_one_move_five == player_two_move_three || player_one_move_five == player_two_move_four) &&
                    Z < 2;
         Z++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3)
            break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv5);
        if (invalid_entry_police(P1mv5) == 1)
        {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else
            player_one_move_five = *P1mv5;
    }
    if (player_one_move_five == player_one_move_one || player_one_move_five == player_one_move_two || player_one_move_five == player_one_move_three || player_one_move_five == player_one_move_four ||
        player_one_move_five == player_two_move_one || player_one_move_five == player_two_move_two || player_one_move_five == player_two_move_three || player_one_move_five == player_two_move_four)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    move_X(player_one_move_five);
    new_board();
    if (win_check() == 1)
    {
        printf("\nPlayer 1 wins! \n");
        return 0;
    }
    else
    {
        printf("\nTied game. \nThanks for playing! Don't forget to check out single player mode! \n");
        return 0;
    }
}

// FUNCTIONS

int invalid_entry_police(char string[255])
{
    int chance;
    for (chance = 1; ((strlen(string) != 1) || !(string[0] == '1' || string[0] == '2' || string[0] == '3' || string[0] == '4' ||
                                                 string[0] == '5' || string[0] == '6' || string[0] == '7' || string[0] == '8' || string[0] == '9')) &&
                     (chance < 3);
         chance++)
    {
        invalid_entry_count++;
        if (invalid_entry_count >= 3)
            break;
        printf("\nInvalid entry. Please choose a number between 1 and 9: ");
        scanf("%s", string);
    }
    if ((invalid_entry_count >= 3) || (strlen(string) != 1) || !(string[0] == '1' || string[0] == '2' || string[0] == '3' || string[0] == '4' || string[0] == '5' || string[0] == '6' || string[0] == '7' || string[0] == '8' || string[0] == '9'))
        return 1;

    else
        return 0;
}
void new_board()
{
    printf("\n %c | %c | %c \n", position_one, position_two, position_three);
    printf("___|___|___\n");
    printf(" %c | %c | %c \n", position_four, position_five, position_six);
    printf("___|___|___\n");
    printf(" %c | %c | %c \n", position_seven, position_eight, position_nine);
    printf("   |   |   \n");
}
void move_X(char m)
{
    if (m == '1')
        position_one = 'X';
    if (m == '2')
        position_two = 'X';
    if (m == '3')
        position_three = 'X';
    if (m == '4')
        position_four = 'X';
    if (m == '5')
        position_five = 'X';
    if (m == '6')
        position_six = 'X';
    if (m == '7')
        position_seven = 'X';
    if (m == '8')
        position_eight = 'X';
    if (m == '9')
        position_nine = 'X';
}
void move_O(char m)
{
    if (m == '1')
        position_one = 'O';
    if (m == '2')
        position_two = 'O';
    if (m == '3')
        position_three = 'O';
    if (m == '4')
        position_four = 'O';
    if (m == '5')
        position_five = 'O';
    if (m == '6')
        position_six = 'O';
    if (m == '7')
        position_seven = 'O';
    if (m == '8')
        position_eight = 'O';
    if (m == '9')
        position_nine = 'O';
}
char default_mode()
{
    if (position_one == ' ')
        return '1';
    if (position_two == ' ')
        return '2';
    if (position_three == ' ')
        return '3';
    if (position_four == ' ')
        return '4';
    if (position_five == ' ')
        return '5';
    if (position_six == ' ')
        return '6';
    if (position_seven == ' ')
        return '7';
    if (position_eight == ' ')
        return '8';
    if (position_nine == ' ')
        return '9';
}

// function returns 1 if X's have won and returns 2 if O's have won
int win_check()
{
    if ((position_one == 'X') && (position_two == 'X') && (position_three == 'X'))
        return 1;
    if ((position_four == 'X') && (position_five == 'X') && (position_six == 'X'))
        return 1;
    if ((position_seven == 'X') && (position_eight == 'X') && (position_nine == 'X'))
        return 1;
    if ((position_one == 'X') && (position_four == 'X') && (position_seven == 'X'))
        return 1;
    if ((position_two == 'X') && (position_five == 'X') && (position_eight == 'X'))
        return 1;
    if ((position_three == 'X') && (position_six == 'X') && (position_nine == 'X'))
        return 1;
    if ((position_one == 'X') && (position_five == 'X') && (position_nine == 'X'))
        return 1;
    if ((position_seven == 'X') && (position_five == 'X') && (position_three == 'X'))
        return 1;
    if ((position_one == 'O') && (position_two == 'O') && (position_three == 'O'))
        return 2;
    if ((position_four == 'O') && (position_five == 'O') && (position_six == 'O'))
        return 2;
    if ((position_seven == 'O') && (position_eight == 'O') && (position_nine == 'O'))
        return 2;
    if ((position_one == 'O') && (position_four == 'O') && (position_seven == 'O'))
        return 2;
    if ((position_two == 'O') && (position_five == 'O') && (position_eight == 'O'))
        return 2;
    if ((position_three == 'O') && (position_six == 'O') && (position_nine == 'O'))
        return 2;
    if ((position_one == 'O') && (position_five == 'O') && (position_nine == 'O'))
        return 2;
    if ((position_seven == 'O') && (position_five == 'O') && (position_three == 'O'))
        return 2;
    return 0;
}
int kill_prog()
{
    if (win_check() == 1)
    {
        if (choice_XorO == '1')
        {
            printf("\nYou Win! \nThanks for playing!\n");
            return 1;
        }
        else if (choice_XorO == '2')
        {
            printf("\nComputer Wins. \nTry again!\n");
            return 1;
        }
    }
    if (win_check() == 2)
    {
        if (choice_XorO == '2')
        {
            printf("\nYou Win! \nThanks for playing!\n");
            return 1;
        }
        else if (choice_XorO == '1')
        {
            printf("\nComputer Wins. \nTry again!\n");
            return 1;
        }
    }
    return 0;
}
char find_third_O()
{
    if ((position_one == 'O') && (position_two == 'O') && (position_three == ' '))
        return '3';
    if ((position_one == ' ') && (position_two == 'O') && (position_three == 'O'))
        return '1';
    if ((position_one == 'O') && (position_two == ' ') && (position_three == 'O'))
        return '2';
    if ((position_four == 'O') && (position_five == 'O') && (position_six == ' '))
        return '6';
    if ((position_four == 'O') && (position_five == ' ') && (position_six == 'O'))
        return '5';
    if ((position_four == ' ') && (position_five == 'O') && (position_six == 'O'))
        return '4';
    if ((position_seven == 'O') && (position_eight == 'O') && (position_nine == ' '))
        return '9';
    if ((position_seven == 'O') && (position_eight == ' ') && (position_nine == 'O'))
        return '8';
    if ((position_seven == ' ') && (position_eight == 'O') && (position_nine == 'O'))
        return '7';
    if ((position_one == 'O') && (position_four == 'O') && (position_seven == ' '))
        return '7';
    if ((position_one == 'O') && (position_four == ' ') && (position_seven == 'O'))
        return '4';
    if ((position_one == ' ') && (position_four == 'O') && (position_seven == 'O'))
        return '1';
    if ((position_two == ' ') && (position_five == 'O') && (position_eight == 'O'))
        return '2';
    if ((position_two == 'O') && (position_five == 'O') && (position_eight == ' '))
        return '8';
    if ((position_two == 'O') && (position_five == ' ') && (position_eight == 'O'))
        return '5';
    if ((position_three == 'O') && (position_six == 'O') && (position_nine == ' '))
        return '9';
    if ((position_three == ' ') && (position_six == 'O') && (position_nine == 'O'))
        return '3';
    if ((position_three == 'O') && (position_six == ' ') && (position_nine == 'O'))
        return '6';
    if ((position_one == 'O') && (position_five == 'O') && (position_nine == ' '))
        return '9';
    if ((position_one == ' ') && (position_five == 'O') && (position_nine == 'O'))
        return '1';
    if ((position_one == 'O') && (position_five == ' ') && (position_nine == 'O'))
        return '5';
    if ((position_seven == 'O') && (position_five == 'O') && (position_three == ' '))
        return '3';
    if ((position_seven == 'O') && (position_five == ' ') && (position_three == 'O'))
        return '5';
    if ((position_seven == ' ') && (position_five == 'O') && (position_three == 'O'))
        return '7';
    else
        return '0';
}
char find_third_X()
{
    if ((position_one == 'X') && (position_two == 'X') && (position_three == ' '))
        return '3';
    if ((position_one == ' ') && (position_two == 'X') && (position_three == 'X'))
        return '1';
    if ((position_one == 'X') && (position_two == ' ') && (position_three == 'X'))
        return '2';
    if ((position_four == 'X') && (position_five == 'X') && (position_six == ' '))
        return '6';
    if ((position_four == 'X') && (position_five == ' ') && (position_six == 'X'))
        return '5';
    if ((position_four == ' ') && (position_five == 'X') && (position_six == 'X'))
        return '4';
    if ((position_seven == 'X') && (position_eight == 'X') && (position_nine == ' '))
        return '9';
    if ((position_seven == 'X') && (position_eight == ' ') && (position_nine == 'X'))
        return '8';
    if ((position_seven == ' ') && (position_eight == 'X') && (position_nine == 'X'))
        return '7';
    if ((position_one == 'X') && (position_four == 'X') && (position_seven == ' '))
        return '7';
    if ((position_one == 'X') && (position_four == ' ') && (position_seven == 'X'))
        return '4';
    if ((position_one == ' ') && (position_four == 'X') && (position_seven == 'X'))
        return '1';
    if ((position_two == ' ') && (position_five == 'X') && (position_eight == 'X'))
        return '2';
    if ((position_two == 'X') && (position_five == 'X') && (position_eight == ' '))
        return '8';
    if ((position_two == 'X') && (position_five == ' ') && (position_eight == 'X'))
        return '5';
    if ((position_three == 'X') && (position_six == 'X') && (position_nine == ' '))
        return '9';
    if ((position_three == ' ') && (position_six == 'X') && (position_nine == 'X'))
        return '3';
    if ((position_three == 'X') && (position_six == ' ') && (position_nine == 'X'))
        return '6';
    if ((position_one == 'X') && (position_five == 'X') && (position_nine == ' '))
        return '9';
    if ((position_one == ' ') && (position_five == 'X') && (position_nine == 'X'))
        return '1';
    if ((position_one == 'X') && (position_five == ' ') && (position_nine == 'X'))
        return '5';
    if ((position_seven == 'X') && (position_five == 'X') && (position_three == ' '))
        return '3';
    if ((position_seven == 'X') && (position_five == ' ') && (position_three == 'X'))
        return '5';
    if ((position_seven == ' ') && (position_five == 'X') && (position_three == 'X'))
        return '7';
    else
        return '0';
}
