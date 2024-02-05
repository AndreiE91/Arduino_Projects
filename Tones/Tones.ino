#include "pitches.h" // contains the frequency values for all
//the notes
// notes in the melody – constant values defining frequency
//for each used note
int melody[] = {
NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3,
NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = { 4,8,8,4,4,4,4,4 };
void setup()
{
for (int thisNote = 0; thisNote < 8; thisNote++) {
// iterate over the notes of the melody:
// to calculate the note duration, take one second
//divided by the note type.
// e.g. quarter note = 1000 / 4, eighth note = 1000/8,
//etc.
int noteDuration = 1000/noteDurations[thisNote];
tone(8, melody[thisNote],noteDuration);
// to distinguish the notes, set a minimum time
//between them: note's duration + 30%
int pauseBetweenNotes = noteDuration * 1.30;
delay(pauseBetweenNotes);
noTone(8); // stop the tone playing for current note
}
}
void loop() { } // no need to repeat the melody