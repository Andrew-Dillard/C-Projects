// Include standard libraries for input/output, random numbers, string operations, character checks, and time
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Define constant for maximum number of incorrect guesses allowed
#define MAX_NUM_INCORRECT_GUESSES 6

// Define different categories for the player to choose a word from
// These are arrays of pointers, where each pointer points to the first letter of a word
const char *bible_names[] = {
    "adam", "eve", "noah", "abraham", "sarah", "isaac", "jacob", "joseph", "moses", "aaron",
    "david", "solomon", "elijah", "elisha", "ruth", "esther", "daniel", "jonah", "mary", "jesus"};

const char *animals[] = {
    "tiger", "elephant", "giraffe", "zebra", "lion", "bear", "wolf", "fox", "deer", "rhino",
    "hippo", "cheetah", "panther", "eagle", "hawk", "owl", "snake", "turtle", "crocodile", "lemur"};

const char *toys[] = {
    "doll", "truck", "puzzle", "ball", "kite", "train", "blocks", "robot", "teddy", "car",
    "boat", "plane", "marble", "lego", "frisbee", "scooter", "wagon", "rocket"};

const char *plants[] = {
    "tree", "flower", "grass", "bush", "cactus", "vine", "rose", "tulip", "daisy", "lily",
    "fern", "moss", "bamboo", "pine", "oak", "maple", "clover", "ivy", "sunflower"};

const char *megaman[] = {
    "megaman", "roll", "gutsman", "freezeman", "cutman", "shadowman", "elecman", "torchman",
    "protoman", "bass", "glide", "lan", "higsby", "yai", "dex", "mayl", "chaud",
    "wily", "chip", "netbattle"};

const char *star_wars[] = {
    "luke", "leia", "han", "vader", "yoda", "obiwan", "chewbacca", "kyber", "force", "palpatine",
    "anakin", "padme", "maul", "jango", "boba", "lando"};

// Global pointer to the chosen category's word list
const char **words = NULL;

// Function to display the hangman state based on incorrect guesses
void draw_hangman(int num_incorrect_guesses)
{
  // Print the number of wrong guesses remaining
  printf("\nWrong guesses remaining: %d\n", MAX_NUM_INCORRECT_GUESSES - num_incorrect_guesses);
  // Simple ASCII art for hangman stages can be added here
}

// Function to display word progress with spaces between letters
void display_word_progress(const char *word_progress, int word_len)
{
  printf("Word: ");
  for (int i = 0; i < word_len; i++)
  {
    printf("%c ", word_progress[i]);
  }
  printf("\n");
}

// Function to handle category selection and setup
void select_category(int *category_choice, char *category_choice_str, int *num_words)
{
  // Prompt user to choose a category by entering a number
  printf("\nPlease choose a category. Enter the number of your choice...\n");
  printf("\n1. Bible Names\n");
  printf("2. Animals\n");
  printf("3. Toys\n");
  printf("4. Plants\n");
  printf("5. Megaman\n");
  printf("6. Star Wars\n\n");

  // Array of category names for display and assignment
  const char *categories[] = {"Bible Names", "Animals", "Toys", "Plants", "Megaman", "Star Wars"};

  // Buffer to store user input for category choice
  char category_input[256];
  // Read user input
  fgets(category_input, sizeof(category_input), stdin);
  // Remove trailing newline from input
  category_input[strcspn(category_input, "\n")] = '\0';
  // Convert input string to integer
  *category_choice = atoi(category_input);

  // Assign the appropriate word list and category details based on user choice
  switch (*category_choice)
  {
  case 1:
    words = bible_names;
    *num_words = sizeof(bible_names) / sizeof(bible_names[0]);
    strcpy(category_choice_str, categories[0]);
    break;
  case 2:
    words = animals;
    *num_words = sizeof(animals) / sizeof(animals[0]);
    strcpy(category_choice_str, categories[1]);
    break;
  case 3:
    words = toys;
    *num_words = sizeof(toys) / sizeof(toys[0]);
    strcpy(category_choice_str, categories[2]);
    break;
  case 4:
    words = plants;
    *num_words = sizeof(plants) / sizeof(plants[0]);
    strcpy(category_choice_str, categories[3]);
    break;
  case 5:
    words = megaman;
    *num_words = sizeof(megaman) / sizeof(megaman[0]);
    strcpy(category_choice_str, categories[4]);
    break;
  case 6:
    words = star_wars;
    *num_words = sizeof(star_wars) / sizeof(star_wars[0]);
    strcpy(category_choice_str, categories[5]);
    break;
  default:
    // Default to Bible Names for invalid input
    printf("\nInvalid category. Defaulting to Bible Names.\n");
    words = bible_names;
    *num_words = sizeof(bible_names) / sizeof(bible_names[0]);
    strcpy(category_choice_str, categories[0]);
    *category_choice = 1;
    break;
  }
  // Display the chosen category
  printf("\nCategory choice: %s\n", category_choice_str);
}

