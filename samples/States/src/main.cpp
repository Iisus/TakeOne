#include "SampleUtil.h"
#include "StateCube.h"
#include "StateSphere.h"
#include "StateObjects.h"
#include "StateFPS.h"
#include "StateSolarSystem.h"


int main()
{
    Engine engine (1024, 768, "TakeOne");

    engine.Init(true);

    StateCube stateCube(&engine);
    StateSphere stateSphere(&engine);
    StateObjects stateObjects(&engine, "Armchair");
    StateFPS stateFPS(&engine);
    StateSolarSystem stateSolarSystem(&engine);

    stateCube.SetPrevState(&stateSolarSystem);
    stateCube.SetNextState(&stateSphere);

    stateSphere.SetPrevState(&stateCube);
    stateSphere.SetNextState(&stateObjects);

    stateObjects.SetPrevState(&stateSphere);
    stateObjects.SetNextState(&stateFPS);

    stateFPS.SetPrevState(&stateObjects);
    stateFPS.SetNextState(&stateSolarSystem);

    stateSolarSystem.SetPrevState(&stateFPS);
    stateSolarSystem.SetNextState(&stateCube);

    engine.PushState(&stateCube);

    engine.Run();

    engine.Cleanup();

    return 0;
}
