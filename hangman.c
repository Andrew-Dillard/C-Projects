// Include standard libraries for input/output, random numbers, string operations, character checks, and time
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Validate input: trim newline, check if it matches expected format
int validate_input(char *input, size_t size, int (*check)(int))
{
  input[strcspn(input, "\n")] = '\0';
  if (input[0] == '\0')
    return 0;
  for (int i = 0; input[i] != '\0'; i++)
    if (!check(input[i]))
      return 0;
  return 1;
}

// check operating system of user and define clear screen command
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// Define constant for maximum number of incorrect guesses allowed
#define MAX_NUM_INCORRECT_GUESSES 6
#define MAX_WORD_LENGTH 50

// Define different categories for the player to choose a word from
// These are arrays of pointers, where each pointer points to the first letter of a word
const char *bible_names[] = {
    "adam", "noah", "abraham", "sarah", "isaac", "jacob", "joseph", "moses", "aaron",
    "david", "solomon", "elijah", "elisha", "ruth", "esther", "daniel", "jonah", "mary", "jesus", "cain"};

const char *animals[] = {
    "tiger", "elephant", "giraffe", "zebra", "lion", "bear", "wolf", "deer", "rhino",
    "hippo", "cheetah", "panther", "eagle", "hawk", "snake", "turtle", "crocodile", "lemur", "monkey", "panda"};

const char *toys[] = {
    "doll", "truck", "puzzle", "ball", "kite", "train", "blocks", "robot", "teddy",
    "boat", "plane", "marble", "lego", "frisbee", "scooter", "wagon", "rocket", "yoyo"};

const char *plants[] = {
    "tree", "flower", "grass", "bush", "cactus", "vine", "rose", "tulip", "daisy", "lily",
    "fern", "moss", "bamboo", "pine", "maple", "clover", "sunflower", "willow", "orchid"};

const char *megaman[] = {
    "megaman", "roll", "gutsman", "freezeman", "cutman", "shadowman", "elecman", "torchman",
    "protoman", "bass", "glide", "higsby", "chaud",
    "wily", "chip", "netbattle", "rush", "mayl", "gateman"};

const char *star_wars[] = {
    "luke", "leia", "vader", "yoda", "obiwan", "chewbacca", "kyber", "force", "palpatine",
    "anakin", "padme", "maul", "jango", "boba", "lando", "solo"};

const char *lord_of_the_rings[] = {
    "frodo", "gandalf", "aragorn", "legolas", "gimli", "boromir", "samwise", "merry", "pippin",
    "bilbo", "sauron", "gollum", "saruman", "elrond", "galadriel", "theoden", "eowyn", "faramir", "denethor"};

const char *colors[] = {
    "blue", "green", "yellow", "purple", "orange", "black", "white", "brown", "silver", "gold",
    "indigo", "violet", "magenta", "cyan", "turquoise", "lavender", "maroon", "olive", "teal"};

const char *jobs[] = {
    "doctor", "teacher", "engineer", "lawyer", "chef", "pilot", "artist", "nurse", "farmer", "writer",
    "actor", "singer", "fireman", "plumber", "electrician", "mechanic", "scientist", "programmer", "architect"};

const char *superheroes[] = {
    "batman",
    "superman",
    "spiderman",
    "ironman",
    "thor",
    "hulk",
    "wonderwoman",
    "flash",
    "aquaman",
    "blackwidow",
    "hawkeye",
    "robin",
    "antman"};

// All categories for random word suggestions
const char **all_categories[] = {
    bible_names,
    animals,
    toys,
    plants,
    megaman,
    star_wars,
    lord_of_the_rings,
    colors,
    jobs,
    superheroes};

const int category_sizes[] = {
    sizeof(bible_names) / sizeof(bible_names[0]),
    sizeof(animals) / sizeof(animals[0]),
    sizeof(toys) / sizeof(toys[0]),
    sizeof(plants) / sizeof(plants[0]),
    sizeof(megaman) / sizeof(megaman[0]),
    sizeof(star_wars) / sizeof(star_wars[0]),
    sizeof(lord_of_the_rings) / sizeof(lord_of_the_rings[0]),
    sizeof(colors) / sizeof(colors[0]),
    sizeof(jobs) / sizeof(jobs[0]),
    sizeof(superheroes) / sizeof(superheroes[0])};

const char *category_names[] = {
    "Bible Names", "Animals", "Toys", "Plants", "Megaman",
    "Star Wars", "Lord of the Rings", "Colors", "Jobs", "Superheroes"};

