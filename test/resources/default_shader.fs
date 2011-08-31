precision mediump float;

uniform sampler2D u_texture;

varying vec2 v_texCoord;

void main()
{
	// gl_FragColor = texture2D(u_texture, v_texCoord);
	gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}
