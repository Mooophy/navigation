

long distance1, time1;
long distance2, time2;
long distance3, time3;

void setup()
{ 
  
  pinMode(5, OUTPUT); 
  pinMode(6, INPUT);
  
  pinMode(7, OUTPUT);  
  pinMode(8, INPUT);
  
  pinMode(9, OUTPUT);
  pinMode(10,INPUT);
  
  Serial.begin(9600);
}
void loop()
{
  
   //!  sensor 1    
   digitalWrite(5,LOW);
   delayMicroseconds(2); 
   digitalWrite(5,HIGH);
   delayMicroseconds(5);
   time1 = pulseIn(6,HIGH);
   distance1 = time1 * 0.034;
   
   //!  sensor 2  
   digitalWrite(7,LOW);
   delayMicroseconds(2); 
   digitalWrite(7,HIGH);
   delayMicroseconds(5);  
   time2 = pulseIn(8,HIGH);
   distance2 = time2 * 0.034;


   //!  sensor 3 
   digitalWrite(9,LOW);
   delayMicroseconds(2); 
   digitalWrite(9,HIGH);
   delayMicroseconds(5);
   time3 = pulseIn(10,HIGH);
   distance3 = time3 * 0.034;  
   
   
    Serial.print(distance1 );
    Serial.print("|");
    Serial.print(distance2 );    
    Serial.print("|");
    Serial.print(distance3 );
    Serial.print("|");    
    Serial.println();
    
  delay(50);  
  
  
}

