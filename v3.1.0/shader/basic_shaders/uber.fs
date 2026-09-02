#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

uniform bool useLighting;

void main()
{

    vec3 diffuseColor  = texture(diffuseMap,  TexCoords).rgb * material.diffuse;
    vec3 specularColor = texture(specularMap, TexCoords).rgb * material.specular;
    vec3 ambientColor  = texture(diffuseMap,  TexCoords).rgb * material.ambient;

    if (!useLighting)
    {
        FragColor = vec4(diffuseColor, 1.0);
        return;
    }

    // Ambient
    vec3 ambient = light.ambient * ambientColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseColor;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * specularColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}