created this one for my friend's birthday, she's actually very close to me, we texted daily. I learnt about passive buzzer and LCD in this project. although it's a 16 pins, i managed to learned them all, probably used a (idk how do I call that) to transform it to a 4pins.
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
