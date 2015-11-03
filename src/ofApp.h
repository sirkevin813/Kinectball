#pragma once

#include "ofMain.h"
#include "ofxKinectCommonBridge.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxKinectCommonBridge kinect;
		ofShader k4wShader;
		ofPlanePrimitive plane;

		float ball_x;
		float ball_y;
		float ball_dx;
		float ball_dy;

		bool first_time;

		int leftHand_x_p1;
		int leftHand_y_p1;
		int rightHand_x_p1;
		int rightHand_y_p1;

		int leftHand_x_p2;
		int leftHand_y_p2;
		int rightHand_x_p2;
		int rightHand_y_p2;

		bool p1_active;  //which skeletons are active
		bool p2_active;  

		ofTrueTypeFont font;
		int left_score;
		int right_score;

		bool hockeyMode;
		bool passMode;

		int seconds;
		int lastSecond;

		//constants 
		float MAGNITUDE;
};
