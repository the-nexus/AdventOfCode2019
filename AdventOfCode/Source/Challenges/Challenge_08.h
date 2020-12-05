#pragma once

#include "Common/Challenge.h"

#define LAYER_HEIGHT 6
#define LAYER_WIDTH 25

class CChallenge_08 : public CChallenge
{
private:
    struct SLayer
    {
        int m_data[LAYER_HEIGHT][LAYER_WIDTH];
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadImageLayers();

    static std::string const sm_inputFilePath;
    std::vector<SLayer> m_imageLayers;
};
