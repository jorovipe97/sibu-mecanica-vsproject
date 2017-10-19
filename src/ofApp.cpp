#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	r.setup(PORT);
	sender.setup(HOST, PORT2);
	informStatusToCentProjVolk.setup(HOST_CENVOLKAN, SEND_PORT);
	informStatusToHolo.setup(HOST_HOLO, SEND_PORT);
	informStatusToKinect.setup(HOST_KINECT, SEND_PORT);

	ofSetWindowShape(50, 50);

	pinDeMando = 7;
	pinAciertos = 8;
	aciertos = 0;
	vAcierto = false;
	controlPaso = true;

	vTiempo = false;

	arduino.connect("com8", 57600);
	arduino.sendFirmwareVersionRequest();

	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
}
//--------------------------------------------------------------
void ofApp::setupArduino(const int & version)
{
	printf("Se inicializa en el arduino");
	printf("\n");

	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);

	arduino.sendDigitalPinMode(pinDeMando, ARD_OUTPUT);
	arduino.sendDigitalPinMode(pinAciertos, ARD_INPUT);
	arduino.sendDigital(pinDeMando, ARD_LOW);

	ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::recibirArduino);
}

//--------------------------------------------------------------
void ofApp::recibirArduino(const int & version) {

	//ofRemoveListener(arduino.EDigitalPinChanged, this, &ofApp::recibirArduino);
	string pruebaTexto = "Valor aciertos: ";

	vAcierto = arduino.getDigital(pinAciertos);

	if (vAcierto == true && controlPaso == true)
	{
		aciertos += 1;
		cout << pruebaTexto << " " << aciertos << ". " << endl;

		// Every time an correct kick occurs increment the counter and send the variable counter value using OSC
		informStatusToCentProjVolk.informNumCorrectKicks(aciertos);
		informStatusToHolo.informNumCorrectKicks(aciertos);
		informStatusToKinect.informNumCorrectKicks(aciertos);
	}
	int n;
	if (aciertos > 30)
	{
		n = 1;
		ofxOscMessage enviar;
		enviar.setAddress("/control/numAciertos");
		enviar.addIntArg(n);
		sender.sendMessage(enviar, false);

		informStatusToCentProjVolk.informDespiertoStatus();
		informStatusToHolo.informDespiertoStatus();
		informStatusToKinect.informDespiertoStatus();


		controlPaso = true;
	}
	else
	{
		n = 0;
		ofxOscMessage enviar;
		enviar.setAddress("/control/numAciertos");
		enviar.addIntArg(n);
		sender.sendMessage(enviar, false);
		controlPaso = true;
	}
}
//--------------------------------------------------------------
void ofApp::update() {
	arduino.update();

	while (r.hasWaitingMessages()) {
		ofxOscMessage m;
		r.getNextMessage(&m);

		if (m.getAddress() == "/actuador") {
			mensaje = m.getArgAsInt(0);
		}
	}

	if (mensaje == 1) {
		tiempo = ofGetElapsedTimeMillis();
		mensaje = 0;
		arduino.sendDigital(pinDeMando, ARD_HIGH);
		vTiempo = true;
	}
	if (ofGetElapsedTimeMillis() - tiempo >= 100 && vTiempo == true) {
		arduino.sendDigital(pinDeMando, ARD_LOW);
		vTiempo = false;
	}


}

//--------------------------------------------------------------
void ofApp::draw() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
