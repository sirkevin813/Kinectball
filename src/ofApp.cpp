#include "ofApp.h"

/*Notes:
	time_since_P1_has_touched_ball and time_since_p2_has
	_touched_ball update and if one gets too high the 
	hands turn red and a red countdown appears before 
	seconds returns to 0
*/

//--------------------------------------------------------------
void ofApp::setup(){

	kinect.initSensor();
	//kinect.initIRStream(640, 480);
//	kinect.initColorStream(640, 480, true);
	kinect.initDepthStream(640, 480, true);
	kinect.initSkeletonStream(true);

	//simple start
	kinect.start();
	ofDisableAlphaBlending(); //Kinect alpha channel is default 0;
	ofSetWindowShape(640, 480);

	first_time=true;
	
	ball_x = 480/2;
	ball_y = 640/2;
	ball_dx = 4;
	ball_dy = 4;

	p1_active = false;
	p2_active = false;

	font.loadFont("XPED.ttf", 32);
	left_score=0;
	right_score=0;

	 hockeyMode= true;
	 passMode= false;

	MAGNITUDE = 6;

	seconds=0;
	lastSecond=-1;

}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();

	p1_active = false;
	p2_active = false;

	if(kinect.isNewSkeleton()) {
		std::cout<<"new skeleton"<<std::endl;
        for( int i = 0; i < kinect.getSkeletons().size(); i++) 
        {
                // has a head? probably working ok then :)
            if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
            {
				std::cout<<i<<std::endl;
				if (!p1_active){
					SkeletonBone leftHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_LEFT)->second;
					leftHand_x_p1 = leftHand.getScreenPosition().x;
					leftHand_y_p1 = leftHand.getScreenPosition().y;

					SkeletonBone rightHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_RIGHT)->second;
					rightHand_x_p1 = rightHand.getScreenPosition().x;
					rightHand_y_p1 = rightHand.getScreenPosition().y;
					p1_active=true;
				}
				else if (!p2_active){
					SkeletonBone leftHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_LEFT)->second;
					leftHand_x_p2 = leftHand.getScreenPosition().x;
					leftHand_y_p2 = leftHand.getScreenPosition().y;

					SkeletonBone rightHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_RIGHT)->second;
					rightHand_x_p2 = rightHand.getScreenPosition().x;
					rightHand_y_p2 = rightHand.getScreenPosition().y;
					p2_active=true;
				}
	
				// just get the first two				
            }
        }
    }


	ball_x+=ball_dx;
	ball_y+=ball_dy;

	if (ofDist(rightHand_x_p1, rightHand_y_p1, (float)ball_x, (float)ball_y)<60){
		//Vec calculations
		//slope (this is our direction
		float delta_y = rightHand_y_p1 - ball_y;
		float delta_x = rightHand_x_p1 - ball_x;
		ofVec2f v2f(delta_y, delta_x);
		v2f.normalize(); //boil it down to JUST a direction
		v2f*=MAGNITUDE;
		std::cout<<v2f<<std::endl;
		
		ball_dx=v2f.x; 
		ball_dy=v2f.y;
	}

	else if (ofDist(leftHand_x_p1, leftHand_y_p1, (float)ball_x, (float)ball_y)<60){
		//Vec calculations
		//slope (this is our direction
		float delta_y = leftHand_y_p1 - ball_y;
		float delta_x = leftHand_x_p1 - ball_x;
		ofVec2f v2f(delta_y, delta_x);
		v2f.normalize(); //boil it down to JUST a direction
		v2f*=MAGNITUDE;
		std::cout<<v2f<<std::endl;
		
		ball_dx=v2f.x; 
		ball_dy=v2f.y;
	}

	else if (ofDist(rightHand_x_p2, rightHand_y_p2, (float)ball_x, (float)ball_y)<60){
		//Vec calculations
		//slope (this is our direction
		float delta_y = leftHand_y_p2 - ball_y;
		float delta_x = leftHand_x_p2 - ball_x;
		ofVec2f v2f(delta_y, delta_x);
		v2f.normalize(); //boil it down to JUST a direction
		v2f*=MAGNITUDE;
		std::cout<<v2f<<std::endl;
		
		ball_dx=v2f.x; 
		ball_dy=v2f.y;
	}

	else if (ofDist(leftHand_x_p2, leftHand_y_p2, (float)ball_x, (float)ball_y)<60){
		//Vec calculations
		//slope (this is our direction
		float delta_y = leftHand_y_p2 - ball_y;
		float delta_x = leftHand_x_p2 - ball_x;
		ofVec2f v2f(delta_y, delta_x);
		v2f.normalize(); //boil it down to JUST a direction
		v2f*=MAGNITUDE;
		std::cout<<v2f<<std::endl;
		
		ball_dx=v2f.x; 
		ball_dy=v2f.y;
	}

	

	if (ball_x<=0){
		ball_dx=-ball_dx;
		if (hockeyMode) right_score++;
		if (passMode  ){ seconds=0;
		std::cout<<"ball_x<=0"<<std::endl;}
	}
	if (ball_x >= 640){
		ball_dx=-ball_dx;
		if (hockeyMode) left_score++;
		if (passMode  ){ seconds=0;
		std::cout<<"ball_x >= 640"<<std::endl;}
	}
	if (ball_y<=0 || ball_y >= 480){
		ball_dy=-ball_dy;
		if (passMode  ){ seconds=0;
		std::cout<<"ball_y<=0 || ball_y >= 480  :  "<<ball_y<<std::endl;}
	}

	
		
		
	if (ofGetSeconds() != lastSecond){
		lastSecond=ofGetSeconds();
		seconds++;
	 }