#define TOTAL_CATEGORIES (sizeof(all_categories) / sizeof(all_categories[0]))
#define TOTAL_WORDS 182 // Precalculated total words across all categories

// Global pointer to the chosen category's word list
const char **words = NULL;

// Function to display the hangman state based on incorrect guesses
void draw_hangman(int num_incorrect_guesses)
{
  // Print the number of wrong guesses remaining
  printf("Wrong guesses remaining: %d\n", MAX_NUM_INCORRECT_GUESSES - num_incorrect_guesses);

  // Display ASCII art based on the number of incorrect guesses
  switch (num_incorrect_guesses)
  {
  case 0:
    printf("  _____\n");
    printf("  |   |\n");
    printf("      |\n");
    printf("      |\n");
    printf("      |\n");
    printf("      |\n");
    printf("========\n");
    break;
  case 1:
    printf("  _____\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf("      |\n");
    printf("      |\n");
    printf("      |\n");
    printf("========\n");
    break;
  case 2:
    printf("  _____\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf("  |   |\n");
    printf("      |\n");
    printf("      |\n");
    printf("========\n");
    break;
  case 3:
    printf("  _____\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|   |\n");
    printf("      |\n");
    printf("      |\n");
    printf("========\n");
    break;
  case 4:
    printf("  _____\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    printf("      |\n");
    printf("      |\n");
    printf("========\n");
    break;
  case 5:
    printf("  _____\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    printf(" /    |\n");
    printf("      |\n");
    printf("========\n");
    break;
  case 6:
    printf("  _____\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    printf(" / \\  |\n");
    printf("      |\n");
    printf("========\n");
    break;
  }
}

// Function to display word progress with spaces between letters
void display_word_progress(const char *word_progress, int word_len)
{
  printf("\nWord: ");
  for (int i = 0; i < word_len; i++)
  {
    printf("%c ", word_progress[i]);
  }
  printf("\n");
}

// Function to display incorrect letters
void display_incorrect_letters(const char *guessed_letters, int num_guessed_letters, const char *word, int word_len)
{
  printf("Incorrect guesses: ");
  int found = 0;
  for (int i = 0; i < num_guessed_letters; i++)
  {
    int in_word = 0;
    for (int j = 0; j < word_len; j++)
    {
      if (guessed_letters[i] == word[j])
      {
        in_word = 1;
        break;
      }
    }
    if (!in_word)
    {
      printf("%c ", guessed_letters[i]);
      found = 1;
    }
  }
  if (!found)
    printf("None");
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
  printf("6. Star Wars\n");
  printf("7. Lord of the Rings\n");
  printf("8. Colors\n");
  printf("9. Jobs\n");
  printf("10. Superheroes\n\n");

  // Buffer to store user input for category choice
  char category_input[256];
  fgets(category_input, sizeof(category_input), stdin);
  if (!validate_input(category_input, sizeof(category_input), isdigit))
  {
    printf("\nInvalid category. Defaulting to Bible Names.\n");
    words = bible_names;
    *num_words = sizeof(bible_names) / sizeof(bible_names[0]);
    strcpy(category_choice_str, category_names[0]);
    *category_choice = 1;
    return;
  }
  *category_choice = atoi(category_input);

  // Assign the appropriate word list and category details based on user choice
  switch (*category_choice)
  {
  case 1:
    words = bible_names;
    *num_words = sizeof(bible_names) / sizeof(bible_names[0]);
    strcpy(category_choice_str, category_names[0]);
    break;
  case 2:
    words = animals;
    *num_words = sizeof(animals) / sizeof(animals[0]);
    strcpy(category_choice_str, category_names[1]);
    break;
  case 3:
    words = toys;
    *num_words = sizeof(toys) / sizeof(toys[0]);
    strcpy(category_choice_str, category_names[2]);
    break;
  case 4:
    words = plants;
    *num_words = sizeof(plants) / sizeof(plants[0]);
    strcpy(category_choice_str, category_names[3]);
    break;
  case 5:
    words = megaman;
    *num_words = sizeof(megaman) / sizeof(megaman[0]);
    strcpy(category_choice_str, category_names[4]);
    break;
  case 6:
    words = star_wars;
    *num_words = sizeof(star_wars) / sizeof(star_wars[0]);
    strcpy(category_choice_str, category_names[5]);
    break;
  case 7:
    words = lord_of_the_rings;
    *num_words = sizeof(lord_of_the_rings) / sizeof(lord_of_the_rings[0]);
    strcpy(category_choice_str, category_names[6]);
    break;
  case 8:
    words = colors;
    *num_words = sizeof(colors) / sizeof(colors[0]);
    strcpy(category_choice_str, category_names[7]);
    break;
  case 9:
    words = jobs;
    *num_words = sizeof(jobs) / sizeof(jobs[0]);
    strcpy(category_choice_str, category_names[8]);
    break;
  case 10:
    words = superheroes;
    *num_words = sizeof(superheroes) / sizeof(superheroes[0]);
    strcpy(category_choice_str, category_names[9]);
    break;
  default:
    // Default to Bible Names for invalid input
    printf("\nInvalid category. Defaulting to Bible Names.\n");
    words = bible_names;
    *num_words = sizeof(bible_names) / sizeof(bible_names[0]);
    strcpy(category_choice_str, category_names[0]);
    *category_choice = 1;
    break;
  }
}

// Function to get custom word from Player 1 in two-player mode and return category name
void get_custom_word(char *custom_word, char *category_choice_str)
{
  char input[MAX_WORD_LENGTH];
  int valid = 0;

  while (!valid)
  {
    printf("\nPlayer 2, please look away while Player 1 selects the word.\n");

    printf("Player 1, do you want to enter a custom word (1) or choose from 10 random suggestions (2)? ");
    char mode_choice_input[256];
    fgets(mode_choice_input, sizeof(mode_choice_input), stdin);
    if (!validate_input(mode_choice_input, sizeof(mode_choice_input), isdigit))
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
      // Custom word input
      printf("Enter a custom word (letters only, max %d characters): ", MAX_WORD_LENGTH - 1);
      fgets(input, sizeof(input), stdin);
      if (!validate_input(input, sizeof(input), isalpha) || strlen(input) >= MAX_WORD_LENGTH)
      {
        printf("\nInvalid word. Use letters only, max %d characters.\n", MAX_WORD_LENGTH - 1);
        continue;
      }
      // Convert to lowercase
      for (int i = 0; input[i] != '\0'; i++)
      {
        input[i] = tolower(input[i]);
      }
      strcpy(category_choice_str, "Custom Word");
    }
    else
    {
      // Suggestions
      printf("Here are 10 random word suggestions:\n");

      char suggested_words[10][MAX_WORD_LENGTH];
      int category_indices[10];

      for (int c = 0; c < TOTAL_CATEGORIES; c++)
      {
        int idx = rand() % category_sizes[c];
        strcpy(suggested_words[c], all_categories[c][idx]);
        category_indices[c] = c;
        printf("%d. %s\n", c + 1, suggested_words[c]);
      }

      printf("Choose a word by entering its number (1-10): ");
      char choice_input[256];
      fgets(choice_input, sizeof(choice_input), stdin);
      if (!validate_input(choice_input, sizeof(choice_input), isdigit))
      {
        printf("\nInvalid choice. Please try again.\n");
        continue;
      }
      int choice = atoi(choice_input) - 1;
      if (choice < 0 || choice >= 10)
      {
        printf("\nInvalid choice. Please try again.\n");
        continue;
      }

      strcpy(input, suggested_words[choice]);
      strcpy(category_choice_str, category_names[category_indices[choice]]);
    }

    // Confirm the word with Player 1
    printf("\nYour word: %s\nIs this correct? (y/n): ", input);
    char confirm[256];
    fgets(confirm, sizeof(confirm), stdin);
    if (!validate_input(confirm, sizeof(confirm), isalpha))
    {
      printf("\nPlease select again.\n");
      continue;
    }
    if (tolower(confirm[0]) == 'y')
    {
      valid = 1;
      system(CLEAR_SCREEN); // Clear the screen after confirmation
      printf("\nPlayer 2, you can look back now.\n");
    }
    else
    {
      printf("\nPlease select again.\n");
    }
  }

  // Copy to custom_word
  strcpy(custom_word, input);
}

int main()
{
  // Display welcome message
  printf("\nWelcome to Hangman!\n");

  // Seed random number generator with current time for varied word selection
  srand(time(NULL));

  // Variable to control replay loop
  char play_again = 'y';
  // Continue playing as long as the user enters 'y' or 'Y'
  while (tolower(play_again) == 'y')
  {
    // Prompt for game mode
    printf("\nChoose game mode:\n1. Single Player\n2. Two Player\nEnter 1 or 2: ");
    char mode_input[256];
    fgets(mode_input, sizeof(mode_input), stdin);
    if (!validate_input(mode_input, sizeof(mode_input), isdigit) || (mode_input[0] != '1' && mode_input[0] != '2'))
    {
      printf("\nInvalid mode. Defaulting to Single Player.\n");
      mode_input[0] = '1';
    }
    int game_mode = atoi(mode_input);

    // Variables for category selection and game setup
    int category_choice = 0;
    char category_choice_str[256] = "";
    int num_words = 0;
    char word[MAX_WORD_LENGTH];
    int word_len;

    if (game_mode == 1)
    {
      // Single-player mode: select category and random word
      select_category(&category_choice, category_choice_str, &num_words);
      strcpy(word, words[rand() % num_words]);
      word_len = strlen(word);
    }
    else
    {
      // Two-player mode: Player 1 inputs a custom word or selects from suggestions
      get_custom_word(word, category_choice_str);
      word_len = strlen(word);
    }

    // Create array to track word progress with underscores
    char word_progress[MAX_WORD_LENGTH];
    memset(word_progress, '_', word_len);
    word_progress[word_len] = '\0';
    // Track number of incorrect guesses
    int num_incorrect_guesses = 0;
    // Array to store guessed letters, initialized to null
    char guessed_letters[26] = {0};
    // Track number of unique guessed letters
    int num_guessed_letters = 0;

    // Main game loop: continues until max incorrect guesses reached
    while (num_incorrect_guesses < MAX_NUM_INCORRECT_GUESSES)
    {
      // Display game state
      printf("\nCategory: %s\n", category_choice_str);
      printf("%d letter word\n", word_len);
      display_incorrect_letters(guessed_letters, num_guessed_letters, word, word_len);
      draw_hangman(num_incorrect_guesses);
      display_word_progress(word_progress, word_len);
      // Prompt for letter guess
      printf("\n%sGuess a letter: ", game_mode == 2 ? "Player 2, " : "");
      // Buffer for user input
      char input[256];
      fgets(input, sizeof(input), stdin);
      if (!validate_input(input, sizeof(input), isalpha))
      {
        printf("\nInvalid input. Please enter a letter.\n");
        continue;
      }
      // Variable to store the guessed letter
      char guess = '\0';
      int char_count = 0;
      for (int i = 0; input[i] != '\0'; i++)
      {
        if (guess == '\0')
        {
          // Convert guess to lowercase
          guess = tolower(input[i]);
        }
        char_count++;
      }
      // Check for multiple letters
      if (char_count > 1)
      {
        printf("\nPlease enter only one letter. Try again.\n");
        continue;
      }
      // Check if letter was already guessed
      if (strchr(guessed_letters, guess))
      {
        printf("\nOops, already guessed that letter. Try a new letter.\n");
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
        printf("\nYes, there %s %d %c%s\n", (count == 1) ? "is" : "are", count, guess, (count == 1) ? "." : "'s.");
      }
      if (guess_found == 0)
      {
        printf("\nSorry, no %c\n", guess);
        // Increment incorrect guess count
        num_incorrect_guesses++;
      }
      // Check if the word has been fully guessed
      if (strcmp(word_progress, word) == 0)
      {
        // Display win message and exit game loop
        printf("\n%sYou win! Word: %s\n\n", game_mode == 2 ? "Player 2, " : "", word);
        break;
      }
    }
    // If max incorrect guesses reached, display lose message
    if (num_incorrect_guesses >= MAX_NUM_INCORRECT_GUESSES)
    {
      printf("\nCategory: %s\n", category_choice_str);
      printf("%d letter word\n", word_len);
      draw_hangman(num_incorrect_guesses);
      display_word_progress(word_progress, word_len);
      printf("\n%sYou lose! The word was: %s\n\n", game_mode == 2 ? "Player 2, " : "", word);
    }

    // Prompt to play again
    printf("Would you like to play again? (y/n): ");
    char input[256];
    fgets(input, sizeof(input), stdin);
    if (!validate_input(input, sizeof(input), isalpha))
    {
      printf("\nInvalid input. Defaulting to no.\n");
      play_again = 'n';
    }
    else
    {
      // Store first character of input as play_again choice
      play_again = tolower(input[0]);
    }
  }

  // Display exit message when player chooses not to replay
  printf("\nThanks for playing!\n");
  return 0;
}