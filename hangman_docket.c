// Hangman game implementation in C
// Supports single-player (random word from category) and two-player (custom word) modes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// --- Constants and Data ---

#define MAX_NUM_INCORRECT_GUESSES 6
#define MAX_WORD_LENGTH 20
#define TOTAL_CATEGORIES 10
#define MAX_CATEGORY_NAME 256

// Clear screen command based on operating system
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// Game state structure
typedef struct
{
  char word[MAX_WORD_LENGTH];                  // The target word to guess
  char word_progress[MAX_WORD_LENGTH];         // Current state of guessed letters
  char guessed_letters[26];                    // Letters guessed by the player
  int num_incorrect_guesses;                   // Number of incorrect guesses
  int num_guessed_letters;                     // Number of unique letters guessed
  int word_len;                                // Length of the target word
  int game_mode;                               // 1 for single-player, 2 for two-player
  char category_choice_str[MAX_CATEGORY_NAME]; // Name of the selected category
  int num_words;                               // Number of words in the selected category
} GameState;

// Word lists for each category
const char *bible_names[] = {"adam", "noah", "abraham", "sarah", "isaac", "jacob", "joseph", "moses", "aaron", "david", "solomon", "elijah", "elisha", "ruth", "esther", "daniel", "jonah", "mary", "jesus", "cain"};
const char *animals[] = {"tiger", "elephant", "giraffe", "zebra", "lion", "bear", "wolf", "deer", "rhino", "hippo", "cheetah", "panther", "eagle", "hawk", "snake", "turtle", "crocodile", "lemur", "monkey", "panda"};
const char *toys[] = {"doll", "truck", "puzzle", "ball", "kite", "train", "blocks", "robot", "teddy", "boat", "plane", "marble", "lego", "frisbee", "scooter", "wagon", "rocket", "yoyo"};
const char *plants[] = {"tree", "flower", "grass", "bush", "cactus", "vine", "rose", "tulip", "daisy", "lily", "fern", "moss", "bamboo", "pine", "maple", "clover", "sunflower", "willow", "orchid"};
const char *megaman[] = {"megaman", "roll", "gutsman", "freezeman", "cutman", "shadowman", "elecman", "torchman", "protoman", "bass", "glide", "higsby", "chaud", "wily", "chip", "netbattle", "rush", "mayl", "gateman"};
const char *star_wars[] = {"luke", "leia", "vader", "yoda", "obiwan", "chewbacca", "kyber", "force", "palpatine", "anakin", "padme", "maul", "jango", "boba", "lando", "solo"};
const char *lord_of_the_rings[] = {"frodo", "gandalf", "aragorn", "legolas", "gimli", "boromir", "samwise", "merry", "pippin", "bilbo", "sauron", "gollum", "saruman", "elrond", "galadriel", "theoden", "eowyn", "faramir", "denethor"};
const char *colors[] = {"blue", "green", "yellow", "purple", "orange", "black", "white", "brown", "silver", "gold", "indigo", "violet", "magenta", "cyan", "turquoise", "lavender", "maroon", "olive", "teal"};
const char *jobs[] = {"doctor", "teacher", "engineer", "lawyer", "chef", "pilot", "artist", "nurse", "farmer", "writer", "actor", "singer", "fireman", "plumber", "electrician", "mechanic", "scientist", "programmer", "architect"};
const char *superheroes[] = {"batman", "superman", "spiderman", "ironman", "thor", "hulk", "wonderwoman", "flash", "aquaman", "blackwidow", "hawkeye", "robin", "antman"};

// Array of all category word lists
const char **all_categories[] = {bible_names, animals, toys, plants, megaman, star_wars, lord_of_the_rings, colors, jobs, superheroes};

// Sizes of each category word list
const int category_sizes[] = {
    sizeof(bible_names) / sizeof(bible_names[0]), sizeof(animals) / sizeof(animals[0]),
    sizeof(toys) / sizeof(toys[0]), sizeof(plants) / sizeof(plants[0]),
    sizeof(megaman) / sizeof(megaman[0]), sizeof(star_wars) / sizeof(star_wars[0]),
    sizeof(lord_of_the_rings) / sizeof(lord_of_the_rings[0]), sizeof(colors) / sizeof(colors[0]),
    sizeof(jobs) / sizeof(jobs[0]), sizeof(superheroes) / sizeof(superheroes[0])};

// Category names for display
const char *category_names[] = {"Bible Names", "Animals", "Toys", "Plants", "Megaman", "Star Wars", "Lord of the Rings", "Colors", "Jobs", "Superheroes"};

// --- Utility Functions ---

// Validates input against a check function (e.g., isalpha, isdigit)
// single_char: 1 for single-character, 0 for multi-character
// Returns 1 if valid, 0 otherwise
int validate_input(char *input, size_t size, int (*check)(int), int single_char)
{
  input[strcspn(input, "\n")] = '\0';
  if (input[0] == '\0')
    return 0;
  if (single_char && strlen(input) != 1)
    return 0;
  for (int i = 0; input[i]; i++)
    if (!check(input[i]))
      return 0;
  return 1;
}

