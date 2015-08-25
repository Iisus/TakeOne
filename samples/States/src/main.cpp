#include "SampleUtil.h"
#include "StateCube.h"
#include "StateSphere.h"
#include "StateObjects.h"
#include "StateFPS.h"


int main()
{
    Engine engine (1024, 768, "TakeOne");

    engine.Init(false);

    StateCube stateCube(&engine);
    StateSphere stateSphere(&engine);
    StateObjects stateObjects(&engine, "Armchair");
    StateFPS stateFPS(&engine);

    stateCube.SetNextState(&stateSphere);
    stateCube.SetPrevState(&stateFPS);

    stateSphere.SetNextState(&stateObjects);
    stateSphere.SetPrevState(&stateCube);

    stateObjects.SetNextState(&stateFPS);
    stateObjects.SetPrevState(&stateSphere);

    stateFPS.SetNextState(&stateCube);
    stateFPS.SetPrevState(&stateObjects);

    engine.PushState(&stateFPS);

    engine.Run();

    engine.Cleanup();

    return 0;
}
