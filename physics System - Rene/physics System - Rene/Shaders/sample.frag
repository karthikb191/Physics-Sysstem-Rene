#version 120

uniform sampler2D diffuse;
varying vec2 texCoord0;
varying vec4 Color;

void main(){
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	gl_FragColor = Color * texture2D(diffuse, texCoord0);
}