int main()
{
  // Display welcome message
  printf("\nWelcome to hangman! Can you guess the word?\n");

  // Seed random number generator with current time for varied word selection
  srand(time(NULL));

  // Variable to control replay loop
  char play_again = 'y';
  // Continue playing as long as the user enters 'y' or 'Y'
  while (tolower(play_again) == 'y')
  {
    // Variables for category selection and game setup
    int category_choice;
    char category_choice_str[256] = "";
    int num_words = 0;

    // Select a category and set up words
    select_category(&category_choice, category_choice_str, &num_words);

    // Select a random word from the chosen category
    const char *word = words[rand() % num_words];
    // Get the length of the selected word
    int word_len = strlen(word);
    // Create array to track word progress with underscores
    char word_progress[word_len + 1];
    // Initialize word progress with underscores
    memset(word_progress, '_', word_len);
    // Add null terminator to word progress
    word_progress[word_len] = '\0';
    // Track number of incorrect guesses
    int num_incorrect_guesses = 0;
    // Array to store guessed letters, initialized to null
    char guessed_letters[26] = {0};
    // Track number of unique guessed letters
    int num_guessed_letters = 0;

    // Display the number of letters in the word
    printf("\n%d letter word\n", word_len);

    // Main game loop: continues until max incorrect guesses reached
    while (num_incorrect_guesses < MAX_NUM_INCORRECT_GUESSES)
    {
      // Display current hangman state
      draw_hangman(num_incorrect_guesses);
      // Show current word progress with spaces
      display_word_progress(word_progress, word_len);
      // Prompt for letter guess
      printf("\nGuess a letter: ");
      // Buffer for user input
      char input[256];
      // Read user input
      fgets(input, sizeof(input), stdin);
      // Remove trailing newline
      input[strcspn(input, "\n")] = '\0';
      // Variable to store the guessed letter
      char guess = '\0';
      // Count alphabetic characters in input
      int char_count = 0;
      // Process input to extract a single letter
      for (int i = 0; input[i] != '\0'; i++)
      {
        if (isalpha(input[i]))
        {
          if (guess == '\0')
          {
            // Convert guess to lowercase
            guess = tolower(input[i]);
          }
          char_count++;
        }
        else
        {
          // Handle non-alphabetic input
          printf("letters only please. Try again\n");
          break;
        }
      }
      // Skip if no valid letter was entered
      if (guess == '\0')
        continue;
      // Check for multiple letters
      if (char_count > 1)
      {
        printf("Please enter only one letter. Try again.\n");
        continue;
      }
      // Check for empty input
      if (!guess)
      {
        printf("Invalid input. Please enter a letter.\n");
        continue;
      }
      // Check if letter was already guessed
      if (strchr(guessed_letters, guess))
      {
        printf("Oops, already guessed that letter. Try a new letter\n");
        continue;
      }
      // Add valid guess to guessed letters
      guessed_letters[num_guessed_letters] = guess;
      num_guessed_letters++;

      // Check if guess is in the word
      int guess_found = 0;
      int count = 0;
      for (int i = 0; i < word_len; i++)
      {
        if (word[i] == guess)
        {
          // Update word progress with correct guess
          word_progress[i] = guess;
          count++;
        }
      }
      guess_found = (count > 0) ? 1 : 0;

      // Display result of guess
      if (guess_found == 1)
      {
        printf("Yes, there %s %d %c%s\n", (count == 1) ? "is" : "are", count, guess, (count == 1) ? "." : "'s.");
      }
      if (guess_found == 0)
      {
        printf("Sorry, no %c\n", guess);
        // Increment incorrect guess count
        num_incorrect_guesses++;
      }
      // Check if the word has been fully guessed
      if (strcmp(word_progress, word) == 0)
      {
        // Display win message and exit game loop
        printf("\nYou win! Word: %s\n\n", word);
        break;
      }
    }
    // If max incorrect guesses reached, display lose message
    if (num_incorrect_guesses >= MAX_NUM_INCORRECT_GUESSES)
    {
      draw_hangman(num_incorrect_guesses);
      printf("\nYou lose! The word was: %s\n\n", word);
    }

    // Prompt to play again
    printf("Would you like to play again? (y/n): ");
    char input[256];
    fgets(input, sizeof(input), stdin);
    // Store first character of input as play_again choice
    play_again = tolower(input[0]);
  }

  // Display exit message when player chooses not to replay
  printf("\nThanks for playing!\n");
  return 0;
}