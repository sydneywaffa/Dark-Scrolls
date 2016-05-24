#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <alfont.h>

//function initialization
void loadmap (int data[100][100]);
int battle (int enemynum);
int moveInput ();
int enemyCheck();
void saveGame();
BITMAP *drawmap(int data[100][100]);
void loadScreen();
void init();
int loadGame();
int menu(int *floaded, int location);
int newgame();
void levelup();
