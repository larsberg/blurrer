#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	
	img.loadImage("images/street.jpg");
	img.resize(ofGetWidth(), ofGetHeight());
	
	blur.allocate(ofGetWidth(), ofGetHeight());
	
	

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
	blur.drawBlur( img.getTextureReference() );
	
	//img.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'l')
	{
		blur.compileShader();
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
