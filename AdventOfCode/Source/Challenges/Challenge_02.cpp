#include "Challenge_02.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_02::sm_inputFilePath = "Inputs/Input_Challenge_02.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_FirstPart()
{
    return LoadInitialMemory();
}

EErrorCode CChallenge_02::Run_FirstPart()
{
    m_intcodeProgram.SetMemoryAt(1, 12);
    m_intcodeProgram.SetMemoryAt(2, 2);

    EErrorCode programErrorCode = EErrorCode::Success;
    while (!m_intcodeProgram.HasTerminated() && programErrorCode == EErrorCode::Success)
    {
        programErrorCode = m_intcodeProgram.RunNextOperation();
    }

    if (programErrorCode == EErrorCode::Success)
    {
        std::cout << "First integer = " << m_intcodeProgram.GetMemoryAt(0) << std::endl;
    }

    return programErrorCode;
}

EErrorCode CChallenge_02::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_SecondPart()
{
    return LoadInitialMemory();
}

EErrorCode CChallenge_02::Run_SecondPart()
{
    EErrorCode programErrorCode = EErrorCode::Success;
    bool foundPermutation = true;
    int permutation = 0;

    for (; permutation < 10000; ++permutation)
    {
        m_intcodeProgram.ResetProgram();
        m_intcodeProgram.SetMemoryAt(1, permutation / 100);
        m_intcodeProgram.SetMemoryAt(2, permutation % 100);

        while (!m_intcodeProgram.HasTerminated() && programErrorCode == EErrorCode::Success)
        {
            programErrorCode = m_intcodeProgram.RunNextOperation();
        }

        if (programErrorCode == EErrorCode::Success)
        {
            if (m_intcodeProgram.GetMemoryAt(0) == 19690720)
            {
                // FOUND!
                foundPermutation = true;
                break;
            }
        }
        else
        {
            break;
        }
    }

    if (foundPermutation)
    {
        std::cout << "Permutation = " << permutation << std::endl;
    }

    return programErrorCode;
}

EErrorCode CChallenge_02::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::LoadInitialMemory()
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

    m_intcodeProgram.SetInitialMemory(initialMemory, memorySize);

    delete[] initialMemory;
    return EErrorCode::Success;
}
