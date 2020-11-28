#include "Challenge_05.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_05::sm_inputFilePath = "Inputs/Input_Challenge_05.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_FirstPart()
{
    return LoadIntcodeProgramMemory();
}

EErrorCode CChallenge_05::Run_FirstPart()
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

EErrorCode CChallenge_05::CleanUp_FirstPart()
{
    delete[] m_initialProgramMemory;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_SecondPart()
{
    return LoadIntcodeProgramMemory();
}

EErrorCode CChallenge_05::Run_SecondPart()
{
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_05::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::LoadIntcodeProgramMemory()
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

EErrorCode CChallenge_05::RunIntcodeProgram(int* programMemory)
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
