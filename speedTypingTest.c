// CS 2600 Systems Programming
// Tyler Carrasco, Tiffany Dinh, Brandon Doan, Kendan Phan, Angela Salcido
// Final Project in C
// C program that replicates a speed typing test

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h> //For size_t
#include <time.h>
#include "start_timer.h"

int paragraphInput(const char paragraph[], char userInput[], size_t inputSize, double *elapsedTime);
int isEmpty(const char input[]);
void generateParagraph(char paragraph[], int numWords);

int main() {

  srand(time(NULL)); // Seed the random number generator
  int menuInput = 0; // ints 1 or 2 will be stored in menuInput
  char replayInput; // store user input for replay menu
  
  char progStr[1500];

  char userStr[1000]; // store user string input that can store up to 1000 characters char userStr[500];

  int correctNumChar = 0;
  double wpm = 0;
  double accuracy = 0;
  int extraNumChar = 0;

  // variables for while loop
  int i = 0; // i keeps track of programStr char position
  int j = 0; // j keeps track of userStr char position

  double elapsedTime = 0;

  int ch; // ch stores next character from user input

  // do while loop for main menu
  do {

    printf("* * * WELCOME TO OUR SPEED TYPING TEST! * * *\n\n");
    printf("~~~~~~MAIN MENU~~~~~~\n");
    printf("You will be given a paragraph to copy, and your speed and accuracy will be measured.\n");
    printf("Do your best!\n\n");
    printf("1) Start\n");
    printf("2) Exit\n");
    printf("Please enter a number from 1 to 2: ");

    scanf("%d", &menuInput); // user's menu input will be stored in menuInput

    ch = getchar(); // get next character from user input after scanf()

    // if the next character is not a new line, then set the menuInput equal to 0 and clear input buffer
    if (ch != '\n') {
      menuInput = 0;
      while ((ch = getchar()) != '\n');
    }

    // if menuInput is not 1 or 2, then it is an invalid input
    if (menuInput != 1 && menuInput != 2) {
      printf("\nInvalid input, please try again.\n");
    }

  } while (menuInput != 1 && menuInput != 2);

  if (menuInput == 1) {

    do {

      // reset variables for if user plays again
      int correctNumChar = 0;
      double wpm = 0;
      double accuracy = 0;
      int extraNumChar = 0;
      int i = 0;
      int j = 0;
      double elapsedTime = 0;

      generateParagraph(progStr, 25); // generating a paragraph with 25 words

      // if paragraphInput successfully took in user input
      if (paragraphInput(progStr, userStr, sizeof(userStr), &elapsedTime) == 0) {
	printf("Could not get user input");
	return 1;
      }

      // if user enters an empty input
      if (isEmpty(userStr) == 1) {
	printf("Input is empty. Please start the program again.\n");
	return 0;
      }

      // find length of string for progStr and userStr
      int progStrLength = strlen(progStr);
      int userStrLength = strlen(userStr);

      printf("Length of program string: %d\n", progStrLength);
      printf("Length of user string: %d\n", userStrLength);

      // while loop to traverse through each corresponding character and accounts for different situation

      // while progStrLength and userStrLength have not reached the end during traversal
      while (i < progStrLength && j < userStrLength) {

	// if character position in progStr and userStr are equal
	if (progStr[i] == userStr[j]) {
	  correctNumChar++; // increment correctNumChar
	  i++; // increment progStr position
	  j++; // // increment userStr position
	}

	// else if two characters are switched
	else if ((i + 1 < progStrLength && j + 1 < userStrLength) && (progStr[i] == userStr[j + 1]) && (progStr[i + 1] == userStr[j])) {
	  // increment both string positions by 2
	  i += 2;
	  j += 2;
	}

	// else if user forgot a character
	/*
	  ex) progStr: Hi my n|ame is Angela 
	  userStr: Hi my n|me is Angela
	  (anything before | has been compared)

	  this else if compares the next letter that's after | in the progStr (m) and if it's equal to the current letter userStr is at after the | then we know the user forgot a character, so we i++ to the next position to compare
	*/
	
	else if ((i + 1 < progStrLength) && (progStr[i + 1] == userStr[j])) {
	  i++; // increment progStr position
	}

	// else if user types extra character
	/*
	  progStr: Hi my n|ame is Angela 
	  userStr: Hi my n|a||ame is Angela
	*/

	else if ((j + 1 < userStrLength) && (userStr[j + 1] == progStr[i])) {
	  j++; // increment userStr position
	  extraNumChar++; // increment extraNumChar
	} 

	// else ordinary incorrect character
	/*
	  progStr: Hi my n|ame is Angela 
	  userStr: Hi my n|ime is Angela
	*/

	else {
	  i++; // increment progStr position
	  j++; // increment userStr position
	}
      }

      // code here to lower accuracy when user types extra characters/words

      // if programStr has been completely looked through, but userStr still has characters
      if (i == progStrLength && j < userStrLength) {
	while(j < userStrLength) {
	  j++; // increment userStr position
	  extraNumChar++; // increment number of extra chars
	}
      }

      printf("Extra Number of Characters: %d\n", extraNumChar);
      printf("Correct Number of Characters: %d\n", correctNumChar);

      printf("Elapsed time: %f\n", elapsedTime);

      // calculate WPM if elapsed time is greater than 0
	
      if (elapsedTime > 0) {
	wpm = ((double)correctNumChar/5)/(elapsedTime/60);
	printf("WPM: %f\n", wpm);
      }

      // calculate accuracy
      accuracy = ((double)correctNumChar/(progStrLength + extraNumChar))*100;
      printf("accuracy: %f%%\n\n", accuracy);

      // do while loop for replay menu to ask if user wants to play again
      do {
	printf("Would you like to try again? (Y/N): ");
	scanf(" %c", &replayInput);
        ch = getchar(); // get next character from user input after scanf()

    // if the next character is not a new line, then set the replayInput equal to 0 and clear input buffer
    if (ch != '\n') {
      replayInput = 0;
      while ((ch = getchar()) != '\n');
    }

      } while (replayInput != 'Y' && replayInput != 'y' && replayInput != 'N' && replayInput != 'n');

    } while (replayInput == 'Y' || replayInput == 'y');

    // if user chooses 'N' or 'n' during replay menu
    if (replayInput == 'N' || replayInput == 'n') {
      printf("\nThanks for playing! Goodbye.\n");
    }
    
  }

  // if user chooses to exit program
  else if (menuInput == 2) {
    printf("\nExiting program... Goodbye!\n");

  }

  return 0;
}

