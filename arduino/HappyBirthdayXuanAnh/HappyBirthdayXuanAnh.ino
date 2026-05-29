/* 
 ===============================================================================
  PROJECT REFLECTION: PERSONALIZED BIRTHDAY TIMER & MUSIC BOX
 ===============================================================================
 
  1. LCD 1602A INTERFACE (PARALLEL 4-BIT MODE)
  -----------------------------------------------------------------------------
  * Library: Uses <LiquidCrystal.h>. Constructor order is critical: 
    LiquidCrystal lcd(rs, en, d4, d5, d6, d7).
    
  * Power & Contrast: 
    - VDD -> 5V & VSS -> GND (Powers the internal logic chip).
    - V0  -> Connected to a potentiometer wiper to dial in text contrast. 
             Without it, the screen becomes completely blank or fully blocked out.
             
  * Control Pins:
    - RS (Register Select) -> Tells the LCD if incoming data is a system command 
         (like clearing the screen) or an actual character string to display.
    - RW (Read/Write)      -> Wired to GND to permanently lock the LCD into 
         "Write" mode (5V would switch it to "Read" mode).
    - E (Enable)           -> Acts like an "Enter" key. It toggles to signal 
         the LCD to read the data currently waiting on the data pins.
         
  * Data & Backlight:
    - D4 to D7 -> Transmits data bytes split into two 4-bit halves. This saves 
         4 digital pins on the Arduino Uno compared to 8-bit mode.
    - A (Anode)   -> Backlight positive. REQUIRES a current-limiting resistor 
         (220 ohm - 1k ohm) to protect the internal LED from burning out.
    - K (Cathode) -> Backlight negative. Connects straight to GND.
    
  * Essential Code Functions: lcd.clear(), lcd.setCursor(col, row), lcd.print().
 
  2. AUDIO SYSTEM (PASSIVE BUZZER)
  -----------------------------------------------------------------------------
  * Playback Logic: Uses two matching arrays—one for note pitches (frequencies 
    in Hz) and one for note rhythmic values (e.g., 2, 4, 8).
  * Timing Calculation: Actual note duration in milliseconds = base tempo / note value.
  * Clean Performance: Uses tone(pin, frequency) to generate the sound, a delay() 
    to hold it, and a strict noTone(pin) followed by a short gap delay to ensure 
    identical musical notes do not blend or bleed together.
 ===============================================================================
*/


#include <LiquidCrystal.h>
// Frequencies for musical notes (in Hz)
#define NOTE_G3  196
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_C5  523
#define REST 0


// Define the LCD pins 
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Define pin numbers
const int buttonPin = 13;
const int buzzerPin = A0;
// Your exact LED array: 1st(5), 2nd(4), 3rd(3), 4th(2), 5th(13)
const int leds[] = {8, 9, 10, 11, 12}; 
const int numLeds = 5;



// The Happy Birthday melody notes
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, 
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, 
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, 
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4 
};

// Slow tempo base for the melody
const int slowTempoBase = 1200; 

// Note durations (Fixed the rhythm so no beats are skipped)
int noteDurations[] = {
  8, 8, 4, 4, 4, 2, 
  8, 8, 4, 4, 4, 2, 
  8, 8, 4, 4, 4, 4, 2, 
  8, 8, 4, 4, 4, 2  
};

int sunshineMelody[] = {
  REST, NOTE_G3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, 
  REST, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_C4, 
  REST, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_A4,
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4,
  REST, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_A4,
  REST, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  REST, NOTE_C4, NOTE_D4, NOTE_E4, 
  REST, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4
};

int sunshineDurations[] = {
  4, 4, 4, 4, 2, 2,
  4, 4, 4, 4, 2, 2,
  4, 4, 4, 4, 2, 2,
  4, 4, 4, 4, 1,
  4, 4, 4, 4, 2, 2,
  4, 4, 4, 4, 2, 2,
  2, 4, 4, 2, 
  4, 4, 2, 4, 4, 1,

};

