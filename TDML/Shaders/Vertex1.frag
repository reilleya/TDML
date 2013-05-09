//Vertex1.frag
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com;

uniform sampler2D tex;
 
in vec3 out_n_dir;
in vec2 out_t_coo;

uniform float useLighting; 

void main()
{
    vec4 color = texture2D(tex, out_t_coo);
	float alphaval = color[3];
	if(useLighting==1)
	{
		color *= max(dot(normalize(out_n_dir), vec3(-1,0,0)), 0.0);
		color[3] = alphaval;
	}
    gl_FragColor = color;
}
