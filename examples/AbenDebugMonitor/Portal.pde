class Portal
{
  int id;
  color rgb = color(0);
  int dmxAddress;

  float x = 0;
  float y = 0;
  float r = 0;

  float width = 120f;
  float height = 230f;
  float thickness = 20f;

  boolean isOn = false;

  public Portal(int id, int dmxAddress, float x, float y, float r)
  {
    this.id = id;
    this.x = x;
    this.y = y;
    this.r = r;
    this.dmxAddress = dmxAddress;
  }

  boolean isInside(PVector v)
  { 
    return (v.x >= x && v.x <= (x + width))
      && (v.y >= y && v.y <= (y + height));
  }
}
