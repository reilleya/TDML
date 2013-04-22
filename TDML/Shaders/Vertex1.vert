in vec3 v_pos;
in vec3 n_dir;
in vec2 t_coo;

out vec3 out_n_dir;
out vec2 out_t_coo;

void main()
{
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	
	out_n_dir = n_dir;
	out_t_coo = t_coo;
}
