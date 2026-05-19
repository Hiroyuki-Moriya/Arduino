// sketch name = TEMPandHUM_SENS
// Outline:温度と湿度センサー DHT11用
// V0.0 ELEGOO社のソースをほぼ転用
// >>  ライブラリ導入 SimpleDHT
// >>  ビットシフトと結合

/* 参考資料
  ELEGOO社
    Lesson 11 DHT11 Temperature and Humidity Sensor
      取説 P85
      ソース  DHT11_Example > DHT11_Example.ino
*/
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

/*
 * Initialize the serial port.
 */
void setup()
{
  Serial.begin(9600);
}

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment(float *temperature, float *humidity)
{
  static unsigned long measurement_timestamp = millis();

  /* Measure once every four seconds. */
  if (millis() - measurement_timestamp > 3000ul)
  {
    if (dht_sensor.measure(temperature, humidity) == true)
    {
      measurement_timestamp = millis();
      return (true);
    }
  }

  return (false);
}

/*
 * Main program loop.
 */
void loop()
{
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if (measure_environment(&temperature, &humidity) == true)
  {
    Serial.print("T = ");
    Serial.print(temperature, 1);
    Serial.print(" deg. C, H = ");
    Serial.print(humidity, 1);
    Serial.println("%");
  }
}
