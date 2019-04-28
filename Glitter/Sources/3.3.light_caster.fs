

#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D  specular;
    sampler2D emission;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;
    
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
    
};

uniform Light light;

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 ourTextCoords;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


void main()
{
    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTextCoords));
    
    
    // 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir =  normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ourTextCoords));
    
    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec *  vec3(texture( material.specular,ourTextCoords));
    
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));
    
    
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    vec3 result = ambient + diffuse + specular ;
    
    FragColor = vec4(result, 1.0);
    
}
