#pragma once

namespace TakeOne
{
    class Engine;

    class State
    {
    public:

        State(Engine* pEngine) : mEngine(pEngine) {}

        virtual void Enter() = 0;
        virtual void Exit() = 0;

        virtual void HandleEvents() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;

    protected:
        Engine* mEngine;
    };
}
