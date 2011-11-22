uniform mat4 u_matModelViewProj;

attribute vec3 a_position;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;

void main()
{
	gl_Position = u_matModelViewProj * vec4(a_position, 1.0);
	v_texCoord = a_texCoord;
}
