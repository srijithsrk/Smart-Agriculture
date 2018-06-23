void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,INPUT);
digitalWrite(2,HIGH);
pinMode(13,OUTPUT);
pinMode(3,OUTPUT);

pinMode(5,OUTPUT);
pinMode(4,OUTPUT);
digitalWrite(4,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  char x=Serial.read();
  if(x=='1')
 digitalWrite(13,1);
 else if(x=='2')
 digitalWrite(13,0);
 
int c=analogRead(A0);
int leakage=digitalRead(2);
if(leakage==0)
{
  Serial.println("Lekage");
  digitalWrite(3,1);
}
else
digitalWrite(3,0);
if(c<350)
digitalWrite(5,1);
else
digitalWrite(5,0);
//Serial.println(c);
delay(1000);
}
