#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char guess_1[255], guess_2[255], guess_3[255], guess_4[255], guess_5[255], guess_6[255], guess_7[255],
     guess_8[255], guess_9[255], guess_10[255],guess_11[255], guess_12[255], guess_13[255], guess_14[255],
     guess_15[255], guess_16[255], guess_17[255], guess_18[255], guess_19[255], guess_20[255],
     guess_21[255], guess_22[255], guess_23[255], guess_24[255], guess_25[255], guess_26[255];

char the_answer[255];
char space_tracker[255];
char start_blank[255];
char choose_to_guess[255];

int how_many_of_correct_letters = 0;
int wrong_guess_count = 0;

int win_checker ();
int success_or_failure_of_letter_guess (int how_many_of_correct_letters, char Guess);
char choose_to_guess_entry_checker ();
int invalid_letter_guess_checker(char guess[255]);
void board_update ();

//char[30] invalid_phrase_word_check (char word_or_phrase[30]);



char *invalid_phrase_word_check(char word_or_phrase[30]) {

    char result[30];


printf("\nword_or_phrase: %s\n", word_or_phrase);
printf("\nstrlen(word_or_phrase): %d\n", strlen(word_or_phrase));                                    // TROUBLE STARTS HERE

//for (int z = 0; ((strlen(word_or_phrase) < 6 || strlen(word_or_phrase) > 20) && z < 2) ;z++) {
//        printf("\nInvalid entry. Please enter a word or phrase that is 6 to 20 total letters. ");
//        gets(word_or_phrase);
//    }
//    if (strlen(word_or_phrase) < 6 || strlen(word_or_phrase) > 20) {
//        printf("\nYou had your chance. Program terminated1. \n");
//        return 0;
//      }


    int b = 1;
    for (int a=0; (word_or_phrase[a] != '\0' && word_or_phrase[a] != ' ' && b < 3);a++) {
        printf("\ninside for loop\n");
        if ((isalpha(word_or_phrase[a]) == 0) || (strlen(word_or_phrase) < 6) || (strlen(word_or_phrase) > 20)) {
            printf("\nInvalid entry. Please enter a word or phrase that is 6 to 20 total letters. ");
            gets(word_or_phrase);
            b++;
            a=-1;
        }
    }

    printf("\nbetween loops\n");

    for (int a2 = 0; word_or_phrase[a2] != '\0' && word_or_phrase[a2] != ' ' ;a2++) {
        if (isalpha(word_or_phrase[a2]) == 0 || strlen(word_or_phrase) < 6 || strlen(word_or_phrase) > 20) {
        printf("\nYou had your chance. Program terminated2. \n");
        *result = "0";
        printf("result: %s", result);
        return result;
        }
    }


    int j,k = 0;
    for (j = 0; word_or_phrase[j] != '\0' ;j++) {
        if (word_or_phrase[j] != ' ')
        {
            result[k] = tolower(word_or_phrase[j]);
            k++;
            space_tracker[j] = '0';
        }
        else if (word_or_phrase

                 [j] == ' ') space_tracker[j] = '1';
    }
    space_tracker[j] = '\0';
    result[k] = '\0';


    printf("\nresult: %s\n", result);
    return result;

}


int main()
{

    int i;
    for (i=0; i < 20;i++) {
    start_blank[i] = ' ';
}
    start_blank[i] = '\0';

    char big_guess_1[255], Big_Guess_1[255];
    char the_entry[255];


    printf("Welcome to Hangman! \n");
    printf("\nPlease enter a word or phrase that is 6 to 20 total letters. \n");
    gets(the_entry);

    for (int z = 0; ((strlen(the_entry) < 6 || strlen(the_entry) > 20) && z < 2) ;z++) {
        printf("\nInvalid entry. Please enter a word or phrase that is 6 to 20 total letters. ");
        gets(the_entry);
    }
    if (strlen(the_entry) < 6 || strlen(the_entry) > 20) {
        printf("\nYou had your chance. Program terminated1. \n");
        return 0;
      }


    int a,b = 1;
    for (a=0; (the_entry[a] != '\0' && the_entry[a] != ' ' && b < 3);a++) {
        if (isalpha(the_entry[a]) == 0) {
            printf("\nInvalid entry. Please enter only letters. \n");
            gets(the_entry);
            b++;
            a=-1;
        }
    }
    for (int a2 = 0; the_entry[a] != '\0' && the_entry[a] != ' ' ;a++) {
        if (isalpha(the_entry[a2]) == 0) {
        printf("\nYou had your chance. Program terminated2. \n");
        return 0;
        }
    }


    int j,k = 0;
    for (j = 0; the_entry[j] != '\0' ;j++) {
        if (the_entry[j] != ' ')
        {
            the_answer[k] = tolower(the_entry[j]);
            k++;
            space_tracker[j] = '0';
        }
        else if (the_entry[j] == ' ') space_tracker[j] = '1';
    }
    space_tracker[j] = '\0';
    the_answer[k] = '\0';



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");             // guess 1
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);


        printf("invalid_phrase_word_check(big_guess_1): %s", invalid_phrase_word_check(big_guess_1));


        if (invalid_phrase_word_check(big_guess_1) == "0") return 0;



        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;






    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 2
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    printf("\nstart_blank: %s\n", start_blank);
    printf("\nthe_answer: %s\n", the_answer);
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 3
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }


    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 4
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 5
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 6
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }


    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 7
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }


    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 8
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 9
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }


    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 10
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 11
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 12
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }


    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 13
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 14
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 15
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 16
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 17
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }




    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 18
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }




    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 19
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 20
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 21
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }




    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 22
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }




    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 23
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 24
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }



    printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 25
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }




