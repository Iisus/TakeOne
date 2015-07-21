////out vec4 fragColor;
//
//in vec4 fragmentColor;
//void main(){
//
//    fragColor = fragmentColor;
//}

#version 330

uniform mat4 model;

// material settings
uniform sampler2D u_texture;
uniform float u_shininess;
uniform vec4 u_color_specular;
uniform vec4 u_color_diffuse;
uniform int u_textures_count;

uniform struct Light {
    vec3 position;
    vec3 intensities; //a.k.a the color of the light
    float attenuation;
    float ambientCoefficient;
} light;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;
in vec3 cameraPosition;

out vec4 finalColor;

void main() {

    vec3 normal = normalize(transpose(inverse(mat3(model))) * fragNormal);
    vec3 surfacePos = vec3(model * vec4(fragVert, 1));
    vec4 surfaceColor = u_color_diffuse;
    
    //if( u_textures_count > 0 )
        surfaceColor = texture(u_texture, fragTexCoord);
        
    vec3 surfaceToLight = normalize(light.position - surfacePos);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;

    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), 1 - u_shininess);
    vec3 specular = specularCoefficient * u_color_specular.rgb * light.intensities;

    //attenuation
    float distanceToLight = length(light.position - surfacePos);
    float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

    //linear color (color before gamma correction)
    vec3 linearColor = ambient + attenuation*(diffuse + specular);

    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/1.8);
    finalColor = vec4(pow(linearColor, gamma), 1.2f);
    //finalColor = vec4(surfaceColor.rgb, 1.0f);
}
