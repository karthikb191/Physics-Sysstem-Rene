#version 120

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;
varying vec4 Color;

uniform vec4 color = vec4(1, 1, 1, 1);
uniform mat4 transform;

void main(){
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	//Color = vec4(1, 1, 0, 1);
	Color = color;
}