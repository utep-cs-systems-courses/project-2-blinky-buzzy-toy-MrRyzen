#ifndef buzzer_included
#define buzzer_included

#define A# 233.08		/* switch2 is p2.1 */
#define B# 246.94		/* switch2 is p2.1 */
#define A 440.00		/* switch1 is p2.0 */
#define D 293.66		/* switch4 is p2.3 */
#define F 349.23
#define G# 415.30
#define G 392.00		/* switch3 is p2.2 */

void buzzer_init();
void buzzer_set_period(short cycles);
void play_song();

#endif // included
