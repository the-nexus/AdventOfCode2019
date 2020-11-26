#include "Challenge_01.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_01::sm_inputFilePath = "Inputs/Input_Challenge_01.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_01::SetUp_FirstPart()
{
    return EErrorCode::Success;
}

EErrorCode CChallenge_01::Run_FirstPart()
{
    std::ifstream inputFile(sm_inputFilePath.c_str());
    if (!inputFile.is_open())
    {
        return EErrorCode::FileNotFound;
    }

    int totalRequiredFuel = 0;

    std::string line;
    while (std::getline(inputFile, line))
    {
        totalRequiredFuel += GetRequiredFuel(atoi(line.c_str()));
    }
    inputFile.close();

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
    std::ifstream inputFile(sm_inputFilePath.c_str());
    if (!inputFile.is_open())
    {
        return EErrorCode::Success;
    }

    int totalRequiredFuel = 0;

    std::string line;
    while (std::getline(inputFile, line))
    {
        totalRequiredFuel += GetRecursiveRequiredFuel(atoi(line.c_str()));
    }
    inputFile.close();

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
