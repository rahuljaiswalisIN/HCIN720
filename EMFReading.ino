int readEMF=A4;
String fiveSecData ="";
int data[1000]={};

void setup() {
    pinMode(D7,OUTPUT);
    pinMode(readEMF,INPUT);
    Particle.function("funcKey", funcName);
    Particle.variable("fiveSecData", fiveSecData);
}

void loop() {
  
}
int takeReading(){
    
    int startTimer = 0;
    int currentTime = 0;
    startTimer = Time.second();
    currentTime = Time.second();
    if(startTimer>53){
            delay(6000);
            startTimer = Time.second();
    }
    digitalWrite(D7,HIGH);
        for(int i=0;currentTime<=startTimer+6;i++) {
            data[i]=analogRead(readEMF);
            currentTime = Time.second();
        }
        arrayToString();
        digitalWrite(D7,LOW);
        return currentTime;
}
int funcName(String switch1) {
  if(switch1=="HIGH"){
        return takeReading();
  }
    return 777;
}

void arrayToString(){
    String fiveSecData1="";
    String fiveSecData2="";
    String fiveSecData3="";

    for(int c=0;c<100;c++){
        fiveSecData1=fiveSecData1+","+String(data[c]);
    }
    for(int c=100;c<200;c++){
        fiveSecData2=fiveSecData2+","+String(data[c]);
    }
    for(int c=200;c<300;c++){
        fiveSecData3=fiveSecData3+","+String(data[c]);
    }

    fiveSecData=fiveSecData1;
    Particle.publish("data1",fiveSecData , 1, PUBLIC);
    fiveSecData=fiveSecData2;
    Particle.publish("data2",fiveSecData , 1, PUBLIC);
    fiveSecData=fiveSecData3;
    Particle.publish("data3",fiveSecData , 1, PUBLIC);
}
