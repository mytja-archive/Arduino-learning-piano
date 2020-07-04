#include <Tone.h>
#include "kuzapazi.h"
#include "merrychristmas.h"
#include "happy.h"
#include "ringtone.h"

// Copyright
// Thanks to https://github.com/robsoncouto/arduino-songs, he did most songs that are included

// This code is meant for educational purposes and I, the owner don't allow making money (commercial use) with or without any modifications.
// copyright mytja - https://github.com/mytja/

// Version: Guinea pig 1.0

// Here are defined some important variables
int note = 0;
int mode = 2;  // Set a mode - song
char text;
boolean songlearn = false;

// Here are defined LEDs for learning
const int led_c1 = 11;
const int led_d1 = 12;
const int led_e1 = A0;
const int led_f1 = A1;
const int led_g1 = A2;
const int led_a1 = A3;
const int led_h1 = A4;               // USA uses B instead H
const int led_c2 = A5;

// Here are defined all the buttons for playing
const int c1 = 2;
const int d1 = 3;
const int e1 = 4;
const int f1 = 5;
const int g1 = 6;
const int a1 = 7;
const int h1 = 8;                    // USA uses B instead H
const int c2 = 9;

const int modeBtn = 13; // Button to change mode is here

// Here is the speaker defined
const int speaker = 10;




Tone tone1;   // Here are tones defined

void ifModeBtn(){
  if (digitalRead(modeBtn)==HIGH){
    int mode = mode + 1;
    note = 1000000;
    Serial.println("modeBTN: ON");
    delay(300);
    if (mode==0){
      led_startup();
    }
    else if (mode==1){
      kuzapazi_refren();
    }
    else if (mode==2){
      Serial.println("mode 2");
    }
    else if (mode==3){
      Serial.println("mode 3");
    }
    if (mode==4){
      mode = 0;
    }
  }
}

int notes_ringtone[] = {

  // Nokia Ringtone 
  // Score available at https://musescore.com/user/29944637/scores/5266155
  
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};

int tempo = 180;

int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

int notes = sizeof(notes_ringtone) / sizeof(notes_ringtone[0]) / 2;

void startup_ringtone(){
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = notes_ringtone[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone1.play(10, notes_ringtone[thisNote]);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    tone1.stop();
}
}


// int led_kuzapazi[] = {led_c1, led_c1, led_c1, led_c1, led_d1, led_d1, led_d1, led_d1, led_e1, led_e1, led_d1, led_d1, led_c1, led_c1, led_c1, led_c1};

// Function to turn all leds off
void turnoffall(){
  digitalWrite(led_c1, LOW);
  digitalWrite(led_d1, LOW);
  digitalWrite(led_e1, LOW);
  digitalWrite(led_f1, LOW);
  digitalWrite(led_g1, LOW);
  digitalWrite(led_a1, LOW);
  digitalWrite(led_h1, LOW);
  digitalWrite(led_c2, LOW);
}

void led_startup(){
  digitalWrite(led_c1, HIGH);
  delay(50);
  digitalWrite(led_c1, LOW);
  digitalWrite(led_d1, HIGH);
  delay(50);
  digitalWrite(led_d1, LOW);
  digitalWrite(led_e1, HIGH);
  delay(50);
  digitalWrite(led_e1, LOW);
  digitalWrite(led_f1, HIGH);
  delay(50);
  digitalWrite(led_f1, LOW);
  digitalWrite(led_g1, HIGH);
  delay(50);
  digitalWrite(led_g1, LOW);
  digitalWrite(led_a1, HIGH);
  delay(50);
  digitalWrite(led_a1, LOW);
  digitalWrite(led_h1, HIGH);
  delay(50);
  digitalWrite(led_h1, LOW);
  digitalWrite(led_c2, HIGH);
  delay(50);
  digitalWrite(led_c2, LOW);
  turnoffall();
}

void kuzapazi_refren(){
  for (note = 0; 15 > note; note++){
    tone1.play(notes_kuzapazi[note]);
    delay(250);
    tone1.stop();
    delay(100);
  }
}

//void kuzapazi_learn(){
//  note = 0;
//  while (15 > note){
//    note++;
//    text = notes_kuzapazi[note];
//    songlearn = true;
//    while (songlearn==true){
//      if (text==NOTE_C4){
//        while (digitalRead(c1) == LOW){
//          digitalWrite(led_c1, HIGH);
//          delay(20);
//        }
//        digitalWrite(11, LOW);
//        tone1.play(NOTE_C4);
//        delay(100);
//        tone1.stop();
//        songlearn = false;
//      }
//    }
//  }
//}

