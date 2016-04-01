#include "ofApp.h"
#include "ofxIldaFrame.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground( 0 );
    receiver.setup( PORT );
    
    etherdream.setup();
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    float speed = 10000;//ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 30000);
    ofLog() << "Speed: " << speed;
    etherdream.setPPS(speed);
    
    while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage m;
        receiver.getNextMessage( m );
        
        if( m.getAddress() == "/new" ) {
            lines.clear();
            ildaFrame.clear();
        }
        if( m.getAddress() == "/path" ) {
            ofPoint point;
            ofPolyline line;
            for( int i = 0; i < m.getNumArgs(); i++ ) {
                if( i%2==0) {
                    point.x = m.getArgAsFloat( i );
                } else {
                    point.y = m.getArgAsFloat( i );
                    //point *= 2.0;
                    
                    ofVec2f scale( 1 / 19, 1 / 10 );
                    ofPoint p = ofPoint(point.x / (float) ofGetWidth(), point.y / (float)ofGetHeight());
                    p *= 5.0;
                    //point *= scale;
                    line.addVertex( p );
                }
            }
            //line.simplify( 2.0 );
            lines.push_back( line );
            ildaFrame.polyProcessor.params.targetPointCount = 1500;
            ildaFrame.addPoly( line );
            
        }
        
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ildaFrame.update();
    
    // draw to the screen
    ildaFrame.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    // send points to the etherdream
    etherdream.setPoints(ildaFrame);
    
    ofSetColor(255);
    ofDrawBitmapString(ildaFrame.getString(), 10, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'f': ofToggleFullscreen(); break;
            
            
            // clear the frame
        case 'c': ildaFrame.clear(); break;
        case 'n': {
            break;
        }
        case '>': ildaFrame.polyProcessor.params.targetPointCount += 10; break;
        case '<': if(ildaFrame.polyProcessor.params.targetPointCount > 20) ildaFrame.polyProcessor.params.targetPointCount -= 10; break;

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
    ildaFrame.getLastPoly().lineTo(x / (float)ofGetWidth(), y / (float)ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ildaFrame.addPoly();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
