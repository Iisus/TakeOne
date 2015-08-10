#include "LightNode.h"

TakeOne::LightNode::LightNode(LightType pLightType)
    : mLightType(pLightType)
{

}

TakeOne::LightNode::~LightNode()
{

}

void TakeOne::LightNode::SetupDirectional(glm::vec3 pDirection, glm::vec3 pAmbientColor, glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor)
{
    SetDirection(pDirection);
    SetAmbientColor(pAmbientColor);
    SetDiffuseColor(pDiffuseColor);
    SetSpecularColor(pSpecularColor);
}

void TakeOne::LightNode::SetupPoint(glm::vec3 pPosition, glm::vec3 pAmbientColor, glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor,
                float pCutOff, float pCuterCutOff)
{
    SetPosition(pPosition);
    SetAmbientColor(pAmbientColor);
    SetDiffuseColor(pDiffuseColor);
    SetSpecularColor(pSpecularColor);
    SetCutOff(pCutOff);
    SetCuterCutOff(pCuterCutOff);
}

void TakeOne::LightNode::SetupSpot(glm::vec3 pPosition, glm::vec3 pDirection, glm::vec3 pAmbientColor, glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor,
                float pCutOff, float pCuterCutOff, float pConstantAttenuation, float pLinearAttenuation, float pQuadraticAttenuation)
{
    SetPosition(pPosition);
    SetDirection(pDirection);
    SetAmbientColor(pAmbientColor);
    SetDiffuseColor(pDiffuseColor);
    SetSpecularColor(pSpecularColor);
    SetCutOff(pCutOff);
    SetCuterCutOff(pCuterCutOff);
    SetConstantAttenuation(pConstantAttenuation);
    SetLinearAttenuation(pLinearAttenuation);
    SetQuadraticAttenuation(pQuadraticAttenuation);
}


glm::vec3 TakeOne::LightNode::GetPosition() const
{
    return mTransform->GetPosition();
}
void TakeOne::LightNode::SetPosition(glm::vec3 pPosition)
{
    mTransform->SetPosition(pPosition);
}

glm::vec3 TakeOne::LightNode::GetDirection() const
{
    return mDirection;
}
void TakeOne::LightNode::SetDirection(glm::vec3 pDirection)
{
    mDirection = pDirection;
}

glm::vec3 TakeOne::LightNode::GetAmbientColor() const
{
    return mAmbientColor;
}
void TakeOne::LightNode::SetAmbientColor(glm::vec3 pAmbientColor)
{
    mAmbientColor = pAmbientColor;
}

glm::vec3 TakeOne::LightNode::GetDiffuseColor() const
{
    return mDiffuseColor;
}
void TakeOne::LightNode::SetDiffuseColor(glm::vec3 pDiffuseColor)
{
    mDiffuseColor = pDiffuseColor;
}

glm::vec3 TakeOne::LightNode::GetSpecularColor() const
{
    return mSpecularColor;
}
void TakeOne::LightNode::SetSpecularColor(glm::vec3 pSpecularColor)
{
    mSpecularColor = pSpecularColor;
}


float TakeOne::LightNode::GetCutOff() const
{
    return mCutOff;
}
void TakeOne::LightNode::SetCutOff(float pCutOff)
{
    mCutOff = pCutOff;
}

float TakeOne::LightNode::GetCuterCutOff() const
{
    return mCuterCutOff;
}
void TakeOne::LightNode::SetCuterCutOff(float pCuterCutOff)
{
    mCuterCutOff = pCuterCutOff;
}


float TakeOne::LightNode::GetConstantAttenuation() const
{
    return mConstantAttenuation;
}
void TakeOne::LightNode::SetConstantAttenuation(float pConstantAttenuation)
{
    mConstantAttenuation = pConstantAttenuation;
}

float TakeOne::LightNode::GetLinearAttenuation() const
{
    return mLinearAttenuation;
}
void TakeOne::LightNode::SetLinearAttenuation(float pLinearAttenuation)
{
    mLinearAttenuation = pLinearAttenuation;
}

float TakeOne::LightNode::GetQuadraticAttenuation() const
{
    return mQuadraticAttenuation;
}
void TakeOne::LightNode::SetQuadraticAttenuation(float pQuadraticAttenuation)
{
    mQuadraticAttenuation = pQuadraticAttenuation;
}
