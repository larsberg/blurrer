//
//  blurShader.frag
//
//  Created by lars berg on 1/14/15.
//

uniform sampler2DRect depthMap;
uniform vec2 direction;
uniform float radius;

varying vec2 uv;

#define EULER 2.718281828459045

float numSamples = 20.;
float threshold = .05;
float selfShadowAdjust = .1;

float mapLinear( in float x, in float a1, in float a2, in float b1, in float b2 ) {
	return b1 + ( x - a1 ) * ( b2 - b1 ) / ( a2 - a1 );
}

float getDelta( float d0, float d1)
{
	float delta = (d0 - d1) / threshold;
	
	if(delta >= 0. && delta < 1.)
	{
		return 1. - max(0., delta * (1. + selfShadowAdjust) - selfShadowAdjust);
	}

	return 1.;
}

float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453) * 2. - 1.;
}

void main()
{
	vec3 c = vec3(0.);
	
	float r = 1.;
	float d;
	vec2 st = vec2(0.);
	
	float depthPixel = texture2DRect(depthMap, uv ).x;
	float ao = 0.;
	
	float rad = radius * (1. - depthPixel * depthPixel );
	
	vec2 rs = gl_FragCoord.xy * .01;
	
	for (int i = 0; i < int(numSamples); i++)
	{
		st = vec2(rand( vec2( rs.x, rs.y + r * 33.) ), rand(vec2(rs.x + r*13., rs.y ) ));
		
		ao += getDelta( depthPixel, texture2DRect( depthMap, uv + st * rad ).x );
		
		r++;
	}
	
	ao /= numSamples;
	
	gl_FragColor = vec4( vec3( pow(ao, 2.) ), 1.);
}
