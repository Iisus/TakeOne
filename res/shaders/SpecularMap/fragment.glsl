#version 330 core

uniform sampler2D u_DiffuseMap;
uniform sampler2D u_SpecularMap;
uniform float     u_Shininess;
 
uniform vec3 u_LightPosition;
uniform vec3 u_LightAmbientColor;
uniform vec3 u_LightDiffuseColor;
uniform vec3 u_LightSpecularColor;


uniform vec3 u_ViewPos;

in vec3 FragPos;
in vec3 FragNormal;
in vec2 FragTexCoord;

out vec4 FinalColor;
  
void main()
{
    // Ambient
    vec3 ambient = u_LightAmbientColor * vec3(texture(u_DiffuseMap, FragTexCoord));
  	
    // Diffuse 
    vec3 norm = normalize(FragNormal);
    vec3 lightDir = normalize(u_LightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_LightDiffuseColor * diff * vec3(texture(u_DiffuseMap, FragTexCoord));  
    
    // Specular
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
    vec3 specular = u_LightSpecularColor * spec * vec3(texture(u_SpecularMap, FragTexCoord));
        
    FinalColor = vec4(ambient + diffuse + specular, 1.0f);  
} 

