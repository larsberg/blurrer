//
//  blurShader.frag
//
//  Created by lars berg on 1/14/15.
//

uniform sampler2DRect map;
uniform sampler2DRect depthMap;
uniform vec2 direction;
uniform int radius;

varying vec2 uv;

void main()
{
	gl_FragColor = texture2DRect(map, uv);
	
	vec3 c = vec3(0.);
	
	int gi = 0;
	float r = - float(radius), d;
	vec2 st = vec2(0.);
	
	float depthPixel = pow(texture2DRect(depthMap, uv ).x, 2.) * 1.5;
	vec2 dir = direction * depthPixel;
	for (int i = -radius; i <= radius; i++)
	{
		c = max(c, texture2DRect( map, uv + dir * r ).xyz);
		r++;
	}
	
	gl_FragColor = vec4(c, 1.);
}
