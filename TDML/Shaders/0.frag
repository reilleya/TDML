//0.frag;
//Created by Andrew Reilley;
//Development began 7/26/12;
//Do not redistribute, modify, or claim ownership of this library!;
//If you use this library, please credit Andrew Reilley or eggplantanimation.com;
//Contact email: areill1337@gmail.com;

uniform sampler2D tex;
 
in vec3 out_n_dir;
in vec2 out_t_coo;
in float out_useLighting; 
in float out_useTextures;
in vec3 out_sunVec;
in vec4 out_diffuseColor;

void main()
{
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	if(out_useTextures==1)
	{
		color = texture2D(tex, out_t_coo);
	}
	float alphaval = color[3];
	if(out_useLighting==1)
	{
		color *= max(dot(out_n_dir, out_sunVec), 0.0);
		color[3] = alphaval;
	}
	if(out_useTextures==1)
	{
		gl_FragColor = color;
	}
	else
	{
		gl_FragColor = out_diffuseColor;
	}
}
