#version 330
// It was expressed tha tsome drivers required this next line to function
precision highp float;

in vec4 ex_Color;
out vec4 gl_FragColor;

void main( void )
{
	gl_FragColor = vec4( ex_Color, 1.0 );
}