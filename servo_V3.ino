
int left=0;
int center=0;
int right=0;
int mod=0;
int servopin = 9;    //Define servo interface digital interface 7
int angle =0;        //Angle of rotation of the servo

void servopulse(int angle)//Define an impulse function
{
  int pulsewidth=(angle*11)+500;  //The angle is converted to a pulse width value of 500-2480
  digitalWrite(servopin,HIGH);    //The servo interface level to the highest
  delayMicroseconds(pulsewidth);  //The number of microseconds of the delay pulse width value
  digitalWrite(servopin,LOW);     //The servo interface level to low
  delayMicroseconds(20000-pulsewidth); //20000 can be replaced: "frequency = 1 / (20000/1000000)"
}

void setup()
{
  pinMode(servopin,OUTPUT);//Set the servo interface as the output interface
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(7,INPUT);
  pinMode(12,INPUT);
}

void loop()
{
  left = digitalRead(2);
  center = digitalRead(4);
  right = digitalRead(7);
  mod = digitalRead(12);

  if (left == HIGH){
    angle =180;
    servopulse(angle);
  }
   if (center == HIGH){
    angle =90;
    servopulse(angle);
  }
  else if (right == HIGH){
    angle =0;
    servopulse(angle);
  }
  else if (mod == HIGH){
    angle = angle +10;
    servopulse(angle);
    delay(500);
  }
  else{
    delay(5);
  //for(angle=0;angle<=360;angle++){
      //Reference impulse function
  //    servopulse(angle);
  //    delay(5);
  // }
  }
 // for(angle=360;angle>=0;angle--){
      //Reference impulse function
 //    servopulse(angle);
 //    delay(20);
 //}
}