void setup() {
  // Define speaker
  pinMode(speaker, OUTPUT);
  tone1.begin(speaker);

  // Serial begin
  Serial.begin(9600);

  // Define Buttons
  pinMode(c1, INPUT);
  pinMode(d1, INPUT);
  pinMode(e1, INPUT);
  pinMode(f1, INPUT);
  pinMode(g1, INPUT);
  pinMode(a1, INPUT);
  pinMode(h1, INPUT);
  pinMode(c2, INPUT);

  // Define LEDs
  pinMode(led_c1, OUTPUT);
  pinMode(led_d1, OUTPUT);
  pinMode(led_e1, OUTPUT);
  pinMode(led_f1, OUTPUT);
  pinMode(led_g1, OUTPUT);
  pinMode(led_a1, OUTPUT);
  pinMode(led_h1, OUTPUT);
  pinMode(led_c2, OUTPUT);
  
  turnoffall();
  
  led_startup();
  startup_ringtone();
}

void loop() {

  // Kuza pazi
  while (mode==1){
    kuzapazi_refren();
    note = -1;
    while (14 > note){
      note++;
      Serial.println(note);
      songlearn = true;
      while (songlearn==true){
        if (notes_kuzapazi[note]==NOTE_C4){
          while (digitalRead(c1) == LOW){
            digitalWrite(led_c1, HIGH);
            delay(20);
          }
          digitalWrite(led_c1, LOW);
          tone1.play(NOTE_C4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_kuzapazi[note]==NOTE_D4){
          while (digitalRead(d1) == LOW){
            digitalWrite(led_d1, HIGH);
            delay(20);
          }
          digitalWrite(led_d1, LOW);
          tone1.play(NOTE_D4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_kuzapazi[note]==NOTE_E4){
          while (digitalRead(e1) == LOW){
            digitalWrite(led_e1, HIGH);
            delay(20);
          }
          digitalWrite(led_e1, LOW);
          tone1.play(NOTE_E4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        
      }
    }
    mode = 0;

  // We wish you a merry christmas
  }
  while (mode==2){
    note = -1;
    while (58 > note){
      note++;
      Serial.println(note);
      songlearn = true;
      while (songlearn==true){
        if (notes_merrychristmas[note]==NOTE_C5){
          while (digitalRead(c1) == LOW){
            digitalWrite(led_c1, HIGH);
            delay(20);
          }
          digitalWrite(led_c1, LOW);
          tone1.play(NOTE_C5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_merrychristmas[note]==NOTE_D5){
          while (digitalRead(d1) == LOW){
            digitalWrite(led_d1, HIGH);
            delay(20);
          }
          digitalWrite(led_d1, LOW);
          tone1.play(NOTE_D5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_merrychristmas[note]==NOTE_E5){
          while (digitalRead(e1) == LOW){
            digitalWrite(led_e1, HIGH);
            delay(20);
          }
          digitalWrite(led_e1, LOW);
          tone1.play(NOTE_E5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_merrychristmas[note]==NOTE_F5){
          while (digitalRead(f1) == LOW){
            digitalWrite(led_f1, HIGH);
            delay(20);
          }
          digitalWrite(led_f1, LOW);
          tone1.play(NOTE_F5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_merrychristmas[note]==NOTE_G5){
          while (digitalRead(g1) == LOW){
            digitalWrite(led_g1, HIGH);
            delay(20);
          }
          digitalWrite(led_g1, LOW);
          tone1.play(NOTE_G5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_merrychristmas[note]==NOTE_A5){
          while (digitalRead(a1) == LOW){
            digitalWrite(led_a1, HIGH);
            delay(20);
          }
          digitalWrite(led_a1, LOW);
          tone1.play(NOTE_A5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_merrychristmas[note]==NOTE_B5){
          while (digitalRead(h1) == LOW){
            digitalWrite(led_h1, HIGH);
            delay(20);
          }
          digitalWrite(led_h1, LOW);
          tone1.play(NOTE_B5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_merrychristmas[note]==NOTE_C6){
          while (digitalRead(c2) == LOW){
            digitalWrite(led_c2, HIGH);
            delay(20);
          }
          digitalWrite(led_c2, LOW);
          tone1.play(NOTE_C6);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if(notes_merrychristmas[note]==4){
          delay(10);
          songlearn = false;
        }
        else if(notes_merrychristmas[note]==8){
          delay(10);
          songlearn = false;
        }
        else if(notes_happy[note]==2){
          delay(10);
          songlearn = false;
        }
      }
    }
    mode = 0;
  }


  // Happy birthday
  while (mode==3){
    note = -1;
    while (47 > note){
      note++;
      Serial.println(note);
      songlearn = true;
      while (songlearn==true){
        if (notes_happy[note]==NOTE_C4){
          while (digitalRead(c1) == LOW){
            digitalWrite(led_c1, HIGH);
            delay(20);
          }
          digitalWrite(led_c1, LOW);
          tone1.play(NOTE_C4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_happy[note]==NOTE_D4){
          while (digitalRead(d1) == LOW){
            digitalWrite(led_d1, HIGH);
            delay(20);
          }
          digitalWrite(led_d1, LOW);
          tone1.play(NOTE_D4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_happy[note]==NOTE_E4){
          while (digitalRead(e1) == LOW){
            digitalWrite(led_e1, HIGH);
            delay(20);
          }
          digitalWrite(led_e1, LOW);
          tone1.play(NOTE_E4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_happy[note]==NOTE_F4){
          while (digitalRead(f1) == LOW){
            digitalWrite(led_f1, HIGH);
            delay(20);
          }
          digitalWrite(led_f1, LOW);
          tone1.play(NOTE_F4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_happy[note]==NOTE_G4){
          while (digitalRead(g1) == LOW){
            digitalWrite(led_g1, HIGH);
            delay(20);

          }
          digitalWrite(led_g1, LOW);
          tone1.play(NOTE_G4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_happy[note]==NOTE_A4){
          while (digitalRead(a1) == LOW){
            digitalWrite(led_a1, HIGH);
            delay(20);
          }
          digitalWrite(led_a1, LOW);
          tone1.play(NOTE_A4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_happy[note]==NOTE_B4){
          while (digitalRead(h1) == LOW){
            digitalWrite(led_h1, HIGH);
            delay(20);
          }
          digitalWrite(led_h1, LOW);
          tone1.play(NOTE_B4);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if (notes_happy[note]==NOTE_C5){
          while (digitalRead(c2) == LOW){
            digitalWrite(led_c2, HIGH);
            delay(20);
          }
          digitalWrite(led_c2, LOW);
          tone1.play(NOTE_C5);
          delay(300);
          tone1.stop();
          songlearn = false;
        }
        else if(notes_happy[note]==4){
          delay(10);
          songlearn = false;
        }
        else if(notes_happy[note]==8){
          delay(10);
          songlearn = false;
        }
        else if(notes_happy[note]==2){
          delay(10);
          songlearn = false;
        }
      }
    }
    mode = 0;
  }
  // Standard piano - mode 0
  if (digitalRead(c1)==HIGH){
    tone1.play(NOTE_C4);
    Serial.println("c1");
    delay(30);
    tone1.stop();
  }
  else if (digitalRead(d1)==HIGH){
    tone1.play(NOTE_D4);
    Serial.println("d1");
    delay(30);
    tone1.stop();
  }
  else if (digitalRead(e1)==HIGH){
    Serial.println("e1");
    tone1.play(NOTE_E4);
    delay(30);
    tone1.stop();
  }
  else if (digitalRead(f1)==HIGH){
    Serial.println("f1");
    tone1.play(NOTE_F4);
    delay(30);
    tone1.stop();
  }
  else if (digitalRead(g1)==HIGH){
    Serial.println("g1");
    tone1.play(NOTE_G4);
    delay(30);
    tone1.stop();
  }
  else if (digitalRead(a1)==HIGH){
    Serial.println("a1");
    tone1.play(NOTE_A4);
    delay(30);
    tone1.stop();
  }
  else if (digitalRead(h1)==HIGH){
    Serial.println("h1");
    tone1.play(NOTE_B4);
    delay(30);
    tone1.stop();
  }
  else if (digitalRead(c2)==HIGH){
    Serial.println("c2");
    tone1.play(NOTE_C5);
    delay(30);
    tone1.stop();
  }
}
