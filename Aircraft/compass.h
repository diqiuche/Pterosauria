//电子罗盘(GY-271 HMC5883L)
class Ccompass
{
 private :
  HMC5883L mag;
  int16_t mx, my, mz;
  ulong m_lastTime;
  float m_point;

 public :
  Ccompass(){
    Wire.begin();
    Serial.println("HMC5883L: Initializing I2C devices...");
    mag.initialize();
    Serial.print("HMC5883L: Testing device connections...");
    Serial.print(mag.testConnection() ? "successful\n" : "failed\n");
    m_point = 0;
    m_lastTime = millis();
  }

  float GetPoint(){
    ulong currentTime = millis();
    if(currentTime - m_lastTime > 20){
      m_lastTime = currentTime;
      mag.getHeading(&mx, &my, &mz);
      float heading = atan2(my, mx);
      if(heading < 0) heading += 2 * M_PI;
      m_point = (heading * 180/M_PI);
    }
    return m_point;
  }

};
