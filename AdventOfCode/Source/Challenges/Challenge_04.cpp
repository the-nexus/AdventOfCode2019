#include "Challenge_04.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_04::sm_inputFilePath = "Inputs/Input_Challenge_04.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_FirstPart()
{
    return LoadPasswordRange();
}

EErrorCode CChallenge_04::Run_FirstPart()
{
    int validPasswordCount = 0;
    for (unsigned int currentPassword = m_firstPassword; currentPassword < m_lastPassword; ++currentPassword)
    {
        bool isFirstDigitValue = true;
        bool hasConsecutiveMatchingDigitValues = false;
        bool hasIncreasingDigitValues = true;

        unsigned int previousDigitValue = 0;
        for (int digitIdx = DIGIT_COUNT - 1; digitIdx >= 0; --digitIdx)
        {
            unsigned int mul = static_cast<unsigned int>(pow(10, digitIdx));
            unsigned int digitValue = (currentPassword / mul) % 10;

            if (digitValue < previousDigitValue)
            {
                hasIncreasingDigitValues = false;
                break;
            }

            if (!isFirstDigitValue && digitValue == previousDigitValue)
            {
                hasConsecutiveMatchingDigitValues = true;
            }

            previousDigitValue = digitValue;
            isFirstDigitValue = false;
        }

        if (hasConsecutiveMatchingDigitValues && hasIncreasingDigitValues)
        {
            ++validPasswordCount;
        }
    }

    std::cout << "Number of valid passwords: " << validPasswordCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_FirstPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::SetUp_SecondPart()
{
    return LoadPasswordRange();
}

EErrorCode CChallenge_04::Run_SecondPart()
{
    int validPasswordCount = 0;
    for (unsigned int currentPassword = m_firstPassword; currentPassword < m_lastPassword; ++currentPassword)
    {
        bool isFirstDigitValue = true;
        bool hasConsecutiveDoubleMatchingDigitValues = false;
        bool hasIncreasingDigitValues = true;
        int consecutiveMatchingDigitValueCount = 1;

        unsigned int previousDigitValue = 0;
        for (int digitIdx = DIGIT_COUNT - 1; digitIdx >= 0; --digitIdx)
        {
            unsigned int mul = static_cast<unsigned int>(pow(10, digitIdx));
            unsigned int digitValue = (currentPassword / mul) % 10;

            if (digitValue < previousDigitValue)
            {
                hasIncreasingDigitValues = false;
                break;
            }

            if (!isFirstDigitValue)
            {
                bool const isMatchingDigitValue = digitValue == previousDigitValue;
                if (isMatchingDigitValue)
                {
                    ++consecutiveMatchingDigitValueCount;
                }

                if (!isMatchingDigitValue || digitIdx == 0)
                {
                    if (consecutiveMatchingDigitValueCount == 2)
                    {
                        hasConsecutiveDoubleMatchingDigitValues = true;
                    }
                    consecutiveMatchingDigitValueCount = 1;
                }
            }

            previousDigitValue = digitValue;
            isFirstDigitValue = false;
        }

        if (hasConsecutiveDoubleMatchingDigitValues && hasIncreasingDigitValues)
        {
            ++validPasswordCount;
        }
    }

    std::cout << "Number of valid passwords: " << validPasswordCount << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_04::CleanUp_SecondPart()
{
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_04::LoadPasswordRange()
{
    std::string line;
    EErrorCode const readErrorCode = FileHelper::ReadFirstLine(sm_inputFilePath, line);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    std::vector<std::string> items;
    FileHelper::SplitLine(line, "-", items);

    m_firstPassword = atoi(items[0].c_str());
    m_lastPassword = atoi(items[1].c_str());

    return EErrorCode::Success;
}
