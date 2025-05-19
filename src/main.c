
#include "background_system.h"
#include "camera_system.h"
#include "components.h"
#include "init_system.h"
#include "physics_system.h"
#include "player_controller_system.h"
#include "pray_camera.h"
#include "pray_default_systems.h"
#include "pray_engine.h"
#include "pray_system.h"
#include "raylib.h"
#include "shape_system.h"
#include <sys/types.h>


static void centerDot()
{
    DrawCircle(0, 0, 5, GREEN);
}

int main(void)
{
    prayEngineInitialize();

    registerComponents();

    registerBackgroundSystem();
    registerShapeSystem();
    registerCameraSystem();
    registerPhysicsSystem();
    registerPlayerControllerSystem();
    registerInitSystem();

    System system = {
        .renderUpdateWorldSpace = centerDot,
    };
    praySystemsRegister(system);


    prayRegisterDefaultSystems();

    prayEngineRun();

    prayEngineDestroy();

    return 0;
}
