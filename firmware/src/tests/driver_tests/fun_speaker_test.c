/*
a fun speaker test. it plays alle-meine-entchen. this code was vibe-coded with gemini
*/

#include "driver_speaker.h"
#include <stdint.h>
#include "hal_time.h"

// Die Noten der Melodie
musical_note_t entchen_notes[] = {
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, // Al-le mei-ne Ent-chen
    NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5,         // schwim-men auf dem See,
    NOTE_A5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5,         // schwim-men auf dem See,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, // Köpf-chen in das Was-ser,
    NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_C5          // Schwänz-chen in die Höh'.
};

// Die Dauer pro Note (in ms)
uint16_t entchen_durations[] = {
    300, 300, 300, 300, 600, 600, 
    300, 300, 300, 300, 900, 
    300, 300, 300, 300, 900,
    300, 300, 300, 300, 600, 600,
    300, 300, 300, 300, 900
};

void system_ticks_callback_handler(void);

int main(void)
{
	SPEAKER_init();
	TIME_init();
	TIME_set_system_ticks_callback(system_ticks_callback_handler);

    uint8_t num_notes = sizeof(entchen_notes) / sizeof(entchen_notes[0]);

    for (uint8_t i = 0; i < num_notes; i++) {
        // Ton starten
        SPEAKER_play_sound(entchen_notes[i], entchen_durations[i]);
        
        // Wir warten die gesamte Zeit der Note + eine kleine Pause
        // Damit die Pause hörbar ist, muss das Delay etwas länger sein als der Ton
        TIME_delay_ms(entchen_durations[i] + 50); 
    }
}

void system_ticks_callback_handler(void)
{
	SPEAKER_system_tick();
}