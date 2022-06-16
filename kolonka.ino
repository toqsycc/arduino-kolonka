// Arduino Nano 328P (w/ Old Bootloader)
// Bluetooth and TF card stereo speaker
// OLED display, RGB diodes, TF module

// Pinout:
// OLED |   SDA: A4  SCK: A5
// RGB  |   Rch: D3  Gch: D5  Bch: D6
//      |   Controls Inverted! (Common +5V)

#define RGBD_CHANNELS     3   // Count of PWM color bus
#define RED_PWMC          3   // PWM bus, Red
#define GRN_PWMC          5   // PWM bus, Green
#define BLU_PWMC          6   // PWM bus, Blue

class RGBDiode
{
private:
  byte            *channels;
  
  // Automatic disable LED on init
  inline void     InitializeBus()
  {
    pinMode(RED_PWMC, OUTPUT);
    pinMode(GRN_PWMC, OUTPUT);
    pinMode(BLU_PWMC, OUTPUT);
    for (byte i(RED_PWMC); i <= BLU_PWMC; i++)
    {
      if (i == 4) continue;
      else
        digitalWrite(i, HIGH);
    }
  }
  // Automatic set LED color on init 
  inline void   InitializeBus(byte* color)
  {
    pinMode(RED_PWMC, OUTPUT);
    pinMode(GRN_PWMC, OUTPUT);
    pinMode(BLU_PWMC, OUTPUT);
    for (byte i(RED_PWMC), e(0); i <= BLU_PWMC; i++, e++)
    {
      if (i == 4) continue;
      else
        analogWrite(i, e);
    }
  }
public:
  RGBDiode()
  {
    channels = new byte[RGBD_CHANNELS]{ 0x00 };
    this->InitializeBus();
  }
  RGBDiode(byte* color)
  {
    channels = color;
    this->InitializeBus(color);
  }
  ~RGBDiode()
  {
    memset(this, NULL, sizeof(*this));
  }
};

#include <DFRobotDFPlayerMini.h>
#include <OLED_I2C.h>
OLED dsp(SDA, SCL);
extern uint8_t SmallFont[];
String out("RGB mode");
RGBDiode *led;
void setup() {
  // put your setup code here, to run once:
  dsp.begin(SSD1306_128X32);
  dsp.setFont(SmallFont);
  led = new RGBDiode();
}

void loop() {
  // put your main code here, to run repeatedly:
  dsp.clrScr();
  //dsp.invert(true);
  dsp.print(out.c_str(), LEFT, 0);
  dsp.update();
  while(1);
}
