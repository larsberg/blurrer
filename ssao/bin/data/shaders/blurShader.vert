//
//  blurShader.vert
//
//  Created by lars berg on 1/14/15.
//

uniform vec2 imgDim;
varying vec2 uv;

void main()
{
	uv = (gl_Vertex.xy * .5 + .5) * imgDim;
	
	gl_Position = gl_Vertex;// * vec4(.5,.5,.5,1.);
}