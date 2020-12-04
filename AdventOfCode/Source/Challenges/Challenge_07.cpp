#include "Challenge_07.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_07::sm_inputFilePath = "Inputs/Input_Challenge_07.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::SetUp_FirstPart()
{
    GeneratePhasePermutations(0);
    return LoadInitialMemory();
}

EErrorCode CChallenge_07::Run_FirstPart()
{
    size_t const lastProgramIdx = AMPLIFIER_COUNT - 1;

    EErrorCode programErrorCode = EErrorCode::Success;
    int highestThrusterSignal = 0;

    for (std::vector<int> const& permutation : m_phasePermutations)
    {
        for (size_t programIdx = 0; programIdx < AMPLIFIER_COUNT; ++programIdx)
        {
            m_intcodePrograms[programIdx].ResetProgram();
            m_intcodePrograms[programIdx].PushInput(permutation[programIdx]);
        }

        m_intcodePrograms[0].PushInput(0);

        size_t programIdx = 0;
        while (!m_intcodePrograms[programIdx].HasTerminated() && programErrorCode == EErrorCode::Success)
        {
            programErrorCode = m_intcodePrograms[programIdx].RunNextOperation();

            if (m_intcodePrograms[programIdx].HasOutput())
            {
                int const outputSignal = m_intcodePrograms[programIdx].PopOutput();
                if (programIdx == lastProgramIdx)
                {
                    //std::cout << "Output signal = " << outputSignal << std::endl;
                    if (highestThrusterSignal < outputSignal)
                    {
                        highestThrusterSignal = outputSignal;
                    }
                    break;
                }
                else
                {
                    ++programIdx;
                    m_intcodePrograms[programIdx].PushInput(outputSignal);
                }
            }
        }
    }

    if (programErrorCode == EErrorCode::Success)
    {
        std::cout << "Highest thruster signal = " << highestThrusterSignal << std::endl;
    }
    return programErrorCode;
}

EErrorCode CChallenge_07::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::SetUp_SecondPart()
{
    GeneratePhasePermutations(5);
    return LoadInitialMemory();
}

EErrorCode CChallenge_07::Run_SecondPart()
{
    size_t const lastProgramIdx = AMPLIFIER_COUNT - 1;

    EErrorCode programErrorCode = EErrorCode::Success;
    int highestThrusterSignal = 0;

    for (std::vector<int> const& permutation : m_phasePermutations)
    {
        std::cout << "Permutation = ( ";
        for (int const val : permutation)
        {
            std::cout << val << " ";
        }
        std::cout << ")" << std::endl;

        for (size_t programIdx = 0; programIdx < AMPLIFIER_COUNT; ++programIdx)
        {
            m_intcodePrograms[programIdx].ResetProgram();
            m_intcodePrograms[programIdx].PushInput(permutation[programIdx]);
        }

        m_intcodePrograms[0].PushInput(0);

        size_t programIdx = 0;
        while (!m_intcodePrograms[programIdx].HasTerminated() && programErrorCode == EErrorCode::Success)
        {
            programErrorCode = m_intcodePrograms[programIdx].RunNextOperation();

            if (m_intcodePrograms[programIdx].HasOutput())
            {
                int const outputSignal = m_intcodePrograms[programIdx].PopOutput();
                if (programIdx == lastProgramIdx && highestThrusterSignal < outputSignal)
                {
                    highestThrusterSignal = outputSignal;
                }

                programIdx = (programIdx + 1) % AMPLIFIER_COUNT;
                m_intcodePrograms[programIdx].PushInput(outputSignal);
            }
        }
    }

    if (programErrorCode == EErrorCode::Success)
    {
        std::cout << "Highest thruster signal = " << highestThrusterSignal << std::endl;
    }
    return programErrorCode;
}

EErrorCode CChallenge_07::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_07::LoadInitialMemory()
{
    std::string line;
    EErrorCode const readErrorCode = FileHelper::ReadFirstLine(sm_inputFilePath, line);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    std::vector<std::string> items;
    FileHelper::SplitLine(line, ",", items);

    size_t const memorySize = items.size();
    int* initialMemory = new int[memorySize];

    for (size_t memoryIdx = 0; memoryIdx < memorySize; ++memoryIdx)
    {
        initialMemory[memoryIdx] = atoi(items[memoryIdx].c_str());
    }

    for (size_t programIdx = 0; programIdx < AMPLIFIER_COUNT; ++programIdx)
    {
        m_intcodePrograms[programIdx].SetInitialMemory(initialMemory, memorySize);
    }

    delete[] initialMemory;

    std::cout << "Loaded initial memory (" << memorySize << ")" << std::endl;
    return EErrorCode::Success;
}

void CChallenge_07::GeneratePhasePermutations(int const firstValue)
{
    std::vector<int> currentPermutation;
    std::vector<int> availablePhaseValues;

    for (int phaseCount = 0; phaseCount < AMPLIFIER_COUNT; ++phaseCount)
    {
        int const phaseValue = firstValue + phaseCount;

        currentPermutation.push_back(-1);
        availablePhaseValues.push_back(phaseValue);
    }

    m_phasePermutations.clear();
    GeneratePhasePermutations_Recursive(availablePhaseValues, currentPermutation, 0);

    std::cout << "Generated permutations (" << m_phasePermutations.size() << ")" << std::endl;
}

void CChallenge_07::GeneratePhasePermutations_Recursive(std::vector<int>& availablePhaseValues, std::vector<int>& phasePermutation, size_t const permutationIdx)
{
    if (permutationIdx < AMPLIFIER_COUNT)
    {
        for (size_t phaseValueIdx = 0; phaseValueIdx < AMPLIFIER_COUNT; ++phaseValueIdx)
        {
            if (availablePhaseValues[phaseValueIdx] >= 0)
            {
                int const phaseValue = availablePhaseValues[phaseValueIdx];

                availablePhaseValues[phaseValueIdx] = -1;
                phasePermutation[permutationIdx] = phaseValue;

                GeneratePhasePermutations_Recursive(availablePhaseValues, phasePermutation, permutationIdx + 1);

                availablePhaseValues[phaseValueIdx] = phaseValue;
                phasePermutation[permutationIdx] = -1;
            }
        }
    }
    else
    {
        m_phasePermutations.push_back(phasePermutation);
    }
}
