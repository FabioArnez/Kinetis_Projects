
String in;         // incoming serial byte
String out= "Hola K64F";
void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
 
 
}

void loop()
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    in = Serial.readString();
    
    
    if(in=="Hola Arduino        ") {
        Serial.println("Hola k64F           ");
    }
    else{
            Serial.println("Hola Desconocido    ");
    
    
    }
    // read first analog input, divide by 4 to make the range 0-255:
    
      }
}

