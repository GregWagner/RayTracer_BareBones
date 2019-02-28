#include "ofApp.h"
#include "ofxGui.h"

#include "GeometricObjects/Sphere.h"
#include "Utilities/Vector3D.h"
#include "ViewPlane.h"
ofxFloatSlider lineSpacingSlider;
ofxToggle lineTestToggle;
ofxPanel gui;
ofImage img;
ofColor backgroundColor = ofColor(0, 0, 0);

ViewPlane viewPlane;
int GUI_height = 80;

Sphere sphereRed, sphereGreen, sphereBlue;

//--------------------------------------------------------------
void ofApp::setup() {

  //simple test to see that teh Vector3D class compiles, links and runs correctly.
  cout << "Hello Joel." << endl;

  Vector3D a = Vector3D(1, 2, 3);
  Vector3D b = Vector3D(1, 1, 1);
  Vector3D c = a - b;
  cout << "a = (" << a.x << ", " << a.y << ", " << a.z << ")" << endl;
  cout << "c = (" << c.x << ", " << c.y << ", " << c.z << ")" << endl;


  //Create a ViewPlane that is 500x500. The actuall window will be larger.
  viewPlane = ViewPlane(500, 500);

  //Set the inside size of the window to be taller than the viewPlane to have room at the tip for the GUI
  ofSetWindowShape(viewPlane.hres, viewPlane.vres + GUI_height);
  ofSetWindowPosition(30, 30);
  ofBackground(backgroundColor);

  //This allocates space for an offscreen buffer. 
  //The image will be rendered in this buffer pixel by pixel. Then, when all updates are done for the frame, the 
  //   buffer is sent to the display.
  //Notice that this large buffer is only created once. Each frame, it is reused.
  img.allocate(viewPlane.hres, viewPlane.vres, OF_IMAGE_COLOR);
  img.setColor(backgroundColor);

  gui.setup();
  // add a slider with <label>, <initial value>, <min>, <max>
  gui.add(lineSpacingSlider.setup("Spacing", 10, 1, 100));
  gui.add(lineTestToggle.setup("Show Drawing Example", true));

  sphereRed   = Sphere(0, 0, 100, 100);
  sphereGreen = Sphere(0, 0, 50, 50);
  sphereBlue  = Sphere(100, 50, 100, 50);
}

//--------------------------------------------------------------
void ofApp::update() {

  img.setColor(backgroundColor);
  // Default circle resolution 10, which draws a regular Icosagon.
  // ofSetCircleResolution(100);

  // int centerX = ofGetWidth() / 2;
  // int centerY = ofGetHeight() / 2;
  // ofDrawCircle(centerX, centerY, radius);
  
  if (lineTestToggle) {
    int blue = 0;
    for (double x = 0; x < img.getWidth(); x += lineSpacingSlider) {
      blue = (255 * x) / img.getWidth();
      for (int y = 0; y < img.getHeight(); y++) {
        img.setColor(x, y, ofColor(255, 0, blue));
      }
    }
  } 
  else {
    // This loop ray traces a ray from the center of each pixel straight down
    // the z axis. Thus, the direction of every ray is: (0,0,-1) Let row range
    // from 0 to vres-1. Let col (column) range form 0 to hres-1. Then the world
    // coordinates (x, y, z) of the start or origin of each ray is:
    
    //for speed, do not create a new ray each itteration of the loop
    Ray ray = Ray(); //the default direction is (0,0,1) which is what we want for all our rays here.
    ShadeRec hitReturnData = ShadeRec();

    sphereBlue.set_center(100, 50, 110 - lineSpacingSlider);

    double hitTime;
    ofColor pixelColor = NULL; 
    ofColor RED   = ofColor(200, 0, 0); 
    ofColor GREEN = ofColor(0, 200, 0);
    ofColor BLUE  = ofColor(70, 70, 255);

    for (double col = 0; col < viewPlane.hres; col++) {
      for (int row = 0; row < viewPlane.vres; row++) {
        
        double minHitTime = std::numeric_limits<double>::max();
        ofColor pixelColor = NULL; 

        ray.start.x = viewPlane.pixelSize * (col - 0.5*(viewPlane.hres-1));
        ray.start.y = viewPlane.pixelSize * ((viewPlane.vres - row) - 0.5*(viewPlane.vres - 1));

        //Since each ray is traced in the direction (0,0,1) with z<ray.start.z will not be hit by the ray.
        ray.start.z = 10; //Best to start the ray some distance in front of the eye 

        //Each ray is traced to each of the three spheres.
        //NOTE: hitTime is an ***output*** variable. If the input ray hits the sphere, then
        //     the sphere's hit() method sets its value to the **first**  intersection point that the given ray 
        //     hits. 
        //Whenever we find a hit, we look at the hitTime, if that hitTime is less than any other object's hitTime
        //     for this particular ray, then that hit point is in front of any past hitpoints for the given ray.
        if (sphereRed.hit(ray, hitTime, hitReturnData)) {
          if (hitTime < minHitTime) { //This will **always** be true since the red sphere is the first object tested.
            minHitTime = hitTime;
            pixelColor = RED;
          }
        }
        if (sphereGreen.hit(ray, hitTime, hitReturnData)) {
          if (hitTime < minHitTime) {
            minHitTime = hitTime;
            pixelColor = GREEN;
          }
        }
        if (sphereBlue.hit(ray, hitTime, hitReturnData)) {
          if (hitTime < minHitTime) {
            minHitTime = hitTime;
            pixelColor = BLUE;
          }
        } 


        if (pixelColor != NULL) {
          img.setColor(col, row, pixelColor);
        }
      }
    }
    
  }
  img.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  gui.draw();
  img.draw(0, GUI_height);
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}