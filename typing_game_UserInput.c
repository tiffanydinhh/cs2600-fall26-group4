#include <stdio.h>
#include <string.h>

int main(void){
  //Defining text paragraph
  const char paragraph[] = "Half the world was pulling on his colors, as nights turned into days top the hours. A glow was coming down, coming down. I don't know why, but it felt like a tiger striped sky.";

  //Holding up to 256 character inputs
  char userInput[256];

  //Creating space to display paragraph further away
  printf("Type the following text: \n\n%s\n\n", paragraph);
  printf("Typing: ");

  //Reads user line, if reading fails, prints an error and stops program
  if (fgets(userInput, sizeof userInput, stdin) == NULL) {
    printf("Could not read your input.\n");
    return 1;
  }

  //Removes newline character from userInput
  userInput[strcspn(userInput, "\n")] = '\0';

  //Printing final user output
  printf("\nYou typed:\n%s\n", userInput);

  return 0;

}

  

  
