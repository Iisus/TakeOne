#include "SampleUtil.h"

#include "MainState.h"


int main()
{
    Engine engine (1024, 768, "TakeOne");

    engine.PushState(std::make_unique<MainState>(&engine));

    engine.Run();

    return 0;
}
