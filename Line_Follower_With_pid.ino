//IR Variable
int left_ir = 2;
int forward_ir = 4;
int right_ir = 6;


//Motor Variable
int left_en = 9;
int left_motor_1 = 8;
int left_motor_2 = 10;

int right_en = 11;
int right_motor_1 = 13;
int right_motor_2 = 12;


//PID constant
float kp = 1.2;
float ki = 0;
float kd = 0;
float P = 0, D = 0, I = 0, PID_value = 0, previous_error = 0;


void setup() {

  pinMode(left_ir, INPUT);
  pinMode(forward_ir, INPUT);
  pinMode(right_ir, INPUT);

  pinMode(left_en, OUTPUT);
  pinMode(left_motor_1, OUTPUT);
  pinMode(left_motor_2, OUTPUT);

  pinMode(right_en, OUTPUT);
  pinMode(right_motor_1, OUTPUT);
  pinMode(right_motor_2, OUTPUT);

  //Serial.begin(9600);
}

void loop() {

  PID_Control();

}

void PID_Control()
{
  //determine the position of car by reading the ir sensors

  int read_left = (digitalRead(left_ir));
  int read_right = (digitalRead(right_ir));
  int read_forward = (digitalRead(forward_ir));


  int position_ = ((read_left * 0) + (read_right * 2000) + (read_forward * 1000)) / (read_left + read_right + read_forward);

  int Error = 1000 - position_;

  P = Error;
  I = I + Error;
  D = Error - previous_error;
  previous_error = Error;
  PID_value = (kp * P) + (kd * D) * (ki * I); //represent the speed of motors

  int motorSpeed_left = 75 - PID_value;
  int motorSpeed_right = 75 + PID_value;

  if (motorSpeed_left >110)
  {
    motorSpeed_left =110;
  }
  if (motorSpeed_right >105)
  {
    motorSpeed_right =105;
  }
  if (motorSpeed_left < -100)
  {
    motorSpeed_left = -100;
  }
  if (motorSpeed_right < -100)
  {
    motorSpeed_right = -100;
  }

  movement(motorSpeed_left, motorSpeed_right);
}

void movement(int left_speed, int right_speed)
{

  if (left_speed < 0)
  {
    left_speed = 0 - left_speed;
    digitalWrite(left_motor_1, HIGH);
    digitalWrite(left_motor_2, LOW);
  }
  else
  {
    digitalWrite(left_motor_1, LOW);
    digitalWrite(left_motor_2, HIGH);
  }
  if (right_speed < 0)
  {
    right_speed = 0 - right_speed;
    digitalWrite(right_motor_1, HIGH);
    digitalWrite(right_motor_2, LOW);
  }
  else
  {
    digitalWrite(right_motor_1, LOW);
    digitalWrite(right_motor_2, HIGH);
  }

  analogWrite(left_en, left_speed);
  analogWrite(right_en, right_speed);

}
