#pragma once

#include "Node.h"
#include "Material.h"

namespace TakeOne
{
    enum class LightType
    {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    class LightNode : private Node
    {
    public:
        LightNode(LightType pLightType = LightType::DIRECTIONAL);
        LightNode(LightNode&& pOther);
        LightNode& operator=(LightNode&& pOther);
        ~LightNode(); //empty


        void SetLightType(LightType pLightType) { mLightType = pLightType; }
        LightType GetLightType() const { return mLightType; }


        void SetupDirectional(glm::vec3 pDirection, glm::vec3 pAmbientColor, glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor);

        void SetupPoint(glm::vec3 pPosition, glm::vec3 pAmbientColor, glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor,
                        float pCutOff, float pCuterCutOff);

        void SetupSpot(glm::vec3 pPosition, glm::vec3 pDirection, glm::vec3 pAmbientColor, glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor,
                        float pCutOff, float pCuterCutOff, float pConstantAttenuation, float pLinearAttenuation, float pQuadraticAttenuation);


        glm::vec3 GetPosition() const;
        void SetPosition(glm::vec3 pPosition);

        glm::vec3 GetDirection() const;
        void SetDirection(glm::vec3 pDirection);

        glm::vec3 GetAmbientColor() const;
        void SetAmbientColor(glm::vec3 pAmbientColor);

        glm::vec3 GetDiffuseColor() const;
        void SetDiffuseColor(glm::vec3 pDiffuseColor);

        glm::vec3 GetSpecularColor() const;
        void SetSpecularColor(glm::vec3 pSpecularColor);


        float GetCutOff() const;
        void SetCutOff(float pCutOff);

        float GetCuterCutOff() const;
        void SetCuterCutOff(float pCuterCutOff);


        float GetConstantAttenuation() const;
        void SetConstantAttenuation(float pConstantAttenuation);

        float GetLinearAttenuation() const;
        void SetLinearAttenuation(float pLinearAttenuation);

        float GetQuadraticAttenuation() const;
        void SetQuadraticAttenuation(float pQuadraticAttenuation);

        void ApplyLight(Material& pMaterial);

    private:

        LightType mLightType;

        //we don't use the one from transofm because we don't actually transform the light,
        //but instead just send the parameter to the shader
        glm::vec3 mDirection;

        glm::vec3 mAmbientColor;
        glm::vec3 mDiffuseColor;
        glm::vec3 mSpecularColor;

        //for point light and spot light
        float mCutOff;
        float mCuterCutOff;

        //for spot light
        float mConstantAttenuation;
        float mLinearAttenuation;
        float mQuadraticAttenuation;
    };
}
