//
//  ofxBlurrer.h
//
//  Created by lars berg on 1/14/15.
//

#pragma once

#include "ofMain.h"

class ofxBlurrer
{
public:
	ofxBlurrer();
	~ofxBlurrer();
	
	void setup();
	
	void allocate(int w, int h);
	
	// 1D gaussian kernel
	static vector<float>gaussianKernel ( int radius, float weight = 1.);
	
	void blurToFbo(ofTexture& inputTexture);
	
	void bokeh(ofTexture& inputTexture);
	
	void updateFbo(ofTexture& inputTexture);
	
	void drawBlur( ofTexture& inputTexture );
	
	void compileShader()
	{
		blurShader.load("shaders/blurShader");
		bokehShader.load("shaders/bokeh");
	}
	
	bool bUpdateFbo, bIsSetup;
	int numIterations, radius;
	float brightness;
	string path;
	ofShader blurShader;
	ofShader bokehShader;
	ofFbo fbo1, fbo2;
	vector<float> kernel;
	
	int bokehIterations;
	
	ofImage radialGradient;
};