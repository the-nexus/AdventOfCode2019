#include "Challenge_01.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_01::sm_inputFilePath = "Inputs/Input_Challenge_01.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_FirstPart()
{
    return EErrorCode::Success;
}

EErrorCode CChallenge_01::Run_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    int totalRequiredFuel = 0;
    for (std::string const& line : lines)
    {
        int const moduleMass = atoi(line.c_str());
        totalRequiredFuel += GetRequiredFuel(moduleMass);
    }

    std::cout << "Total required fuel = " << totalRequiredFuel << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_01::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_SecondPart()
{
    return EErrorCode::Success;
}

EErrorCode CChallenge_01::Run_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    int totalRequiredFuel = 0;
    for (std::string const& line : lines)
    {
        int const moduleMass = atoi(line.c_str());
        totalRequiredFuel += GetRecursiveRequiredFuel(moduleMass);
    }

    std::cout << "Total required fuel = " << totalRequiredFuel << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_01::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
int CChallenge_01::GetRequiredFuel(int const mass)
{
    return (mass / 3) - 2;
}

int CChallenge_01::GetRecursiveRequiredFuel(int const mass)
{
    int const requiredFuel = GetRequiredFuel(mass);
    if (requiredFuel > 0)
    {
        return requiredFuel + GetRecursiveRequiredFuel(requiredFuel);
    }
    else
    {
        return 0;
    }
}
