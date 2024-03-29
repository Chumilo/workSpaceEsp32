#include <Arduino.h>
#include <BluetoothSerial.h>
#define alpha_config 0.5
#define DataLenght 2
#define ConstValue 0.0618
#define SampleTime 100
#define Ch1 23
#define Ch2 19
#define Ch3 27
#define Ch4 14

const char *DeviceName = "RobotMovil";

uint8_t direction = 0;

BluetoothSerial SerialBt;

// Distance
float SensorRight = 0.0;
float SensorFront = 0.0;
float SensorLeft = 0.0;

uint32_t LastTime = 0;
uint32_t LastTime2 = 0;

float vrRef = 0.0;
float vlRef = 0.0;

float cvR = 0.0;
float cvL = 0.0;

float SpeedRightReference = 0.0;
float SpeedLeftReference = 0.0;

// Send Data
String InputString = "";
bool StringComplete = false;
const char Separator = ',';
float Data[DataLenght];

class ControlPID
{

public:
  float kp;
  float ki;
  float kd;
  float setpoint;

  float input, output, velmax;
  float error, LastError, SumError;
  float proportional, derivative;

  ControlPID() {}

  void init(float Kp, float Ki, float Kd, float VelMax)
  {
    kp = Kp;
    ki = Ki;
    kd = Kd;
    velmax = VelMax;
  }

  float control(float setpoint, float vel)
  {
    input = (vel * 100.0) / velmax;
    error = setpoint - input;

    proportional = kp * error;
    SumError += ki * error * (millis() - LastTime) / 1000.0;
    derivative = kd * (error - LastError) / ((millis() - LastTime) / 1000.0);

    output = proportional + SumError + derivative;
    LastError = error;

    if (output >= 100.0)
      output = 100.0;
    else if (output <= -100.0)
      output = -100.0;

    return output;
  }
};
ControlPID ControlRight;
ControlPID ControlLeft;

struct Encoder
{
  volatile int32_t n = 0;
  volatile uint8_t Ant = 0;
  volatile uint8_t Act = 0;
  double LinealSpeed = 0.0;
} EncoderRight, EncoderLeft;

class Sensor
{

public:
  uint8_t echo_pin;
  uint8_t trig_pin;
  float duration;
  float distance;
  float st;
  float alpha;

  Sensor() {}

  void init(uint8_t EchoPin, uint8_t TrigPin, float Alpha)
  {
    echo_pin = EchoPin;
    trig_pin = TrigPin;
    alpha = Alpha;
    st = 0.0;
    duration = 0.0;
    distance = 0.0;
    pinMode(echo_pin, INPUT);
    pinMode(trig_pin, OUTPUT);
  }

  float calcular_distancia(float st_1)
  {
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    duration = pulseIn(echo_pin, HIGH);
    distance = 0.034 * (duration / 2.0);

    st = (alpha * distance) + ((1.0 - alpha) * st_1);
    return st;
  }
};
Sensor sensor_left;
Sensor sensor_front;
Sensor sensor_right;

class Motor
{
public:
  uint8_t Channel;
  uint8_t MaxSpeed;
  uint8_t SpeedPin;
  uint8_t InputA;
  uint8_t InputB;

  Motor() {}

  void init(uint8_t ch, uint8_t max_speed, uint8_t speed_pin, uint8_t input_a, uint8_t input_b)
  {
    Channel = ch;
    MaxSpeed = max_speed;
    SpeedPin = speed_pin;
    InputA = input_a;
    InputB = input_b;

    pinMode(SpeedPin, OUTPUT);
    pinMode(InputA, OUTPUT);
    pinMode(InputB, OUTPUT);

    ledcSetup(Channel, 5000, 8);
    ledcAttachPin(SpeedPin, Channel);
  }

  void SetSpeed(uint8_t Percentage)
  {
    uint8_t Speed = (MaxSpeed * Percentage) / 100;
    ledcWrite(Channel, Speed);
  }

  void MoveForward()
  {
    digitalWrite(InputA, HIGH);
    digitalWrite(InputB, LOW);
  }

  void MoveBackward()
  {
    digitalWrite(InputA, LOW);
    digitalWrite(InputB, HIGH);
  }

  void Stop()
  {
    digitalWrite(InputA, LOW);
    digitalWrite(InputB, LOW);
  }
};
Motor RightMotor;
Motor LeftMotor;

void IRAM_ATTR EncoderR()
{
  EncoderRight.Ant = EncoderRight.Act;

  if (digitalRead(Ch2))
    bitSet(EncoderRight.Act, 0);
  else
    bitClear(EncoderRight.Act, 0);
  if (digitalRead(Ch1))
    bitSet(EncoderRight.Act, 1);
  else
    bitClear(EncoderRight.Act, 1);

  if (EncoderRight.Ant == 2 && EncoderRight.Act == 0)
    EncoderRight.n++;
  if (EncoderRight.Ant == 0 && EncoderRight.Act == 1)
    EncoderRight.n++;
  if (EncoderRight.Ant == 3 && EncoderRight.Act == 2)
    EncoderRight.n++;
  if (EncoderRight.Ant == 1 && EncoderRight.Act == 3)
    EncoderRight.n++;

  if (EncoderRight.Ant == 1 && EncoderRight.Act == 0)
    EncoderRight.n--;
  if (EncoderRight.Ant == 3 && EncoderRight.Act == 1)
    EncoderRight.n--;
  if (EncoderRight.Ant == 0 && EncoderRight.Act == 2)
    EncoderRight.n--;
  if (EncoderRight.Ant == 2 && EncoderRight.Act == 3)
    EncoderRight.n--;
}

