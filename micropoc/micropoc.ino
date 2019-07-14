#define LED 4
#define OUT 3
#define BTN 2

int state = 0;
bool Fall = false;
bool verb = false;
unsigned long t;
float T1;
float T2;
float T3;
float Tchange = 0;
void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(OUT, OUTPUT);
  digitalWrite(LED,HIGH);
  digitalWrite(OUT,LOW);
  Serial.begin(115200);
  delay(100);
  Fall = false;
}

void loop() {
  delay(100);
  t = millis();
  if(state == 0){
    digitalWrite(LED,HIGH);
    digitalWrite(OUT,LOW);
    if(digitalRead(BTN)==LOW){
      state = 1;
    }
    
  }else if(state == 1){
    digitalWrite(LED,HIGH);
    digitalWrite(OUT,LOW);
    if(digitalRead(BTN)==HIGH){
      T1=t+10000;
      state = 2;
    }
    
  }else if(state == 2){
    digitalWrite(LED,(t/1000)%2);
    digitalWrite(OUT,LOW);
    if(digitalRead(BTN)==LOW){
      T3=t;
      state = 3;
    }
    if(t>T1){
      T2=t+1000;
      state = 4;
    }
    
  }else if(state == 3){
    digitalWrite(LED,(t/1000)%2);
    digitalWrite(OUT,LOW);
    if(digitalRead(BTN)==HIGH){
      if(t>T3+1000){
        state = 0;
      }else{
        T1 = T1+10000;
        state = 2;
      }
    }
    if(t>T1){
      T2=t+1000;
      state = 4;
    }  
    
  }else if(state == 4){
    digitalWrite(LED,HIGH);
    digitalWrite(OUT,HIGH);
    if(t>T2){
      state = 0;
    }
  }
  if(verb){Serial.println(state);}
  if(verb){Serial.println(T1-t);}
}
