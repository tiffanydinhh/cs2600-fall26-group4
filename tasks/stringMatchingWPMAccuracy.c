// CS 26000 Systems Programming
// Tyler Carrasco, Tiffany Dinh, Brandon Doan, Kendan Phan, Angela Salcido
// Final Project in C
// C program that replicates a speed typing test

#include <stdio.h>
#include <string.h>

int main() {
  
  int menuInput; // ints 1 or 2 will be stored in menuInput
  char progStr[] = "I love Enhypen so much!";
  char userStr[] = "I love enhypen so mch! <3";

  int correctNumChar = 0;
  double wpm = 0;
  double accuracy = 0;
  int extraNumChar = 0;

  // initialize i and j for the while loop
  int i = 0;
  int j = 0;


  printf("* * * WELCOME TO OUR SPEED TYPING TEST! * * *\n\n");
  printf("~~~~~~MAIN MENU~~~~~~\n");
  printf("You will be given a paragraph to copy, and your speed and accuracy will be measured.\n");
  printf("Do your best!\n\n");
  printf("1) Start\n");
  printf("2) Exit\n");
  printf("Please enter a number from 1 to 2: ");

  scanf("%d", &menuInput); // user's menu input will be stored in menuInput

  /*
    if (menuInput == 1) {

    }

    else (menuInput == 2) {


    }
  */

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
      extraNumChar++; // increment number of extra characters
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

  // if programStr has been completely looked through, but userStr still has characters
  if (i == progStrLength && j < userStrLength) {
    while(j < userStrLength) {
      j++; // increment userStr position
      extraNumChar++; // increment number of extra chars
    }
  }

  printf("Extra Number of Characters: %d\n", extraNumChar);
  printf("Correct Number of Characters: %d\n", correctNumChar);

  // calculate WPM
  wpm = ((double)correctNumChar/5)/0.5;
  printf("WPM: %f\n", wpm);

  // calculate accuracy
  accuracy = ((double)correctNumChar/(progStrLength + extraNumChar))*100;
  printf("accuracy: %f%%\n", accuracy);


  return 0;
}

