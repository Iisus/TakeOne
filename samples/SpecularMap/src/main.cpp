#include "SampleUtil.h"

void Update(double Dt);
void Draw();

int main()
{
    Engine engine(1024, 768, "TakeOne");
    DefaultRes defaultRes(SampleUtil::RES_FOLDER);

    engine.SetUpdateCallback(Update);
    engine.SetDrawCallback(Draw);

    engine.Run();

    return 0;
}

void Update(double Dt)
{

}

void Draw()
{

}
