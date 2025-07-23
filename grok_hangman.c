#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORD_LENGTH 20
#define MAX_TRIES 6

const char *words[] = {
    "apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
int num_words = sizeof(words) / sizeof(words[0]);

void draw_hangman(int tries)
{
  printf("Tries left: %d\n", MAX_TRIES - tries);
  // Simple ASCII art for hangman stages can be added here
}

int main()
{
  srand(time(NULL));
  const char *word = words[rand() % num_words];
  int word_len = strlen(word);
  char guessed[word_len + 1];
  memset(guessed, '_', word_len);
  guessed[word_len] = '\0';

  int tries = 0;
  char used_letters[26] = {0};
  int used_count = 0;

  while (tries < MAX_TRIES)
  {
    draw_hangman(tries);
    printf("Word: %s\n", guessed);
    printf("Guess a letter: ");
    char guess;
    scanf(" %c", &guess);
    guess = tolower(guess);

    if (!isalpha(guess) || strchr(used_letters, guess))
    {
      printf("Invalid or already guessed.\n");
      continue;
    }
    used_letters[used_count++] = guess;

    int found = 0;
    for (int i = 0; i < word_len; i++)
    {
      if (word[i] == guess)
      {
        guessed[i] = guess;
        found = 1;
      }
    }

    if (!found)
      tries++;

    if (strcmp(guessed, word) == 0)
    {
      printf("You win! Word: %s\n", word);
      return 0;
    }
  }

  draw_hangman(tries);
  printf("You lose! Word: %s\n", word);
  return 0;
}