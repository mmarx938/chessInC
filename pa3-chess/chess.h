#include<stdio.h>
#include<math.h>
#define MAX_COMMAND_TOKEN_LENGTH 6
#define WHITE 1
#define BLACK -1

#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
}square;

typedef enum {
    NONE = 0,
    WHITE_SHORT = 1,
    WHITE_LONG = 2,
    BLACK_SHORT = 4,
    BLACK_LONG = 8
}castle;
extern square board[8][8];
extern int turn;
char getCommandWord(char command[], int maxLength);
handleShow();
handleCapture();
handleMove();



//
extern int r;
extern int w;
extern int b;
extern int t;
extern int import;
extern char blackPlayerName[100];
extern char whitePlayerName[100];
extern void *cronoMin(void *data);
extern char *substring(char *destination, const char *source, int beg, int n);
extern int powInt(int x, int y);
extern void cronoMain();
extern void resetBoard();
extern int secondsLeftWhite;
extern int secondsLeftBlack;
extern char *posInitial[2];
extern char *posFinal[2];
extern char *gameHistory[3000];
