import peasy.PeasyCam;
import ch.bildspur.postfx.builder.*;
import ch.bildspur.postfx.pass.*;
import ch.bildspur.postfx.*;

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress mcuAddress;

PostFX fx;

int padding = 50;

String mcuPath = "/dev/tty.usbserial-14410";
boolean isMcuAvailable = false;

MicroControllerUnit mcu = new MicroControllerUnit(this, mcuPath);

PeasyCam cam;

boolean debug = true;

Portal[] portals = new Portal[5];

void setup()
{
  frameRate(120);
  size(800, 600, P3D);
  surface.setTitle("åben Debug Monitor");

  fx = new PostFX(this);

  cam = new PeasyCam(this, -20, 200, 0, 800);
  cam.rotateX(radians(-75));

  randomSeed(7148);
  initPortals();

  // try to attach
  checkDevices();
  if (isMcuAvailable)
    mcu.attach();
}

void initPortals()
{
  // fix luboids sizes
  float hw = width / 2f;
  float hh = height / 2f;

  for (int i = 0; i < portals.length; i++)
  {
    portals[i] = new Portal(i, i * 4, 
      random(-hw, hw), 
      random(-hh, hh), 
      random(0, 360));
  }
}

void draw()
{
  if (oscP5 == null)
  {
    // osc
    oscP5 = new OscP5(this, 9000);
    mcuAddress = new NetAddress("192.168.4.1", 8000);
  }

  checkDevices();

  background(0);
  updateLights();
  renderLights();

  // add bloom filter
  fx.render()
    .bloom(0.0f, 10, 20f)
    .compose();

  showInfo();
}

void updateLights()
{
  if (!mcu.isAttached())
    return;

  String raw = mcu.readData();

  if (debug && raw != null && !raw.startsWith("SLR") && !raw.trim().equals(""))
  {
    println("MCU: " + raw.trim());
  }

  if (raw == null || !raw.startsWith("SLR"))
    return;

  // display debug data
  if (debug)
    showDebug(raw.trim());

  // relevant data
  String[] data = raw.split(";");
  for (int i = 0; i < data.length - 2; i++)
  {
    try
    {
      String[] rawValues = data[i+1].split(" ");

      float r = gamma8[(int)round(map(Float.parseFloat(rawValues[0]), 0f, 1f, 0f, 255f))];
      float g = gamma8[(int)round(map(Float.parseFloat(rawValues[1]), 0f, 1f, 0f, 255f))];
      float b = gamma8[(int)round(map(Float.parseFloat(rawValues[2]), 0f, 1f, 0f, 255f))];

      portals[i].rgb = color(r, g, b);
    }
    catch(Exception ex)
    {
    }
  }
}

void showDebug(String text)
{
  cam.beginHUD();
  fill(0, 255, 0);
  textSize(14);
  text("Debug \"" + text + "\"", 20, height - 50);
  cam.endHUD();
}

void showInfo()
{
  cam.beginHUD();
  fill(255);
  textSize(14);
  text("MCU detected: " + isMcuAvailable + "\nattached: " + (mcu.isAttached()) + "\nFPS: " + round(frameRate), 20, 20);
  cam.endHUD();
}

void renderLights()
{
  pushMatrix();

  for (Portal portal : portals)
  {
    stroke(75);
    fill(portal.rgb);

    pushMatrix();
    translate(portal.x, portal.y);
    rotateZ(radians(portal.r));

    // side 1
    pushMatrix();
    translate(portal.width * 0.5f, 0f);
    box(portal.thickness, portal.thickness, portal.height);
    popMatrix();

    // side 2
    pushMatrix();
    translate(portal.width * -0.5f, 0f);
    box(portal.thickness, portal.thickness, portal.height);
    popMatrix();

    // top
    pushMatrix();
    translate(0f, 0f, portal.height / 2f + (portal.thickness / 2f));
    box(portal.width + portal.thickness, portal.thickness, portal.thickness);
    popMatrix();

    popMatrix();
  }
  popMatrix();
}

void keyPressed()
{
  if (key == ' ')
  {
    // try to connect
    if (isMcuAvailable)
      mcu.attach();
    else
      println("No MCU detected!");
  }

  if (key == 'i')
  {
    int seed = (int)random(0, 10000);
    randomSeed(seed);
    initPortals();

    println("Seed: " + seed);
  }

  if (key == 's')
  {
    OscMessage msg = new OscMessage("/aben/show/start");
    msg.add(1.0f);
    oscP5.send(msg, mcuAddress);
  }

  if (key == 'r')
  {
    OscMessage msg = new OscMessage("/aben/rainbow/on");
    msg.add(1.0f);
    oscP5.send(msg, mcuAddress);
  }

  if (key == 'd') {
    OscMessage msg = new OscMessage("/aben/portal/debug/activate");
    msg.add(float(round(random(0, 5))));
    oscP5.send(msg, mcuAddress);
  }
}

void checkDevices()
{
  isMcuAvailable = new File(mcuPath).exists();
}

void oscEvent(OscMessage theOscMessage) {
}
