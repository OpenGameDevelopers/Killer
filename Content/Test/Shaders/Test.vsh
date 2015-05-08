attribute vec3 Position;
attribute vec3 Colour;
attribute vec2 ST;
attribute vec3 Normal;

uniform mat4 View;
uniform mat4 Projection;
uniform mat4 World;

varying vec4 f_Colour;
varying vec2 f_ST;
varying vec3 f_Normal;
varying vec3 f_Position;

void main( )
{
	f_Colour = vec4( Colour, 1.0 );
	f_ST = ST;
	f_Normal = Normal;
	f_Position = Position;
	gl_Position = vec4( Position, 1.0 ) * World * View * Projection;
}