void setup() {
  lcd.begin(16, 2);
  
  // Set LED and Buzzer pins as outputs
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Happy Birthday ");
  lcd.setCursor(0, 1);
  lcd.print("nhan nut mo qua");
  
  while (digitalRead(buttonPin) == HIGH) {
    delay(10); // Tiny pause to keep the processor stable while waiting
  }

  // --- STAGE 1: The Countdown (Stops at 59) ---
  for (int seconds = 55; seconds <= 59; seconds++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Xuan Anh 16tuoi! ");
    lcd.setCursor(0, 1);
    lcd.print("  Dem nguoc: ");
    lcd.print(60 - seconds);


    digitalWrite(leds[4], HIGH); 
    tone(buzzerPin, 1000, 100); 
    delay(100);                  
    digitalWrite(leds[4], LOW); 
    delay(900);                  
  }

  // --- STAGE 2: Midnight Animations ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" == 12:00 AM == ");
  lcd.setCursor(0, 1);
  lcd.print("    ~ ROAR! ~    "); 
  
  for(int i = 0; i < 10; i++) {
    digitalWrite(leds[3], HIGH); 
    digitalWrite(leds[4], HIGH); 
    tone(buzzerPin, 1500, 50);   
    delay(50);
    digitalWrite(leds[3], LOW);
    digitalWrite(leds[4], LOW);
    delay(50);                   
  }

  for(int sweeps = 0; sweeps < 3; sweeps++) {
    for(int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], HIGH);
      delay(40);
      digitalWrite(leds[i], LOW);
    }
    for(int i = numLeds - 2; i > 0; i--) {
      digitalWrite(leds[i], HIGH);
      delay(40);
      digitalWrite(leds[i], LOW);
    }
  }

  for(int blinks = 0; blinks < 5; blinks++) {
    digitalWrite(leds[0], HIGH); digitalWrite(leds[2], HIGH); digitalWrite(leds[4], HIGH);
    digitalWrite(leds[1], LOW); digitalWrite(leds[3], LOW);
    delay(100);
    digitalWrite(leds[0], LOW); digitalWrite(leds[2], LOW); digitalWrite(leds[4], LOW);
    digitalWrite(leds[1], HIGH); digitalWrite(leds[3], HIGH);
    delay(100);
  }
  
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], LOW);
  }

  // --- STAGE 3: Happy Birthday Text & ENERGETIC Melody ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*Happy Birthday*"); 
  lcd.setCursor(0, 1);
  lcd.print("   XUAN ANH <3  ");       
  
  int numNotes = sizeof(melody) / sizeof(melody[0]);
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {
    int actualDuration = slowTempoBase / noteDurations[thisNote];

    // Play the note continuously
    tone(buzzerPin, melody[thisNote]);

    // Visualizer Effect
    if (melody[thisNote] == NOTE_C4) {        digitalWrite(leds[0], HIGH); }
    else if (melody[thisNote] == NOTE_D4) {   digitalWrite(leds[1], HIGH); }
    else if (melody[thisNote] == NOTE_E4) {   digitalWrite(leds[2], HIGH); }
    else if (melody[thisNote] == NOTE_F4) {   digitalWrite(leds[3], HIGH); }
    else {                                    digitalWrite(leds[4], HIGH); }

    if (noteDurations[thisNote] == 2) {
      for(int i = 0; i < numLeds; i++) {
        digitalWrite(leds[i], HIGH);
      }
    }

    // Keep the note and LEDs on for the exact duration
    delay(actualDuration);

    // FORCE STOP the buzzer and LEDs so the next note is clean
    for(int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], LOW);
    }
    noTone(buzzerPin);

    int gap = actualDuration * 0.40;
    delay(gap);
  }

    // =========================================================================
  // INSERT THIS RIGHT AFTER THE HAPPY BIRTHDAY FOR-LOOP ENDS, BEFORE THE LAST } OF SETUP
  // =========================================================================

  // --- STAGE 4: You Are My Sunshine (Custom Lyrics & Melody Loop) ---
  int numNotesSunshine = sizeof(sunshineMelody) / sizeof(sunshineMelody[0]);

  for (int thisNote = 0; thisNote < numNotesSunshine; thisNote++) {
    int actualDuration = slowTempoBase / sunshineDurations[thisNote];

    // 1. Play your custom note
    tone(buzzerPin, sunshineMelody[thisNote]);

    // 2. CUSTOM VISUALIZER EFFECT (Replaced the old step 2)
    if (sunshineMelody[thisNote] == NOTE_G3) {
      digitalWrite(leds[4], HIGH); // Lowest note lights up 1st LED
    } 
    else if (sunshineMelody[thisNote] == NOTE_C4) {
      digitalWrite(leds[0], HIGH); // C4 lights up 2nd LED
    } 
    else if (sunshineMelody[thisNote] == NOTE_D4) {
      digitalWrite(leds[1], HIGH); // D4 lights up 3rd LED
    } 
    else if (sunshineMelody[thisNote] == NOTE_E4) {
      digitalWrite(leds[2], HIGH); // E4 lights up 4th LED
    } 
    else if (sunshineMelody[thisNote] == NOTE_G4) {
      digitalWrite(leds[2], HIGH); // E4 lights up 4th LED
    } 
    else if (sunshineMelody[thisNote] == NOTE_F4) {
      digitalWrite(leds[3], HIGH); // F4 lights up 5th LED (Your pastel blue!)
    } 
    else if (sunshineMelody[thisNote] == NOTE_A4) {
      // Highest note: Flash your pastel blue AND the one next to it!
      digitalWrite(leds[4], HIGH); 
    }

    // 3. 💡 LYRICS ENGINE: Change the text depending on which note is playing
    // (Example: Change text at note index 0, note index 5, note index 10, etc.)
    if (thisNote == 1) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("  You are my");
      lcd.setCursor(0, 1); lcd.print("    sunshine");
    }
    else if (thisNote == 7) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("   my only");
      lcd.setCursor(0, 1); lcd.print("    sunshine");
    }
    else if (thisNote == 13) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("   You make me");
      lcd.setCursor(0, 1); lcd.print("    happy");
    }
    else if (thisNote == 19) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("  when skies are");
      lcd.setCursor(0, 1); lcd.print("         gray");
    }
    else if (thisNote == 24) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("Youll never know");
      lcd.setCursor(0, 1); lcd.print("    dear");
    }
    else if (thisNote == 30) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("   how much I");
      lcd.setCursor(0, 1); lcd.print("      love you");
    }
    else if (thisNote == 36) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("   Please dont");
      lcd.setCursor(0, 1); lcd.print("    take");
    }
    else if (thisNote == 40) {
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("   my sunshine");
      lcd.setCursor(0, 1); lcd.print("       away");
    }
    // 💡 Add more "else if (thisNote == X)" blocks here for the rest of your lyrics!

    // 4. Hold the note
    delay(actualDuration);

    // 5. Clean up for the next note
    for(int i = 0; i < numLeds; i++) {
      digitalWrite(leds[i], LOW);
    }
    noTone(buzzerPin);

    int gap = actualDuration * 0.40;
    delay(gap);
  }

  // --- STAGE 5: Final Personalized Message ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tuoi 16 ruc ro  ");
  lcd.setCursor(0, 1);
  lcd.print(" nhe Xuan Anh!  ");
  
  for (int i=0; i<5; i++){
  digitalWrite(leds[i], HIGH); 
  }
}

/**/

void loop(){

}