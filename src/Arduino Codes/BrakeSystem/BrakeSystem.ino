int relay1 = 8;      
int relay2 = 9;   
int led1 = 4;      
int led2 = 5;
#define LOCK 1
#define RELEASE -1

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(relay1, OUTPUT);  
  pinMode(relay2, OUTPUT);  
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT);
  Serial.begin(115200);
}

if (Serial.available() > 0) {
          // read the incoming byte:
          String incomingByte = Serial.readString();
          Serial.println(incomingByte.toInt()); 
          Brake(incomingByte.toInt()); 
        }
}
void Brake(int val){ //New Brake Funcs
    if(val == LOCK){
      Serial.print("Rel");
      Serial.println(val);
      digitalWrite(relay1, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(relay2, LOW);
      digitalWrite(led2, LOW);
    }
    if(val == RELEASE){
      digitalWrite(relay2, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(relay1, LOW);
      digitalWrite(led1, LOW);

    }
    if(val != 1 && val!= -1){
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
}