// Parameters: prompt (text to display), input/size (buffer for input), check (validation function), single_char (1 for single-character, 0 for multi-character)
// Returns 1 if input is valid, 0 otherwise
int get_validated_input(const char *prompt, char *input, size_t size, int (*check)(int), int single_char)
{
  printf("%s", prompt);
  fgets(input, size, stdin);
  return validate_input(input, size, check, single_char);
}

// --- Game Display Functions ---

// Displays the hangman ASCII art based on the number of incorrect guesses
void draw_hangman(int num_incorrect_guesses)
{
  static const char *hangman_stages[] = {
      "  _____\n  |   |\n      |\n      |\n      |\n      |\n========\n",
      "  _____\n  |   |\n  O   |\n      |\n      |\n      |\n========\n",
      "  _____\n  |   |\n  O   |\n  |   |\n      |\n      |\n========\n",
      "  _____\n  |   |\n  O   |\n /|   |\n      |\n      |\n========\n",
      "  _____\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n========\n",
      "  _____\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n========\n",
      "  _____\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========\n"};
  printf("Wrong guesses remaining: %d\n", MAX_NUM_INCORRECT_GUESSES - num_incorrect_guesses);
  printf("%s", hangman_stages[num_incorrect_guesses]);
}

// Displays the current state of the word with spaces between letters
void display_word_progress(const GameState *state)
{
  printf("\nWord: ");
  for (int i = 0; i < state->word_len; i++)
  {
    printf("%c ", state->word_progress[i]);
  }
  printf("\n");
}

// Displays letters guessed that are not in the word
void display_incorrect_letters(const GameState *state)
{
  printf("Incorrect guesses: ");
  int found = 0;
  for (int i = 0; i < state->num_guessed_letters; i++)
  {
    int in_word = 0;
    for (int j = 0; j < state->word_len; j++)
    {
      if (state->guessed_letters[i] == state->word[j])
      {
        in_word = 1;
        break;
      }
    }
    if (!in_word)
    {
      printf("%c ", state->guessed_letters[i]);
      found = 1;
    }
  }
  if (!found)
    printf("None");
  printf("\n");
}

// --- Game Logic Functions ---

// Prompts the user to select a category and returns the word list
// Sets category_choice and num_words, stores category name in state
const char **select_category(GameState *state)
{
  printf("\nPlease choose a category. Enter the number of your choice...\n");
  for (int i = 0; i < TOTAL_CATEGORIES; i++)
  {
    printf("%d. %s\n", i + 1, category_names[i]);
  }
  char input[256];
  int category_choice = 1; // Default to Bible Names
  if (!get_validated_input("Enter a number (1-10): ", input, sizeof(input), isdigit, 1))
  {
    printf("\nInvalid category. Defaulting to Bible Names.\n");
  }
  else
  {
    category_choice = atoi(input);
    if (category_choice < 1 || category_choice > TOTAL_CATEGORIES)
    {
      printf("\nInvalid category. Defaulting to Bible Names.\n");
      category_choice = 1;
    }
  }

  state->num_words = category_sizes[category_choice - 1];
  strcpy(state->category_choice_str, category_names[category_choice - 1]);
  return all_categories[category_choice - 1];
}

// Prompts Player 1 to input a custom word or select from random suggestions in two-player mode
// Stores the chosen word and category name in state
void get_custom_word(GameState *state)
{
  char input[MAX_WORD_LENGTH];
  int valid = 0;
  while (!valid)
  {
    printf("\nPlayer 2, please look away while Player 1 selects the word.\n");
    char mode_choice_input[256];
    if (!get_validated_input("\nChoose word selection method:\n1. Enter a custom word\n2. Choose from random suggestions\nEnter 1 or 2: ",
                             mode_choice_input, sizeof(mode_choice_input), isdigit, 1))
    {
      printf("\nInvalid choice. Please enter 1 or 2.\n");
      continue;
    }
    int mode_choice = atoi(mode_choice_input);
    if (mode_choice != 1 && mode_choice != 2)
    {
      printf("\nInvalid choice. Please enter 1 or 2.\n");
      continue;
    }
    if (mode_choice == 1)
    {
      char prompt[256];
      snprintf(prompt, sizeof(prompt), "Enter a custom word: ");
      if (!get_validated_input(prompt, input, sizeof(input), isalpha, 0) || strlen(input) >= MAX_WORD_LENGTH)
      {
        printf("\nInvalid word. Use letters only, max %d characters.\n", MAX_WORD_LENGTH - 1);
        continue;
      }
      for (int i = 0; input[i] != '\0'; i++)
      {
        input[i] = tolower(input[i]);
      }
      strcpy(state->category_choice_str, "Custom Word");
    }
    else
    {
      printf("\nChoose a word from the following suggestions:\n");
      char suggested_words[10][MAX_WORD_LENGTH];
      int category_indices[10];
      for (int c = 0; c < TOTAL_CATEGORIES; c++)
      {
        int idx = rand() % category_sizes[c];
        strcpy(suggested_words[c], all_categories[c][idx]);
        category_indices[c] = c;
        printf("%d. %s\n", c + 1, suggested_words[c]);
      }
      char choice_input[256];
      if (!get_validated_input("Enter a number (1-10): ", choice_input, sizeof(choice_input), isdigit, 0))
      {
        printf("\nInvalid choice. Please enter a number between 1 and 10.\n");
        continue;
      }
      int choice = atoi(choice_input) - 1;
      if (choice < 0 || choice >= 10)
      {
        printf("\nInvalid choice. Please enter a number between 1 and 10.\n");
        continue;
      }
      strcpy(input, suggested_words[choice]);
      strcpy(state->category_choice_str, category_names[category_indices[choice]]);
    }
    char prompt[256];
    snprintf(prompt, sizeof(prompt), "Is this the word you want? %s (y/n): ", input);
    char confirm[256];
    if (!get_validated_input(prompt, confirm, sizeof(confirm), isalpha, 1))
    {
      printf("\nPlease select again.\n");
      continue;
    }
    if (tolower(confirm[0]) == 'y')
    {
      valid = 1;
      system(CLEAR_SCREEN);
      printf("\nPlayer 2, you can look back now.\n");
    }
    else
    {
      printf("\nPlease select again.\n");
    }
  }
  strcpy(state->word, input);
  state->word_len = strlen(state->word);
}

