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
    return RunIntcodeProgram(m_initialProgramMemory, 1);
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
    return RunIntcodeProgram(m_initialProgramMemory, 5);
}

EErrorCode CChallenge_05::CleanUp_SecondPart()
{
    delete[] m_initialProgramMemory;
    return EErrorCode::Success;
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

EErrorCode CChallenge_05::RunIntcodeProgram(int* programMemory, int const inputValue)
{
    size_t programIdx = 0;
    bool shouldRunProgram = true;

    while (shouldRunProgram)
    {
        int const paramModes = programMemory[programIdx] / 100;
        int const opcode = programMemory[programIdx] % 100;

        size_t paramIdxA, paramIdxB, paramIdxC;

        switch (opcode)
        {
        //===============================================================================================
        // Addition
        case 1:
            paramIdxA = GetParamMode(paramModes, 0) > 0 ? programIdx + 1 : programMemory[programIdx + 1];
            paramIdxB = GetParamMode(paramModes, 1) > 0 ? programIdx + 2 : programMemory[programIdx + 2];
            paramIdxC = programMemory[programIdx + 3];

            programMemory[paramIdxC] = programMemory[paramIdxA] + programMemory[paramIdxB];
            programIdx += 4;
            break;


        //===============================================================================================
        // Multiplication
        case 2:
            paramIdxA = GetParamMode(paramModes, 0) > 0 ? programIdx + 1 : programMemory[programIdx + 1];
            paramIdxB = GetParamMode(paramModes, 1) > 0 ? programIdx + 2 : programMemory[programIdx + 2];
            paramIdxC = programMemory[programIdx + 3];

            programMemory[paramIdxC] = programMemory[paramIdxA] * programMemory[paramIdxB];
            programIdx += 4;
            break;


        //===============================================================================================
        // Input value
        case 3:
            paramIdxA = programMemory[programIdx + 1];

            programMemory[paramIdxA] = inputValue;
            std::cout << "Input   <<  " << inputValue << std::endl;
            programIdx += 2;
            break;


        //===============================================================================================
        // Output value
        case 4:
            paramIdxA = GetParamMode(paramModes, 0) > 0 ? programIdx + 1 : programMemory[programIdx + 1];

            std::cout << "Output  >>  " << programMemory[paramIdxA] << std::endl;
            programIdx += 2;
            break;


        //===============================================================================================
        // Jump if not 0
        case 5:
            paramIdxA = GetParamMode(paramModes, 0) > 0 ? programIdx + 1 : programMemory[programIdx + 1];
            paramIdxB = GetParamMode(paramModes, 1) > 0 ? programIdx + 2 : programMemory[programIdx + 2];
            if (programMemory[paramIdxA] != 0)
            {
                programIdx = programMemory[paramIdxB];
            }
            else
            {
                programIdx += 3;
            }
            break;


        //===============================================================================================
        // Jump if 0
        case 6:
            paramIdxA = GetParamMode(paramModes, 0) > 0 ? programIdx + 1 : programMemory[programIdx + 1];
            paramIdxB = GetParamMode(paramModes, 1) > 0 ? programIdx + 2 : programMemory[programIdx + 2];
            if (programMemory[paramIdxA] == 0)
            {
                programIdx = programMemory[paramIdxB];
            }
            else
            {
                programIdx += 3;
            }
            break;


        //===============================================================================================
        // Is lesser
        case 7:
            paramIdxA = GetParamMode(paramModes, 0) > 0 ? programIdx + 1 : programMemory[programIdx + 1];
            paramIdxB = GetParamMode(paramModes, 1) > 0 ? programIdx + 2 : programMemory[programIdx + 2];
            paramIdxC = programMemory[programIdx + 3];

            programMemory[paramIdxC] = programMemory[paramIdxA] < programMemory[paramIdxB] ? 1 : 0;
            programIdx += 4;
            break;


        //===============================================================================================
        // Is equal
        case 8:
            paramIdxA = GetParamMode(paramModes, 0) > 0 ? programIdx + 1 : programMemory[programIdx + 1];
            paramIdxB = GetParamMode(paramModes, 1) > 0 ? programIdx + 2 : programMemory[programIdx + 2];
            paramIdxC = programMemory[programIdx + 3];

            programMemory[paramIdxC] = programMemory[paramIdxA] == programMemory[paramIdxB] ? 1 : 0;
            programIdx += 4;
            break;


        //===============================================================================================
        // Terminate program
        case 99:
            shouldRunProgram = false;
            break;


        //===============================================================================================
        default:
            return EErrorCode::Undefined;
        }
    }

    return EErrorCode::Success;
}

int CChallenge_05::GetParamMode(int const paramModes, int const idx)
{
    return (paramModes / static_cast<int>(pow(10, idx))) % 10;
}
