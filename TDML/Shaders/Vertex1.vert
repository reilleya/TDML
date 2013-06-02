//Vertex1.vert
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com;

uniform mat4 modelMat; 
uniform float useLighting; 
uniform float useTextures;

in vec3 v_pos;
in vec3 n_dir;
in vec2 t_coo;

out vec3 out_n_dir;
out vec2 out_t_coo;
out float out_useLighting; 
out float out_useTextures;

void main()
{
	//gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ProjectionMatrix * modelMat * gl_Vertex;
	
	out_n_dir = n_dir; 
	out_t_coo = t_coo;
	out_useLighting = useLighting;
	out_useTextures = useTextures;
}
