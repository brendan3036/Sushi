#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"
#define MAX_LEN 1023


int isSpecialChar(char letter) {return (letter == '<' || letter == '>' || letter == '|');}
int isLetter(char letter) {return (letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || letter == '/';}
int isQuote(char letter) {return letter == '"';}
int isBlank(char letter) {return letter == ' ';}
int isEnd(char letter) {return letter == '\0';}
int isNewLine(char letter) {return letter == '\n';}
/*!, #, $, &, ', (, ), *, +, ,, -, ., /, :, ;, =, ?, @, [, ],  */
int isOtherChar(char letter) {return letter == ';';}

char** string_tok(char *input, char **tokenizedCmd)
{
  /**
   *  state = 0 -- Nothing in Particular
   *  state = 1 -- A word
   *  state = 2 -- A special char
   *  state = 3 -- In quotes
   *  state = 4 -- End of command
   */
  int state = 0;
  int com_num = 0;    
  int loopnum = 0;
  int i = 0;
  while(!isEnd(input[i]))
  {
    int pos = 0;
    switch(state)
    {
      case 0:
        //printf("In Case 0: input[i] = '%c'\n", input[i]);
        if(isLetter(input[i])) {state = 1;}
        if(isSpecialChar(input[i])) {state = 2;}
        if(isQuote(input[i])) {state = 3;}
        if(isBlank(input[i])) {i++;}
        if(isEnd(input[i])) {state = 4;}
        if(isNewLine(input[i])) {i++;} //TODO Why does the program Start with a newLine
        break;
      case 1:
        pos = 0;
        while(isLetter(input[i]))
        {
          tokenizedCmd[com_num][pos] = input[i];
          
          i++;
          pos++;
         
        }
        state = 0;
        com_num++;
        pos = 0;
        //printf("[com_num][pos] = [%d][%d]\n", com_num, pos);
        //printf("input[i] = '%c'\n", input[i]);
        break;
      case 2:
        pos = 0;
        while(isSpecialChar(input[i]))
        {
          tokenizedCmd[com_num][pos] = input[i];
          i++;
          pos++;
        }
        com_num++;
        state = 0;
        break;
      case 3:
        i++;
        pos = 0;
        while(!isQuote(input[i]) || isEnd(input[i] || isNewLine(input[i])))
        {
          tokenizedCmd[com_num][pos] = input[i];
          i++;
          pos++;
        }
        i++;
        com_num++;
        pos = 0;
        state = 0;
        break;
      case 4:
        printf("End of command\n\n");
        break;
    }
    loopnum++;
  }

    return tokenizedCmd;

}

// Only used for testing
// int main(int argc, char const *argv[]) 
// {

//   char userinput[MAX_LEN];

//   printf("> ");
//   fgets(userinput, MAX_LEN, stdin);

//   string_tok(userinput);
//   for (int row = 0; row < AMNT_ROWS; row++)
//   {
//     for (int col = 0; col < ROW_LNGTH; col++)
//     {
//          printf( "[%d][%d]: '%c' - ", row, col, tokenizedCmd[row][col] );
//     }
//     printf("\n");
//  }

//   return 0;
// }