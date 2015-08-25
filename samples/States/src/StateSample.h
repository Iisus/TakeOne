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

    void LoadObject(const string& pObject);
    void AddObject(const string& pObjectName, unique_ptr<RenderNode> pNode);

    CameraNode mCamera;
    shared_ptr<Program> mProgram;

    unordered_map<string, vector<unique_ptr<RenderNode>>> mObjects;

    unordered_map<int, bool> mPressedKeys;

    //customisable
    float mCameraMoveSpeed;
    float mCameraRotateSpeed;

private:
    State* mNextState;
    State* mPrevState;

    int mMouseScroolCallbackHandle;
    int mMouseBtnCallbackHandle;
    int mMousePosCallbackHandle;
    int mKeyboardCallbackHandle;

    float mCameraHorAngle;
    float mCameraVerAngle;
};
