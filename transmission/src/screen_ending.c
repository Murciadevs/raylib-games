/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

#include <string.h>
#include <stdlib.h>

#define MAX_TITLE_CHAR 256
#define MAX_SUBTITLE_CHAR 256

//----------------------------------------------------------------------------------
// Local Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

static Texture2D texBackground = { 0 };
static Texture2D texNewspaper = { 0 };
static Texture2D texVignette = { 0 };
static Sound fxNews = { 0 };
static Font fontNews = { 0 };

static float rotation = 0.1f;
static float scale = 0.05f;
static int state = 0;

static Mission *missions = NULL;
static char headline[MAX_TITLE_CHAR] = "\0";

static char *codingWords[MAX_CODING_WORDS] = {
    "pollo\0",
    "conejo\0",
    "huevo\0",
    "nido\0",
    "aire\0",
    "armario\0",
    "agujero\0",
    "platano\0",
    "pastel\0",
    "mercado\0",
    "raton\0",
    "melon\0",
};

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;

    rotation = 0.1f;
    scale = 0.05f;
    state = 0;

    texBackground = LoadTexture("resources/textures/ending_background.png");
    texVignette = LoadTexture("resources/textures/message_vignette.png");
    fxNews = LoadSound("resources/audio/fx_batman.ogg");

    missions = LoadMissions("resources/missions.txt");
    int wordsCount = missions[currentMission].wordsCount;

    strcpy(headline, missions[currentMission].msg);     // Base headline
    int len = strlen(headline);

    // Remove @ from headline
    // TODO: Also remove additional spaces
    for (int i = 0; i < len; i++)
    {
        if (headline[i] == '@') headline[i] = ' ';
    }

    for (int i = 0; i < wordsCount; i++)
    {
        if (messageWords[i].id != missions[currentMission].sols[i])
        {
            // WARNING: It fails if the last sentence word has a '.' after space
            char *title = TextReplace(headline, messageWords[i].text, codingWords[messageWords[i].id]);

            if (title != NULL)
            {
                strcpy(headline, title);     // Base headline updated
                free(title);
            }
        }
    }

    TraceLog(LOG_WARNING, "Titular: %s", headline);

    // Generate newspaper with title and subtitle
    Image imNewspaper = LoadImage("resources/textures/ending_newspaper.png");
    fontNews = LoadFontEx("resources/fonts/Lora-Bold.ttf", 32, 0, 250);
    ImageDrawTextEx(&imNewspaper, fontNews, headline, (Vector2){ 50, 220 }, fontNews.baseSize, 0, DARKGRAY);

    texNewspaper = LoadTextureFromImage(imNewspaper);
    //UnloadFont(fontNews);
    UnloadImage(imNewspaper);
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    framesCounter++;

    if (framesCounter == 10) PlaySound(fxNews);

    if (state == 0)
    {
        rotation += 18.0f;
        scale += 0.0096f;

        if (scale >= 1.0f)
        {
            scale = 1.0f;
            state = 1;
        }
    }

    if ((state == 1) && (IsKeyPressed(KEY_ENTER) || IsButtonPressed()))
    {
        currentMission++;

        if (currentMission >= totalMissions)
        {
            finishScreen = 2;
            currentMission = 0;
        }
        else finishScreen = 1;
    }
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    DrawTexture(texBackground, 0, 0, WHITE);

    DrawTexturePro(texNewspaper, (Rectangle){ 0, 0, texNewspaper.width, texNewspaper.height },
                   (Rectangle){ GetScreenWidth()/2, GetScreenHeight()/2, texNewspaper.width*scale, texNewspaper.height*scale },
                   (Vector2){ (float)texNewspaper.width*scale/2, (float)texNewspaper.height*scale/2 }, rotation, WHITE);

    DrawTextureEx(texVignette, (Vector2){ 0, 0 }, 0.0f, 2.0f, WHITE);

    // Draw debug information
    DrawTextEx(fontNews, headline, (Vector2){ 10, 10 }, fontNews.baseSize, 0, RAYWHITE);

    for (int i = 0; i < missions[currentMission].wordsCount; i++)
    {
        DrawText(codingWords[messageWords[i].id], 10, 60 + 30*i, 20, (messageWords[i].id == missions[currentMission].sols[i]) ? GREEN : RED);
    }

    if (state == 1) DrawButton("continuar");
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    UnloadTexture(texBackground);
    UnloadTexture(texNewspaper);
    UnloadTexture(texVignette);

    UnloadSound(fxNews);
    free(missions);
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}