double getTime(void) {
  struct timespec ts;

  clock_gettime(CLOCK_MONOTONIC, &ts);

  return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

int paragraphInput(const char paragraph[], char userInput[], size_t inputSize, double *elapsedTime) {
  
  printf("\nType the following text: \n\n%s\n\n", paragraph);
  printf("Typing:\n");
  fflush(stdout);

  double start = getTime();

  //Reads user line, returns 0 if fails to read input
  if (fgets(userInput, inputSize, stdin) == NULL) {
    return 0;
  }

  double end = getTime();
  *elapsedTime = end - start;

  //Removes newline character from userInput
  userInput[strcspn(userInput, "\n")] = '\0';

  //Printing final user output
  printf("\nYou typed: %s\n", userInput);

  return 1;
}

int isEmpty(const char input[]) {

  // index counter
  int i = 0;

  while(input[i] != '\0'){
    // checking input for escape characters
    if(input[i] != ' ' && input[i] != '\n' && input[i] != '\t'){
      return 0;
    }
    i++;
  }

  // once the while loop terminates at the end of the char array
  return 1;

}

void generateParagraph(char paragraph[], int numWords) {

  FILE *file = fopen("words.txt", "r");

  char words[1500][50];
  int used[1500] = {0};
  int count = 0;

  paragraph[0] = '\0';

  if (file == NULL) {
    printf("Unable to open words.txt\n");
    return;
  }

  // Read words from the file
  while (count < 1500 && fscanf(file, "%49s", words[count]) == 1) {
    count++;
  }

  fclose(file);

  if (numWords > count) {
    numWords = count;
  }

  // Randomly select words
  for (int i = 0; i < numWords; i++) {

    int index = rand() % count;

    // Prevent duplicates
    while (used[index] == 1) {
      index = rand() % count;
    }

    used[index] = 1;

    // Add to paragraph[]
    strcat(paragraph, words[index]);

    // Space after each word except the last one
    if (i != numWords - 1) {
      strcat(paragraph, " ");
    }
  }
}
