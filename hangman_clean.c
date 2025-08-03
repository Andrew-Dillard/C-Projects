#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_NUM_INCORRECT_GUESSES 6

const char *bible_names[] = {
    "adam", "eve", "noah", "abraham", "sarah", "isaac", "jacob", "joseph", "moses", "aaron", "david", "solomon", "elijah", "elisha", "ruth", "esther", "daniel", "jonah", "mary", "jesus"};

const char *animals[] = {
    "tiger", "elephant", "giraffe", "zebra", "lion", "bear", "wolf", "fox", "deer", "rhino",
    "hippo", "cheetah", "panther", "eagle", "hawk", "owl", "snake", "turtle", "crocodile", "lemur"};

const char *toys[] = {"doll", "truck", "puzzle", "ball", "kite", "train", "blocks", "robot", "teddy", "car", "boat", "plane", "marble", "lego", "frisbee", "scooter", "wagon", "rocket"};

const char *plants[] = {"tree", "flower", "grass", "bush", "cactus", "vine", "rose", "tulip", "daisy", "lily", "fern", "moss", "bamboo", "pine", "oak", "maple", "clover", "ivy", "sunflower"};

const char *megaman[] = {
    "megaman", "roll", "gutsman", "freezeman", "cutman", "shadowman", "elecman", "torchman",
    "protoman", "bass", "glide", "lan", "higsby", "yai", "dex", "mayl", "chaud",
    "wily", "chip", "netbattle"};

const char *star_wars[] = {
    "luke", "leia", "han", "vader", "yoda", "obiwan", "chewbacca", "kyber", "force", "palpatine", "anakin", "padme", "maul", "jango", "boba", "lando"};

const char **words = NULL;

void draw_hangman(int num_incorrect_guesses)
{
  printf("\nWrong guesses remaining: %d\n", MAX_NUM_INCORRECT_GUESSES - num_incorrect_guesses);
}

int main()
{
  printf("\nWelcome to hangman! Can you guess the word?\n");
  printf("Please choose a category. Enter the number of your choice... \n");
  printf("1. Bible Names\n");
  printf("2. Animals\n");
  printf("3. Toys\n");
  printf("4. Plants\n");
  printf("5. Megaman\n");
  printf("6. Star Wars\n\n");

  char category_input[256];
  fgets(category_input, sizeof(category_input), stdin);
  category_input[strcspn(category_input, "\n")] = '\0';

  int category_choice = atoi(category_input);

  char *category_choice_str[] = {"/0"};

  int num_words = 0;

  switch (category_choice)
  {
  case 1:
    words = bible_names;
    num_words = sizeof(bible_names) / sizeof(bible_names[0]);
    *category_choice_str = "Bible Names";
    break;
  case 2:
    words = animals;
    num_words = sizeof(animals) / sizeof(animals[0]);
    *category_choice_str = "Animals";
    break;
  case 3:
    words = toys;
    num_words = sizeof(toys) / sizeof(toys[0]);
    *category_choice_str = "Toys";
    break;
  case 4:
    words = plants;
    num_words = sizeof(plants) / sizeof(plants[0]);
    *category_choice_str = "Plants";
    break;
  case 5:
    words = megaman;
    num_words = sizeof(megaman) / sizeof(megaman[0]);
    *category_choice_str = "Megaman";
    break;
  case 6:
    words = star_wars;
    num_words = sizeof(star_wars) / sizeof(star_wars[0]);
    *category_choice_str = "Star Wars";
    break;
  default:
    printf("\nInvalid category. Defaulting to Bible Names.\n");
    words = bible_names;
    num_words = sizeof(bible_names) / sizeof(bible_names[0]);
    *category_choice_str = "Bible Names";
    break;
  }

  printf("\nCategory choice: %s\n", *category_choice_str);

  srand(time(NULL));
  const char *word = words[rand() % num_words];
  int word_len = strlen(word);
  char word_progress[word_len + 1];
  memset(word_progress, '_', word_len);
  word_progress[word_len] = '\0';
  int num_incorrect_guesses = 0;
  char guessed_letters[26] = {0};
  int num_guessed_letters = 0;

  while (num_incorrect_guesses < MAX_NUM_INCORRECT_GUESSES)
  {
    draw_hangman(num_incorrect_guesses);
    printf("Word: %s\n", word_progress);
    printf("Guess a letter: ");
    char input[256];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    char guess = '\0';
    int char_count = 0;
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
    if (guess == '\0')
      continue;

    if (char_count > 1)
    {
      printf("Please enter only one letter. Try again.\n");
      continue;
    }
    if (!guess)
    {
      printf("Invalid input. Please enter a letter.\n");
      continue;
    }
    if (strchr(guessed_letters, guess))
    {
      printf("Oops, already guessed that letter. Try a new letter\n");
      continue;
    }
    guessed_letters[num_guessed_letters] = guess;
    num_guessed_letters++;

    int guess_found = 0;
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

    if (guess_found == 1)
    {
      printf("Yes, there %s %d %c%s\n", (count == 1) ? "is" : "are", count, guess, (count == 1) ? "." : "'s.");
    }

    if (guess_found == 0)
    {
      printf("Sorry, no %c\n", guess);
      num_incorrect_guesses++;
    }

    if (strcmp(word_progress, word) == 0)
    {
      printf("\nYou win! Word: %s\n\n", word);
      return 0;
    }
  }
  draw_hangman(num_incorrect_guesses);
  printf("\nYou lose! The word was: %s\n\n", word);
  return 0;
}