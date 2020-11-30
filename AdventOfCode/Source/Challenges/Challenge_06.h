#pragma once

#include "Common/Challenge.h"

class CChallenge_06 : public CChallenge
{
private:
    struct SAstralBody
    {
        std::string m_id = "";
        std::string m_parentId = "";
        SAstralBody* m_parent = nullptr;
        std::vector<SAstralBody*> m_children;
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    EErrorCode CreateAstralBodies();
    EErrorCode DestroyAstralBodies(SAstralBody* bodyToDestroy);
    bool InsertChildBody(SAstralBody* parentBody, SAstralBody* childBody);

    static int SumAstralBodyDepths(int const currentDepth, SAstralBody const* root);
    static SAstralBody const* FindAstralBody(std::string const& bodyId, SAstralBody const* rootBody);
    static int GetDistanceBetweenAstralBodies(SAstralBody const* firstBody, SAstralBody const* secondBody, SAstralBody const* bodyToIgnore = nullptr);

    static std::string const sm_inputFilePath;

    SAstralBody* m_root;
};
