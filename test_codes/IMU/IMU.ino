#include <Wire.h>

#define MPU9250_ADDR 0x68
#define AK8963_ADDR  0x0C

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Wake up MPU-9250
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(0x6B); // Power management
  Wire.write(0x00); // Wake up
  Wire.endTransmission(true);

  // Enable I2C bypass to access AK8963 magnetometer
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(0x37); // INT_PIN_CFG register
  Wire.write(0x02); // Bypass enable
  Wire.endTransmission(true);

  // Initialize magnetometer (AK8963)
  Wire.beginTransmission(AK8963_ADDR);
  Wire.write(0x0A); // CNTL1 register
  Wire.write(0x16); // Continuous measurement mode 2, 16-bit
  Wire.endTransmission(true);

  Serial.println("MPU-9250 initialized");
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz, mx, my, mz;

  // Read accelerometer
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU9250_ADDR, 6, true);
  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();

  // Read gyroscope
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU9250_ADDR, 6, true);
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();

  // Read magnetometer
  Wire.beginTransmission(AK8963_ADDR);
  Wire.write(0x03);
  Wire.endTransmission(false);
  Wire.requestFrom(AK8963_ADDR, 6, true);
  if (Wire.available() == 6) {
    mx = Wire.read() | (Wire.read() << 8);
    my = Wire.read() | (Wire.read() << 8);
    mz = Wire.read() | (Wire.read() << 8);
  }

  Serial.print("Accel: ");
  Serial.print(ax); Serial.print(", ");
  Serial.print(ay); Serial.print(", ");
  Serial.print(az); Serial.print(" | ");

  Serial.print("Gyro: ");
  Serial.print(gx); Serial.print(", ");
  Serial.print(gy); Serial.print(", ");
  Serial.print(gz); Serial.print(" | ");

  Serial.print("Mag: ");
  Serial.print(mx); Serial.print(", ");
  Serial.print(my); Serial.print(", ");
  Serial.println(mz);

  delay(200);
}