// Runs the main game loop, handling guesses and updating game state
void play_game(GameState *state)
{
  memset(state->word_progress, '_', state->word_len);
  state->word_progress[state->word_len] = '\0';
  state->num_incorrect_guesses = 0;
  state->num_guessed_letters = 0;
  memset(state->guessed_letters, 0, 26);
  while (state->num_incorrect_guesses < MAX_NUM_INCORRECT_GUESSES)
  {
    printf("\nCategory: %s\n", state->category_choice_str);
    printf("%d letter word\n", state->word_len);
    display_incorrect_letters(state);
    draw_hangman(state->num_incorrect_guesses);
    display_word_progress(state);
    char input[256];
    char prompt[256];
    snprintf(prompt, sizeof(prompt), "\n%sGuess a letter: ", state->game_mode == 2 ? "Player 2, " : "");
    if (!get_validated_input(prompt, input, sizeof(input), isalpha, 1))
    {
      printf("\nInvalid input. Please enter a letter.\n");
      continue;
    }
    char guess = tolower(input[0]);
    if (strchr(state->guessed_letters, guess))
    {
      printf("\nOops, already guessed that letter. Try a new letter.\n");
      continue;
    }
    state->guessed_letters[state->num_guessed_letters++] = guess;
    int guess_found = 0, count = 0;
    for (int i = 0; i < state->word_len; i++)
    {
      if (state->word[i] == guess)
      {
        state->word_progress[i] = guess;
        count++;
      }
    }
    guess_found = count > 0;
    printf("\n%s %s %d %c%s\n", guess_found ? "Yes," : "Sorry,",
           count == 1 ? "there is" : "there are", count, guess, count == 1 ? "." : "'s.");
    if (!guess_found)
      state->num_incorrect_guesses++;
    if (strcmp(state->word_progress, state->word) == 0)
    {
      printf("\n%sYou win! Word: %s\n\n", state->game_mode == 2 ? "Player 2, " : "", state->word);
      return;
    }
  }
  printf("\nCategory: %s\n", state->category_choice_str);
  printf("%d letter word\n", state->word_len);
  display_incorrect_letters(state);
  draw_hangman(state->num_incorrect_guesses);
  display_word_progress(state);
  printf("\n%sYou lose! The word was: %s\n\n", state->game_mode == 2 ? "Player 2, " : "", state->word);
}

// --- Main Function ---

// Entry point for the Hangman game
// Manages game setup, mode selection, and replay loop
int main()
{
  printf("\nWelcome to Hangman!\n");
  srand(time(NULL));
  char play_again = 'y';
  while (tolower(play_again) == 'y')
  {
    GameState state = {0}; // Initialize all fields to zero
    char mode_input[256];
    if (!get_validated_input("\nChoose game mode:\n1. Single Player\n2. Two Player\nEnter 1 or 2: ",
                             mode_input, sizeof(mode_input), isdigit, 1) ||
        (mode_input[0] != '1' && mode_input[0] != '2'))
    {
      printf("\nInvalid mode. Defaulting to Single Player.\n");
      state.game_mode = 1;
    }
    else
    {
      state.game_mode = atoi(mode_input);
    }
    if (state.game_mode == 1)
    {
      const char **selected_words = select_category(&state);
      strcpy(state.word, selected_words[rand() % state.num_words]);
      state.word_len = strlen(state.word);
    }
    else
    {
      get_custom_word(&state);
    }
    play_game(&state);
    char input[256];
    if (!get_validated_input("Would you like to play again? (y/n): ", input, sizeof(input), isalpha, 1))
    {
      printf("\nInvalid input. Defaulting to no.\n");
      play_again = 'n';
    }
    else
    {
      play_again = tolower(input[0]);
    }
  }
  printf("\nThanks for playing!\n");
  return 0;
}