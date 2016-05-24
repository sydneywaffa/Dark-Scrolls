/****************************************************************************************
 * Written By Will Renaud             FOR: Ics3g            Proposal Written MAY 9, 1015*
 *										                                                *
 *                                          USER INFO                                   *
 *    MOVE: up = w   down = s    left = a   right = d    esc = menu    space = use menu *
 *    BATTLE:  a = fast attack   s = heavy attack                                       *
 *                                        												*
 *                            		DARK SCROLLS										*
 *    During this project I hope to learn how to make graphical user interfaces and 	*
 * input systems. I also hope to learn how to fully modulate a game program and write in*
 * a way that makes it easy for others to add extra levels, enemies, or custom graphics *
 * and audio to the game and make it their own, however this feature will only be an 	*
 * afterthought in terms of design schedule, core functionality will come first.		*
 *																						*
 *    Dark Scrolls is a classic RPG recreation and re-environment of the classic game   *
 * "DARK SOULS" which is created by "Fromsoft". Dark scrolls runs by allowing the player*
 * explore a mostly linear dungeon one area at a time. During this exploration/         *
 * progression battles are triggered at semi-random intervals and player is launched 	*
 * into a battle, which is it's own mostly self contained subroutine. 					*
 *    The Battle will display a room with the character on one side and the enemy(s) on *
 * the opposite side. The user will be provided with a menu of attacks, spells, and 	*
 * items use in battle. Character stats will determine how effective attacks and spells *
 * are and how quickly the character may attack. The enemies will run on a random 		*
 * selection of basic attacks are suited to the specific enemy or area. Boss battles 	*
 * will be placed at the end of areas and will be designed to provide a considerable	*
 * challenge.																			*
 *    Player objective is to advance through all levels and beat all the bosses and 	*
 * clear the game. Save points will be implemented where stats, items, and progress will*
 * be saved to a save file. An extra feature i would like to add is a modular program	*
 * system that allows user to create their own enemies, textures, maps, and items.		*
 * Unfortunately to do this it means files would have to be accessible to users making	*
 * cheating possible through editing of save files.										*
 *																						*
 *																						*
 *									Dev Plan											*
 *May 9: Basic Frame complete						deadline met						*
 *May 11: Battle System Underway					deadline met						*
 *May 15: Battle System Complete					deadline met						*
 *May 22: Basic Demo/Level 1 complete				deadline met						*
 *May 23 - June 2: Level Creation & Bug Fixing		deadline met						*
 *June 2: Full Completion Date						deadline met						*
 *June 9: Full Release								postponed to clean up bits			*
 *June 30: Level Expansion 1						on track to be completed			*
 * -Further Level Updates dateless 														*
 *  development will continue until 													*
 *  all levels from original game are recreated in new format.						    *
 *																						*
 *																						*
 *-extra features to be implemented if ahead of schedule:								*
 * -saves	<- working great															*
 * -user level creation guide	<- not yet												*
 * -extra modularity for user level creation	<- DONE! but no user guide yet			*
 *												levels can be created in 10 minutes		*
 * -revamped and higher definition graphics	<- graphics were degraded for retro feel	*
 *																						*
 *																						*
 *-Removable Features:																	*
 * -stat levelup	<- working! but the resistance stat is pending debugging			*
 * -equipment/weapon changing <-cancelled												*
 * -respawns	<- have to reload from save												*
 * -Battle Animation	<-unfinished but present										*
 * -Multi-Enemy battles	<- cancelled													*
 * -Enemy attack pattern (will just use random attack instead of a pattern) <-cancelled	*
 *																						*
 * 									   													*
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <alfont.h>
#include "PWAllegro.h"


// globals are used for variables that require a lot of passing by reference
int health;
int str, dex, speed, faith, intel, res, vit;
int level, eXP;
int i, j;
int mapnumber;
int magicAttackNum, magicHealNum;
int musique;







//main is voided since no arguments need to be passed
int main(void)
{
    
    
    
    
    
    // initialises allegro, alFont, time, and keyboard.
    init();
    

    // displays a loading screen
    loadScreen();
    
    
    // initialisation of the player bitmaps and the map. 
    // also declares font and music 
    int keypressed, lastkey = 1;
    BITMAP *pdown = NULL,*pup = NULL,*pleft = NULL,*pright = NULL;
    BITMAP *map = NULL;
    SAMPLE *fanfare, *mapmusic1;
    ALFONT_FONT *arial = alfont_load_font("C:/Windows/Fonts/arial.ttf"); 
    
    // loads music and player bitmaps
    fanfare = load_sample("FFXIV ARR OST Duty Complete Theme (.wav");
    mapmusic1 = load_sample("Nameless Song - Dark Souls Soundtrac.wav");
    pdown = load_bitmap("solaire2.bmp", NULL);
    pup = load_bitmap("solaire2up.bmp", NULL);
    pleft = load_bitmap("solaire2left.bmp", NULL);
    pright = load_bitmap("solaire2right.bmp", NULL);
    // creates map bitmap for graphics to be loaded into
    map = create_bitmap(960,640);
    

    // creates map data for wall detection and map drawing
    int mapdata[100][100];
    // sets default map to 0
    mapnumber = 0;
    // sets number of spells you can cast before recharging to 2 and 5
    magicAttackNum = 2;
    magicHealNum = 5;
    // sets default music to 1
    musique = 1;
    // loaded is used to cheack weather player has loaded a game
    int loaded = 0;
    
    int musicswitch, battlestart;
    char levelname[100];
    
    //loads default map file from text file
    loadmap(mapdata);
    
    //draws map from map file
    map = drawmap(mapdata);
    

    // checks to confirm player loading
    if (pdown == NULL)
    {
        allegro_message("missing player file");
        return 1;
    }
    if (pup == NULL)
    {
        allegro_message("missing player file");
        return 1;
    }
    if (pright == NULL)
    {
        allegro_message("missing player file");
        return 1;
    }
    if (pleft == NULL)
    {
        allegro_message("missing player file");
        return 1;
    }
    if (map == NULL)
    {
        allegro_message("map failed to load");
        return 2;
    }
    

    


    
    

    
    

    //seed random
    srand(time(NULL));
    //font size set
    alfont_set_font_size(arial, 25);
    //defaults exit status to false (1 = true 0 = false   no bool in c)
    int quit = 0;
    
    //defaults health
    health = 100;
    
    int bossbattle = 0;
    
    
    /*MAIN GAME LOOP*/
    //loops until quit = true
    while ((quit == 0))
    {


        //main menu. returns quit status. location and load status are passed
        quit = menu(&loaded, mapdata[i][j]);
        
        // quit = 2 when new game is selected. this then reloads the map for new game
        if (quit == 2)
        {
            
            // loads and draws map then resets health
            loadmap(mapdata);
            map = drawmap(mapdata);
            health = 80 + (vit * 20);
            
            //when map is loaded the map name is set
            switch (mapnumber)
            {
                case 0:strcpy(levelname, "Undead Asylum        ");
                       break;
                case 1:strcpy(levelname, "Undead Burg          ");
                       break;
                case 2:strcpy(levelname, "Undead Parish        ");
                       break;
                case 3:strcpy(levelname, "Lower Burg           ");
                       break;
                case 4:strcpy(levelname, "Depths               ");
                       break;
                case 5:strcpy(levelname, "Blighttown           ");
                       break;
                default: strcpy(levelname, "lordran                ");
                
            }  
            // sets quit to false so game doesn't exit
            quit = 0;
        }
        //action loop continues until player dies or player presses escape to reach menu
        // skips if exit true
        while (!key[KEY_ESC] && (quit == 0) && (health > 0))
        {
            
            // checks to make sure music isn't already playing (0 = playing, 1 =not)
            if (musique == 1)
            {
                //randomises which music track to play.
                musicswitch = rand() % 2;
                //only 1 track for now, had more but made file too large. will add later
                if (musicswitch == 0)
                {
                    play_sample(mapmusic1, 255, 128, 1000, 1);
                }
                else
                {
                    play_sample(mapmusic1, 255, 128, 1000, 1);
                }
                // sets music to playing
                musique = 0;
            }
            // printing of map
            masked_blit(map, screen, 0,0,((-i+9)*16),((-j+9)*16),960,640);
            // checks what the last key pressed and determines which bitmap should be
            // printed based of direction. uses allegro key codes.
            switch (keypressed)
            {
                //if left is pressed
                case 1: masked_blit(pleft, screen, 0,0,144,144,16,16);
                        lastkey = keypressed;
                        break;
                //if right is pressed
                case 4: masked_blit(pright, screen, 0,0,144,144,16,16);
                        lastkey = keypressed;
                        break;
                //if down is pressed
                case 19: masked_blit(pdown, screen, 0,0,144,144,16,16);
                        lastkey = keypressed;
                        break;
                //if up is pressed
                case 23: masked_blit(pup, screen, 0,0,144,144,16,16);
                        lastkey = keypressed;
                        break;
                //if user puts in invalid directional input it defaults to last direction
                default: switch (lastkey)
                         {
                             case 1: masked_blit(pleft, screen, 0,0,144,144,16,16);
                                     break;
                             case 4: masked_blit(pright, screen, 0,0,144,144,16,16);
                                     break;
                             case 19: masked_blit(pdown, screen, 0,0,144,144,16,16);
                                     break;
                             case 23: masked_blit(pup, screen, 0,0,144,144,16,16);
                                     break;
                         }
        
            }   
            // stats, health, and experience printed to bottom of screen 
            // with the map name at top of the screen
            alfont_textprintf_aa_ex(screen, arial, 5, 5, 0xFFFFFF, -1, "%s", levelname);
            alfont_textprintf_aa_ex(screen, arial, 10, 210, 0xFFFFFF, -1, "str:%d dex:%d speed:%d ", str, dex, speed);
            alfont_textprintf_aa_ex(screen, arial, 10, 240, 0xFFFFFF, -1, "faith:%d intel:%d res:%d vit:%d",  faith, intel, res, vit);
            alfont_textprintf_aa_ex(screen, arial, 10, 270, 0xFFFFFF, -1, "(%d/%d hp) (exp:%d/%d)",  health, (80 + (vit * 20)), eXP, (level * 200));
        

            // debug info printed to command window
            printf("x = %d  y = %d INPUT = %d\n attack:%d \n heal%d \n", i, j, keypressed, magicAttackNum, magicHealNum);
            printf("mapdata = %d\n", mapdata[i][j]);
            
            //checks to see if user entered boss room tile, which is tile 4.
            if (mapdata[i][j] == 4)
            {
                //stops map music
                stop_sample(mapmusic1);
                //starts boss battle with enemy code 4, which is the boss code.
                //returns result of boss battle
                bossbattle = battle(4);
            }
            // if user is not on boss door boss battle result is reset to false
            else
            {
                bossbattle = 0;
            }
            // checks to see if user is on the save point tile, which is tile 5.
            if (mapdata[i][j] == 5)
            {
                //if user gets to save point health and magic is reset to full.
                health = 80 + (vit * 20);
                magicAttackNum = (intel * 2);
                magicHealNum = faith + 4;
            }
            //checks to see if the user has won a boss battle.
            if (bossbattle == 1)
            {
    			// sets status back to false
                bossbattle = 0;
                //advances user to next level
                mapnumber += 1;
                // only 6 levels at the moment (0-5).
                // since level 6 does not exist, reaching six means player has won game
                if (mapnumber == 6)
                {
                    
                    //screen cleared
                    BITMAP *blank = create_bitmap(300,300);
                    clear_bitmap(blank);
                    //win theme is played
                    play_sample(fanfare, 255, 128, 1000, 0);
                    masked_blit(blank, screen, 0, 0, 0, 0, 300, 300);
                    //win message is printed
                    alfont_textprintf_aa_ex(screen, arial, 30, 100, 0x00FF00, -1, "YOU HAVE CONQUERED");
                    alfont_textprintf_aa_ex(screen, arial, 50, 120, 0x00FF00, -1, "THE UNDEAD BURG");
                    alfont_textprintf_aa_ex(screen, arial, 100, 200, 0x00FF00, -1, "YOU WIN");
                    alfont_textprintf_aa_ex(screen, arial, 50, 270, 0xFFFFFF, -1, "HOLD ANY BUTTON");
                    //several buffers so player wont accidentally skip by holding a key
                    clear_keybuf();
                    readkey();
                    clear_keybuf();
                    readkey();
                    clear_keybuf();
                    readkey();
                    //bitmaps destroyed
                    destroy_bitmap(blank);
                    destroy_bitmap(pdown);
                    destroy_bitmap(pup);
                    destroy_bitmap(pleft);
                    destroy_bitmap(pright);
                    destroy_bitmap(map);
                    destroy_sample(fanfare);
                    destroy_sample(mapmusic1);
                    alfont_exit();
                    return 1;
                }
                // loads new map file and draws it out
                loadmap(mapdata);
                map = drawmap(mapdata);
                // sets start location for each map
                if (mapnumber == 1)
                {
                    i = 54;
                    j = 3;
                }
                if (mapnumber == 2)
                {
                    i = 5;
                    j = 2;
                }
                if (mapnumber == 3)
                {
                    i = 3;
                    j = 2;
                }
                if (mapnumber == 4)
                {
                    i = 3;
                    j = 3;
                }
                if (mapnumber == 5)
                {
                    i = 4;
                    j = 3;
                }
                
                
            }
        
			//checks to see if user has enough experience to level up
            levelup();
            //processes user directional input and checks to see if user is hitting wall
            //returns user direction
            keypressed = moveInput(mapdata, &i, &j);
                         

        

            // checks to see if user has encountered enemy (3 in 100 chance)
            battlestart = enemyCheck();
    		// if enemy is encountered then music is stopped 
    		// and enemy type is passed to battle
            if (battlestart < 3)
            {
                stop_sample(mapmusic1);
                
                battle(battlestart);
            }
            //all key buffers are flushed, just in case. was having errors earlier
            clear_keybuf();
            fflush(stdin);
        
        
                 
        
        
        }
    }
 
    //quit message
    allegro_message("IF ONLY I COULD BE SO INCANDESCENT!");
    
    
    //assets destroyed
    
    destroy_bitmap(pdown);
    destroy_bitmap(pup);
    destroy_bitmap(pleft);
	destroy_bitmap(pright);
    destroy_bitmap(map);
    destroy_sample(fanfare);
	destroy_sample(mapmusic1);
    alfont_exit();
    return 0;
}
END_OF_MAIN()

