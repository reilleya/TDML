uniform sampler2D tex;
 
in vec3 out_n_dir;
in vec2 out_t_coo;
 
void main()
{
    vec4 color = texture2D(tex, out_t_coo);
    out_n_dir-=vec3(0, 1, 0);
    color*=vec4(out_n_dir[0],out_n_dir[1],out_n_dir[2],1);
    gl_FragColor = color;
}
