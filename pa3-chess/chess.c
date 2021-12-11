#include "chess.h"
square board[8][8];
int turn;
char whitePlayerName[100];
char blackPlayerName[100];
int r = 0;
int w = 0;
int b = 0;
int t = 0;
int import = 0;
char *posInitial[2];
char *posFinal[2];
char *gameHistory[3000];
int secondsLeftWhite;
int secondsLeftBlack;
char *timeNumber;

void resetBoard() {
    turn = WHITE;//WHITE moves first
    int i, j;
    for (i = 2; i < 6;i++)
        for (j = 0;j < 8;j++)
            board[i][j] = EMPTY;
    for (j = 0;j < 8;j++) {
        board[1][j] = BLACK * PAWN;
        board[6][j] = WHITE * PAWN;
    }
    board[0][0] = board[0][7] = BLACK * ROOK;
    board[7][0] = board[7][7] = WHITE * ROOK;
    board[0][1] = board[0][6] = BLACK * KNIGHT;
    board[7][1] = board[7][6] = WHITE * KNIGHT;
    board[0][2] = board[0][5] = BLACK * BISHOP;
    board[7][2] = board[7][5] = WHITE * BISHOP;
    board[0][3] = BLACK * QUEEN;
    board[7][3] = WHITE * QUEEN;
    board[0][4] = BLACK * KING;
    board[7][4] = WHITE * KING;
}
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;//either space or new line
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);//skip leading white spaces
    if (lastCharacter == '\n') {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}

// Function to implement substring function in C
char* substring(char *destination, const char *source, int beg, int n)
{
    // extracts `n` characters from the source string starting from `beg` index
    // and copy them into the destination string
    while (n > 0)
    {
        *destination = *(source + beg);

        destination++;
        source++;
        n--;
    }

    // null terminate destination string
    *destination = '\0';

    // return the destination string
    return destination;
}

void removeUpper(char *string) {
  int indexString = 0, indexNewString = 0;
  char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ)(.-";
  int addChar = 1;
  // iterate string character by character
  while (string[indexString]) {
    // First we assume that the letter must remain
    addChar = 1;
    int indexChars = 0;
    // iterate forbidden characters
    while (chars[indexChars]) {
      // Y si la letra actual es uno de los caracteres, ya no se agrega
      if (string[indexString] == chars[indexChars]) {
        addChar = 0;
      }
      indexChars++;
    }
    // Depending on the variable above, the letter is added to the new string
    if (addChar) {
      string[indexNewString] = string[indexString];
      indexNewString++;
    }
    indexString++;
  }

  // At the end the NULL character is added to end the string
  string[indexNewString] = 0;
}

int main(int argc, char** argv) {
    /*
    * You can access all the command-line arguments here
    * argv[1], argv[2], ...
    * Example of import option: -i d2d4,d7d5,e2e4,d5xe4,Ng1h3,Ke8d7,Qd1d3
    * which is equivalent to a new game started this way:
    * mv d2 d4
    * mv d7 d5
    * mv e2 e4
    * cp d5 e4
    * mv g1 h3
    * mv e8 d7
    * mv d1 d3
    */



    //validate that arguments exists
    if(argc < 2){
        printf("Too few arguments\n");
        return;
    }

    //iterate through arguments
    int argNumber;
    for(argNumber = 1; argNumber < argc; argNumber++){
        if(!strcmp(argv[argNumber], "-r"))
            r = r == 0 ? 1 : 0;

        if(!strcmp(argv[argNumber], "-w")){
            handleWhitePlayerName(argv[argNumber + 1]);
            w = w == 0 ? 1 : 0;
            argNumber++;
        }

        if(!strcmp(argv[argNumber], "-b")){
            handleBlackPlayerName(argv[argNumber + 1]);
            b = b == 0 ? 1 : 0;
            argNumber++;
        }

        if(!strcmp(argv[argNumber], "-i")){
            //Parse movements
            printf("Importing Game\n");

            import=1; //Import flag
            resetBoard();

            char *arg = argv[argNumber+1];

            char *pt;
            pt = strtok (arg,",");
            while (pt != NULL) {
                char *ordenFinal[10];

                removeUpper(pt);

                //MV
                if(strlen(pt) == 4){
                    substring(posInitial, pt, 0,2);
                    substring(posFinal, pt, 2,2);
                    strcat(ordenFinal, &posInitial);
                    strcat(ordenFinal, " ");
                    strcat(ordenFinal, &posFinal);

                    printf(">>mv %s %s\n", &posInitial, &posFinal);
                    handleMove();
                }
                //CP
                if(strlen(pt) == 5){
                    //validate capture flag
                    char *flagCP[1];
                    substring(flagCP, pt, 2, 1);

                    if(!strcmp(flagCP, "x")){
                        substring(posInitial, pt, 0,2);
                        substring(posFinal, pt, 3,2);
                        strcat(ordenFinal, &posInitial);
                        strcat(ordenFinal, " ");
                        strcat(ordenFinal, &posFinal);

                        printf(">>cp %s %s\n", &posInitial, &posFinal);
                        handleCapture();
                    }
                }

                pt = strtok (NULL, ",");
            }

            argNumber++;
        }

        if(!strcmp(argv[argNumber], "-t")){
            t = 1;
            timeNumber = argv[argNumber + 1];
            argNumber++;
        }
    }

    if(t)
    {
        pthread_t timerGame;
        pthread_t cronoMainThread;

        pthread_create(&timerGame, NULL, &cronoMin, timeNumber);
        pthread_create(&cronoMainThread, NULL, &cronoMain, "");

        pthread_join(timerGame, NULL);
        pthread_join(cronoMainThread, NULL);
    }
    else
        cronoMain();
}
