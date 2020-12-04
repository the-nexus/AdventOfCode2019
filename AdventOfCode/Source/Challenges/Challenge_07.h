#pragma once

#include "Common/Challenge.h"
#include "../Utilities/IntcodeProgram.h"

#define AMPLIFIER_COUNT 5

class CChallenge_07 : public CChallenge
{
private:
    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode LoadInitialMemory();

    void GeneratePhasePermutations(int const firstValue);
    void GeneratePhasePermutations_Recursive(std::vector<int>& availablePhaseValues, std::vector<int>& phasePermutation, size_t const permutationIdx);

    static std::string const sm_inputFilePath;
    CIntcodeProgram m_intcodePrograms[AMPLIFIER_COUNT];
    std::vector<std::vector<int>> m_phasePermutations;
};
