#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirectionalLight{
    vec3 direction;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
};

struct PointLight{
    vec3 position;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float outerCutOff;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

out vec4 outColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texcoord;
in vec3 viewPos;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform Material material;
uniform DirectionalLight dirLight;
#define NR_POINT_LIGHTS 2
uniform PointLight pointLight[NR_POINT_LIGHTS];
#define NR_SPOT_LIGHTS 1
uniform SpotLight spotLight[NR_SPOT_LIGHTS];

vec3 calcDirectionalLight(vec3 Normal, vec3 viewDir);
vec3 calcPointLight(PointLight Light, vec3 Normal, vec3 viewDir);
vec3 calcSpotLight(SpotLight Light, vec3 Normal, vec3 viewDir);

void main(){
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 Normal = normalize(normal);

    vec3 result = calcDirectionalLight(Normal, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        result += calcPointLight(pointLight[i], Normal, viewDir);
    }
    for(int i = 0; i < NR_SPOT_LIGHTS; i++){
        result += calcSpotLight(spotLight[i], Normal, viewDir);
    }
    outColor = vec4(result, 1.0f);
}

vec3 calcDirectionalLight(vec3 Normal, vec3 viewDir){
    vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, texcoord));

    //Diffuse

    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(Normal, lightDir), 0.0f);
    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuse, texcoord));
    //texture(tex, texcoord)

    //Specular
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dirLight.specular * spec * vec3(texture(material.specular, texcoord));

    vec3 result = (ambient + diffuse + specular);
    return result;
}

vec3 calcPointLight(PointLight Light, vec3 Normal, vec3 viewDir){
    vec3 lightDir = normalize(Light.position - fragPos);
    //Diffuse
    float diff = max(dot(Normal, lightDir), 0.0f);
    //Specular
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    //Attenuation
    float distance = length(Light.position - fragPos);
    float attenuation = 1.0f / (Light.constantAttenuation + Light.linearAttenuation * distance + Light.quadraticAttenuation * (distance * distance));

    //Colors
    vec3 ambient = Light.ambient * vec3(texture(material.diffuse, texcoord));
    vec3 diffuse = Light.diffuse * diff * vec3(texture(material.diffuse, texcoord));
    vec3 specular = Light.specular * spec * vec3(texture(material.specular, texcoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight Light, vec3 Normal, vec3 viewDir){
    vec3 lightDir = normalize(Light.position - fragPos);


   // if(theta > Light.cutOff){
        float diff = max(dot(Normal, lightDir), 0.0f);
        vec3 diffuse = Light.diffuse * diff * vec3(texture(material.diffuse, texcoord));

        vec3 reflectDir = reflect(-lightDir, Normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
        float distance = length(Light.position - fragPos);
        vec3 specular = Light.specular * spec * vec3(texture(material.specular, texcoord));
        float attenuation = 1.0f / (Light.constantAttenuation + Light.linearAttenuation * distance + Light.quadraticAttenuation * (distance * distance));

        float theta = dot(lightDir, normalize(-Light.direction));
        float epsilon = Light.cutOff - Light.outerCutOff;
        float intensity = clamp((theta - Light.outerCutOff) / epsilon, 0.0f, 1.0f);

        diffuse *= intensity;
        specular *= intensity;

        diffuse *= attenuation;
        specular *= attenuation;

        return (diffuse + specular);

}