printf("\nPress 1 to guess a letter and 2 to guess the word/phrase: ");       // guess 26
    gets(choose_to_guess);
    if (choose_to_guess_entry_checker(choose_to_guess) == '1') return 0;

    if (choose_to_guess[0] == '2') {
        printf("\nOk, what's the word/phrase? ");
        gets(big_guess_1);
        for (j = 0, k = 0; big_guess_1[j] != '\0' ;j++) {
        if (big_guess_1[j] != ' ')
        {
            Big_Guess_1[k] = tolower(big_guess_1[j]);
            k++;
        }
        }
        Big_Guess_1[k] = '\0';
        if (strcmp(Big_Guess_1, the_answer) == 0) {
            printf("\nYou guessed it! Good game! \n");
            return 0;
        }
        else printf("\nWrong guess. \n");
        wrong_guess_count++;
    }


    else if (choose_to_guess[0] == '1') {
    printf("\nGuess a letter: ");
    gets(guess_1);
    if (choose_to_guess_entry_checker(guess_1) == 1) return 0;
    else *guess_1 = tolower(*guess_1);

    int q;
    for (q=0; the_answer[q] != '\0'; q++) {
    if (*guess_1 == the_answer[q]) {
        start_blank[q] = *guess_1;
        how_many_of_correct_letters++;
    }
    }

    success_or_failure_of_letter_guess (how_many_of_correct_letters, *guess_1);
    }
    board_update();
    how_many_of_correct_letters = 0;
    if (win_checker() == 0) {
        printf("\nCongrats! You win! \n");
        return 0;
    }


printf("start_blank: %s\n", start_blank);

printf("space_tracker: %s", space_tracker);


printf("End of line. \n");
return 0;
}











int success_or_failure_of_letter_guess (int how_many_of_correct_letters, char Guess) {
     if (how_many_of_correct_letters == 0) {
        printf("\nThere are no %c's. Guess again. \n", Guess);
        wrong_guess_count++;
    }
    else if (how_many_of_correct_letters > 1) {
        printf("\nGood guess! There are %d %c's!\n", how_many_of_correct_letters, Guess);
    }
    else if (how_many_of_correct_letters == 1) {
        printf("\nGood guess! There is %d %c!\n", how_many_of_correct_letters, Guess);
    }
    return 0;
}

char choose_to_guess_entry_checker () {

    for (int c1 = 0; ((!(*choose_to_guess == '1' || *choose_to_guess == '2') || (strlen(choose_to_guess) != 1)) && c1 < 2); c1++) {
        printf("\nOops. Please press 1 to guess a letter and 2 to guess the word/phrase: ");
        gets(choose_to_guess);
    }
    if ((!(*choose_to_guess == '1' || *choose_to_guess == '2') || (strlen(choose_to_guess) != 1))) {
        printf("You had your chance. Program terminated3. \n");
        return '1';
        }
        return '0';
}

int invalid_letter_guess_checker(char guess[255]) {
    for (int i = 0; ((strlen(guess) != 1 || isalpha(*guess) == 0) && i < 2) ;i++)
    {

        printf("Oops. Please enter a single letter: ");
        gets(guess);
    }
        if (strlen(guess) != 1 || isalpha(*guess) == 0) {
        printf("You had your chance. Program terminated4. \n");
        return 1;
        }
        return 0;
    }

void board_update () {
    printf("\n");
    int p,p2 = 0;
    for (p=0; p < strlen(space_tracker) ;p++) {
        if (space_tracker[p] == '0') {
            printf("  %c   ", start_blank[p2]);
            p2++;
            }
        else if ((space_tracker[p] == '1'))
            printf("   ");

    }
    printf("\n");
    int r;
    for (r=0; r < strlen(space_tracker); r++) {
        if (space_tracker[r] == '0') {
           printf("_____ ");
        }
        else if (space_tracker[r] == '1') {
            printf("   ");
        }
    }
     printf("\n");
}

int win_checker () {
    int c = 0;
    for (int b = 0; b < strlen(the_answer); b++) {
        if (start_blank[b] == ' ') c++;
    }
    printf("\nc: %d\n", c);
    return c;
}


