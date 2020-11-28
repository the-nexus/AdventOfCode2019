#pragma once

#include "Common/Challenge.h"

#define DIGIT_COUNT 6

class CChallenge_04 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadPasswordRange();

    static std::string const sm_inputFilePath;

    unsigned int m_firstPassword = 0;
    unsigned int m_lastPassword = 0;
};
