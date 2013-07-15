#include <Esplora.h>

int last_cmd;
int btn = 9;
const int note[] = {262,277,294,311,330,349,370,392,415,440,466,494,523};

void setup()
{
  Serial.begin(9600);
  for (int a = 0; a < 13; a++)
  {
    Esplora.tone(note[a]);
    Esplora.writeRGB(0,(a*20),(a*20));
    delay(50);
  }
  for (int a = 12; a > 0; a--)
  {
    Esplora.writeRGB(0,(a*20),(a*20));
    delay(50);
  }
  Esplora.writeRGB(0,0,0);
  Esplora.noTone();
}

void loop()
{
  delay(100);
  // What button is pushed and is it to turn on or off?
  if (Esplora.readButton(SWITCH_UP) == LOW)
  {
    if (btn == 1)
    {
      btn = 9;
    }
    else
    {
      btn = 1;
      
      for (int a = 13; a > 0; a--)
      {
        Esplora.tone(note[a]);
        Esplora.writeRGB(255,255,255);
        delay(10);
        Esplora.writeRGB(0,0,0);
        delay(10);
      }
      Esplora.noTone();
      Serial.println("0");
    }
    delay(100);
  }
  if (Esplora.readButton(SWITCH_DOWN) == LOW)
  {
    if (btn == 2)
    {
      btn = 9;
      Esplora.writeRGB(0,0,0);
    }
    else
    {
      btn = 2;
      Esplora.writeRGB(0,255,0);
    }
    delay(100);
  }
  if (Esplora.readButton(SWITCH_LEFT) == LOW)
  {
    if (btn == 3)
    {
      btn = 9;
      Esplora.writeRGB(0,0,0);
    }
    else
    {
      btn = 3;
      Esplora.writeRGB(0,0,255);
    }
    delay(100);
  }
  if (Esplora.readButton(SWITCH_RIGHT) == LOW)
  {
    if (btn == 4)
    {
      btn = 9;
    }
    else
    {
      btn = 4;
    }
    delay(100);
  }

  // Slider = Look in direction
  int slider = Esplora.readSlider();
  // Look forward
  if ((slider < 600) && (slider > 499))
  {
    Serial.println("8");
    delay(100);
  }
  // Look Left
  if (slider == 1023)
  {
    Serial.println("6");
    delay(100);
  }
  // Look Right
  if (slider == 0)
  {
    Serial.println("7");
    delay(100);
  }

  // Right Button = AutoRoam
  if (btn == 4)
  {
    Serial.println("5");
    Esplora.writeRGB(0,127,127);
    btn = 9;
    delay(5000);
    Esplora.writeRGB(0,0,0);
  }

  
  // Down Button = Joystick motion
  while (btn == 2)
  //while (Esplora.readButton(SWITCH_DOWN) == LOW)
  {
    // Exit Esplora Control Mode
    if (Esplora.readButton(SWITCH_DOWN) == LOW)
    {
      btn = 9;
      Serial.println("9");
      Esplora.writeRGB(0,0,0);
      delay(200);
    }
    int JxAxis = Esplora.readJoystickX();
    int JyAxis = Esplora.readJoystickY();
    if ((JxAxis == -1) && (JyAxis == -1) && (last_cmd != 9))
    {
      Serial.println("9");
      last_cmd = 9;
    }
    // Left
    else if ((JxAxis >= 10) && (JyAxis == -1) && (last_cmd != 2))
    {
      Serial.println("2");
      last_cmd = 2;
    }
    // Right
    else if ((JxAxis <= -10) && (JyAxis == -1) && (last_cmd != 3))
    {
      Serial.println("3");
      last_cmd = 3;
    }
    // Forward
    else if ((JyAxis >= 10) && (JxAxis == -1) && (last_cmd != 4))
    {
      Serial.println("4");
      last_cmd = 4;
    }
    // Backward
    else if ((JyAxis <= -10) && (JxAxis == -1) && (last_cmd != 1))
    {
      Serial.println("1");
      last_cmd = 1;
    };
  }
  
  // Left Button = Accelerometer Control
  // X+ = Left  X- = Right  Y- = Fwd  Y+ = Bwd
  while (btn == 3)
  //while (Esplora.readButton(SWITCH_LEFT) == LOW)
  {
    // Exit Esplora Control Mode
    if (Esplora.readButton(SWITCH_LEFT) == LOW)
    {
      btn = 9;
      Serial.println("9");
      Esplora.writeRGB(0,0,0);
      delay(200);
    }
    int xAxis = Esplora.readAccelerometer(X_AXIS);
    int yAxis = Esplora.readAccelerometer(Y_AXIS);
    if ((xAxis > 50) && (last_cmd != 2))
    {
      Serial.println("2");
      last_cmd = 2;
    }
    else if ((xAxis < -50) && (last_cmd != 3))
    {
      Serial.println("3");
      last_cmd = 3;
    }
    else if ((yAxis > 50) && (last_cmd != 4))
    {
      Serial.println("4");
      last_cmd = 4;
    }
    else if ((yAxis < -50) && (last_cmd != 1))
    {
      Serial.println("1");
      last_cmd = 1;
    }
    else
    {
      last_cmd = 9;
    }    
    delay(100);
  }
}

