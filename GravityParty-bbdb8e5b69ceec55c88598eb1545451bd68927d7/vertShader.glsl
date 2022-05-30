#version 430

uniform float offset;
layout (location = 0)in vec3 position;
layout (location = 1)in vec2 texCoord;
layout (location=2) in vec3 vertNormal;




out vec4 varyingColor1;
out vec4 varyingColor2;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform int x;

layout(binding = 0) uniform sampler2D samp;

//vary color

out vec2 ptc;

struct PositionalLight
{ vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform mat4 norm_matrix;


void main(void)
{

	vec4 P = mv_matrix * vec4(position,1.0);
	vec3 N = normalize((norm_matrix * vec4(vertNormal,1.0)).xyz);
	vec3 L = normalize(light.position - P.xyz);



	// view vector is equivalent to the negative of view space vertex position
	vec3 V = normalize(-P.xyz);

	// R is reflection of -L with respect to surface normal N
	vec3 R = reflect(-L,N);



	// ambient, diffuse, and specular contributions
	vec3 ambient = ((globalAmbient ) + (light.ambient )).xyz;
	vec3 diffuse = light.diffuse.xyz  * max(dot(N,L), 0.0);
	vec3 specular = light.specular.xyz * pow(max(dot(R,V), 0.0f), 5.0f);


	// send the color output to the fragment shader
	
	varyingColor1 = vec4((ambient + diffuse ), 1.0);
	varyingColor2 = vec4((specular), 1.0);

	gl_Position = proj_matrix*mv_matrix*vec4(position,1.0);
	ptc = texCoord;
}