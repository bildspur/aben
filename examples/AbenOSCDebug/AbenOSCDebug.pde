/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress network;

void setup() {
  size(400, 400);
  frameRate(25);

  oscP5 = new OscP5(this, 8000); // incoming
  network = new NetAddress("192.168.4.255", 9000); // outgoing
}


void draw() {
  background(0);
}

void mousePressed() {
  OscMessage msg = new OscMessage("/aben/portal/settings");
  msg.add(0);
  oscP5.send(msg, network);
}

void oscEvent(OscMessage msg) {
  print(msg.netAddress() + " (" + msg.addrPattern() + ")");

  if (msg.arguments().length > 0)
  {
    print(": " + msg.typetag());
    print(" > " + msg.arguments()[0]);
  }

  println();
}
