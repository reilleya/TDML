//0.vert;
//Created by Andrew Reilley;
//Development began 7/26/12;
//Do not redistribute, modify, or claim ownership of this library!;
//If you use this library, please credit Andrew Reilley or eggplantanimation.com;
//Contact email: areill1337@gmail.com;

uniform mat4 modelMat; 
uniform mat3 normalMat;
uniform float useLighting; 
uniform float useTextures;
uniform vec3 sunVec;
uniform mat4 projMat;
uniform vec4 diffuseColor;

in vec3 v_pos;
in vec3 n_dir;
in vec2 t_coo;

out vec3 out_n_dir;
out vec2 out_t_coo;
out float out_useLighting; 
out float out_useTextures;
out vec3 out_sunVec;
out vec4 out_diffuseColor;

void main()
{
	gl_Position = projMat * modelMat * gl_Vertex;
	out_n_dir = normalize(normalMat * n_dir);
	out_t_coo = t_coo;
	out_useLighting = useLighting;
	out_useTextures = useTextures;
	out_sunVec = (sunVec);
	out_diffuseColor = diffuseColor;
}
