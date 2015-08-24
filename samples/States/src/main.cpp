#include "SampleUtil.h"
#include "StateCube.h"
#include "StateSphere.h"
#include "StateObjects.h"


int main()
{
    Engine engine (1024, 768, "TakeOne");

    StateCube stateCube(&engine);
    StateSphere stateSphere(&engine);
    StateObjects stateObjects(&engine, "House02");

    stateCube.SetNextState(&stateSphere);
    stateCube.SetPrevState(&stateObjects);

    stateSphere.SetNextState(&stateObjects);
    stateSphere.SetPrevState(&stateCube);

    stateObjects.SetNextState(&stateCube);
    stateObjects.SetPrevState(&stateSphere);

    engine.PushState(&stateSphere);

    engine.Run();

    return 0;
}
