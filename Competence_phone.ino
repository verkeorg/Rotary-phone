#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// vakiot ja muuttujat
AudioPlaySdWav           playWav1;
AudioOutputAnalog         audioOutput;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);

#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

int needToPrint = 0; // Do we have a new number? / Onko meillä uusi numero?
int laskuri; // Counter for the dialed number / Tämä laskee veivatun numeron
int kytkin1 = 0; // Switch position 1 / Kytkimen asento 1
int kytkin2 = 1; // Switch position 2 / Kytkimen asento 2
int dialpin = 2; // Pin to read dial pulses / Pinni josta luetaan veivaus
int hookpin = 3; // Pin to read phone on hook / Pinni josta luetaan hook
const int ledpin = 4; // Pin to add external LED / Virran merkkivalo
int dac = A21; // Pin for sound out / Pinni jonne lähetetään ääni
int lastState = HIGH; // Has the dialpin changed / Onko pinnin tila muuttunut, vertailuarvo?
int trueState = HIGH; // Current state of dialpin / Tämänhetkinen pinnin tila
long aikaleima = 0; // Timestamp for last change of dialpin / Aikaleima jolloin pinnin tila muuttunut
int veivausviive = 1000; // Delay for dial to stop turning / Viive jolloin numero on veivattu, ms
int debounceDelay = 1; // Delay to stabilise each pulse / Viive signaalin stabiloitumiselle, ms

void setup()
{
  Serial.begin(9600);
  pinMode(dialpin, INPUT_PULLUP);
  pinMode(hookpin, INPUT_PULLUP);
  pinMode(ledpin, OUTPUT);
  pinMode(kytkin1, INPUT_PULLUP);
  pinMode(kytkin2, INPUT_PULLUP);
  
  long aikaleima = millis();
  AudioMemory(8);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  
  
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // sd-card not found, stop here and print error 
    while (1) {
      Serial.println("SD-card not found, stopping!");
      delay(500);
    }
  }
} 

void playFile(const char *filename)
{
  int offhook = digitalRead(hookpin);
  if (offhook == 1) {
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Play sound. This loop is used as long as a sample is playing.
  playWav1.play(filename);

  // Delay while clip is read
  delay(5);

  // While sound is played.
  while (playWav1.isPlaying()) {
    int offhook = digitalRead(hookpin);
    if (offhook == 0) { // If phone is put down, stop playback
      Serial.println("Phone on hook, stopping playback");
      playWav1.stop();
    }

    else {
      
    }
  }
}

  if (offhook == 0) {
    AudioPlaySdWav(stop);
    Serial.println("Phone is on the hook, audio stopped!");
  }
}



void loop()
{

  int reading = digitalRead(dialpin);
  int onhook = digitalRead(hookpin);
  // digitalWrite(ledpin, HIGH);

  

  if (onhook == HIGH) {

    if ((millis() - aikaleima) > veivausviive) {
// If current time minus the timestamp is bigger than the delay, 
// a number is not being dialed or has just finished dialing

      if (needToPrint) {
// If we have numbers to count AND the dial is not spinning (see above), do the following

        if (laskuri == 1) { //competence 1 - here the files are about digital youth work competencies
          needToPrint = 0;
          Serial.println("Recognising previous council conclusions");
          playFile("prev.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 2) { //competence 2
          needToPrint = 0;
          Serial.println("Recommendation 12");
          playFile("rec12.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 3) { //competence 3
          needToPrint = 0;
          Serial.println("Recommendation 13");
          playFile("rec13.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 4) { //competence 4
          needToPrint = 0;
          Serial.println("Recommendation 14");
          playFile("rec14.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 5) { //competence 5
          needToPrint = 0;
          Serial.println("Recommendation 15");
          playFile("rec15.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 6) { //competence 6
          needToPrint = 0;
          Serial.println("Recommendation 16");
          playFile("rec16.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 7) { //competence 7
          needToPrint = 0;
          Serial.println("Recommendation 17");
          playFile("rec17.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 8) { //competence 8
          needToPrint = 0;
          Serial.println("Recommendation 18");
          playFile("rec18.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

        if (laskuri == 9) { //competence 9
          needToPrint = 0;
          Serial.println("Recommendation 19");
          playFile("rec19.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }
        
        if (laskuri == 10) { //competence 10, when zero is dialed
          needToPrint = 0;
          Serial.println("Recommendation 20");
          playFile("rec20.WAV");  // filenames are always uppercase 8.3 format
          delay(500);
        }

      needToPrint = 0;
      laskuri = 0;
      }
  } 

if (reading != lastState) {
  aikaleima = millis();
  // Update timestamp to when the signal last changed (ie. dial is turning)
  }
if ((millis() - aikaleima) > debounceDelay) {
  // introduce a delay to get rid of false open / closed reading on the dial. Adjust this depending on your phone.
  if (reading != trueState) {
    // Switch on dial has just opened or closed
    trueState = reading;
    if (trueState == HIGH) {
    // every pulse HIGH adds 1 to the counter. This might be reversed (low) on some phones!
    laskuri++; 
    needToPrint = 1; // update variable "needtoprint", because we have new numbers
    } 
}
}
lastState = reading;
}
} 
