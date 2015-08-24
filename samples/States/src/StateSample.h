#pragma once

#include "SampleUtil.h"
#include "State.h"
#include "CameraNode.h"
#include "RenderNode.h"
#include "Program.h"

class StateSample : public State
{
public:
    StateSample(Engine* pEngine);

    void SetNextState(State* pNextState);
    void SetPrevState(State* pPrevState);

    virtual void Enter();
    virtual void Exit();

    virtual void HandleEvents();
    virtual void Update();
    virtual void Draw();

protected:

    virtual void MouseScrool(double pXOffset, double pYOffset) {}
    virtual void MouseBtnPress(int pButton, int pAction, int pMods) {}
    virtual void MousePos(double pXPos, double pYPos) {}
    virtual void Keyboard(int pKey, int pScancode, int pAction, int pMods) {}

    void LoadScene(const string& pScene);
    void AddNode(unique_ptr<RenderNode> pNode);

    CameraNode mCamera;
    shared_ptr<Program> mProgram;

    vector<unique_ptr<RenderNode>> mObjectNodes;

    unordered_map<int, bool> mPressedKeys;

    //customisable
    float mCameraMoveSpeed;
    float mCameraRotateSpeed;

private:
    void SetupObjects();
    void UpdateInput();

    State* mNextState;
    State* mPrevState;

    int mMouseScroolCallbackHandle;
    int mMouseBtnCallbackHandle;
    int mMousePosCallbackHandle;
    int mKeyboardCallbackHandle;

    float mCameraHorAngle;
    float mCameraVerAngle;
};
