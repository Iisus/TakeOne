#pragma once

#include "SampleUtil.h"
#include "State.h"
#include "CameraNode.h"
#include "RenderNode.h"
#include "Program.h"
#include "Primitives.h"

class StateObjects : public State
{
public:
    StateObjects(Engine* pEngine, string pScene);

    void SetNextState(State* pNextState);
    void SetPrevState(State* pPrevState);

    virtual void Enter();
    virtual void Exit();

    virtual void HandleEvents();
    virtual void Update();
    virtual void Draw();

private:
    void SetupObjects();
    void UpdateInput();

    State* mNextState;
    State* mPrevState;

    CameraNode mCamera;
    shared_ptr<Program> mProgram;

    vector<RenderNode> mObjectNodes;

    int mMouseScroolCallbackHandle;
    int mMousePosCallbackHandle;
    int mKeyboardCallbackHandle;
    unordered_map<int, bool> mPressedKeys;

    string mScene;
};
