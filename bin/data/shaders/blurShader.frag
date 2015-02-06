//
//  blurShader.frag
//
//  Created by lars berg on 1/14/15.
//

uniform sampler2DRect map;
uniform vec4 color;
uniform vec2 direction;
uniform float brightness;
uniform int radius;

uniform float gausKern[41];

varying vec2 uv;

void main()
{
	gl_FragColor = texture2DRect(map, uv);
	
	vec3 sum = vec3(0.0);
	
	int gi = 0;
	float r = - float(radius);
	for (int i = -radius; i <= radius; i++)
	{
		sum += texture2DRect(map, uv + direction * r ).xyz * gausKern[gi];
		gi++;
		r += 1.;
	}
	
	gl_FragColor = vec4(sum.rgb * brightness, 1.);
}
