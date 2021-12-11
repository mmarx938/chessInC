#include"chess.h"
handleShow() {
    int i, j;

    if(b) //if b was found 
        printf("--> %s ", r == 0 ? blackPlayerName : whitePlayerName);
    if(t) // if t was found 
        printTimeLeft(secondsLeftBlack);

    printf("\nboard\t");
    if(!r){
        for (i = 0; i < 8; i++)//file labels...
            printf("%c%c", 'a' + i, i == 7 ? '\n' : '\t');
        for (i = 0; i < 8; i++)//table itself
            for (j = 0; j < 9; j++)
                printf("%d%c", j == 0 ? 8 - i : board[i][j - 1], j == 8 ? '\n' : '\t');
    }
    else{
        for (i = 0; i < 8; i++)//file labels...
            printf("%c%c", 'h' - i, i == 7 ? '\n' : '\t');
        for (i = 0; i < 8; i++)//table itself
            for (j = 0; j < 9; j++)
                printf("%d%c", j == 0 ? i + 1 : board[7-i][8-j], j == 8 ? '\n' : '\t');
    }

    if(w) // if w argument was found 
        printf("--> %s ", r == 0 ? whitePlayerName : blackPlayerName);
    if(t) // if t argument was found 
        printTimeLeft(secondsLeftWhite);

    printf("\n");
}

void printTimeLeft(int tseconds){
    int hours;
    int minutes;
    int seconds;

    char textHours[20];
    char textMinutes[20];
    char textSeconds[20];

    hours = tseconds / 3600;
    minutes = (tseconds-hours*3600)/60;
    seconds = tseconds-(hours*3600+minutes*60);

    sprintf(textHours, "%d", hours);
    sprintf(textMinutes, "%d", minutes);
    sprintf(textSeconds, "%d", seconds);

    printf("--> %s%s:%s%s:%s%s", hours < 10 ? "0" : "",textHours,minutes < 10 ? "0" : "", textMinutes, seconds < 10 ? "0" : "", textSeconds);
}
