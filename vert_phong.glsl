#version 430
layout (location=0) in vec3 vertPos;
layout (location = 1)in vec2 texCoord;
layout (location=2) in vec3 vertNormal;
layout (location=3) in vec3 vertTangent;





out vec3 varyingNormal;
 // eye-space vertex normal
out vec3 varyingLightDir;
 // vector pointing to the light
out vec3 varyingVertPos;
out vec3 varyingTangent;
 // vertex position in eye space
 out vec3 varyingHalfVector;
out vec3 originalVertex;


struct PositionalLight
{ vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform mat4 norm_matrix;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform int button;

layout(binding = 0) uniform sampler2D samp;
layout(binding = 1) uniform sampler2D sampn;

out vec2 ptc;

void main(void)
{ // output vertex position, light direction, and normal to the rasterizer for interpolation

originalVertex = vertPos;
varyingVertPos=(mv_matrix * vec4(vertPos,1.0)).xyz;
varyingLightDir = light.position - varyingVertPos;
varyingNormal=(norm_matrix * vec4(vertNormal,1.0)).xyz;
varyingTangent=(norm_matrix * vec4(vertTangent,1.0)).xyz;
varyingHalfVector = (varyingLightDir + (-varyingVertPos)).xyz;

//vec4 p = vec4(vertPos,1.0) + vec4( (vertNormal * ((texture(sampn, texCoord).r) / 5.0f)),1.0f );



gl_Position=proj_matrix * mv_matrix * vec4(vertPos,1.0);
//gl_Position=proj_matrix * mv_matrix * p;
ptc = texCoord;
}
