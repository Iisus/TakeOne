#pragma once

#include "SampleUtil.h"
#include "State.h"
#include "CameraNode.h"

class MainState : public State
{
public:

    MainState(Engine* pEngine);

    virtual void Enter();
    virtual void Exit();

    virtual void HandleEvents();
    virtual void Update();
    virtual void Draw();

private:
    CameraNode mCamera;
};
