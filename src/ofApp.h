#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "VolcanStatusInformer.h"
#include "HostsNames.h"

#define HOST "localhost"
#define PORT 12345
#define PORT2 12346

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxOscReceiver r;
	ofxOscSender sender;

	VolcanStatusInformer informStatusToHolo;
	VolcanStatusInformer informStatusToCentProjVolk; // PC which is responsable of project over the pyramidal surface
	VolcanStatusInformer informStatusToKinect;

	int mensaje;

	int pinDeMando;
	int pinAciertos;
	int aciertos;
	bool vAcierto;
	bool controlPaso;

	ofArduino arduino;

	void ofApp::setupArduino(const int & version);
	void ofApp::recibirArduino(const int & version);

	float tiempo;
	bool vTiempo;


};