/*
		for( int i = 0; i < kinect.getSkeletons().size(); i++) 
		{

			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
			{

				// just get the first one
				SkeletonBone headBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD)->second;
				SkeletonBone lHandBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_LEFT)->second;
				SkeletonBone rHandBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_RIGHT)->second;
				ofVec3f hb( headBone.getScreenPosition().x, headBone.getScreenPosition().y, 0 );
				head = head.getInterpolated(hb, 0.5);
				head.z =  ofInterpolateCosine( head.z, headBone.getStartPosition().x, 0.5) + 0.1;
				ofVec3f lhb(lHandBone.getScreenPosition().x, lHandBone.getScreenPosition().y, 0);
				lHand = lHand.getInterpolated( lhb, 0.5);
				lHand.z = ofInterpolateCosine( lHand.z, lHandBone.getStartPosition().x, 0.5);
				ofVec3f rhb(rHandBone.getScreenPosition().x, rHandBone.getScreenPosition().y, 0);
				rHand = rHand.getInterpolated( rhb, 0.5);
				rHand.z = ofInterpolateCosine( rHand.z, rHandBone.getStartPosition().x, 0.5);

				cout << headBone.getScreenPosition()  << endl;
				cout << rHandBone.getScreenPosition() << endl;
				cout << lHandBone.getScreenPosition() << endl;
*/
}

//--------------------------------------------------------------
void ofApp::draw(){
//	kinect.draw(640,0);
	kinect.drawDepth(0, 0);

	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofSetLineWidth(3.0f);
	auto skeletons = kinect.getSkeletons();
	for(auto & skeleton : skeletons) {
		for(auto & bone : skeleton) {
			switch(bone.second.getTrackingState()) {
			case SkeletonBone::Inferred:
				ofSetColor(0, 0, 255);
				break;
			case SkeletonBone::Tracked:
				ofSetColor(0, 255, 0);
				break;
			case SkeletonBone::NotTracked:
				ofSetColor(255, 0, 0);
				break;
			}

			auto index = bone.second.getStartJoint();
			auto connectedTo = skeleton.find((_NUI_SKELETON_POSITION_INDEX) index);
			if (connectedTo != skeleton.end()) {
				ofLine(connectedTo->second.getScreenPosition(), bone.second.getScreenPosition());
			}

			ofCircle(bone.second.getScreenPosition(), 10.0f);
		}
	}
	


	first_time=false;

	ofPopStyle();
	
	//hands
	ofCircle( leftHand_x_p1, leftHand_y_p1, 40);
	ofCircle(rightHand_x_p1,rightHand_y_p1, 40);

	ofSetColor(ofColor::aquamarine);
	ofCircle( leftHand_x_p2, leftHand_y_p2, 40);
	ofCircle(rightHand_x_p2,rightHand_y_p2, 40);
	ofSetColor(ofColor::white);

	//ball
	ofSetColor(ofColor::aqua);
	ofCircle(ball_x, ball_y, 30);
	//std::cout<<"ball_x: "<<ball_x<<" ball_y: "<<ball_y<<" ball_dx: "<<ball_dx<<" ball_dy: "<<ball_dy<<std::endl;
	ofSetColor(255);

	//score
	if (hockeyMode){
		font.drawString(std::to_string(left_score), 150,100);
		font.drawString(std::to_string(right_score),470,100);
	}
	else{
		font.drawString(std::to_string(seconds), 310, 100);
	}

	//score mode info
	font.drawString("Mode:", 25, 450);
	if (hockeyMode) ofSetColor(ofColor::green);
	font.drawString("Hockey(1)", 125, 450);
	ofSetColor(ofColor::white);
	if (passMode) ofSetColor(ofColor::green);
	font.drawString("Pass(2)",300, 450);
	ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key=='1'){
		hockeyMode=true;
		passMode=false;
		right_score=0;
		left_score=0;
	}
	else if (key=='2'){
		std::cout<<"still pressed"<<std::endl;
		passMode=true;
		hockeyMode=false;
		seconds=0;
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
