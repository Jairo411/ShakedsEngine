#version 450 core

struct Light {
	vec3 position;
	float ambientValue;
	float diffuseValue;
	vec3 lightColour;	
};

// COMPLETE!: create material struct - exact same as handelr class : no name string, instead of gluint we need a sampler2d

struct Material {
	sampler2D diffuseMap;
	float shininess;
	float transparency;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;
out vec4 fColour;

//uniform sampler2D inputTexture; this is now the diffuseMap in Material struct

uniform vec3 cameraPos;

uniform Light light;

uniform Material material;

void main() {
	//vec3 ambient = light.ambientValue * texture(inputTexture, TexCoords).rgb * light.lightColour;

	//vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(light.position - FragPosition);
	//float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = diff * texture(inputTexture, TexCoords).rgb * light.lightColour;

	//float specularStrength = 0.5;
	//vec3 viewDir = normalize(cameraPos - FragPosition);
	//vec3 reflectDir = reflect(-lightDir, norm);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	//vec3 specular = specularStrength * spec * light.lightColour;

	//vec3 result = ambient + diffuse + specular;

	//fColour = vec4(result, 1.0f);

	// NEW SHADER
	//ambient
	vec3 ambient = light.ambientValue * material.ambient * texture(material.diffuseMap, TexCoords).rgb *
	light.lightColour;
	
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;
	
	//specular
	vec3 viewDir = normalize(cameraPos-FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour;
	vec3 result = ambient + diffuse + specular;
	
	fColour = vec4(result, material.transparency);
}