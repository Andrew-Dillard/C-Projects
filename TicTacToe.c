// Tic Tac Toe game with single and two player modes
// Fun fact: There are 255,168 possible games of Tic Tac Toe!

// this is a git test 7/21/25

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char choice_XorO;
char a=' ',b=' ',c=' ',d=' ',e=' ',f=' ',g=' ',h=' ',i=' ';
int invalid_entry_count = 0;

void moveX (char);                              // applies X's
void moveO (char);                              // applies O's
void new_board ();                              // shows updated game
char default_mode ();                           // computer's default mode of playing like you read a book
int win_check();                                // checks to see if either side has won
int kill_prog();                                // terminates program if someone has won
char find_third_O();                            // finds winning move for O's
char find_third_X();                            // finds winning move for X's
int invalid_entry_police (char string[255]);    // ensures entry is 1 character and a number between 1 and 9

int main()
{
    int duplicate_entry_count = 0;
    char game_mode;
    char Pmv1, Pmv2, Pmv3, Pmv4, Pmv5;
    char Cmv1, Cmv2, Cmv3, Cmv4, Cmv5;
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
    for (int game_mode_chance = 1; ((strlen(Game_mode) != 1) || !(Game_mode[0] == '1' || Game_mode[0] == '2'))
                                    && game_mode_chance < 3; game_mode_chance++)
    {
        printf("\nInvalid entry. Please enter 1 for single player mode and 2 for two player mode: ");
        scanf("%s", Game_mode);
    }

    if ((strlen(Game_mode) != 1) || !(Game_mode[0] == '1' || Game_mode[0] == '2')) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else game_mode = Game_mode[0];
    if (game_mode == '1'){
        printf("\nSingle player mode. Can you beat the computer?...\n");
        printf("\nX's go first. Would you like to be X's or O's? \n");
        printf("\nPress 1 to be X's and 2 to be O's: ");
        scanf(" %s", Choice_XorO);
        for (int choice_XorO_chance = 1; ((strlen(Choice_XorO) != 1) || !(Choice_XorO[0] == '1' || Choice_XorO[0] == '2'))
                                          && choice_XorO_chance < 3; choice_XorO_chance++)
    {
        printf("\nInvalid entry. Please press 1 to be X's and 2 to be O's: ");
        scanf("%s", Choice_XorO);
    }

    if ((strlen(Choice_XorO) != 1) || !(Choice_XorO[0] == '1' || Choice_XorO[0] == '2')) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
        }
    else choice_XorO = Choice_XorO[0];
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



    if (choice_XorO == '2')                                             //  computer's first move if it is X's
    {
        Cmv1 = '5';
        moveX(Cmv1);
        new_board();
    }

    printf("Cmv1: %c\n", Cmv1);

    printf("\nEnter move 1: ");                                         // player move 1
    scanf(" %s", Move_1);
    if (invalid_entry_police(Move_1) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else Pmv1 = Move_1[0];
    for (int s = 0; Pmv1 == Cmv1 && s < 2; s++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", Move_1);
        if (invalid_entry_police(Move_1) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else Pmv1 = Move_1[0];
    }
    if (Pmv1 == Cmv1 || duplicate_entry_count >= 3)
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    if (choice_XorO == '1') moveX(Pmv1);
    else if (choice_XorO == '2') moveO(Pmv1);
    new_board();

    if (choice_XorO == '1') {                                           //  computer move 2 if X's and move 1 if O's
    if (Pmv1!='5') Cmv2 = '5';
    else Cmv2 = default_mode();
}
    if (choice_XorO == '2')
        {
        if (Pmv1 == '1')  Cmv2 = '9';
        else Cmv2 = default_mode();
        moveX(Cmv2);
        }
    else if (choice_XorO == '1') moveO(Cmv2);
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

    printf("\nEnter move 2: ");                                                 // player move 2
    scanf(" %s", Move_2);
    if (invalid_entry_police(Move_2) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else Pmv2 = Move_2[0];
    for (int t=0; (((Pmv2 == Cmv1)||(Pmv2 == Cmv2)||(Pmv2 == Pmv1)) && (t < 2)); t++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", Move_2);
        if (invalid_entry_police(Move_2) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else Pmv2 = Move_2[0];
    }
    if ((Pmv2 == Cmv1)||(Pmv2 == Cmv2)||(Pmv2 == Pmv1)||(duplicate_entry_count >= 3))
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    if (choice_XorO == '1') moveX(Pmv2);
    else if (choice_XorO == '2') moveO(Pmv2);
    new_board();

    Cmv3 = find_third_X();                                                  //  computer move 3 if X's and move 2 if O's
    if (Cmv3 == '0') Cmv3 = find_third_O();
    if (choice_XorO == '2' && Cmv3 == '0')
    {
        if (Cmv2 == '1')
        {
            if (c == ' ') Cmv3 = '3';
            if (g == ' ' && Pmv1 != '4' && Pmv1 != '9') Cmv3 = '7';
            if (Pmv1 == '9' && Pmv2 == '2')  Cmv3 = '7';
        }
        if (Pmv1 == '1' && Cmv2 == '9')
        {
            if (Pmv2 == '6') Cmv3 = '8';
            if (Pmv2 == '8') Cmv3 = '6';
        }
    }
    if (Cmv3 == '0' && choice_XorO == '1') {
        if (Pmv1 == '2') {
            if (Pmv2 == '4') Cmv3 = '1';
            if (Pmv2 == '6') Cmv3 = '3';
        }
        if (Pmv1 == '4') {
            if (Pmv2 == '2') Cmv3 = '1';
            if (Pmv2 == '8') Cmv3 = '7';
        }
        if (Pmv1 == '6') {
            if (Pmv2 == '2') Cmv3 = '3';
            if (Pmv2 == '8') Cmv3 = '9';
        }
        if (Pmv1 == '8') {
            if (Pmv2 == '4') Cmv3 = '7';
            if (Pmv2 == '6') Cmv3 = '9';
        }
        if (e == 'X' && i == 'X') Cmv3 = '3';
        if (c == 'X' && h == 'X') Cmv3 = '9';
        if (c == 'X' && d == 'X') Cmv3 = '1';
        if (c == 'X' && g == 'X') Cmv3 = '6';
        if (a == 'X' && h == 'X') Cmv3 = '7';
        if (a == 'X' && h == 'X') Cmv3 = '7';
        if (a == 'X' && i == 'X') Cmv3 = '2';
        if (i == 'X' && a == 'X') Cmv3 = '2';
        if (i == 'X' && b == 'X') Cmv3 = '3';
        if (i == 'X' && d == 'X') Cmv3 = '7';
        if (c == 'X' && g == 'X') Cmv3 = '6';
        if (f == 'X' && g == 'X') Cmv3 = '9';
        if (b == 'X' && g == 'X') Cmv3 = '3';
    }
    if (Cmv3 == '0') Cmv3 = default_mode();
    if (choice_XorO == '2')      moveX(Cmv3);
    else if (choice_XorO == '1') moveO(Cmv3);
    new_board();
    if(kill_prog() == 1) return 0;

    printf("\n 1 | 2 | 3 \n");
    printf("___|___|___\n");
    printf(" 4 | 5 | 6 \n");
    printf("___|___|___\n");
    printf(" 7 | 8 | 9 \n");
    printf("   |   |   \n");

    printf("\nEnter move 3: ");                                                 // player move 3
    scanf(" %s", Move_3);
    if (invalid_entry_police(Move_3) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else Pmv3 = Move_3[0];
    for (int u=0; (((Pmv3 == Cmv1)||(Pmv3 == Cmv2)||(Pmv3 == Cmv3)||(Pmv3 == Pmv1)||(Pmv3 == Pmv2)) && (u < 2)); u++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", Move_3);
        if (invalid_entry_police(Move_3) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else Pmv3 = Move_3[0];
    }
    if ((Pmv3 == Cmv1)||(Pmv3 == Cmv2)||(Pmv3 == Cmv3)||(Pmv3 == Pmv1)||(Pmv3 == Pmv2)||(duplicate_entry_count >= 3))
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    if (choice_XorO == '1') moveX(Pmv3);
    else if (choice_XorO == '2') moveO(Pmv3);
    new_board();
    if(kill_prog() == 1) return 0;

    if (choice_XorO == '1')                                                         //  computer move 4 if X's and move 3 if O's
        {
            Cmv4 = find_third_O();
            if (Cmv4 == '0')     Cmv4 = find_third_X();
            if ((Cmv4 == '0') && a == 'X' && f == 'X' && h == 'X') Cmv4 = '7';
            if (Cmv4 == '0')     Cmv4 = default_mode();
            moveO(Cmv4);
        }
    if (choice_XorO == '2')
        {
            Cmv4 = find_third_X();
            if (Cmv4 == '0')     Cmv4 = find_third_O();
            if (Cmv4 == '0')     Cmv4 = default_mode();
            moveX(Cmv4);
        }
    new_board();
    if(kill_prog() == 1) return 0;

    printf("\nEnter move 4: ");                                                         // player move 4
    scanf(" %s", Move_4);
    if (invalid_entry_police(Move_4) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else Pmv4 = Move_4[0];
    for (int v = 0; ((Pmv4 == Cmv1)||(Pmv4 == Cmv2)||(Pmv4 == Cmv3)||(Pmv4 == Cmv4)||(Pmv4 == Pmv1)
                   ||(Pmv4 == Pmv2)||(Pmv4 == Pmv3)) && v < 2; v++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", Move_4);
        if (invalid_entry_police(Move_4) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else Pmv4 = Move_4[0];
    }
    if ((Pmv4 == Cmv1)||(Pmv4 == Cmv2)||(Pmv4 == Cmv3)||(Pmv4 == Cmv4)||(Pmv4 == Pmv1)
             ||(Pmv4 == Pmv2)||(Pmv4 == Pmv3)||(duplicate_entry_count >= 3))
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    if (choice_XorO == '1') moveX(Pmv4);
    else if (choice_XorO == '2') moveO(Pmv4);
    new_board();
    if(kill_prog() == 1) return 0;

    if (choice_XorO == '1')                                             //  computer move 5 if X's and move 4 if O's (final move)
        {
            Cmv5 = find_third_O();
            if (Cmv5 == '0')     Cmv5 = find_third_X();
            if (Cmv5 == '0')     Cmv5 = default_mode();
            moveO(Cmv5);
        }
    if (choice_XorO == '2')
        {
            Cmv5 = find_third_X();
            if (Cmv5 == '0')     Cmv5 = find_third_O();
            if (Cmv5 == '0')     Cmv5 = default_mode();
            moveX(Cmv5);
        }
    new_board();
    if(kill_prog() == 1) return 0;
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

    printf("\nEnter move 5: ");                                              // player move 5 (final move)
    scanf(" %s", Move_5);
    if (invalid_entry_police(Move_5) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else Pmv5 = Move_5[0];
    for (int w = 0; ((Pmv5 == Cmv1)||(Pmv5 == Cmv2)||(Pmv5 == Cmv3)||(Pmv5 == Cmv4)||
                     (Pmv5 == Pmv1)||(Pmv5 == Pmv2)||(Pmv5 == Pmv3)||(Pmv5 == Pmv4)) && w < 2; w++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", Move_5);
        if (invalid_entry_police(Move_5) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else Pmv5 = Move_5[0];
    }
    if ((Pmv5 == Cmv1)||(Pmv5 == Cmv2)||(Pmv5 == Cmv3)||(Pmv5 == Cmv4)||
        (Pmv5 == Pmv1)||(Pmv5 == Pmv2)||(Pmv5 == Pmv3)||(Pmv5 == Pmv4)||(duplicate_entry_count >= 3))
    {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    if (choice_XorO == '1')      moveX(Pmv5);
    else if (choice_XorO == '2') moveO(Pmv5);
    new_board();
    if(kill_prog() == 1) return 0;
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
    char p1_mv1, p1_mv2, p1_mv3, p1_mv4, p1_mv5;
    char p2_mv1, p2_mv2, p2_mv3, p2_mv4;
    printf("\nWelcome to two player mode. \n");
    printf("\nPlayer 1 will be X's and Player 2 will be O's. \n");
    printf("\nPlease use above diagram to enter your moves.\n");
    printf("\n 1 | 2 | 3 \n");
    printf("___|___|___\n");
    printf(" 4 | 5 | 6 \n");
    printf("___|___|___\n");
    printf(" 7 | 8 | 9 \n");
    printf("   |   |   \n");

    printf("\nEnter move Player 1: ");                                         // Player 1 move 1
    scanf("%s", P1mv1);
    if (invalid_entry_police(P1mv1) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p1_mv1 = *P1mv1;

    moveX(p1_mv1);
    new_board();

    printf("\nEnter move Player 2: ");                                         // Player 2 move 1
    scanf("%s", P2mv1);
    if (invalid_entry_police(P2mv1) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p2_mv1 = *P2mv1;

    for (int S = 0; p2_mv1 == p1_mv1 && S < 2; S++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv1);
        if (invalid_entry_police(P2mv1) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p2_mv1 = *P2mv1;
    }


    moveO(p2_mv1);
    new_board();

    printf("\nEnter move Player 1: ");                                          // Player 1 move 2
    scanf("%s", P1mv2);
    if (invalid_entry_police(P1mv2) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p1_mv2 = *P1mv2;
    for (int T = 0; (p1_mv2 == p1_mv1 || p1_mv2 == p2_mv1) && T < 2; T++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv2);
        if (invalid_entry_police(P1mv2) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p1_mv2 = *P1mv2;
    }
    if (p1_mv2 == p1_mv1 || p1_mv2 == p2_mv1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    moveX(p1_mv2);
    new_board();

    printf("\n 1 | 2 | 3 \n");
    printf("___|___|___\n");
    printf(" 4 | 5 | 6 \n");
    printf("___|___|___\n");
    printf(" 7 | 8 | 9 \n");
    printf("   |   |   \n");

    printf("\nEnter move Player 2: ");                                         // Player 2 move 2
    scanf("%s", P2mv2);
    if (invalid_entry_police(P2mv2) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p2_mv2 = *P2mv2;

    for (int U = 0; (p2_mv2 == p1_mv1 || p2_mv2 == p1_mv2 || p2_mv2 == p2_mv1) && U < 2; U++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv2);
        if (invalid_entry_police(P2mv2) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p2_mv2 = *P2mv2;
    }
    if (p2_mv2 == p1_mv1 || p2_mv2 == p1_mv2 || p2_mv2 == p2_mv1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    moveO(p2_mv2);
    new_board();

    printf("\nEnter move Player 1: ");                                          // Player 1 move 3
    scanf("%s", P1mv3);
    if (invalid_entry_police(P1mv3) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p1_mv3 = *P1mv3;
    for (int V = 0; (p1_mv3 == p1_mv1 || p1_mv3 == p1_mv2 || p1_mv3 == p2_mv1 || p1_mv3 == p2_mv2) && V < 2; V++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv3);
        if (invalid_entry_police(P1mv3) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p1_mv3 = *P1mv3;
    }
    if (p1_mv3 == p1_mv1 || p1_mv3 == p1_mv2 || p1_mv3 == p2_mv1 || p1_mv3 == p2_mv2) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    moveX(p1_mv3);
    new_board();
    if (win_check() == 1) {
        printf("\nPlayer 1 wins! \n");
        return 0;
    }


    printf("\nEnter move Player 2: ");                                         // Player 2 move 3
    scanf("%s", P2mv3);
    if (invalid_entry_police(P2mv3) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p2_mv3 = *P2mv3;

    for (int W = 0; (p2_mv3 == p1_mv1 || p2_mv3 == p1_mv2 || p2_mv3 == p1_mv3 ||
                     p2_mv3 == p2_mv1 || p2_mv3 == p2_mv2) && W < 2; W++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv3);
        if (invalid_entry_police(P2mv3) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p2_mv3 = *P2mv3;
    }
    if (p2_mv3 == p1_mv1 || p2_mv3 == p1_mv2 || p2_mv3 == p1_mv3 ||
        p2_mv3 == p2_mv1 || p2_mv3 == p2_mv2) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    moveO(p2_mv3);
    new_board();
    if (win_check() == 2) {
        printf("\nPlayer 2 wins! \n");
        return 0;
    }

    printf("\n 1 | 2 | 3 \n");
    printf("___|___|___\n");
    printf(" 4 | 5 | 6 \n");
    printf("___|___|___\n");
    printf(" 7 | 8 | 9 \n");
    printf("   |   |   \n");

    printf("\nEnter move Player 1: ");                                          // Player 1 move 4
    scanf("%s", P1mv4);
    if (invalid_entry_police(P1mv4) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p1_mv4 = *P1mv4;
    for (int X = 0; (p1_mv4 == p1_mv1 || p1_mv4 == p1_mv2 || p1_mv4 == p2_mv3 ||
                     p1_mv4 == p2_mv1 || p1_mv4 == p2_mv2 || p1_mv4 == p2_mv3) && X < 2; X++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv4);
        if (invalid_entry_police(P1mv4) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p1_mv4 = *P1mv4;
    }
    if (p1_mv4 == p1_mv1 || p1_mv4 == p1_mv2 || p1_mv4 == p2_mv3 ||
        p1_mv4 == p2_mv1 || p1_mv4 == p2_mv2 || p1_mv4 == p2_mv3) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    moveX(p1_mv4);
    new_board();
    if (win_check() == 1) {
        printf("\nPlayer 1 wins! \n");
        return 0;
    }

    printf("\nEnter move Player 2: ");                                         // Player 2 move 4
    scanf("%s", P2mv4);
    if (invalid_entry_police(P2mv4) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p2_mv4 = *P2mv4;

    for (int Y = 0; (p2_mv4 == p1_mv1 || p2_mv4 == p1_mv2 || p2_mv4 == p1_mv3 || p2_mv4 == p1_mv4 ||
                     p2_mv4 == p2_mv1 || p2_mv4 == p2_mv2 || p2_mv4 == p2_mv3) && Y < 2; Y++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P2mv4);
        if (invalid_entry_police(P2mv4) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p2_mv4 = *P2mv4;
    }
    if (p2_mv4 == p1_mv1 || p2_mv4 == p1_mv2 || p2_mv4 == p1_mv3 || p2_mv4 == p1_mv4 ||
        p2_mv4 == p2_mv1 || p2_mv4 == p2_mv2 || p2_mv4 == p2_mv3) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    moveO(p2_mv4);
    new_board();
    if (win_check() == 2) {
        printf("\nPlayer 2 wins! \n");
        return 0;
    }

    printf("\nEnter move Player 1: ");                                          // Player 1 move 5
    scanf("%s", P1mv5);
    if (invalid_entry_police(P1mv5) == 1) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    else p1_mv5 = *P1mv5;
    for (int Z = 0; (p1_mv5 == p1_mv1 || p1_mv5 == p1_mv2 || p1_mv5 == p1_mv3 || p1_mv5 == p1_mv4 ||
                     p1_mv5 == p2_mv1 || p1_mv5 == p2_mv2 || p1_mv5 == p2_mv3 || p1_mv5 == p2_mv4) && Z < 2; Z++)
    {
        duplicate_entry_count++;
        if (duplicate_entry_count >= 3) break;
        printf("That spot is already taken. Please pick a unique move. ");
        scanf(" %s", P1mv5);
        if (invalid_entry_police(P1mv5) == 1) {
            printf("\nYou had your chance. Program terminated. \n");
            return 0;
        }
        else p1_mv5 = *P1mv5;
    }
    if (p1_mv5 == p1_mv1 || p1_mv5 == p1_mv2 || p1_mv5 == p1_mv3 || p1_mv5 == p1_mv4 ||
        p1_mv5 == p2_mv1 || p1_mv5 == p2_mv2 || p1_mv5 == p2_mv3 || p1_mv5 == p2_mv4) {
        printf("\nYou had your chance. Program terminated. \n");
        return 0;
    }
    moveX(p1_mv5);
    new_board();
    if (win_check() == 1) {
        printf("\nPlayer 1 wins! \n");
        return 0;
    }
    else {
    printf("\nTied game. \nThanks for playing! Don't forget to check out single player mode! \n");
    return 0;
         }
}

// FUNCTIONS

int invalid_entry_police (char string[255]) {
    int chance;
    for (chance = 1; ((strlen(string) != 1) || !(string[0] == '1'||string[0] == '2'||string[0] == '3'||string[0] == '4'||
                 string[0] == '5'||string[0] == '6'||string[0] == '7'||string[0] == '8'||string[0] == '9')) && (chance < 3); chance++)
    {
        invalid_entry_count++;
        if (invalid_entry_count >= 3) break;
        printf("\nInvalid entry. Please choose a number between 1 and 9: ");
        scanf("%s", string);
    }
        if ((invalid_entry_count >= 3) ||(strlen(string) != 1) || !(string[0] == '1'||string[0] == '2'||string[0] == '3'||string[0] == '4'||
                 string[0] == '5'||string[0] == '6'||string[0] == '7'||string[0] == '8'||string[0] == '9'))
                 return 1;

                 else return 0;

}
void new_board () {
    printf("\n %c | %c | %c \n", a, b, c);
    printf("___|___|___\n");
    printf(" %c | %c | %c \n", d, e, f);
    printf("___|___|___\n");
    printf(" %c | %c | %c \n", g, h, i);
    printf("   |   |   \n");
}
void moveX (char m) {
    if (m == '1') a = 'X';
    if (m == '2') b = 'X';
    if (m == '3') c = 'X';
    if (m == '4') d = 'X';
    if (m == '5') e = 'X';
    if (m == '6') f = 'X';
    if (m == '7') g = 'X';
    if (m == '8') h = 'X';
    if (m == '9') i = 'X';
}
void moveO (char m) {
    if (m == '1') a = 'O';
    if (m == '2') b = 'O';
    if (m == '3') c = 'O';
    if (m == '4') d = 'O';
    if (m == '5') e = 'O';
    if (m == '6') f = 'O';
    if (m == '7') g = 'O';
    if (m == '8') h = 'O';
    if (m == '9') i = 'O';
}
char default_mode () {
    if (a==' ') return '1';
    if (b==' ') return '2';
    if (c==' ') return '3';
    if (d==' ') return '4';
    if (e==' ') return '5';
    if (f==' ') return '6';
    if (g==' ') return '7';
    if (h==' ') return '8';
    if (i==' ') return '9';
}
int win_check() {
    if ((a=='X')&&(b=='X')&&(c=='X'))  return 1;
    if ((d=='X')&&(e=='X')&&(f=='X'))  return 1;
    if ((g=='X')&&(h=='X')&&(i=='X'))  return 1;
    if ((a=='X')&&(d=='X')&&(g=='X'))  return 1;
    if ((b=='X')&&(e=='X')&&(h=='X'))  return 1;
    if ((c=='X')&&(f=='X')&&(i=='X'))  return 1;
    if ((a=='X')&&(e=='X')&&(i=='X'))  return 1;
    if ((g=='X')&&(e=='X')&&(c=='X'))  return 1;
    if ((a=='O')&&(b=='O')&&(c=='O'))  return 2;
    if ((d=='O')&&(e=='O')&&(f=='O'))  return 2;
    if ((g=='O')&&(h=='O')&&(i=='O'))  return 2;
    if ((a=='O')&&(d=='O')&&(g=='O'))  return 2;
    if ((b=='O')&&(e=='O')&&(h=='O'))  return 2;
    if ((c=='O')&&(f=='O')&&(i=='O'))  return 2;
    if ((a=='O')&&(e=='O')&&(i=='O'))  return 2;
    if ((g=='O')&&(e=='O')&&(c=='O'))  return 2;
}
int kill_prog() {
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
}
char find_third_O() {
    if ((a=='O')&&(b=='O')&&(c==' '))  return '3';
    if ((a==' ')&&(b=='O')&&(c=='O'))  return '1';
    if ((a=='O')&&(b==' ')&&(c=='O'))  return '2';
    if ((d=='O')&&(e=='O')&&(f==' '))  return '6';
    if ((d=='O')&&(e==' ')&&(f=='O'))  return '5';
    if ((d==' ')&&(e=='O')&&(f=='O'))  return '4';
    if ((g=='O')&&(h=='O')&&(i==' '))  return '9';
    if ((g=='O')&&(h==' ')&&(i=='O'))  return '8';
    if ((g==' ')&&(h=='O')&&(i=='O'))  return '7';
    if ((a=='O')&&(d=='O')&&(g==' '))  return '7';
    if ((a=='O')&&(d==' ')&&(g=='O'))  return '4';
    if ((a==' ')&&(d=='O')&&(g=='O'))  return '1';
    if ((b==' ')&&(e=='O')&&(h=='O'))  return '2';
    if ((b=='O')&&(e=='O')&&(h==' '))  return '8';
    if ((b=='O')&&(e==' ')&&(h=='O'))  return '5';
    if ((c=='O')&&(f=='O')&&(i==' '))  return '9';
    if ((c==' ')&&(f=='O')&&(i=='O'))  return '3';
    if ((c=='O')&&(f==' ')&&(i=='O'))  return '6';
    if ((a=='O')&&(e=='O')&&(i==' '))  return '9';
    if ((a==' ')&&(e=='O')&&(i=='O'))  return '1';
    if ((a=='O')&&(e==' ')&&(i=='O'))  return '5';
    if ((g=='O')&&(e=='O')&&(c==' '))  return '3';
    if ((g=='O')&&(e==' ')&&(c=='O'))  return '5';
    if ((g==' ')&&(e=='O')&&(c=='O'))  return '7';
        else return '0';
}
char find_third_X() {
    if ((a=='X')&&(b=='X')&&(c==' '))  return '3';
    if ((a==' ')&&(b=='X')&&(c=='X'))  return '1';
    if ((a=='X')&&(b==' ')&&(c=='X'))  return '2';
    if ((d=='X')&&(e=='X')&&(f==' '))  return '6';
    if ((d=='X')&&(e==' ')&&(f=='X'))  return '5';
    if ((d==' ')&&(e=='X')&&(f=='X'))  return '4';
    if ((g=='X')&&(h=='X')&&(i==' '))  return '9';
    if ((g=='X')&&(h==' ')&&(i=='X'))  return '8';
    if ((g==' ')&&(h=='X')&&(i=='X'))  return '7';
    if ((a=='X')&&(d=='X')&&(g==' '))  return '7';
    if ((a=='X')&&(d==' ')&&(g=='X'))  return '4';
    if ((a==' ')&&(d=='X')&&(g=='X'))  return '1';
    if ((b==' ')&&(e=='X')&&(h=='X'))  return '2';
    if ((b=='X')&&(e=='X')&&(h==' '))  return '8';
    if ((b=='X')&&(e==' ')&&(h=='X'))  return '5';
    if ((c=='X')&&(f=='X')&&(i==' '))  return '9';
    if ((c==' ')&&(f=='X')&&(i=='X'))  return '3';
    if ((c=='X')&&(f==' ')&&(i=='X'))  return '6';
    if ((a=='X')&&(e=='X')&&(i==' '))  return '9';
    if ((a==' ')&&(e=='X')&&(i=='X'))  return '1';
    if ((a=='X')&&(e==' ')&&(i=='X'))  return '5';
    if ((g=='X')&&(e=='X')&&(c==' '))  return '3';
    if ((g=='X')&&(e==' ')&&(c=='X'))  return '5';
    if ((g==' ')&&(e=='X')&&(c=='X'))  return '7';
        else return '0';
}
