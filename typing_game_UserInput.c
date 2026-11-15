#include <stdio.h>
#include <string.h>
#include <stddef.h> //For size_t

int paragraphInput(char userInput[], size_t inputSize){
  //Defining text paragraph
  const char paragraph[] = "Half the world was pulling on his colors, as nights turned into days top the hours. A glow was coming down, coming down. I don't know why, but it felt like a tiger striped sky.";

  //Creating space to display paragraph further away
  printf("Type the following text: \n\n%s\n\n", paragraph);
  printf("Typing: ");

  //Reads user line, returns 0 if fails to read input
  if (fgets(userInput, inputSize, stdin) == NULL) {
        return 0;
  }
  
  //Removes newline character from userInput
  userInput[strcspn(userInput, "\n")] = '\0';

  //Printing final user output
  printf("\nYou typed:\n%s\n", userInput);

  return 1;
}

  

  
