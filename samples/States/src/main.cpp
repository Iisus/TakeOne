#include "SampleUtil.h"
#include "StateCube.h"
#include "StateSphere.h"


int main()
{
    Engine engine (1024, 768, "TakeOne");

    StateCube stateCube(&engine);
    StateSphere stateSphere(&engine);

    stateCube.SetNextState(&stateSphere);
    stateCube.SetPrevState(&stateSphere);

    stateSphere.SetNextState(&stateCube);
    stateSphere.SetPrevState(&stateCube);

    engine.PushState(&stateCube);

    engine.Run();

    return 0;
}
