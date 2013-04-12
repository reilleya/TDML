uniform sampler2D tex;
 
void main()
{
    vec4 color = texture(tex,gl_TexCoord[0].st);
    gl_FragColor = color;
    //gl_FragColor = vec4(0.4,0.4,0.8,1.0);
}