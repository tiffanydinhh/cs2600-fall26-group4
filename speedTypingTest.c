// CS 26000 Systems Programming
// Tyler Carrasco, Tiffany Dinh, Brandon Doan, Kendan Phan, Angela Salcido
// Final Project in C
// C program that replicates a speed typing test

#include <stdio.h>
#include <string.h>
#include <stddef.h> //For size_t
#include <time.h>
#include "start_timer.h"

int paragraphInput(const char paragraph[], char userInput[], size_t inputSize, double *elapsedTime);
int isEmpty(const char input[]);

int main() {

  int menuInput; // ints 1 or 2 will be stored in menuInput
  const char progStr[] = "Half the world was pulling on his colors, as nights turned into days top the hours. A glow was coming down, coming down. I don't know why, but it felt like a tiger striped sky.";

  char userStr[500]; // store user string input

  int correctNumChar = 0;
  double wpm = 0;
  double accuracy = 0;
  int extraNumChar = 0;

  // variables for while loop
  int i = 0; // i keeps track of programStr char position
  int j = 0; // j keeps track of userStr char position

  double elapsedTime = 0;


  printf("* * * WELCOME TO OUR SPEED TYPING TEST! * * *\n\n");
  printf("~~~~~~MAIN MENU~~~~~~\n");
  printf("You will be given a paragraph to copy, and your speed and accuracy will be measured.\n");
  printf("Do your best!\n\n");
  printf("1) Start\n");
  printf("2) Exit\n");
  printf("Please enter a number from 1 to 2: ");

  scanf("%d", &menuInput); // user's menu input will be stored in menuInput
  getchar(); // clear left over return key from user menu input



  if (menuInput == 1) {

    // if paragraphInput successfully took in user input
    if (paragraphInput(progStr, userStr, sizeof(userStr), &elapsedTime) == 0) {
      printf("Could not get user input");
      return 1;
    }

    // if user enters an empty input
    if (isEmpty(userStr) == 1) {
      printf("input is empty\n");
      return 0;
    }

    // this code below will be considered inside the 'if menuInput == 1'

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
    printf("accuracy: %f%%\n", accuracy);

  }

  // if user chooses to exit program
  else if (menuInput == 2) {
    printf("Exiting program... Goodbye!\n");

  }

  return 0;
}

double getTime(void) {
  struct timespec ts;

  clock_gettime(CLOCK_MONOTONIC, &ts);

  return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

int paragraphInput(const char paragraph[], char userInput[], size_t inputSize, double *elapsedTime) {
  printf("Type the following text: \n\n%s\n\n", paragraph);
  printf("Typing: ");
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
  printf("\nYou typed:\n%s\n", userInput);
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
