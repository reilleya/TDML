uniform sampler2D tex;
 
in vec3 out_n_dir;
in vec2 out_t_coo;
 
void main()
{
    vec4 color = texture2D(tex, out_t_coo);
    gl_FragColor = color;
    //gl_FragColor = vec4(0.4,0.4,0.8,1.0);
}
