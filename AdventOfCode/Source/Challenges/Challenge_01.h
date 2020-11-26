#pragma once

#include "Common/Challenge.h"

class CChallenge_01 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static int GetRequiredFuel(int const mass);
    static int GetRecursiveRequiredFuel(int const initialMass);

    static std::string const sm_inputFilePath;
};