void IRAM_ATTR EncoderL()
{
  EncoderLeft.Ant = EncoderLeft.Act;

  if (digitalRead(Ch3))
    bitSet(EncoderLeft.Act, 0);
  else
    bitClear(EncoderLeft.Act, 0);
  if (digitalRead(Ch4))
    bitSet(EncoderLeft.Act, 1);
  else
    bitClear(EncoderLeft.Act, 1);

  if (EncoderLeft.Ant == 2 && EncoderLeft.Act == 0)
    EncoderLeft.n++;
  if (EncoderLeft.Ant == 0 && EncoderLeft.Act == 1)
    EncoderLeft.n++;
  if (EncoderLeft.Ant == 3 && EncoderLeft.Act == 2)
    EncoderLeft.n++;
  if (EncoderLeft.Ant == 1 && EncoderLeft.Act == 3)
    EncoderLeft.n++;

  if (EncoderLeft.Ant == 1 && EncoderLeft.Act == 0)
    EncoderLeft.n--;
  if (EncoderLeft.Ant == 3 && EncoderLeft.Act == 1)
    EncoderLeft.n--;
  if (EncoderLeft.Ant == 0 && EncoderLeft.Act == 2)
    EncoderLeft.n--;
  if (EncoderLeft.Ant == 2 && EncoderLeft.Act == 3)
    EncoderLeft.n--;
}

void SpeedMotor()
{
  vrRef = 0.25;
  vlRef = 0.25;

  vrRef = (vrRef * 100.0) / 0.39;
  vlRef = (vlRef * 100.0) / 0.39;

  if (vrRef > 100.0)
    vrRef = 100.0;
  if (vlRef > 100.0)
    vlRef = 100.0;
}

void serialEventRun()
{
  while (SerialBt.available())
  {
    char InChar = (char)SerialBt.read();
    InputString += InChar;
    if (InChar == '\n')
    {
      StringComplete = true;
    }
  }
}

void setup()
{
  Serial.begin(115200);
  SerialBt.begin(DeviceName);

  sensor_left.init(2, 4, alpha_config);
  sensor_front.init(35, 18, alpha_config);
  sensor_right.init(34, 26, alpha_config);

  RightMotor.init(0, 255, 5, 12, 13);
  LeftMotor.init(1, 255, 16, 25, 17);

  ControlRight.init(0.6, 1.0, 3.0, 0.39);
  ControlLeft.init(0.6, 1.0, 3.0, 0.39);

  pinMode(Ch1, INPUT);
  pinMode(Ch2, INPUT);
  pinMode(Ch3, INPUT);
  pinMode(Ch4, INPUT);

  attachInterrupt(Ch1, EncoderR, CHANGE);
  attachInterrupt(Ch2, EncoderR, CHANGE);

  attachInterrupt(Ch3, EncoderL, CHANGE);
  attachInterrupt(Ch4, EncoderL, CHANGE);

  LastTime = millis();
  LastTime2 = millis();
}

void loop()
{
  if (StringComplete)
  {
    for (uint8_t i = 0; i < DataLenght; i++)
    {
      uint8_t Index = InputString.indexOf(Separator);
      Data[i] = InputString.substring(0, Index).toInt();
      InputString = InputString.substring(Index + 1);
    }

    direction = Data[0];
    // porc = Data[1];

    InputString = "";
    StringComplete = false;
  }

  switch (direction)
  {
  case 0:
    RightMotor.SetSpeed(0);
    LeftMotor.SetSpeed(0);
    RightMotor.Stop();
    LeftMotor.Stop();
    break;

  case 1:
    if (millis() - LastTime >= SampleTime)
    {

      SensorRight = sensor_right.calcular_distancia(SensorRight);
      SensorFront = sensor_front.calcular_distancia(SensorFront);
      SensorLeft = sensor_left.calcular_distancia(SensorLeft);

      Serial.println(String(SensorRight) + ',' + String(SensorFront) + ',' + String(SensorLeft));

      if (SensorFront > 20.0)
      {
        SpeedRightReference = 50;
        SpeedLeftReference = 50;
      }
      else if (SensorFront <= 20.0)
      {
        SpeedRightReference = 0;
        SpeedLeftReference = 0;
      }

      EncoderRight.LinealSpeed = (EncoderRight.n * ConstValue) / ((millis() - LastTime));
      EncoderLeft.LinealSpeed = (EncoderLeft.n * ConstValue) / ((millis() - LastTime));

      EncoderRight.n = 0;
      EncoderLeft.n = 0;

      cvR = ControlRight.control(SpeedRightReference, EncoderRight.LinealSpeed);
      cvL = ControlLeft.control(SpeedLeftReference, EncoderLeft.LinealSpeed);

      if (cvR > 0)
      {
        RightMotor.SetSpeed(cvR);
        RightMotor.MoveForward();
      }
      else
      {
        RightMotor.SetSpeed(abs(cvR));
        RightMotor.MoveBackward();
      }

      if (cvL > 0)
      {
        LeftMotor.SetSpeed(cvL);
        LeftMotor.MoveForward();
      }
      else
      {
        LeftMotor.SetSpeed(abs(cvL));
        LeftMotor.MoveBackward();
      }
      LastTime = millis();
    }
    break;
  }
}
