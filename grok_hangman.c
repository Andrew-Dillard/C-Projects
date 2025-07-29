// Include standard libraries for I/O, random numbers, string operations, character checks, and time.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// define constant for maximum number of incorrect guesses allowed
#define MAX_NUM_INCORRECT_GUESSES 6

// the word list for the game, define array whose elements are pointers, containing the memory address of the first character in each string
const char *words[] = {
    "adam", "eve", "noah", "abraham", "sarah", "isaac", "jacob", "joseph", "moses", "aaron", "david", "solomon", "elijah", "elisha", "ruth", "esther", "daniel", "jonah", "mary", "jesus"};

// stores number of elements in the words[] array
int num_words = sizeof(words) / sizeof(words[0]);

// function to show how many incorrect guesses are remaining
void draw_hangman(int num_incorrect_guesses)
{
  printf("\nWrong guesses remaining: %d\n", MAX_NUM_INCORRECT_GUESSES - num_incorrect_guesses);
  // Simple ASCII art for hangman stages can be added here
}

int main()
{
  // Welcome message
  printf("\nWelcome to hangman! Can you guess the word?\n");
  // Seed rand() with the current time for varied random numbers
  srand(time(NULL));
  // use rand() function to pick a random word from the words array and store the reference to its location in memory (pointer) in the *word variable.
  const char *word = words[rand() % num_words];
  // store length of random word selected
  int word_len = strlen(word);
  // create character array called word_progress that is long enough to hold the length of the random word, plus one space for the null terminator, '\0'
  char word_progress[word_len + 1];
  // load the word_progress array with placeholders that are underscores _ the length of the random word
  memset(word_progress, '_', word_len);
  // load the final element in the word_progress array with the null terminator, '\0' NOTE: word_progress[word_len] will always grab the last element in the word_progress array since the first item is item 0
  word_progress[word_len] = '\0';
  // variable to store the number of incorrect guesses used up so far
  int num_incorrect_guesses = 0;
  // character array to store guessed letters. Initialize with {0} which sets the value of all 26 elements to the null terminator character, '\0'
  char guessed_letters[26] = {0};
  // store number of unique guessed letters.
  int num_guessed_letters = 0;

  // game loop
  // as long as the number of incorrect guesses, (num_incorrect_guesses) is less than the number of allowed incorrect guesses, (MAX_NUM_INCORRECT_GUESSES), the game loop will continue to run, allowing the player to keep guessing letters.
  while (num_incorrect_guesses < MAX_NUM_INCORRECT_GUESSES)
  {
    // show user number of incorrect guesses remaining
    draw_hangman(num_incorrect_guesses);
    // display word_progress array, showing underscores and correct guesses of the word to be guessed
    printf("Word: %s\n", word_progress);
    // Prompt user to guess a letter
    printf("Guess a letter: ");
    // Create buffer to hold input line
    char input[256];
    // Read a line of input, including spaces or multiple characters
    fgets(input, sizeof(input), stdin);
    // trim '\n' newline character from player entry
    input[strcspn(input, "\n")] = '\0';
    // create variable to hold player's guessed letter
    char guess = '\0';
    // variable to store number of characters in the player's guess. initialize at 0
    int char_count = 0;
    // loop through the player's input, check for an alphabetic character, assign it to the guess variable (provided it is still empty) in lowercase format. then increment char_count
    for (int i = 0; input[i] != '\0'; i++)
    {
      if (isalpha(input[i]))
      {
        if (guess == '\0')
        {
          guess = tolower(input[i]);
        }
        char_count++;
      }
      else
      {
        printf("letters only please. Try again\n");
        break;
      }
    }
    // if guess variable is empty at this point, a number was entered, and the player got the error message. reset game loop
    if (guess == '\0')
      continue;

    // check for multiple characters entered
    if (char_count > 1)
    {
      printf("Please enter only one letter. Try again.\n");
      continue;
    }
    // check for an empty guess. user just pressed enter
    if (!guess)
    {
      printf("Invalid input. Please enter a letter.\n");
      continue;
    }
    // check for already guessed letter
    if (strchr(guessed_letters, guess))
    {
      printf("Oops, already guessed that letter. Try a new letter\n");
      continue;
    }
    // add player's valid guess to the guessed_letters array at the position of used_count
    guessed_letters[num_guessed_letters] = guess;
    // increment the used_count variable to track where the next guess will be stored in the guessed_letters array
    num_guessed_letters++;

    // new for loop with success message included
    // variable to track if guessed letter is in the word. starts off as 0 which is means incorrect. 1 represents correct
    int guess_found = 0;
    // loop through randomly chosen word, comparing the guess to each position in the string. If a guess matches, add the guess to the word_progress array at that position (of the current loop iteration, i) and change the found variable to 1.
    int count = 0;
    for (int i = 0; i < word_len; i++)
    {
      if (word[i] == guess)
      {
        word_progress[i] = guess;
        count++;
      }
    }
    guess_found = (count > 0) ? 1 : 0;

    // After the loop, if correct:
    if (guess_found == 1)
    {
      printf("Yes, there %s %d %c%s\n", (count == 1) ? "is" : "are", count, guess, (count == 1) ? "." : "'s.");
    }

    // if the guess was incorrect and the found variable is still 0, increment the num_incorrect_guesses variable
    if (guess_found == 0)
    {
      printf("Sorry, no %c\n", guess);
      num_incorrect_guesses++;
    }

    // old for loop
    // for (int i = 0; i < word_len; i++)
    // {
    //   if (word[i] == guess)
    //   {
    //     word_progress[i] = guess;
    //     guess_found = 1;
    //   }
    // }

    // if the word_progress array and the word array are now identical, the player has guessed the word. That means all of the underscores in the word_progress array have been replaced with correct letters. Show winning message and display word. return 0 exits us out of the main() function, terminating the program
    if (strcmp(word_progress, word) == 0)
    {
      printf("You win! Word: %s\n\n", word);
      return 0;
    }
  } // exiting game loop since num_incorrect_guesses >= MAX_NUM_INCORRECT_GUESSES ...
  // display number of tries once more, show losing message, and display word. return 0 exits program
  draw_hangman(num_incorrect_guesses);
  printf("You lose! The word was: %s\n\n", word);
  return 0;
}