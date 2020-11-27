#include "Challenge_02.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_02::sm_inputFilePath = "Inputs/Input_Challenge_02.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_FirstPart()
{
    return LoadIntcodeProgramMemory();
}

EErrorCode CChallenge_02::Run_FirstPart()
{
    m_initialProgramMemory[1] = 12;
    m_initialProgramMemory[2] = 2;

    EErrorCode const programErrorCode = RunIntcodeProgram(m_initialProgramMemory);
    if (programErrorCode != EErrorCode::Success)
    {
        return programErrorCode;
    }

    std::cout << "First integer = " << m_initialProgramMemory[0] << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_02::CleanUp_FirstPart()
{
    delete[] m_initialProgramMemory;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_SecondPart()
{
    return LoadIntcodeProgramMemory();
}

EErrorCode CChallenge_02::Run_SecondPart()
{
    EErrorCode programErrorCode = EErrorCode::Undefined;
    int* programMemory = new int[m_programSize];

    int permutation = 0;
    for (; permutation < 10000; ++permutation)
    {
        for (size_t programIdx = 0; programIdx < m_programSize; ++programIdx)
        {
            programMemory[programIdx] = m_initialProgramMemory[programIdx];
        }

        programMemory[1] = permutation / 100;
        programMemory[2] = permutation % 100;

        programErrorCode = RunIntcodeProgram(programMemory);
        if (programErrorCode != EErrorCode::Success)
        {
            break;
        }
        else if (programMemory[0] == 19690720)
        {
            programErrorCode = EErrorCode::Success;
            break;
        }
    }

    if (programErrorCode == EErrorCode::Success)
    {
        std::cout << "Permutation = " << permutation << std::endl;
    }

    delete[] programMemory;
    return programErrorCode;
}

EErrorCode CChallenge_02::CleanUp_SecondPart()
{
    delete[] m_initialProgramMemory;
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::LoadIntcodeProgramMemory()
{
    std::string line;
    EErrorCode const readErrorCode = FileHelper::ReadFirstLine(sm_inputFilePath, line);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    std::vector<std::string> items;
    FileHelper::SplitLine(line, ",", items);

    size_t const programSize = items.size();
    m_programSize = programSize;
    m_initialProgramMemory = new int[programSize];

    for (size_t programIdx = 0; programIdx < items.size(); ++programIdx)
    {
        m_initialProgramMemory[programIdx] = atoi(items[programIdx].c_str());
    }

    return EErrorCode::Success;
}

EErrorCode CChallenge_02::RunIntcodeProgram(int* programMemory)
{
    size_t programIdx = 0;
    bool shouldRunProgram = true;

    while (shouldRunProgram)
    {
        switch (programMemory[programIdx])
        {
        case 1:
            programMemory[programMemory[programIdx + 3]] = programMemory[programMemory[programIdx + 1]] + programMemory[programMemory[programIdx + 2]];
            programIdx += 4;
            break;

        case 2:
            programMemory[programMemory[programIdx + 3]] = programMemory[programMemory[programIdx + 1]] * programMemory[programMemory[programIdx + 2]];
            programIdx += 4;
            break;

        case 99:
            shouldRunProgram = false;
            break;

        default:
            return EErrorCode::Undefined;
        }
    }

    return EErrorCode::Success;
}
