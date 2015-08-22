#pragma once

#include "SampleUtil.h"
#include "State.h"
#include "CameraNode.h"
#include "RenderNode.h"
#include "Program.h"
#include "Primitives.h"

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
    void SetupBoxRenderer();
    void UpdateInput();

    CameraNode mCamera;
    shared_ptr<Program> mProgram;

    shared_ptr<BoxRenderObject> mBoxRenderer;
    RenderNode mBox1Node;

    std::unordered_map<int, bool> mPressedKeys;
};
