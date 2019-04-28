/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:
int yeeMelody[] = {
  NOTE_C4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_G4, REST, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_GS3
};

int yeeNoteDurations[] = {
  8, 6, 8, 4, 4, 6, 4, 3, 6, 12, 6, 12, 6, 12, 4, 4, 6, 4, 1
};

int allStarMelody[] {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, REST, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_F3, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_G4
};

int allStarNoteDurations[] = {
  8, 8, 16, 16, 16, 16, 8, 8, 16, 16, 4, 8, 16, 16, 8, 16, 16, 16, 16, 8, 16, 16
};

int sandstormMelody[] {
  NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_D4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST, NOTE_B4, REST
};

int sandstormNoteDurations[] {
  32, 32, 32, 32, 32, 32, 32, 32, 8, 2, 16, 3, 32, 32, 32, 32, 32, 32, 32, 32, 8, 2, 1, 32, 32, 32, 32, 32, 32, 32, 32, 8, 2, 32, 32, 32, 32, 32, 32, 32, 32, 8, 2
};

int SPEAKER_PIN = 8;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
}

void loop() {
  if(Serial1.available()) {
    int incoming = Serial1.read();
    Serial1.write("Received ");
    Serial1.write(incoming);
    Serial1.write('\n');
    Serial.write("Received from bluetooth ");
    Serial.write(incoming);
    Serial.write('\n');
    if(incoming == '1') {
      Serial1.write("Playing Yee\n");
      Serial.write("Playing Yee\n");
      int numNotes = (sizeof(yeeMelody) / sizeof(yeeMelody[0]));
      playSong(yeeMelody, yeeNoteDurations, numNotes, 1500);
    }
    if(incoming == '2') {
      Serial1.write("Playing All Star\n");
      Serial.write("Playing All Star\n");
      int numNotes = (sizeof(allStarMelody) / sizeof(allStarMelody[0]));
      playSong(allStarMelody, allStarNoteDurations, numNotes, 2000);
    }    
    if(incoming == '3') {
      Serial1.write("Playing Sandstorm\n");
      Serial.write("Playing Sandstorm\n");
      int numNotes = (sizeof(sandstormMelody) / sizeof(sandstormMelody[0]));
      playSong(sandstormMelody, sandstormNoteDurations, numNotes, 1700);
    }
  }
}

void playSong(int melody[], int noteDurations[], int melodySize, int msPerMeasure) {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < melodySize; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = msPerMeasure / noteDurations[thisNote];
    
    if(melody[thisNote] != REST) {
      tone(SPEAKER_PIN, melody[thisNote], noteDuration);
    }

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER_PIN);
  }
}
