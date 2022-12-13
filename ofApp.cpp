#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);	
}

//--------------------------------------------------------------
void ofApp::update() {

	this->location_list.clear();

	ofFbo fbo;
	ofPixels pixels;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);

	ofTranslate(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
	ofRotate(ofGetFrameNum() * 0.66666666666666666);
	this->draw_arrow(glm::vec2(0, 0), glm::vec2(0, -1), 330, ofColor(255));

	fbo.end();
	fbo.readToPixels(pixels);

	ofColor pix_color;
	int span = 16;
	for (float x = 0 + span * 0.5; x < ofGetWidth(); x += span) {

		for (float y = 0 + span * 0.5; y <= ofGetHeight(); y += span) {

			pix_color = pixels.getColor(x, y);
			if (pix_color != ofColor(0, 0)) {

				this->location_list.push_back(glm::vec3(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.5, 0));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (auto& location : this->location_list){

		auto deg = ofMap(ofNoise(glm::vec4(location * 0.0025, ofGetFrameNum() * 0.01)), 0, 1, -360, 360);
		auto target = glm::vec3(cos(deg *DEG_TO_RAD), sin(deg * DEG_TO_RAD), 0);

		this->draw_arrow(location, location + target, 10, ofColor(255));
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 next_location, float size, ofColor color) {

	auto angle = std::atan2(next_location.y - location.y, next_location.x - location.x);

	ofFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}