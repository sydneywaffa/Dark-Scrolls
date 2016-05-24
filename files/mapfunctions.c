#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <alfont.h>

//extern of globals
extern int health;
extern int str, dex, speed, faith, intel, res, vit;
extern int level, eXP;
extern int i, j;
extern int mapnumber;
extern int magicAttackNum, magicHealNum;
extern int musique;


// processes input and checks for collision
int moveInput (int data[100][100])
{
    

    int input;
    input = readkey() >> 8;
    clear_keybuf();
    
    //each prints out location player moves to for debug
        
	//DOWN  
	//moves player down if S is pressed and tile below is not a wall tile               
    if ((data[i][j + 1] != 0) && (data[i][j + 1] != 6) && (input == KEY_S))
    {
        j += 1;
        printf("%d\n", data[i][j + 1]);
    }
        
    //UP       
    //moves player up if w is pressed and tile above is not a wall tile                             
    if ((data[i][j - 1] != 0) && (data[i][j - 1] != 6) && (input == KEY_W))
    {
        j -= 1;
        printf("%d\n", data[i][j - 1]);
    }
                         
    //RIGHT    
    //moves player right if D is pressed and tile to the right is not a wall tile                                
    if ((data[i + 1][j] != 0) && (data[i + 1][j] != 6) && (input == KEY_D))
    {
        i += 1;
        printf("%d\n", data[i + 1][j]);
    }
                         
                         
    //LEFT
    //moves player left if A is pressed and tile to the left is not a wall tile               
    if ((data[i - 1][j] != 0) && (data[i - 1][j] != 6) && (input == KEY_A))
    {
        i -= 1;
        printf("%d\n", data[i - 1][j]);
    }
    // returns input so main can process direction character faces
    clear_keybuf();
    return input;
}


