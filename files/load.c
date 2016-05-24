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




//allegro, alfont, sound, and the screen are initialized 
void init()
{

    allegro_init();
    alfont_init();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");
    install_timer();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 300,300,0,0);
}




//displays a "loading" screen
void loadScreen()
{

    BITMAP *load = NULL;
    load = load_bitmap("load.bmp", NULL);
    blit(load, screen, 0,0,0,0,300,300);
    destroy_bitmap(load);
}







//loads map data from file
void loadmap (int data[100][100])
{

    FILE *fptr;
    int k, l;
    
    //mapnumber printed for debug
    printf("\n%d\n", mapnumber);
    //chacks map number and loads corresponding data file
    if (mapnumber == 0)
    {
        fptr = fopen("AsylumData.txt", "r");
    }
    if (mapnumber == 1)
    {
        fptr = fopen("BurgData.txt", "r");
        
    }
    if (mapnumber == 2)
    {
        fptr = fopen("ParishData.txt", "r");
    }
    if (mapnumber == 3)
    {
        fptr = fopen("LowerData.txt", "r");
    }
    if (mapnumber == 4)
    {
        fptr = fopen("DepthsData.txt", "r");
    }
    if (mapnumber == 5)
    {
        fptr = fopen("BlightTown.txt", "r");
    }
    //loops through data files (60X40) and loads the file data into the data array
    for (k = 0; k < 40; k++)
    {
        for (l = 0; l < 60; l++)
        {
            fscanf(fptr, "%d ", &data[l][k]);
        }
    }
    fclose(fptr);
    return;
}






//draws tile textures into the map bitmap
BITMAP *drawmap(int data[100][100])
{

    //texture bitmaps are declared and loaded
    BITMAP  *stoneFloor = NULL, *stoneWall = NULL, *stoneWater = NULL, *dirtWall = NULL;
    BITMAP  *grass = NULL, *bonfire = NULL, *map = NULL, *bossDoor = NULL, *sludge = NULL;
    map = create_bitmap(960,640);
    stoneWater = load_bitmap("water_txtr.bmp", NULL);
    grass = load_bitmap("grass_txtr.bmp", NULL);
    stoneWall = load_bitmap("wall_txtr.bmp", NULL);
    stoneFloor = load_bitmap("floor_txtr.bmp", NULL);
    bonfire = load_bitmap("bonfire_txtr.bmp", NULL);
    bossDoor = load_bitmap("FOG_txtr.bmp", NULL);
    dirtWall = load_bitmap("dirtwall_txtr.bmp", NULL);
    sludge = load_bitmap("sludge_txtr.bmp", NULL);
    
	//checks to make sure textures load correctly
    if (grass == NULL)
    {
        allegro_message("missing files");
        return NULL;
    }
    if (stoneFloor == NULL)
    {
        allegro_message("missing files");
        return NULL;
    }
    if (stoneWall == NULL)
    {
        allegro_message("missing files");
        return NULL;
    }
    if (stoneWater == NULL)
    {
        allegro_message("missing files");
        return NULL;
    }
    if (stoneWater == NULL)
    {
        allegro_message("missing files");
        return NULL;
    }
    if (bossDoor == NULL)
    {
        allegro_message("missing THIS? files");
        return NULL;
    }
    
    if (dirtWall == NULL)
    {
        allegro_message("missing files");
        return NULL;
    }
    if (sludge == NULL)
    {
        allegro_message("missing files");
        return NULL;
    }
    

    int k;
    int l;
    //loops through matrix printing texture for each corresponding map-data code
    
    for (k = 0; k < 40; k++)
    {
        for (l = 0; l < 60; l++)
        {
            
            if (data[l][k] == 0)
            {
                masked_blit(stoneWall, map, 0,0,(l * 16),(k * 16),16,16);
            }
            if (data[l][k] == 1)
            {
                masked_blit(stoneFloor, map, 0,0,(l * 16),(k * 16),16,16);
            }
            if (data[l][k] == 2)
            {
                masked_blit(stoneWater, map, 0,0,(l * 16),(k * 16),16,16);
            }
            if (data[l][k] == 3)
            {
                masked_blit(grass, map, 0,0,(l * 16),(k * 16),16,16);
            }
            if (data[l][k] == 4)
            {
                masked_blit(bossDoor, map, 0,0,(l * 16),(k * 16),16,16);
            }
            if (data[l][k] == 5)
            {
                masked_blit( bonfire, map, 0,0,(l * 16),(k * 16),16,16);
            }
            if (data[l][k] == 6)
            {
                masked_blit( dirtWall, map, 0,0,(l * 16),(k * 16),16,16);
            }
            if (data[l][k] == 7)
            {
                masked_blit( sludge, map, 0,0,(l * 16),(k * 16),16,16);
            }
            
        }
    }
    
    destroy_bitmap(stoneWall);
    destroy_bitmap(stoneFloor);
    destroy_bitmap(stoneWater);
    destroy_bitmap(grass);
    destroy_bitmap(bossDoor);
    destroy_bitmap(bonfire);
    destroy_bitmap(dirtWall);
    destroy_bitmap(sludge);
    //returns fully drawn map to main
    return map;
}
