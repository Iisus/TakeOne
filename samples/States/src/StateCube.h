#pragma once

#include "SampleUtil.h"
#include "State.h"
#include "CameraNode.h"
#include "RenderNode.h"
#include "Program.h"
#include "Primitives.h"

class StateCube : public State
{
public:

    StateCube(Engine* pEngine);

    void SetNextState(State* pNextState);
    void SetPrevState(State* pPrevState);

    virtual void Enter();
    virtual void Exit();

    virtual void HandleEvents();
    virtual void Update();
    virtual void Draw();

private:
    void SetupBoxRenderer();
    void UpdateInput();

    State* mNextState;
    State* mPrevState;

    CameraNode mCamera;
    shared_ptr<Program> mProgram;

    shared_ptr<BoxRenderObject> mBoxRenderer;
    RenderNode mBox1Node;

    int mMouseScroolCallbackHandle;
    int mMousePosCallbackHandle;
    int mKeyboardCallbackHandle;
    std::unordered_map<int, bool> mPressedKeys;
};