//checks experience and levels up if user has trained enough
void levelup()
{
    
    
    
    //checks to see if user has more exp than player's level * 200
    // if user does not meet required exp function exits
    if (eXP > (level * 200))
    {
        //screen is cleared
        BITMAP *buff = create_bitmap(300,300);
        int levelup = 0;
        int selected = 0;
        clear_bitmap(buff);
        //font is set
        ALFONT_FONT *arial = alfont_load_font("C:/Windows/Fonts/arial.ttf");
        alfont_set_font_size(arial, 50);
        masked_blit(buff, screen, 0, 0, 0, 0, 300, 300);
        //menu is printed
        alfont_textprintf_aa_ex(screen, arial, 10, 50, 0xFFF177, -1, "Level Up");
        alfont_set_font_size(arial, 15);
        alfont_textprintf_aa_ex(screen, arial, 10, 105, 11340544, -1, "Strength");
        alfont_textprintf_aa_ex(screen, arial, 10, 125, 16773495, -1, "Dexterity");
        alfont_textprintf_aa_ex(screen, arial, 10, 145, 16773495, -1, "Speed");
        alfont_textprintf_aa_ex(screen, arial, 10, 165, 16773495, -1, "Faith");
        alfont_textprintf_aa_ex(screen, arial, 10, 185, 16773495, -1, "Inteligence");
        alfont_textprintf_aa_ex(screen, arial, 10, 205, 16773495, -1, "Resistance");
        alfont_textprintf_aa_ex(screen, arial, 10, 225, 16773495, -1, "Vitality");
        //loops until user selects a skill to level up
        while(levelup == 0)
        {
            
            // currently selected menu element is printed in red while other elements are
            // gold. 
            switch (selected)
            {
                //str
                case 0: alfont_textprintf_aa_ex(screen, arial, 10, 105, 11340544, -1, "Strength");
                        alfont_textprintf_aa_ex(screen, arial, 10, 125, 16773495, -1, "Dexterity");
                        alfont_textprintf_aa_ex(screen, arial, 10, 145, 16773495, -1, "Speed");
                        alfont_textprintf_aa_ex(screen, arial, 10, 165, 16773495, -1, "Faith");
                        alfont_textprintf_aa_ex(screen, arial, 10, 185, 16773495, -1, "Inteligence");
                        alfont_textprintf_aa_ex(screen, arial, 10, 205, 16773495, -1, "Resistance");
                        alfont_textprintf_aa_ex(screen, arial, 10, 225, 16773495, -1, "Vitality");
                        break;
                //dex
                case 1: alfont_textprintf_aa_ex(screen, arial, 10, 105, 16773495, -1, "Strength");
                        alfont_textprintf_aa_ex(screen, arial, 10, 125, 11340544, -1, "Dexterity");
                        alfont_textprintf_aa_ex(screen, arial, 10, 145, 16773495, -1, "Speed");
                        alfont_textprintf_aa_ex(screen, arial, 10, 165, 16773495, -1, "Faith");
                        alfont_textprintf_aa_ex(screen, arial, 10, 185, 16773495, -1, "Inteligence");
                        alfont_textprintf_aa_ex(screen, arial, 10, 205, 16773495, -1, "Resistance");
                        alfont_textprintf_aa_ex(screen, arial, 10, 225, 16773495, -1, "Vitality");
                        break;
                //speed
                case 2: alfont_textprintf_aa_ex(screen, arial, 10, 105, 16773495, -1, "Strength");
                        alfont_textprintf_aa_ex(screen, arial, 10, 125, 16773495, -1, "Dexterity");
                        alfont_textprintf_aa_ex(screen, arial, 10, 145, 11340544, -1, "Speed");
                        alfont_textprintf_aa_ex(screen, arial, 10, 165, 16773495, -1, "Faith");
                        alfont_textprintf_aa_ex(screen, arial, 10, 185, 16773495, -1, "Inteligence");
                        alfont_textprintf_aa_ex(screen, arial, 10, 205, 16773495, -1, "Resistance");
                        alfont_textprintf_aa_ex(screen, arial, 10, 225, 16773495, -1, "Vitality");
                        break;
                //faith
                case 3: alfont_textprintf_aa_ex(screen, arial, 10, 105, 16773495, -1, "Strength");
                        alfont_textprintf_aa_ex(screen, arial, 10, 125, 16773495, -1, "Dexterity");
                        alfont_textprintf_aa_ex(screen, arial, 10, 145, 16773495, -1, "Speed");
                        alfont_textprintf_aa_ex(screen, arial, 10, 165, 11340544, -1, "Faith");
                        alfont_textprintf_aa_ex(screen, arial, 10, 185, 16773495, -1, "Inteligence");
                        alfont_textprintf_aa_ex(screen, arial, 10, 205, 16773495, -1, "Resistance");
                        alfont_textprintf_aa_ex(screen, arial, 10, 225, 16773495, -1, "Vitality");
                        break;
                //intelligence
                case 4: alfont_textprintf_aa_ex(screen, arial, 10, 105, 16773495, -1, "Strength");
                        alfont_textprintf_aa_ex(screen, arial, 10, 125, 16773495, -1, "Dexterity");
                        alfont_textprintf_aa_ex(screen, arial, 10, 145, 16773495, -1, "Speed");
                        alfont_textprintf_aa_ex(screen, arial, 10, 165, 16773495, -1, "Faith");
                        alfont_textprintf_aa_ex(screen, arial, 10, 185, 11340544, -1, "Inteligence");
                        alfont_textprintf_aa_ex(screen, arial, 10, 205, 16773495, -1, "Resistance");
                        alfont_textprintf_aa_ex(screen, arial, 10, 225, 16773495, -1, "Vitality");
                        break;
                //resistance
                case 5: alfont_textprintf_aa_ex(screen, arial, 10, 105, 16773495, -1, "Strength");
                        alfont_textprintf_aa_ex(screen, arial, 10, 125, 16773495, -1, "Dexterity");
                        alfont_textprintf_aa_ex(screen, arial, 10, 145, 16773495, -1, "Speed");
                        alfont_textprintf_aa_ex(screen, arial, 10, 165, 16773495, -1, "Faith");
                        alfont_textprintf_aa_ex(screen, arial, 10, 185, 16773495, -1, "Inteligence");
                        alfont_textprintf_aa_ex(screen, arial, 10, 205, 11340544, -1, "Resistance");
                        alfont_textprintf_aa_ex(screen, arial, 10, 225, 16773495, -1, "Vitality");
                        break;
                //vitality
                case 6: alfont_textprintf_aa_ex(screen, arial, 10, 105, 16773495, -1, "Strength");
                        alfont_textprintf_aa_ex(screen, arial, 10, 125, 16773495, -1, "Dexterity");
                        alfont_textprintf_aa_ex(screen, arial, 10, 145, 16773495, -1, "Speed");
                        alfont_textprintf_aa_ex(screen, arial, 10, 165, 16773495, -1, "Faith");
                        alfont_textprintf_aa_ex(screen, arial, 10, 185, 16773495, -1, "Inteligence");
                        alfont_textprintf_aa_ex(screen, arial, 10, 205, 16773495, -1, "Resistance");
                        alfont_textprintf_aa_ex(screen, arial, 10, 225, 11340544, -1, "Vitality");
                        break;
                //error message
                default: allegro_message("levelup error: %d", selected);
                         return;
                
            }
            //input buffer
            clear_keybuf();
            readkey();
            clear_keybuf();
            // when w is pressed menu cursor (selected element) moves up one unless at top
            // same for s but cursor moves down unless at bottom
            if ((key[KEY_W]) && (selected > 0))
            {
                selected -= 1;
            }
            if ((key[KEY_S]) && (selected < 6))
            {
                
                selected += 1;
                
            }
            //space confirms selection. which subtracts experiance points and adds to 	
            //selected level.
            if (key[KEY_SPACE])
            {
                eXP -= (level * 200);
                switch (selected)
                {
                    case 0: str += 1;
                            levelup = 1;
                            level += 1;
                            break;
                    case 1: dex += 1;
                            levelup = 1;
                            level += 1;
                            break;
                    case 2: speed += 1;
                            levelup = 1;
                            level += 1;
                            break;
                    case 3: faith += 1;
                            levelup = 1;
                            level += 1;
                            break;
                    case 4: intel += 1;
                            levelup = 1;
                            level += 1;
                            break;
                    case 5: res += 1;
                            levelup = 1;
                            level += 1;
                            break;
                    case 6: vit += 1;
                            level += 1;
                            levelup = 1;
                            break;
                    default: allegro_message("levelup add error");
                             return;
                }
            
            }
        }  
        //screen is recleared
        blit(buff, screen, 0,0,0,0,300,300);
        destroy_bitmap(buff);
    }
    
    
    return;
}



