varying vec3 pos;
varying vec3 normal;

void main()
{
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	vec4 ecPosition = gl_ModelViewMatrix * gl_Vertex;
	
	pos = ecPosition.xyz;
	
	gl_Position = gl_ProjectionMatrix * ecPosition;
}