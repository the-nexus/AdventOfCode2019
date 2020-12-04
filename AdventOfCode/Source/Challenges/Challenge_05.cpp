#include "Challenge_05.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_05::sm_inputFilePath = "Inputs/Input_Challenge_05.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_FirstPart()
{
    return LoadInitialMemory();
}

EErrorCode CChallenge_05::Run_FirstPart()
{
    m_intcodeProgram.PushInput(1);

    EErrorCode programErrorCode = EErrorCode::Success;
    while (!m_intcodeProgram.HasTerminated() && programErrorCode == EErrorCode::Success)
    {
        programErrorCode = m_intcodeProgram.RunNextOperation();
        if (m_intcodeProgram.HasOutput())
        {
            std::cout << "Output  <<  " << m_intcodeProgram.PopOutput() << std::endl;
        }
    }

    return programErrorCode;
}

EErrorCode CChallenge_05::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::SetUp_SecondPart()
{
    return LoadInitialMemory();
}

EErrorCode CChallenge_05::Run_SecondPart()
{
    m_intcodeProgram.PushInput(5);

    EErrorCode programErrorCode = EErrorCode::Success;
    while (!m_intcodeProgram.HasTerminated() && programErrorCode == EErrorCode::Success)
    {
        programErrorCode = m_intcodeProgram.RunNextOperation();
        if (m_intcodeProgram.HasOutput())
        {
            std::cout << "Output  <<  " << m_intcodeProgram.PopOutput() << std::endl;
        }
    }

    return programErrorCode;
}

EErrorCode CChallenge_05::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_05::LoadInitialMemory()
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
