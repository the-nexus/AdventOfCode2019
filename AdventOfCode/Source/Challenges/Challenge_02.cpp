#include "Challenge_02.h"
#include "../Helpers/FileHelpers.h"
#include "../Utilities/IntcodeProgram.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_02::sm_inputFilePath = "Inputs/Input_Challenge_02.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_FirstPart()
{
    return LoadInitialMemory();
}

EErrorCode CChallenge_02::Run_FirstPart()
{
    CIntcodeProgram program;
    program.SetMemory(m_initialMemory, m_memorySize);
    program.SetMemoryAt(1, 12);
    program.SetMemoryAt(2, 2);


    EErrorCode const programErrorCode = program.Run();
    if (programErrorCode != EErrorCode::Success)
    {
        return programErrorCode;
    }

    std::cout << "First integer = " << program.GetMemoryAt(0) << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_02::CleanUp_FirstPart()
{
    delete[] m_initialMemory;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_02::SetUp_SecondPart()
{
    return LoadInitialMemory();
}

EErrorCode CChallenge_02::Run_SecondPart()
{
    EErrorCode programErrorCode;
    CIntcodeProgram program;

    int permutation = 0;
    for (; permutation < 10000; ++permutation)
    {
        program.SetMemory(m_initialMemory, m_memorySize);
        program.SetMemoryAt(1, permutation / 100);
        program.SetMemoryAt(2, permutation % 100);

        programErrorCode = program.Run();
        if (programErrorCode != EErrorCode::Success)
        {
            break;
        }
        else if (program.GetMemoryAt(0) == 19690720)
        {
            programErrorCode = EErrorCode::Success;
            break;
        }
        else
        {
            programErrorCode = EErrorCode::Undefined;
        }
    }

    if (programErrorCode == EErrorCode::Success)
    {
        std::cout << "Permutation = " << permutation << std::endl;
    }

    return programErrorCode;
}

EErrorCode CChallenge_02::CleanUp_SecondPart()
{
    delete[] m_initialMemory;
    return EErrorCode::NotImplemented;
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

    size_t const programSize = items.size();
    m_memorySize = programSize;
    m_initialMemory = new int[programSize];

    for (size_t memoryIdx = 0; memoryIdx < items.size(); ++memoryIdx)
    {
        m_initialMemory[memoryIdx] = atoi(items[memoryIdx].c_str());
    }

    return EErrorCode::Success;
}
