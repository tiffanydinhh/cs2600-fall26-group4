/************************************************************/
/* Method: isEmpty                                          */
/* Purpose: Checks if the user's input is empty, contains   */
/*          only spaces, tabs, or newline characters.       */
/* Parameters: char input[] - the user's input string.      */
/* Returns: int: 1 if input is empty, 0 if its not.         */
/************************************************************/

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