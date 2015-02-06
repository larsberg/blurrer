//
//  ofxBlurrer.cpp
//
//  Created by lars berg on 1/14/15.
//

#include "ofxBlurrer.h"



ofxBlurrer::ofxBlurrer() :
bUpdateFbo(true),
bIsSetup(false),
numIterations(0),
radius(5),
brightness(1.02),
bokehIterations(2)
{}

ofxBlurrer::~ofxBlurrer()
{}

void ofxBlurrer::setup()
{
	//load blur shaders
	blurShader.load("shaders/blurShader");
	bokehShader.load("shaders/bokeh");
	
	kernel = gaussianKernel(radius);
	bIsSetup = true;
	
	radialGradient.loadImage("images/noise.jpg");
	
	radialGradient.resize(fbo1.getWidth(), fbo1.getHeight());
}

void ofxBlurrer::allocate(int w, int h)
{
	bUpdateFbo = true;
	
	fbo1.allocate( w, h );
	fbo2.allocate( w, h );
	
	radialGradient.resize(w, h);
	
	if(!bIsSetup)
	{
		bIsSetup = true;
		setup();
	}
}

// 1D gaussian kernel
vector<float> ofxBlurrer::gaussianKernel( int radius, float weight)
{
	int mem_amount = (radius*2)+1;
	vector<float> kernel( (radius*2) + 1 );
	
	float twoRadiusSquaredRecip = 1.0 / (2.0 * radius * radius);
	float sqrtTwoPiTimesRadiusRecip = 1.0 / (sqrt(2.0 * PI) * radius);
	
	// Create Gaussian Kernel
	int r = -radius;
	float sum = 0, x, v;
	for (int i = 0; i < kernel.size(); i++)
	{
		v = sqrtTwoPiTimesRadiusRecip * exp(-pow(r * weight, 2) * twoRadiusSquaredRecip);
		kernel[i] = v;
		
		sum+=v;
		r++;
	}
	
	// normalize
	for (auto& k: kernel)	k /= sum;
	
	return kernel;
}

void ofxBlurrer::blurToFbo(ofTexture& inputTexture)
{
	ofPushStyle();
	
	fbo1.begin();
	blurShader.begin();
	blurShader.setUniform1f("brightness", brightness);
	blurShader.setUniform1i("radius", radius);
	blurShader.setUniform1fv("gausKern", &kernel[0], kernel.size());
	blurShader.setUniform2f("direction", 0, 1);
	blurShader.setUniformTexture("map", inputTexture, 0);
	blurShader.setUniform2f("imgDim", inputTexture.getWidth(), inputTexture.getHeight());
	
	ofRect(-1,-1,2,2);
	
	blurShader.end();
	fbo1.end();
	
	fbo2.begin();
	blurShader.begin();
	blurShader.setUniform2f("direction", 1, 0);
	blurShader.setUniformTexture("map", fbo1.getTextureReference(), 0);
	blurShader.setUniform2f("imgDim", fbo1.getWidth(), fbo1.getHeight());
	
	ofRect(-1,-1,2,2);
	
	blurShader.end();
	fbo2.end();
	
	ofPopStyle();
}


void ofxBlurrer::bokeh(ofTexture& inputTexture)
{
	float rot = 180. / (bokehIterations*2+1);
	ofVec2f dir(1, 0);
	ofPushStyle();
	
	fbo2.begin();
	bokehShader.begin();
	bokehShader.setUniform1f("brightness", brightness);
	bokehShader.setUniform1i("radius", radius);
	bokehShader.setUniform1fv("gausKern", &kernel[0], kernel.size());
	bokehShader.setUniform2f("direction", dir.x, dir.y);
	bokehShader.setUniformTexture("map", inputTexture, 0);
	bokehShader.setUniform2f("imgDim", inputTexture.getWidth(), inputTexture.getHeight());
	
	bokehShader.setUniformTexture("depthMap", radialGradient.getTextureReference(), 1);
	
	ofRect(-1,-1,2,2);
	
	bokehShader.end();
	fbo2.end();
	
	for(int i=0; i<bokehIterations; i++)
	{
		dir.rotate( rot );
		
		fbo1.begin();
		bokehShader.begin();
		bokehShader.setUniform2f("direction", dir.x, dir.y);
		bokehShader.setUniformTexture("map", fbo2.getTextureReference(), 0);
		bokehShader.setUniformTexture("depthMap", radialGradient.getTextureReference(), 1);
		bokehShader.setUniform2f("imgDim", fbo2.getWidth(), fbo2.getHeight());
		
		ofRect(-1,-1,2,2);
		
		bokehShader.end();
		fbo1.end();
		
		dir.rotate( rot );
		
		fbo2.begin();
		bokehShader.begin();
		bokehShader.setUniform2f("direction", dir.x, dir.y);
		bokehShader.setUniformTexture("map", fbo1.getTextureReference(), 0);
		bokehShader.setUniformTexture("depthMap", radialGradient.getTextureReference(), 1);
		bokehShader.setUniform2f("imgDim", fbo1.getWidth(), fbo1.getHeight());
		
		ofRect(-1,-1,2,2);
		
		bokehShader.end();
		fbo2.end();
	}
	
	
	ofPopStyle();
}

void ofxBlurrer::updateFbo(ofTexture& inputTexture)
{
//	blurToFbo(inputTexture);
//	
//	//iterations
//	for(int i=0; i<numIterations; i++)	blurToFbo(fbo2.getTextureReference());
	
	bokeh(inputTexture);
	
	//iterations
	for(int i=0; i<numIterations; i++)	bokeh(fbo2.getTextureReference());
}

void ofxBlurrer::drawBlur( ofTexture& inputTexture )
{
	
	if(!bIsSetup)
	{
		bIsSetup = true;
		setup();
	}
	
//	if(bUpdateFbo)
//	{
//		bUpdateFbo = false;
		updateFbo( inputTexture );
//	}
	
	float scale = MAX( ofGetWidth() / fbo2.getWidth(), ofGetHeight() / fbo2.getHeight() );
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() * .5, ofGetHeight() * .5);
	ofScale(scale, scale);
	
	fbo2.draw( fbo2.getWidth() * -.5, fbo2.getHeight() * -.5, fbo2.getWidth(), fbo2.getHeight());
	
	ofPopMatrix();
}