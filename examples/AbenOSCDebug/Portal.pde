class Portal
{
  NetAddress netAddress = null;
  long onlineTimeStamp = -100000;
  long activationTimeStamp = -100000;

  int version = -1;
  float threshold = -1;

  boolean isOnline()
  {
    return (millis() -  onlineTimeStamp < onlineTime);
  }

  boolean isActivated()
  {
    return (millis() -  activationTimeStamp < activationTime);
  }
}
