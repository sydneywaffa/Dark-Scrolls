#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <alfont.h>

/****************************
 * MENU FUNCTIONS!			*
 * Not sorted in any order	*
 ****************************/

//extern of globals
extern int health;
extern int str, dex, speed, faith, intel, res, vit;
extern int level, eXP;
extern int i, j;
extern int mapnumber;
extern int magicAttackNum, magicHealNum;
extern int musique;



// saves game
void saveGame()
{
    
    //opens save file for writing
    FILE *fptr = NULL;
    fptr = fopen("savefile.txt", "w");
    //calculates total level
    level = (str + dex + speed + faith + intel + res + vit) - 6;

    //overwrites save file with currents stats, location, and map.
    fprintf(fptr, "%d\n %d %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n", mapnumber, i, j, str, dex, speed, faith, intel, res, vit, level, eXP);
    //prints stats to command window for debugging
    printf("stats:\n map:%d\n i: %d j: %d\n str:%d\n dex:%d\n speed:%d\n faith:%d\n int:%d\n res:%d\n vit:%d\n level:%d\n exp:%d\n", mapnumber, i, j, str, dex, speed, faith, intel, res, vit, level, eXP);
    //pointer is closed
    fclose(fptr);
    return;
}





//	loads saved data
int loadGame()
{

	//opens save file and reads out stats, location, and level.
    FILE *fpntr;
    fpntr = fopen("savefile.txt", "r");
    allegro_message("%d", mapnumber);
    fscanf(fpntr, "%d", &mapnumber);
    fscanf(fpntr, "%d", &i);
    fscanf(fpntr, "%d", &j);
    fscanf(fpntr, "%d", &str);
    fscanf(fpntr, "%d", &dex);
    fscanf(fpntr, "%d", &speed);
    fscanf(fpntr, "%d", &faith);
    fscanf(fpntr, "%d", &intel);
    fscanf(fpntr, "%d", &res);
    fscanf(fpntr, "%d", &vit);
    fscanf(fpntr, "%d", &level);
    fscanf(fpntr, "%d", &eXP);
    health = 80 + (vit * 20);
    fclose(fpntr);
    //displays loaded data for debug
    allegro_message("stats:\n map:%d\n i: %d j: %d\n str:%d\n dex:%d\n speed:%d\n faith:%d\n int:%d\n res:%d\n vit:%d\n level:%d\n exp:%d\n", mapnumber, i, j, str, dex, speed, faith, intel, res, vit, level, eXP);
	// returns load status as true
    int loaded = 1;
    return loaded;
    
}




// Main Menu

int menu(int *floaded, int location)
{
    
	
    clear_keybuf();
    //menu backdrop is loaded
    BITMAP *menuback;
    menuback = load_bitmap("menuback.bmp", NULL);
    //checks to make sure background loads properly
    if (menuback == NULL)
    {
        allegro_message("menu failed");
    }
    // sets font
    ALFONT_FONT *arial = alfont_load_font("C:/Windows/Fonts/arial.ttf"); 
    
    int load = 0, exit = 0, newG = 0, selected = 0, save = 0;
    //backdrop is printed.
    blit(menuback, screen, 0, 0, 0, 0, 300, 300);
    
	//loops until user loads, saves, starts a new game, or quits.
    while ((load == 0) && (exit == 0) && (newG == 0) && (save == 0))
    {
        blit(menuback, screen, 0, 0, 0, 0, 300, 300);
        //title font size is set
        alfont_set_font_size(arial, 50);

        alfont_textprintf_aa_ex(screen, arial, 10, 50, 11340544, -1, "Dark Scrolls");

        //menu font size is set
        alfont_set_font_size(arial, 20);
        
		// checks which menu item is currently selected and prints that item
		// in different colour. unselected appear in gold while selected items are red 
        
        switch (selected)
        {
            case 0: alfont_textprintf_aa_ex(screen, arial, 10, 120, 11340544, -1, "New Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 160, 16738816, -1, "Load Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 200, 16738816, -1, "Save");
                    alfont_textprintf_aa_ex(screen, arial, 10, 240, 16738816, -1, "Quit");
                    break;
            case 1: alfont_textprintf_aa_ex(screen, arial, 10, 120, 16738816, -1, "New Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 160, 11340544, -1, "Load Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 200, 16738816, -1, "Save");
                    alfont_textprintf_aa_ex(screen, arial, 10, 240, 16738816, -1, "Quit");
                    break;
            case 2: alfont_textprintf_aa_ex(screen, arial, 10, 120, 16738816, -1, "New Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 160, 16738816, -1, "Load Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 200, 11340544, -1, "Save");
                    alfont_textprintf_aa_ex(screen, arial, 10, 240, 16738816, -1, "Quit");
                    break;
            case 3: alfont_textprintf_aa_ex(screen, arial, 10, 120, 16738816, -1, "New Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 160, 16738816, -1, "Load Game");
                    alfont_textprintf_aa_ex(screen, arial, 10, 200, 16738816, -1, "Save");
                    alfont_textprintf_aa_ex(screen, arial, 10, 240, 11340544, -1, "Quit");
                    break;
            // if selected value is not a valid menu item then error message is printed
            default: allegro_message("error: %d", selected);
                     return 0;
        }
        

        //input is buffered
        readkey();
        clear_keybuf();
        


        //processes input and moves menu selection based on key pressed
        if ((key[KEY_W]) && (selected > 0))
        {
            selected -= 1;
        }
        if ((key[KEY_S]) && (selected < 3))
        {
            selected += 1;
        }
        //when space is pressed current selection is confirmed
        if (key[KEY_SPACE])
        {
            switch (selected)
            {
                case 0: newG = 1;
                        exit = 0;
                        break;
                case 1: load = 1;
                        exit = 0;
                        break;
                case 3: exit = 1;
                        break;
                case 2: save = 1;
                        break;
                //error message
                default: allegro_message("menu error: %d", selected);
                
            }
        }
		
		//if load has been selected then saved data is loaded, and map reload is triggered
        if (load == 1)
        {
            *floaded = loadGame();
            exit = 2;
        
        }
		//resets game data and triggers map reload
        if (newG == 1)
        {
            
            allegro_message("newgame");
            newgame();
            exit = 2;
            *floaded = 1;
            
        }
		//checks to make sure a game has been loaded so that theres actually something to
		//save. also makes sure user is at a save point. if player has loaded and is at a
		//savepoint then they may save
        if (save == 1)
        {
            if ((*floaded == 1) && (location == 5))
            {   
                saveGame();
                exit = 0;
            }
            else if ((location != 5) && (location != 0))
            {
                allegro_message("Not at a save point.");
            }
            else
            {
                allegro_message("no game loaded");
                save = 0;
                *floaded = loadGame();
            }
        }
    }
    
   
    //exit status is printed for debug and screen is cleared
    printf("\n%d\n", exit);
    destroy_bitmap(menuback);
    BITMAP *buff = create_bitmap(300,300);
    clear_bitmap(buff);
    masked_blit(buff, screen, 0, 0, 0, 0, 300, 300);
    destroy_bitmap(buff);
    //exit status is returned
    return exit;
}




//resets game data to default but does not overwrite save file
int newgame()
{
    

    
    

    clear_keybuf();
    readkey();
    clear_keybuf();
    
    mapnumber = 0;
    i = 6;
    j = 2;
    str = 1;
    dex = 1;
    speed = 1; 
    faith = 1;
    intel = 1;
    res = 1;
    vit = 1;
    level = 1; 
    eXP = 1;
    
    return 1;
}
