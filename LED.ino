#define red_led 13
#define green_led 12
#define blue_led 11

void setup() 
{
  // put your setup code here, to run once:
  pinMode(red_led,OUTPUT);
  pinMode(green_led,OUTPUT);
  pinMode(blue_led,OUTPUT);
  analogWrite(red_led,255);
  analogWrite(green_led,255);
  analogWrite(blue_led,255);
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available())
  {
    char led_specifier = Serial.read();
    int led_brightness = Serial.parseInt();
    write_leds(led_specifier, led_brightness);
  }
}

void write_leds(char led, int brightness)
{
  if(led == 'r')
  {
    analogWrite(red_led, 255 - brightness);
    return;
  }
  if(led == 'g')
  {
    analogWrite(green_led, 255 - brightness);
    return;
  }
  if(led == 'b')
  {
    analogWrite(blue_led, 255 - brightness);
    return;
  }
  return;
}
