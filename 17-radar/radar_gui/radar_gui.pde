import processing.serial.*; // imports library for serial communication
import java.awt.event.KeyEvent; // imports library for reading the data from the serial port
import java.io.IOException; // imports lib for IO exception handling

Serial myPort; // define Serial object
PFont orcFont; // define font object

// define variables
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;
int canvasWidth=1200;
int canvasHeight=700;
int rangeLimit=40; // the range limit of the sensor in cms

String serialInterface = "/dev/ttyACM0"; // ***CHANGE THIS TO YOUR ARDUINO PORT - can be a COM port (for example on windows) or /dev/ttyACM0 (on linux)***
int baudRate = 9600;

// intitialize serial communication, and set up the screen
void setup() {
 size(canvasWidth, canvasHeight);
 smooth();
 myPort = new Serial(this, serialInterface, baudRate); // starts the serial communication
 myPort.bufferUntil('.'); // reads the data from the serial port up to the character '.'. So actually it reads this: angle,distance.
}

void draw() {
  fill(98,245,31);

  // simulating motion blur and slow fade of the moving line
  noStroke();
  fill(0,4); 
  rect(0, 0, width, height-height*0.065); 
  fill(98,245,31); // green color
  
  // calls the functions for drawing the radar
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

// starts reading data from the Serial Port
void serialEvent (Serial myPort) { 
  // reads the data from the Serial Port
  data = myPort.readStringUntil('.');
  data = data.substring(0,data.length()-1);
  
  index1 = data.indexOf(",");
  angle= data.substring(0, index1); // value of the angle the Arduino Board sent into the Serial Port
  distance= data.substring(index1+1, data.length());
  
  // converts the String variables into Integer
  iAngle = int(angle);
  iDistance = int(distance);
}

// draws the arcs representing the radar
void drawRadar() {
  pushMatrix();
  translate(width/2,height-height*0.074); // moves the starting coordinates to new location
  noFill();
  strokeWeight(2);
  stroke(98,245,31);

  // draws the arc lines
  arc(0,0,(width-width*0.0625),(width-width*0.0625),PI,TWO_PI);
  arc(0,0,(width-width*0.27),(width-width*0.27),PI,TWO_PI);
  arc(0,0,(width-width*0.479),(width-width*0.479),PI,TWO_PI);
  arc(0,0,(width-width*0.687),(width-width*0.687),PI,TWO_PI);

  // draws the angle lines
  line(-width/2,0,width/2,0);
  line(0, 0, (-width/2)*cos(radians(30)), (-width/2)*sin(radians(30)));
  line(0, 0, (-width/2)*cos(radians(60)), (-width/2)*sin(radians(60)));
  line(0, 0, (-width/2)*cos(radians(90)), (-width/2)*sin(radians(90)));
  line(0, 0, (-width/2)*cos(radians(120)), (-width/2)*sin(radians(120)));
  line(0, 0, (-width/2)*cos(radians(150)), (-width/2)*sin(radians(150)));
  line((-width/2)*cos(radians(30)), 0, width/2, 0);
  popMatrix();
}

// draws the object according to the angle and the distance
void drawObject() {
  pushMatrix();
  translate(width/2, height-height*0.074); // moves the starting coordinates to new location
  strokeWeight(9);
  stroke(255,10,10); // set line to red color
  pixsDistance = iDistance*((height-height*0.1666)*0.025); // converts the distance from the sensor from cm to pixels
  if(iDistance<rangeLimit){
    // draws the object according to the angle and the distance
    line(pixsDistance*cos(radians(iAngle)), -pixsDistance*sin(radians(iAngle)), (width-width*0.505)*cos(radians(iAngle)), -(width-width*0.505)*sin(radians(iAngle)));
  }
  popMatrix();
}

// function to draw a line from the sensor
void drawLine() {
  pushMatrix(); // starting a new drawing state
  strokeWeight(9);
  stroke(30,250,60);
  translate(width/2, height-height*0.074); // moves the starting coordinates to new location
  line(0, 0, (height-height*0.12)*cos(radians(iAngle)), -(height-height*0.12)*sin(radians(iAngle))); // draws the line according to the angle
  popMatrix(); // restores the previous drawing state
}

// draws the text on the screen
void drawText() {
  // start drawing text 
  pushMatrix();
  if(iDistance>rangeLimit) {
    noObject = "Out of Range";
  }
  else {
    noObject = "In Range";
  }
  fill(0, 0, 0);
  noStroke();
  rect(0, height-height*0.0648, width, height);
  fill(98, 245, 31);
  
  textSize(25);
  text("10 cms", width-width*0.3854, height-height*0.0833);
  text("20 cms", width-width*0.281, height-height*0.0833);
  text("30 cms", width-width*0.177, height-height*0.0833);
  text("40 cms", width-width*0.0729, height-height*0.0833);
  
  textSize(40);
  text("Angle: " + iAngle +"  ", width-width*0.48, height-height*0.0277);
  text("Distance: ", width-width*0.26, height-height*0.0277);
  
  if(iDistance<rangeLimit) {
    text("        " + iDistance +" cms", width-width*0.225, height-height*0.0277);
  }

  textSize(25);
  fill(98, 245, 60);
  translate((width-width*0.4994)+width/2*cos(radians(30)), (height-height*0.0907)-width/2*sin(radians(30)));
  rotate(-radians(-60));
  text("30 ", 0, 0);
  resetMatrix();
  translate((width-width*0.503)+width/2*cos(radians(60)), (height-height*0.0888)-width/2*sin(radians(60)));
  rotate(-radians(-30));
  text("60 ", 0, 0);
  resetMatrix();
  translate((width-width*0.507)+width/2*cos(radians(90)), (height-height*0.0833)-width/2*sin(radians(90)));
  rotate(radians(0));
  text("90 ", 0, 0);
  resetMatrix();
  translate(width-width*0.513+width/2*cos(radians(120)), (height-height*0.07129)-width/2*sin(radians(120)));
  rotate(radians(-30));
  text("120 ", 0, 0);
  resetMatrix();
  translate((width-width*0.5104)+width/2*cos(radians(150)), (height-height*0.0574)-width/2*sin(radians(150)));
  rotate(radians(-60));
  text("150 ", 0, 0);
  popMatrix(); 
}
