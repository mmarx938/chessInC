#include"chess.h"

int powInt(int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        x *= 10;
    }
    return x;
}

int parseInt(char* chars)
{
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++)
    {
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}

void *cronoMin(void *data){
    char *time;
    time = (char *) data;
    
    int whiteSecondLimit;
    int blackSecondsLimit;
    whiteSecondLimit = parseInt(time) * 60;
    blackSecondsLimit = parseInt(time) * 60;

    secondsLeftWhite = whiteSecondLimit;
    secondsLeftBlack = blackSecondsLimit;
    
    int countWhitePlayer;
    int countBlackPlayer;

    int hoursWhitePlayer;
    int minutesWhitePlayer;
    int secondsWhitePlayer;

    int hoursBlackPlayer=0;
    int minutesBlackPlayer=0;
    int secondsBlackPlayer=0;

    countWhitePlayer=0;
    countBlackPlayer=0;

    struct timespec time1 = {1,0};

    while(1){
        //pthread_delay_np(&time1);
        sleep(1);

        if(turn == 1) //turno del blanco
        {
            countWhitePlayer++;
            
            secondsLeftWhite = (whiteSecondLimit-countWhitePlayer);
            if(countWhitePlayer == whiteSecondLimit)
            {
                break;
            }
        }
        else
        {
            countBlackPlayer++;

            secondsLeftBlack = (blackSecondsLimit-countBlackPlayer);
            if(countBlackPlayer == blackSecondsLimit)
                break;
        }
    }

    printf("%s\n", "No time, end of game");
    printHistory();
    exit(0); //Finaliza el juego por tiemmpo
}

void printHistory(){
    char *game[3000];
    substring(game, &gameHistory, 0, strlen(&gameHistory)-1);
    printf("Game History: %s\n", game);
}

void cronoMain(){
    char command[MAX_COMMAND_TOKEN_LENGTH];
    char lastCharacter;

    if(!import) //Reset the board if no import 
        resetBoard();
    else
        import=0; //Import flag

    printf("Start the game using a mv command! Valid commands are quit, show, mv and cp.\n");
    while (1) {//infinite while loop...
        printf(">>");
        lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        if (strcmp(command, "quit") == 0)//if command === "quit"
        {
            //Print gameHistory
            printHistory();

            exit(0);
        }
        else if (!strcmp(command, "mv"))//if command == "mv"
        {
            if (lastCharacter == '\n')//mv\n
                printf("Too few arguments for mv command! It must be in the form of mv ai bj.\n");
            else
                handleMove();
        }
        else if (!strcmp(command, "cp"))//if command == "cp"
        {
            if (lastCharacter == '\n')//cp\n
                printf("Too few arguments for cp command! It must be in the form of cp ai bj.\n");
            else
                handleCapture();
        }
        else if (!strcmp(command, "show"))//if command == "show"
        {
            if (lastCharacter != '\n') {//show x\n
                printf("Too many arguments for show command! It must be in the form of show.\n");
                while (getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH) != '\n');//skip the ramainder of the invalid show command...
            }
            else
                handleShow();
        }
        else {
            printf("invalid command! Your command must start either with quit, show, mv or cp.\n");
            while (lastCharacter != '\n')//skip the remainder of my invalid command...
                lastCharacter = getCommandWord(command, MAX_COMMAND_TOKEN_LENGTH);
        }
    }
}
