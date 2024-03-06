#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


int tempo = 120;

int buzzer = 12;

int melody[] = {
  NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;

int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

// end of buzzer song setup

void rollDice(int randomNum){ //this function determines what LEDs must be turned on based on the number rolled
  if (randomNum == 1){
      digitalWrite(5,HIGH);  
  }
  else if (randomNum == 2){
    digitalWrite(3,HIGH);  
  }
  else if (randomNum == 3){
    digitalWrite(4,HIGH); 
    digitalWrite(5,HIGH);  
  }
  else if (randomNum == 4){
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);   
  }
  else if (randomNum == 5){
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);   
    digitalWrite(5,HIGH); 
  }
  else if (randomNum == 6){
    digitalWrite(2,HIGH); 
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);  
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);//right and left LED
  pinMode(3,OUTPUT);// bottom left and top right LED
  pinMode(4,OUTPUT);// bottom right and top left LED
  pinMode(5,OUTPUT);// mid LED
  pinMode(11,INPUT);//ir sensor
  pinMode(buzzer,OUTPUT);// buzzer


  //startup LED pattern
  for (int brightness = 255; brightness != 0; brightness--){
    analogWrite(3,brightness);
    analogWrite(4,brightness);
    delay(10);
  }
  for (int brightness = 255; brightness != 0; brightness--){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    analogWrite(5,brightness);
    delay(10);
  }
  for (int brightness = 0; brightness != 255; brightness++){
    digitalWrite(5, LOW);
    analogWrite(3,brightness);
    analogWrite(4,brightness);
    delay(10);
  }
  for (int brightness = 0; brightness != 255; brightness++){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    analogWrite(5,brightness);
    delay(10);
  }
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(500);
  // end of intro sequence
  
  // plays a song on the buzzer
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  //end of buzzer song
}


void loop() {
  // put your main code here, to run repeatedly:
  
// dice roll if a hand goes over the sensor
  if (digitalRead(11) == 0){
    int randomRoll = random(2,6);
    for (int i = 0; i<400; i += 20){ //make LEDs turn on and off to show the dice rolling
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      
      randomRoll = random(1,7);
      rollDice(randomRoll);
      tone(buzzer, 1000-i);
      delay(100+i);
    }
    
    //turn the buzzer and all the LEDs off
    
    noTone(buzzer);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    delay(500);
    randomRoll = random(1,7);
    // turn on LEDs
    rollDice(randomRoll);
    
  }
}