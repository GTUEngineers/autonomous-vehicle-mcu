#define LOCK 1
#define RELEASE -1
#define THROTTLE_MAX 1.7
#define THROTTLE_MIN 0.5
#define THROTTLE_MIN_VAL 0
#define THROTTLE_MAX_VAL 90

int relay_in_pin1 = 8;      
int relay_in_pin2 = 9;       
int led1 = 4;      
int led2 = 5;   
int steer_pulse_pin = 6;      
int steer_direction_pin = 7;     
int last_steering_val = 0;
int throttle_pin = 13;
int selection_flag = 0;
int select_val = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(relay_in_pin1, OUTPUT);  
  pinMode(relay_in_pin2, OUTPUT);  
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT);  
 
  pinMode(steer_pulse_pin, OUTPUT);  
  pinMode(steer_direction_pin, OUTPUT);  
  pinMode(throttle_pin, OUTPUT);  
  
  Serial.begin(9600);
}

void loop()
{
  if(selection_flag == 0){
    Serial.println("STEER : 0\nBRAKE : 1\nTHROTTLE : 2\nValue: "); 
    selection_flag = 1;
  }
  
  if(Serial.available() > 0){
       String incomingByte;
       if(selection_flag == 1){
          incomingByte = Serial.readString();
          select_val = incomingByte.toInt();
          selection_flag = 2;
          if(select_val == 0){
            Serial.println("For STEER \nMAX Value: 7500\nMIN Value:-7500\nValue: ");
          }
          else if(select_val == 1){
            Serial.println("For BRAKE \nLOCK Value: 1\nRELEASE Value:-1\nSTOP value:Other\nValue: ");  
          }
          else if(select_val == 2){
            Serial.println("For THROTTLE \nMAX Value: 90\nMIN Value:0\nValue: ");
          }
          else{
            Serial.println("Invalid");  
          }
      }
      else{
        if(selection_flag == 2){
          if(select_val == 0){
            incomingByte = Serial.readString();
            steerTo(incomingByte.toInt());
          }
          else if(select_val == 1){
            incomingByte = Serial.readString();
            brake(incomingByte.toInt());
          }
          else if(select_val == 2){
            incomingByte = Serial.readString();
            throttle(incomingByte.toInt());
          }
          else{
            Serial.println("Invalid");  
          }
          selection_flag = 0;
        }
     }
  }
}


void throttle(int val)
{
  if(val >= THROTTLE_MIN_VAL && val <= THROTTLE_MAX_VAL){
    analogWrite(throttle_pin,val);
  }
}

void brake(int val)
{
    if(val == LOCK){
      digitalWrite(relay_in_pin1, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(relay_in_pin2, LOW);
      digitalWrite(led2, LOW);
    }
    
    if(val == RELEASE){
      digitalWrite(relay_in_pin2, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(relay_in_pin1, LOW);
      digitalWrite(led1, LOW);

    }
    
    if(val != LOCK && val != RELEASE){
      digitalWrite(relay_in_pin1, LOW);
      digitalWrite(relay_in_pin2, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
}

void steerTo(int val)
{
  int dir_val = 0;
  if(last_steering_val > val){  
    //step
    dir_val = 1;
  }
  digitalWrite(steer_direction_pin, dir_val); 
  digitalWrite(led1, dir_val);  
  
  while(last_steering_val != val){
      digitalWrite(steer_pulse_pin, LOW);  
      delayMicroseconds(150);      
      digitalWrite(steer_pulse_pin, HIGH);  
      delayMicroseconds(150); 
      if(dir_val == 0) {
        ++last_steering_val;
      }
      else{
        --last_steering_val;
      }
  }
}
