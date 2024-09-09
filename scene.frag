#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
	sampler2D diffuse1;
	sampler2D diffuse2;
	sampler2D specular1;
	sampler2D specular2;
	float shiniess;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform DirLight dirLight;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.), material.shiniess);
	vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	FragColor = vec4(CalcDirLight(dirLight, norm, viewDir), 1.);
}