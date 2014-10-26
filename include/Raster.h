#pragma once
//TODO: improve Raster
#include "Log.h"
#include <chrono>

namespace TakeOne
{
    class Raster
    {

    public:
        Raster()
        {
            mT1 = std::chrono::high_resolution_clock::now();
        }
        ~Raster()
        {
            mTotal = std::chrono::high_resolution_clock::now() - mT1;
            LOG_MSG("Raster: %9.9f", mTotal.count());
        }
    private:
        std::chrono::high_resolution_clock::time_point mT1;
        std::chrono::duration<double> mTotal;
    };
}