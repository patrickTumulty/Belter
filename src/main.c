
#include "camera_system.h"
#include "components.h"
#include "init_system.h"
#include "physics_system.h"
#include "pray_camera.h"
#include "pray_default_systems.h"
#include "pray_engine.h"
#include "pray_system.h"
#include "shape_system.h"
#include <sys/types.h>


int main(void)
{
    prayEngineInitialize();

    registerComponents();

    registerShapeSystem();
    registerCameraSystem();
    registerPhysicsSystem();
    registerInitSystem();

    prayRegisterDefaultSystems();

    prayEngineRun();

    prayEngineDestroy();

    return 0;
}
