// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

#define OLED_DC D3
#define OLED_CS D4
#define OLED_RESET D5
int readEMF=A4;
String fiveSecData ="";
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
int data[1000]={};

void setup() {
    pinMode(D7,OUTPUT);
    pinMode(readEMF,INPUT);
    Particle.function("funcKey", funcName);
    Particle.publish("fiveSecData", fiveSecData,5000,PUBLIC);
    Particle.function("displayScreen", displayScreen);

}

void loop() {
  
}

int takeReading(){
    int startTimer = Time.second();
    int i=0;
    if(startTimer>54){
        delay(6000);
    }
    startTimer = Time.second();
    digitalWrite(D7,HIGH);
        while(Time.second()<startTimer+5) {
            data[i]=analogRead(readEMF);
            i++;
        }
        digitalWrite(D7,LOW);
        return arrayToString(i);
}
int funcName(String switch1) {
  if(switch1=="HIGH"){
        return takeReading();
        
  }
    return 0;
}

int arrayToString(int i){
    String fiveSecData1="";
    String fiveSecData2="";
    String fiveSecData3="";
    String fiveSecData4="";

    for(int c=0;c<100;c++){
        fiveSecData1=fiveSecData1+","+String(data[c]);
    }
    for(int c=100;c<200;c++){
        fiveSecData2=fiveSecData2+","+String(data[c]);
    }
    for(int c=200;c<300;c++){
        fiveSecData3=fiveSecData3+","+String(data[c]);
    }
    for(int c=300;c<400;c++){
        fiveSecData4=fiveSecData4+","+String(data[c]);
    }
   
    Particle.publish("data1",fiveSecData1 , 1, PUBLIC);
    
    Particle.publish("data2",fiveSecData2 , 1, PUBLIC);

    Particle.publish("data3",fiveSecData3 , 1, PUBLIC);
    
    Particle.publish("data4",fiveSecData4 , 5, PUBLIC);
    
    return i;

}
int displayScreen(String Screenvalue) {
    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    if(Screenvalue=="1"){
        display.println("Microwave");
    }
    else if(Screenvalue=="2"){
        display.println("Fridge");
    }
    else if(Screenvalue=="3"){
        display.println("TV");
    }
    else if(Screenvalue=="4"){
        display.println("CPU");
    }
    else{
        display.println("No Device");
    }
    display.display();
  return 0;
}