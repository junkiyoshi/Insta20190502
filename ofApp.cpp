#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->radius = 10;
	auto flag = true;
	float sqrt_3 = sqrt(3);
	for (float y = -ofGetHeight() * 0.5 - radius; y < ofGetHeight() * 0.5 + radius; y += radius * 1.5) {

		for (float x = -ofGetWidth() * 0.5 - radius; x < ofGetWidth() * 0.5 + radius; x += radius * sqrt_3) {

			auto location = flag ? glm::vec2(x, y) : glm::vec2(x + this->radius * sqrt_3 * 0.5, y);
			this->hex_locations.push_back(location);
			ofColor hex_color;
			hex_color.setHsb(ofRandom(255), 255, 255);
			this->hex_colors.push_back(hex_color);
		}
		flag = !flag;
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int k = 0; k < 3; k++) {

		float noise_seed = ofRandom(1000);
		for (int i = 0; i < this->hex_locations.size(); i++) {

			auto noise_location = glm::vec2(this->hex_locations[i].x, ofMap(ofNoise(noise_seed, this->hex_locations[i].x * 0.001, ofGetFrameNum() * 0.001), 0, 1, -ofGetHeight() * 0.75, ofGetHeight() * 0.75));
			auto distance = glm::distance(this->hex_locations[i], noise_location);

			if (distance < 60) {

				ofPushMatrix();
				ofTranslate(this->hex_locations[i]);

				vector<glm::vec2> vertices;
				for (int deg = 30; deg <= 390; deg += 60) {

					vertices.push_back(glm::vec2((radius)* cos(deg * DEG_TO_RAD), (radius)* sin(deg * DEG_TO_RAD)));
				}

				ofNoFill();
				ofSetColor(this->hex_colors[i]);

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofFill();
				ofSetColor(this->hex_colors[i], ofMap(distance, 0, 60, 255, 32));

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}