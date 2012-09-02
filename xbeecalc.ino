#define RED_WIRE 6
#define WHITE_WIRE 7

void setup()
{
  
  // start the serial for the xbee
  Serial.begin(9600);
  
  // debug light
  pinMode(13,OUTPUT);
  
}

void loop()
{
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    unsigned char incomingByte = Serial.read();
    sendByte(incomingByte);
  }
  
  // if a wire is pulled low then start reading by calling the get method
  if(!(digitalRead(RED_WIRE)==1 && digitalRead(WHITE_WIRE)==1)) {
    
    // turn on debug light
    digitalWrite(13, HIGH);
    Serial.write(get());
    // turn off debug light
    digitalWrite(13, LOW);
  }
  
}

void sendByte(unsigned char toSend)
{
  for (int b1 =0;b1<8;b1++){
    if(toSend & 1){
      	pinMode(WHITE_WIRE,OUTPUT);
	digitalWrite(WHITE_WIRE,LOW);
	while(digitalRead(RED_WIRE)==1) {}
	pinMode(WHITE_WIRE,INPUT);
	while(digitalRead(RED_WIRE)==0) {}
    }else{
	pinMode(RED_WIRE,OUTPUT);
	digitalWrite(RED_WIRE,LOW);
	while(digitalRead(WHITE_WIRE)==1) {}
	pinMode(RED_WIRE,INPUT);
	while(digitalRead(WHITE_WIRE)==0) {}
    }
    toSend = toSend>>1;
  }
}


unsigned char get()
{
  unsigned char data=0;
  for(int b1=0; b1<8; b1++){
    while(digitalRead(RED_WIRE)==1 & digitalRead(WHITE_WIRE)==1) {}
    if (digitalRead(RED_WIRE) == 1){
      data = (data >> 1) | 0x80;
      pinMode(RED_WIRE,OUTPUT);
      digitalWrite(RED_WIRE,LOW);
      while(digitalRead(WHITE_WIRE)==0) {}
      digitalWrite(RED_WIRE,HIGH);
      pinMode(RED_WIRE,INPUT);
    } else {
      data = data >> 1;
      pinMode(WHITE_WIRE,OUTPUT);
      digitalWrite(WHITE_WIRE,LOW);
      while(digitalRead(RED_WIRE)==0) {}
      digitalWrite(WHITE_WIRE,HIGH);
      pinMode(WHITE_WIRE,INPUT);
    }
  }
  return data;
}

