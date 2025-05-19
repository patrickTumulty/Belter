
#include "background_system.h"
#include "pray_system.h"
#include "raylib.h"

static Texture2D texture;

static void start()
{
    texture = LoadTexture("assets/starfield.png");
}

static void stop()
{
    UnloadTexture(texture);
}

static void renderUpdate()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            DrawTexture(texture, texture.width * (i - 2), texture.height * (j - 2), WHITE);
        }
    }
}

void registerBackgroundSystem()
{
    praySystemsRegister((System) {
        .name = "Background",
        .start = start,
        .stop = stop,
        .renderUpdateWorldSpace = renderUpdate,
    });
}
