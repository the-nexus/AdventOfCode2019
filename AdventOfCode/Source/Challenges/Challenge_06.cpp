#include "Challenge_06.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_06::sm_inputFilePath = "Inputs/Input_Challenge_06.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::SetUp_FirstPart()
{
    return CreateAstralBodies();
}

EErrorCode CChallenge_06::Run_FirstPart()
{
    int const totalDepthSum = SumAstralBodyDepths(0, m_root);
    std::cout << "Total number of orbits = " << totalDepthSum << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_06::CleanUp_FirstPart()
{
    return DestroyAstralBodies(m_root);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::SetUp_SecondPart()
{
    return CreateAstralBodies();
}

EErrorCode CChallenge_06::Run_SecondPart()
{
    SAstralBody const* youBody = FindAstralBody("YOU", m_root);
    SAstralBody const* sanBody = FindAstralBody("SAN", m_root);

    if (youBody && sanBody && youBody->m_parent && sanBody->m_parent)
    {
        int const bodyDistance = GetDistanceBetweenAstralBodies(youBody->m_parent, sanBody->m_parent);
        std::cout << "Orbital transfers required = " << bodyDistance << std::endl;
        return EErrorCode::Success;
    }
    return EErrorCode::Undefined;
}

EErrorCode CChallenge_06::CleanUp_SecondPart()
{
    return DestroyAstralBodies(m_root);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_06::CreateAstralBodies()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_root = new SAstralBody();
    m_root->m_id = "COM";

    std::vector<SAstralBody*> bodies;
    for (std::string const& line : lines)
    {
        std::vector<std::string> items;
        FileHelper::SplitLine(line, ")", items);

        SAstralBody* body = new SAstralBody();
        body->m_id = items[1];
        body->m_parentId = items[0];

        bodies.push_back(body);
    }

    while (bodies.size() > 0)
    {
        for (size_t bodyIdx = 0 ; bodyIdx < bodies.size(); ++bodyIdx)
        {
            if (InsertChildBody(m_root, bodies[bodyIdx]))
            {
                size_t const lastBodyIdx = bodies.size() - 1;
                if (bodyIdx < lastBodyIdx)
                {
                    std::swap(bodies[bodyIdx], bodies[lastBodyIdx]);
                }
                bodies.erase(bodies.end() - 1);
            }
        }
    }

    std::cout << "Tree built!" << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_06::DestroyAstralBodies(SAstralBody* bodyToDestroy)
{
    for (SAstralBody* childBody : bodyToDestroy->m_children)
    {
        DestroyAstralBodies(childBody);
    }

    delete bodyToDestroy;
    return EErrorCode::Success;
}

bool CChallenge_06::InsertChildBody(SAstralBody* parentBody, SAstralBody* childBody)
{
    if (parentBody->m_id.compare(childBody->m_parentId) == 0)
    {
        parentBody->m_children.push_back(childBody);
        childBody->m_parent = parentBody;
        return true;
    }
    else
    {
        for (SAstralBody* body : parentBody->m_children)
        {
            if (InsertChildBody(body, childBody))
            {
                return true;
            }
        }
    }
    return false;
}

int CChallenge_06::SumAstralBodyDepths(int const currentDepth, SAstralBody const* rootBody)
{
    int depthSum = currentDepth;
    int nextDepth = currentDepth + 1;

    for (SAstralBody* childBody : rootBody->m_children)
    {
        depthSum += SumAstralBodyDepths(nextDepth, childBody);
    }

    return depthSum;
}

CChallenge_06::SAstralBody const* CChallenge_06::FindAstralBody(std::string const& bodyId, SAstralBody const* rootBody)
{
    if (rootBody->m_id.compare(bodyId) == 0)
    {
        return rootBody;
    }
    else
    {
        for (SAstralBody const* childBody : rootBody->m_children)
        {
            if (SAstralBody const* foundBody = FindAstralBody(bodyId, childBody))
            {
                return foundBody;
            }
        }
    }

    return nullptr;
}

int CChallenge_06::GetDistanceBetweenAstralBodies(SAstralBody const* firstBody, SAstralBody const* secondBody, SAstralBody const* bodyToIgnore)
{
    SAstralBody const* firstParent = firstBody;
    int distanceToFirstParent = 0;

    while (firstParent != nullptr)
    {
        SAstralBody const* secondParent = secondBody;
        int distanceToSecondParent = 0;

        while (secondParent != nullptr)
        {
            if (firstParent == secondParent)
            {
                return distanceToFirstParent + distanceToSecondParent;
            }

            secondParent = secondParent->m_parent;
            ++distanceToSecondParent;
        }

        firstParent = firstParent->m_parent;
        ++distanceToFirstParent;
    }

    return -1;
}
