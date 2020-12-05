#include "Challenge_08.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_08::sm_inputFilePath = "Inputs/Input_Challenge_08.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_08::SetUp_FirstPart()
{
    return LoadImageLayers();
}

EErrorCode CChallenge_08::Run_FirstPart()
{
    size_t lowestZeroLayerIdx = 0;
    unsigned int lowestZeroCount = -1;

    for (size_t layerIdx = 0; layerIdx < m_imageLayers.size(); ++layerIdx)
    {
        SLayer& imageLayer = m_imageLayers[layerIdx];
        unsigned int zeroCount = 0;

        for (size_t heightIdx = 0; heightIdx < LAYER_HEIGHT; ++heightIdx)
        {
            for (size_t widthIdx = 0; widthIdx < LAYER_WIDTH; ++widthIdx)
            {
                int const dataValue = imageLayer.m_data[heightIdx][widthIdx];
                if (dataValue == 0)
                {
                    ++zeroCount;
                }
            }
        }

        if (zeroCount < lowestZeroCount)
        {
            lowestZeroLayerIdx = layerIdx;
            lowestZeroCount = zeroCount;
        }
    }

    unsigned int oneCount = 0;
    unsigned int twoCount = 0;
    SLayer& imageLayer = m_imageLayers[lowestZeroLayerIdx];

    for (size_t heightIdx = 0; heightIdx < LAYER_HEIGHT; ++heightIdx)
    {
        for (size_t widthIdx = 0; widthIdx < LAYER_WIDTH; ++widthIdx)
        {
            int const dataValue = imageLayer.m_data[heightIdx][widthIdx];
            if (dataValue == 1)
            {
                ++oneCount;
            }
            else if (dataValue == 2)
            {
                ++twoCount;
            }
        }
    }

    int const oneTwoProduct = oneCount * twoCount;
    std::cout << "Product value = " << oneTwoProduct << std::endl;

    return EErrorCode::Success;
}

EErrorCode CChallenge_08::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_08::SetUp_SecondPart()
{
    return LoadImageLayers();
}

EErrorCode CChallenge_08::Run_SecondPart()
{
    SLayer outputImage;
    for (size_t heightIdx = 0; heightIdx < LAYER_HEIGHT; ++heightIdx)
    {
        for (size_t widthIdx = 0; widthIdx < LAYER_WIDTH; ++widthIdx)
        {
            for (size_t layerIdx = 0; layerIdx < m_imageLayers.size(); ++layerIdx)
            {
                outputImage.m_data[heightIdx][widthIdx] = m_imageLayers[layerIdx].m_data[heightIdx][widthIdx];
                if (outputImage.m_data[heightIdx][widthIdx] != 2)
                {
                    break;
                }
            }
        }
    }

    for (size_t heightIdx = 0; heightIdx < LAYER_HEIGHT; ++heightIdx)
    {
        for (size_t widthIdx = 0; widthIdx < LAYER_WIDTH; ++widthIdx)
        {
            switch (outputImage.m_data[heightIdx][widthIdx])
            {
            case 0:
                std::cout << ' ';
                break;

            case 1:
                std::cout << '#';
                break;

            default:
                std::cout << 'X';
                break;
            }
        }
        std::cout << std::endl;
    }
    return EErrorCode::Success;
}

EErrorCode CChallenge_08::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_08::LoadImageLayers()
{
    std::string line;
    EErrorCode const readErrorCode = FileHelper::ReadFirstLine(sm_inputFilePath, line);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    size_t const dataSize = line.size();
    size_t const layerCount = dataSize / (LAYER_HEIGHT * LAYER_WIDTH);

    m_imageLayers.resize(layerCount);
    for (size_t layerIdx = 0; layerIdx < layerCount; ++layerIdx)
    {
        SLayer& imageLayer = m_imageLayers[layerIdx];
        for (size_t heightIdx = 0; heightIdx < LAYER_HEIGHT; ++heightIdx)
        {
            for (size_t widthIdx = 0; widthIdx < LAYER_WIDTH; ++widthIdx)
            {
                size_t const dataIdx = (layerIdx * LAYER_HEIGHT * LAYER_WIDTH) + (heightIdx * LAYER_WIDTH) + widthIdx;
                imageLayer.m_data[heightIdx][widthIdx] = static_cast<int>(line[dataIdx]) - 48;
            }
        }
    }

    return EErrorCode::Success;
}
