uniform float nearClip;
uniform float farClip;

varying vec3 pos;
varying vec3 normal;

float mapLinear( in float x, in float a1, in float a2, in float b1, in float b2 ) {
	return b1 + ( x - a1 ) * ( b2 - b1 ) / ( a2 - a1 );
}

void main()
{
	float d = mapLinear( length(pos), nearClip, farClip, 0., 1.);
//	float d = mapLinear( dot(pos, pos), nearClip * nearClip, farClip * farClip, 0., 1.);
	gl_FragColor = vec4( vec3(d), 1.);
}