// Include standard libraries for I/O, random numbers, string operations, character checks, and time.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// define constant for number of incorrect guesses allowed
#define MAX_TRIES 6

// the word list for the game, define array whose elements are pointers, containing the memory address of the the first character in each string
const char *words[] = {
    "apple", "banana", "cherry", "date", "peach", "fig", "grape", "lemon", "lime", "plum", "pear", "orange", "kiwi", "mango"};

// stores number of elements in the words[] array
int num_words = sizeof(words) / sizeof(words[0]);

// function to show how many tries are remaining
void draw_hangman(int tries)
{
  printf("Tries left: %d\n", MAX_TRIES - tries);
  // Simple ASCII art for hangman stages can be added here
}

int main()
{
  // Seed rand() with the current time for varied random numbers
  srand(time(NULL));
  // use rand() function to pick a random word from the words array and store the reference to its location in memory (pointer) in the *word variable.
  const char *word = words[rand() % num_words];
  // store length of random word selected
  int word_len = strlen(word);
  // create character array called guessed that is long enough to hold the length of the random word, plus one space for the null terminator, '\0'
  char guessed[word_len + 1];
  // load the guessed array with placeholders that are underscores _ the length of the random word
  memset(guessed, '_', word_len);
  // load the final element in the guess array with the null terminator, '\0' NOTE: guess[word_length] will always grab the last element in the guess array since the first item is item 0
  guessed[word_len] = '\0';
  // variable to store the number of tries used so far
  int tries = 0;
  // character array to store guessed letters. Initialize with {0} which sets the value of all 26 elements to the null terminator character, '\0'
  char used_letters[26] = {0};
  // store number of unique guessed letters
  int used_count = 0;

  // game loop
  // as long as the number of incorrect guesses, (tries) is less than the number of allowed incorrect guesses, (MAX_TRIES), the game loop will continue to run, allowing the player to keep guessing letters.
  while (tries < MAX_TRIES)
  {
    // show user number of incorrect guesses remaining
    draw_hangman(tries);
    // display guessed array, showing underscores and correct guesses of the word to be guessed
    printf("Word: %s\n", guessed);
    // prompt user to guess a letter
    printf("Guess a letter: ");
    // create variable to hold player's guessed letter
    char guess;
    // Read user's guessed letter, skipping whitespace, and store in guess
    scanf(" %c", &guess);
    // convert any uppercase letters entered by the user into lowercase
    guess = tolower(guess);

    // if the guessed letter is not an alphabetic character or if the letter has already been guessed, inform the player, and restart the game loop with continue, prompting a new guess
    if (!isalpha(guess) || strchr(used_letters, guess))
    {
      printf("Invalid or already guessed.\n");
      continue;
    }
    // add player's valid guess to the used_letters array at the position of used_count
    used_letters[used_count] = guess;
    // increment the used_count variable to track where the next guess will be stored in the used_letters array
    used_count++;

    // variable to track if guessed letter is in the word. starts off as 0 which is means incorrect. 1 represents correct
    int found = 0;
    // loop through randomly chosen word, comparing the guess to each position in the string. If a guess matches, add the guess to the guessed array at that position (of the currect loop iteration, i) and change the found variable to 1.
    for (int i = 0; i < word_len; i++)
    {
      if (word[i] == guess)
      {
        guessed[i] = guess;
        found = 1;
      }
    }
    // if the guess was incorrect and the found variable is still 0, increment the tries variable
    if (found == 0)
      tries++;
    // if the guessed array and the word array are now identical, the player has guessed the word. That means all of the underscores in the guessed array have been replaced with correct letters. Show winning message and display word. return 0 exits us out of the main() function, terminating the program
    if (strcmp(guessed, word) == 0)
    {
      printf("You win! Word: %s\n", word);
      return 0;
    }
  } // exiting game loop since tries > MAX_TRIES ...
  // display number of tries once more, show losing message, and display word. return 0 exits program
  draw_hangman(tries);
  printf("You lose! The word was: %s\n", word);
  return 0;
}