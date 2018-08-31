#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	this->cap.open("D:\\video\\image32.mp4");
	this->cap_size = cv::Size(1280, 720);

	cv::Mat cap_frame;
	while (true) {

		this->cap >> cap_frame;
		if (cap_frame.empty()) {

			break;
		}

		ofImage image;
		image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
		cv::Mat frame = cv::Mat(cv::Size(image.getWidth(), image.getHeight()), CV_MAKETYPE(CV_8UC3, image.getPixels().getNumChannels()), image.getPixels().getData(), 0);

		cv::resize(cap_frame, cap_frame, this->cap_size);
		cv::cvtColor(cap_frame, cap_frame, CV_BGR2RGB);
		cap_frame.copyTo(frame);

		this->frames.push_back(frame);
		this->images.push_back(image);
	}

	this->src.allocate(ofGetWidth(), ofGetHeight());
	this->dst.allocate(ofGetWidth(), ofGetHeight());

	this->shader.load("shader/shader.vert", "shader/shader.frag");

}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int frame_number = ofGetFrameNum() % this->images.size();

	this->dst.begin();
	ofClear(0);

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex0", this->images[(frame_number + 0) % this->images.size()], 1);
	this->shader.setUniformTexture("tex1", this->images[(frame_number + 5) % this->images.size()], 2);
	this->shader.setUniformTexture("tex2", this->images[(frame_number + 10) % this->images.size()], 3);

	this->src.draw(0, 0);
	this->shader.end();

	this->dst.end();

	ofSetColor(255);
	this->dst.draw(0, 0);

}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(1280, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}