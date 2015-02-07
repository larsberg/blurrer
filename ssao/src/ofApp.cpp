#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
//	camera.setNearClip(1);
//	camera.setFarClip(10000);
	
	worldPosShader.load("shaders/normal");
	blurShader.load("shaders/blurShader");
	
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA16 );
	fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA16 );
	fbo2.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA16 );
	
	positions.resize(120);
	for(auto& p: positions)	p.set(ofRandom(-300, 300),ofRandom(-300, 300),ofRandom(-300, 300));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
	
	//draw geometry depth pass
	fbo.begin();
	
	glClear( GL_DEPTH_BITS );
	
	ofClear(255,255);
	
	camera.begin();
	
	ofEnableDepthTest();
	
	worldPosShader.begin();
	worldPosShader.setUniform1f("nearClip", 1);
	worldPosShader.setUniform1f("farClip", 10000);
	
	for(int i=0; i<positions.size(); i++)
	{
		if(i % 2)
		{
			ofDrawBox(positions[i], 100);
		}
		else
		{
			ofDrawSphere( positions[i], 50);
		}
	}
	
	worldPosShader.end();
	
	camera.end();
	
	fbo.end();
	
	ofSetColor(255);

	//sample left - right
	ofDisableDepthTest();
	
	ofVec2f dir(1, 0);
	fbo2.begin();
	blurShader.begin();
	blurShader.setUniform1f("radius", 30);
	blurShader.setUniform2f("direction", dir.x, dir.y);
	blurShader.setUniform2f("imgDim", fbo.getWidth(), fbo.getHeight());
	
	blurShader.setUniformTexture("depthMap", fbo.getTextureReference(), 1);
	
	ofRect(-1,-1,2,2);
	
	blurShader.end();
	fbo2.end();

	
	fbo2.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if(key == 'l')
	{
		worldPosShader.load("shaders/normal");
		blurShader.load("shaders/blurShader");
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
