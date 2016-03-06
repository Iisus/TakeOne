#include "SampleUtil.h"
#include "StateCube.h"
#include "StateSphere.h"
#include "StateObjects.h"
#include "StateMedievalCity.h"
#include "StateFPS.h"
#include "StateSolarSystem.h"


int main()
{
    Engine engine (1024, 768, "TakeOne");

    engine.Init(true);

    StateCube stateCube(&engine);
    //StateSphere stateSphere(&engine);
    StateObjects stateObjects(&engine, "Armchair");
    StateMedievalCity stateMedievalCity(&engine);
    StateFPS stateFPS(&engine);
    StateSolarSystem stateSolarSystem(&engine);

    stateCube.SetPrevState(&stateSolarSystem);
    stateCube.SetNextState(&stateObjects);

    //stateSphere.SetPrevState(&stateCube);
    //stateSphere.SetNextState(&stateObjects);

    stateObjects.SetPrevState(&stateCube);
    stateObjects.SetNextState(&stateMedievalCity);

    stateMedievalCity.SetPrevState(&stateObjects);
    stateMedievalCity.SetNextState(&stateFPS);

    stateFPS.SetPrevState(&stateMedievalCity);
    stateFPS.SetNextState(&stateSolarSystem);

    stateSolarSystem.SetPrevState(&stateFPS);
    stateSolarSystem.SetNextState(&stateCube);

    engine.PushState(&stateCube);

    engine.Run();

    engine.Cleanup();

    return 0;
}
