#pragma once

#include "Common/Challenge.h"

class CChallenge_02 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadIntcodeProgramMemory();
    static EErrorCode RunIntcodeProgram(int* programMemory);

    static std::string const sm_inputFilePath;
    int* m_initialProgramMemory = nullptr;
    size_t m_programSize = 0;
};