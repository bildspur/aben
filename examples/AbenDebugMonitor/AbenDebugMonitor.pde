import peasy.PeasyCam;
import ch.bildspur.postfx.builder.*;
import ch.bildspur.postfx.pass.*;
import ch.bildspur.postfx.*;

PostFX fx;

int padding = 50;

String mcuPath = "/dev/tty.SLAB_USBtoUART";
boolean isMcuAvailable = false;

MicroControllerUnit mcu = new MicroControllerUnit(this, mcuPath);

PeasyCam cam;

boolean debug = true;

Portal[] portals = new Portal[5];

void setup()
{
  frameRate(60);
  size(800, 600, P3D);
  surface.setTitle("åben Debug Monitor");
  //pixelDensity = 2;

  fx = new PostFX(this);

  cam = new PeasyCam(this, 400);

  randomSeed(100);

  // fix luboids sizes
  float hw = width / 2f;
  float hh = height / 2f;

  for (int i = 0; i < portals.length; i++)
  {
    portals[i] = new Portal(i, i * 4, random(-hw, hw), random(-hh, hh));
  }

  // try to attach
  checkDevices();
  if (isMcuAvailable)
    mcu.attach();
}

void draw()
{
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

  if (debug && raw != null && !raw.startsWith("SLR") && raw.trim() != "")
    println("MCU: " + raw.trim());

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
      float value = Float.parseFloat(data[i+1]);
      int brightness = (int)round(map(value, 0f, 1f, 0f, 255f));
      portals[i].rgb = color(brightness);
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
  textSize(8);
  text("Debug \"" + text + "\"", 20, height - 50);
  cam.endHUD();
}

void showInfo()
{
  cam.beginHUD();
  fill(255);
  textSize(12);
  text("MCU detected: " + isMcuAvailable + "\tattached: " + (mcu.isAttached()) + "\tFPS: " + round(frameRate), 20, 20);
  cam.endHUD();
}

void renderLights()
{
  pushMatrix();
  //translate(padding, padding);

  for (Portal portal : portals)
  {
    stroke(100);
    strokeWeight(1.0f);

    if (portal.isOn)
    {
      stroke(0, 255, 0);
      strokeWeight(2.0f);
      portal.isOn = false;
    }

    fill(portal.rgb);
    rect(portal.x, portal.y, portal.width, portal.height);
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
}

void checkDevices()
{
  isMcuAvailable = new File(mcuPath).exists();
}
