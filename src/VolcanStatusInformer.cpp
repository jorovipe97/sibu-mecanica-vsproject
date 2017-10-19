#include "VolcanStatusInformer.h"

void VolcanStatusInformer::setup(const std::string &hostname, int port) {
	sender.setup(hostname, port);
}

void VolcanStatusInformer::informTransitionStatus() {
	ofxOscMessage m;
	m.setAddress("/tambor/status");
	m.addIntArg(0);
	sender.sendMessage(m, false);
	cout << "Sending 0" << endl;
}

void VolcanStatusInformer::informDormidoStatus() {
	ofxOscMessage m2;
	m2.setAddress("/tambor/status");
	m2.addIntArg(1);
	sender.sendMessage(m2, false);
	cout << "Sending 1" << endl;
}

void VolcanStatusInformer::informDespiertoStatus() {
	ofxOscMessage m3;
	m3.setAddress("/tambor/status");
	m3.addIntArg(2);
	sender.sendMessage(m3, false);
	cout << "Sending 2" << endl;
}

void VolcanStatusInformer::informNumCorrectKicks(unsigned long correct_hits_count) {
	ofxOscMessage m3;
	m3.setAddress("/tambor/correct_hits_counter");
	m3.addIntArg(2);
	sender.sendMessage(m3, false);
	cout << "Sending 2" << endl;
}