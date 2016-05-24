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


//battle function is BIG. runs entire battle instance
int battle (int enemynum)
{

    //runs a loading screen since music sometimes takes a while to load
    loadScreen();
    //bitmaps, font, and music are loaded and other variables declared
    BITMAP *backing = NULL, *player = NULL, *enemy = NULL, *pyromancy = NULL, *buffer = create_bitmap(300,300);
    ALFONT_FONT *arial = alfont_load_font("C:/Windows/Fonts/arial.ttf");
    MIDI *battletheme;
    alfont_set_font_size(arial, 25);
    int enemyHealth = 50;
    int enemyAttack;
    int attack, turntaken;
    int turncount;
    int k, l, p;
    int hitNumber;
    int damageMod;
    int music= 0;

    
    
    //only 1 battle area for now. planning to make more later
    backing = load_bitmap("Battlestage.bmp", NULL);
    
    //checks to see if battle is a boss battle (enemy code 4 is boss battle)
    if (enemynum == 4)
    {
        //if battle is boss battle, different bosses are loaded for each level.
        //different bitmaps and stats are declared for each one
        if (mapnumber == 0)
        {
            enemy = load_bitmap("ASSdemon.bmp", NULL);
            enemyHealth = 500;
            damageMod = 2;
        }
        if (mapnumber == 1)
        {
            enemy = load_bitmap("taurus.bmp", NULL);
            enemyHealth = 1000;
            damageMod = 1;
        }
        if (mapnumber == 2)
        {
            enemy = load_bitmap("bell garg.bmp", NULL);
            enemyHealth = 300;
            damageMod = 6;
        }
        if (mapnumber == 3)
        {
            enemy = load_bitmap("capra.bmp", NULL);
            enemyHealth = 700;
            damageMod = 10;
        }
        if (mapnumber == 4)
        {
            enemy = load_bitmap("GapingDragon.bmp", NULL);
            enemyHealth = 1200;
            damageMod = 6;
        }
        if (mapnumber == 5)
        {
            enemy = load_bitmap("quelaag.bmp", NULL);
            enemyHealth = 1500;
            damageMod = 9;
        }
    }
    
    //if not a boss battle one of 3 enemies are loaded based on the enemy number
    if (enemynum == 0)
    {
        enemy = load_bitmap("hollow.bmp", NULL);
        damageMod = 0;
    }
    if (enemynum == 1)
    {
        enemy = load_bitmap("hollowKnight.bmp", NULL);
        enemyHealth = 100;
        damageMod = 0;
    }
    if (enemynum == 2)
    {
        enemy = load_bitmap("knight.bmp", NULL);
        enemyHealth = 100;
        damageMod = 1;
    }
    //player and magic bitmaps loaded
    player = load_bitmap("solaire2.bmp", NULL);
    pyromancy = load_bitmap("pyro.bmp", NULL);
    
    //rand is seeded with time
    srand(time(NULL));
    
    //music track is randomized
    music = rand() % 2;
    if (music == 0)
    {
        battletheme = load_midi("ffxiii_prelude.mid");
    }
    if (music == 1)
    {
        //gonna get rid of this one at some point 
        battletheme = load_midi("oldking.mid");
    }
    
    
    //initial printing
    masked_blit(backing, buffer, 0,0,0,0,300,300);
    masked_blit(player, buffer, 0,0,100,150,50,50);
    masked_blit(enemy, buffer, 0,0,200,100,100,100);
    alfont_textprintf_aa_ex(buffer, arial, 10, 270, 0xFFFFFF, -1, "(%d/%d hp)",  health, (80 + (vit * 20)));
    blit(buffer, screen,0,0,0,0,300,300);
    srand(time(NULL));
    //main loop
    //music starts playing here
    play_midi(battletheme, 1);
    //battle continues until player dies or enemy dies
    //its possible for both die in the same turn. in which case player loses
    while ((health > 0) && (enemyHealth > 0))
    {
        
		//1 - 4 on the keypad are used for attacks instead of a menu for a simpler UI
        clear_keybuf();
        attack = readkey() >> 8;
        clear_keybuf();
        
		//switch statement for user attacks
        switch (attack)
        {

            //heavy attack
            case KEY_2_PAD: printf("attack 1!\n");
                            //character moves forward to enemy
                            for (k = 0; k < 51; k++)
            		        {
            		            masked_blit(backing, buffer, 0,0,0,0,300,300);
    					        masked_blit(player, buffer, 0,0,(100 + (k * 2)),150,50,50);
    					        masked_blit(enemy, buffer, 0,0,200,100,100,100);
    					        alfont_textprintf_aa_ex(buffer, arial, 10, 270, 0xFFFFFF, -1, "(%d/%d hp)",  health, (80 + (vit * 20)));
            		            blit(buffer, screen,0,0,0,0,300,300);
                                sleep(5);
                            }
            		        //player attacks as a function of strength
            		        enemyHealth -= (20 + (15 * str));
            		        //player is returned to normal position
            		        for (k = 50; k > 0; k--)
            		        {
            		            masked_blit(backing, buffer, 0,0,0,0,300,300);
    					        masked_blit(player, buffer, 0,0,(100 + (k * 2)),150,50,50);
    					        masked_blit(enemy, buffer, 0,0,200,100,100,100);
    					        alfont_textprintf_aa_ex(buffer, arial, 10, 270, 0xFFFFFF, -1, "(%d/%d hp)",  health, (80 + (vit * 20)));
            		            blit(buffer, screen,0,0,0,0,300,300);
                                sleep(5);
                            }
            		        //turn taken show that the player has used heir turn
            		        turntaken = 1;
        			        break;

            //speed attack
            case KEY_1_PAD: printf("attack 2!\n");
                            hitNumber = ((speed * 2) + 2);
                            //same as heavy attack except it hits 4 times. and it gets 
                            // 2 extra hits for every time speed is levelled up.
                            for (p = 0; p < hitNumber; p++)
                            {
                                //move
                                for (k = 0; k < 51; k++)
            		            {
           		                    masked_blit(backing, buffer, 0,0,0,0,300,300);
    					            masked_blit(player, buffer, 0,0,(100 + (k * 2)),150,50,50);
    					            masked_blit(enemy, buffer, 0,0,200,100,100,100);
    					            alfont_textprintf_aa_ex(buffer, arial, 10, 270, 0xFFFFFF, -1, "(%d/%d hp)",  health, (80 + (vit * 20)));
                                    blit(buffer, screen,0,0,0,0,300,300);
                                    sleep(2);
                                }
            		            //attack, as a factor of dexterity stat
            		            enemyHealth -= (5 * dex);
              		            //return
              		            for (k = 50; k > 0; k--)
                 	            {
           		                    masked_blit(backing, buffer, 0,0,0,0,300,300);
   		       		   	            masked_blit(player, buffer, 0,0,(100 + (k * 2)),150,50,50);
  					                masked_blit(enemy, buffer, 0,0,200,100,100,100);
  					                alfont_textprintf_aa_ex(buffer, arial, 10, 270, 0xFFFFFF, -1, "(%d/%d hp)",  health, (80 + (vit * 20)));
     		                        blit(buffer, screen,0,0,0,0,300,300);
                                    sleep(2);
                                }
                            }
            		        turntaken = 1;
        			        break;

            //MAGIC ATTAK: FIREBALL
            case KEY_3_PAD: printf("attack 3!\n");
                            //fireball checks to make sure player hasn't used all casts
                            //and stil has cast points left. cast points aren't displayed
                            if (magicAttackNum != 0)
                            {
                                //fireball is animated and flies into enemy
                                for (k = 0; k < 60; k++)
                                {
                                    masked_blit(backing, buffer, 0,0,0,0,300,300);
   		       		   	            masked_blit(player, buffer, 0,0,100,150,50,50);
  					                masked_blit(enemy, buffer, 0,0,200,100,100,100);
  					                alfont_textprintf_aa_ex(buffer, arial, 10, 270, 0xFF0000, -1, "(%d/%d hp)",  health, (80 + (vit * 20)));
                                    masked_blit(pyromancy, buffer, 0,0,(100 + (k * 2)),150,40,40);
                                    blit(buffer, screen,0,0,0,0,300,300);
                                    sleep(5);    
                                }
                                //attack, as a function of int
                                enemyHealth -= (25 * intel);
                                //lowers cast points by 1
                                magicAttackNum -= 1;
                                
                                
                            }
                            //if no cast points are left then it prints a error message
                            else
                            {
                                masked_blit(backing, buffer, 0,0,0,0,300,300);
     		   	                masked_blit(player, buffer, 0,0,100,150,50,50);
                                masked_blit(enemy, buffer, 0,0,200,100,100,100);
                                alfont_textprintf_aa_ex(buffer, arial, 20, 20, 0xFF0000, -1, "OUT OF ATTACK SPELLS");
                                blit(buffer, screen,0,0,0,0,300,300);
                                clear_keybuf();
                                readkey();
                                clear_keybuf();
                            }
                            turntaken = 1;
                            break;
            //HEAL MAGIC
            case KEY_4_PAD: printf("heal!\n");
                            //checks to see if you have heal cast ponts left
                            if (magicHealNum != 0)
                            {
                                //heals as a function of faith stat
                                health += (40 + (10 * faith));
                                //if heath is healed to over max health its reset to max
                                if (health > (80 + (vit * 20)))
                                {
                                    health = 80 + (vit * 20);
                                }
                                magicHealNum -= 1;
                                
                            }
                            else
                            {
                                 alfont_textprintf_aa_ex(buffer, arial, 20, 20, 0xFF0000, -1, "OUT OF HEAL SPELLS");
                                 blit(buffer, screen,0,0,0,0,300,300);
                                 clear_keybuf();
                                 readkey();
                                 clear_keybuf();
                            }
                            turntaken = 1;
                            break;

            //default states player has not taken turn
            default: turntaken = 0;
        }
    	

        //enemy attack is randomised
        enemyAttack = rand() % 2;
        
        //enemy only takes a turn if player has taken a turn
        if (turntaken == 1)
    	{
            
            switch (enemyAttack)
    	    {
    	        //heavy enemy attack
                case 0: health -= ((5 + (5 * damageMod)) - ((res - 1) * 5));
    	                printf("\n enemydamage: %d", ((5 + (5 * damageMod)) - ((res - 1) * 5)));
    	                if ((5 + (5 * damageMod)) - ((res - 1) * 5) < 0)
    	                {
    	                    health += ((5 + (5 * damageMod)) - ((res - 1) * 5));
                        }
                        break;
    	        //light enemy attack
                case 1: health -= ((2 + (5 * damageMod)) - ((res - 1) * 5));
    	                //attack damage is a function of the enemy's DamageMod stat
    	                //damage is negated as a function of resistance stat
                        printf("\n enemydamage: %d", ((2 + (5 * damageMod)) - ((res - 1) * 5)));
    	                
                        //if damage resisted is more than damage dealt
                        //then no damage happens. there was a bug where res
                        //could make the enemy do negative damage, healing the user
                        if ((2 + (5 * damageMod)) - ((res - 1) * 5) < 0)
    	                {
    	                    health += ((2 + (5 * damageMod)) - ((res - 1) * 5));
                        }
                        break;
    	    }
        }
    	
        
        //everything is reprinted in rest position
        printf("\nhealth: %d %d\n", health, enemyHealth);
        masked_blit(backing, buffer, 0,0,0,0,300,300);
    	masked_blit(player, buffer, 0,0,100,150,50,50);
    	masked_blit(enemy, buffer, 0,0,200,100,100,100);
    	alfont_textprintf_aa_ex(buffer, arial, 10, 270, 0xFFFFFF, -1, "(%d/%d hp)",  health, (80 + (vit * 20)));
    	blit(buffer, screen,0,0,0,0,300,300);
        clear_keybuf();
        
        	   
    }
    destroy_bitmap(backing);
    destroy_bitmap(player);
    destroy_bitmap(enemy);
    destroy_bitmap(pyromancy);
    destroy_bitmap(buffer);
    
    //screen cleared 
    BITMAP *buff = create_bitmap(300,300);
    clear_bitmap(buff);
    masked_blit(buff, screen, 0, 0, 0, 0, 300, 300);
    destroy_bitmap(buff);

    //checks tyo see if player died. if player dies it returns a loss
    if (health <= 0)
    {
        alfont_textprintf_aa_ex(screen, arial, 100, 120, 0xFF0000, -1, "YOU DIED");
        clear_keybuf();
        readkey();
        clear_keybuf();
        stop_midi();
        destroy_midi(battletheme);
        return 0;
    }
    //if player did not die player is given exp as a factor of what stage they're on
    if (enemynum == 4)
    {
        eXP += 1000 * (mapnumber + 1);
    }
    if (enemynum == 2)
    {
        eXP += 200 * (mapnumber + 1);
    }
    if (enemynum == 1)
    {
        eXP += 100 * (mapnumber + 1);
    }
    if (enemynum == 0)
    {
        eXP += 50 * (mapnumber + 1);
    }
    stop_midi();
    destroy_midi(battletheme);
    musique = 1;
    return 1;
}



int enemyCheck()
{

    srand(time(NULL));
    int enemy;
    enemy = rand() % 100;
    return enemy;
}
