#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class VolcanStatusInformer {
public:
	// Metodos
	void setup(const std::string &, int);
	void informTransitionStatus();
	void informDespiertoStatus();
	void informDormidoStatus();
	void informNumCorrectKicks(unsigned long);

private:

	// Fields
	ofxOscSender sender;
};