const int trigPin1 = A0;
const int echoPin1 = A1;

const int trigPin2 = A3;
const int echoPin2 = A4;

const int motor1 = 8;
const int motor2 = 9;

void setup() {
   // initialize serial communication:
      pinMode(trigPin1, OUTPUT);
      pinMode(echoPin1, INPUT);
      pinMode(trigPin2, OUTPUT);
      pinMode(echoPin2, INPUT);
      digitalWrite(trigPin1,LOW);
      digitalWrite(trigPin2,LOW);
      Serial.begin(9600);
}

long duration1, cm1, duration2, cm2;
int input;

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  duration1 = pulseIn(echoPin1, HIGH);
  cm1 = microsecondsToCentimeters(duration1);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
 
  
  duration2 = pulseIn(echoPin2, HIGH);
  cm2 = microsecondsToCentimeters(duration2);

  // convert the time into a distance
 
  Serial.print("S1-");
  Serial.print(cm1);
  Serial.println();
  
  Serial.print("S2-");
  Serial.print(cm2);
  Serial.println();
  
  if(Serial.available() > 0)
  {
    if(Serial.peek() == 'M')
    {
      Serial.read();
      input = Serial.parseInt();
      if(input == 11)
        digitalWrite(8,HIGH);
      else if (input == 10)
        digitalWrite(8,LOW);
      else if(input == 21)
        digitalWrite(9,HIGH);
      else if (input == 20)
        digitalWrite(9,LOW);
         
    }
  }
 
  delay(100);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
