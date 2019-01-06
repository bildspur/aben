import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress network;

Portal[] portals = new Portal[5];

long onlineTime = 10 * 1000;
long activationTime = 5 * 1000;

PFont font;

void setup() {
  size(620, 225);
  frameRate(25);
  pixelDensity(2);

  font = createFont("Andale Mono", 100f);

  oscP5 = new OscP5(this, 8000); // incoming
  network = new NetAddress("192.168.4.255", 9000); // outgoing

  for (int i = 0; i < portals.length; i++)
  {
    portals[i] = new Portal();
  }
}


void draw() {
  background(0);

  float px = 30;
  float lh = 20;

  float h = lh + 20;

  fill(255);
  textFont(font);
  textSize(20);
  text("Portals (" + portals.length + ")", px, h);

  textSize(14);
  h += lh;
  text("id | netaddress (ip)  | online | activated | firmware | threshold |", px, h);
  h += lh;
  text("-- | ---------------- | ------ | --------- | -------- | --------- |", px, h);

  for (int i = 0; i < portals.length; i++)
  {
    Portal p = portals[i];

    h += lh;

    if (p.isOnline())
      fill(0, 255, 0);
    else
      fill(255, 0, 0);

    text(nf(i, 2) + " | " 
      + ps(p.netAddress, 16) + " | " 
      + ps(p.isOnline(), 6) + " | " 
      + ps(p.isActivated(), 9) + " | " 
      + ps(p.version, 8) + " | " 
      + ps(p.threshold, 9) + " | " 
      , px, h);
  }
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

  if (msg.checkAddrPattern("/aben/portal/online"))
  {
    int id = msg.get(0).intValue();
    Portal portal = portals[id];

    portal.netAddress = msg.netAddress();
    portal.onlineTimeStamp = millis();
  }

  if (msg.checkAddrPattern("/aben/portal/activated"))
  {
    int id = msg.get(0).intValue();
    Portal portal = portals[id];

    portal.activationTimeStamp = millis();
  }

  if (msg.addrPattern().startsWith("/aben/portal/") && msg.addrPattern().endsWith("/version"))
  {
    int id = int(msg.addrPattern().replace("/aben/portal/", "").replace("/version", ""));
    Portal portal = portals[id];

    portal.version = int(msg.arguments()[0].toString());
  }

  if (msg.addrPattern().startsWith("/aben/portal/") && msg.addrPattern().endsWith("/threshold"))
  {
    int id = Integer.parseInt(msg.addrPattern().replace("/aben/portal/", "").replace("/threshold", ""));
    Portal portal = portals[id];
    portal.threshold = msg.get(0).floatValue();
  }
}

String ps(Object o, int length)
{
  String s = o != null ? o.toString() : "";

  while (s.length() < length)
  {
    s = " " + s;
  }

  return s;
}
