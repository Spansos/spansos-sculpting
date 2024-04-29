#version 400 core

in vec3 position;
in vec3 normal;
in vec3 color;

out vec3 out_color;

void main( ) {
	if ( mod(position+.025,1).x > .05 ^^ mod(position+.025,1).y > .05 ^^ mod(position+.025,1).z > .05 )
		out_color = vec3( 0, 0, 0 );
	else
		out_color = color * abs( dot( normal, vec3(.6,1,.8) ) );
}