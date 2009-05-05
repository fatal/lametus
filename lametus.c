#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <math.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#include "lametus.h"
#include "encoder.h"
#include "audio.h"

#define VERSION_STRING "1.1-multimedia"

int use_multimedia = 0;

int num_encoders = 0;
struct encoder *encoders[MAX_ENCODERS];
struct audio_source *source = NULL;

int quit = 0;

#define NUM_AVG_SLOTS 150
#define MAX_AVG_SLOTS 300
#define SHORT_AVG_SLOTS 10
int average_window = NUM_AVG_SLOTS;
#define MAX_DIFF_CHANGE 1
short max_peaks[MAX_AVG_SLOTS];
short short_peaks[SHORT_AVG_SLOTS];
int short_index = 0;
#define SHORT_AVG_LIMIT 55
int short_avg_limit = SHORT_AVG_LIMIT;

int cur_avg_index = 0;
int total_avg = 0;
#define TARGET_AVG 45
#define HYSTERESIS 4 
int hysteresis = HYSTERESIS;
#define LIMIT 23
int limit = LIMIT;
int last_diff = 0;
int target_value = TARGET_AVG;

const char keyhelp1[] = "target:     +/-       ";
const char keyhelp2[] = "hysteresis: up/down   ";
const char keyhelp3[] = "window:     left/right";
const char keyhelp4[] = "dB limits:  w/q       ";
const char keyhelp5[] = "short:      a/s       ";

void parse_file(FILE *);
void init_curses() {
	const char * ptr;
	int i;
	const char msg[] = "Lametus ver. " VERSION_STRING; 
        initscr(); start_color(); cbreak(); noecho();
        nonl();
        intrflush(stdscr, FALSE);
        keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	clear();
	move(0,0);
	for(i=0; i<strlen(msg); i++) addch((chtype)msg[i]|COLOR_PAIR(4));
	move(1,0);
	addch('[');
	addch('L');
	addch(']');
	move(3,0);
	addch('[');
	addch('R');
	addch(']');
	move(5,0); addch('A'); addch('v'); addch('g');
	move(6,0); addch('T'); addch('g'); addch('t');

	move(1,78); addch('|'|COLOR_PAIR(3));
	move(2,78); addch('+'|COLOR_PAIR(3));
	move(3,78); addch('|'|COLOR_PAIR(3));

	move(10,40);
	for(ptr=keyhelp1; *ptr; ptr++) addch((chtype)*ptr|COLOR_PAIR(4));
	move(11,40);
	for(ptr=keyhelp2; *ptr; ptr++) addch((chtype)*ptr|COLOR_PAIR(4));
	move(12,40);
	for(ptr=keyhelp3; *ptr; ptr++) addch((chtype)*ptr|COLOR_PAIR(4));
	move(13,40);
	for(ptr=keyhelp4; *ptr; ptr++) addch((chtype)*ptr|COLOR_PAIR(4));
	move(14,40);
	for(ptr=keyhelp5; *ptr; ptr++) addch((chtype)*ptr|COLOR_PAIR(4));

	move(2,3);
	
	for(i=0; i<75; i++) {
		char z;
		if(!(i%10)) z = '+';
		else z = '-';
		if(i>60) addch(z|COLOR_PAIR(3));
		else if(i>45) addch(z|COLOR_PAIR(2));
		else addch(z|COLOR_PAIR(1));
	}
	refresh();
	
	for ( i=0; i<MAX_AVG_SLOTS; i++ ) {
		max_peaks[i] = 0;	
	}

}

void draw_string(char * ptr, short modifier) {
	for(;*ptr; ptr++) addch(*ptr|modifier);
}

void bar(int len, int peak) {
	int i;
	for(i=0; i<len; i++) {
		if(i>60) addch('#'|COLOR_PAIR(3));
		else if(i>45) addch('#'|COLOR_PAIR(2));
		else addch('#'|COLOR_PAIR(1));
	}
	for(;i<75;i++) {
		if(i==peak) {
			if(i>60) addch('#'|COLOR_PAIR(3));
			else if(i>45) addch('#'|COLOR_PAIR(2));
			else addch('#'|COLOR_PAIR(1));
		} else addch(' ');
	}
}
int right_peak = 0;
int left_peak = 0;
int peak_counter = 0;
void max_stereo(short * buf, unsigned len) {
	unsigned i;
	short a=0, b=0, c;
	short left, right;
	for(i=0; i<len; i++) {
		c = buf[i*2];
		if(c<0) c = -c;
		if(c>a) a = c;
		c = buf[i*2+1];
		if(c<0) c = -c;
		if(c>b) b = c;
	}
	// 32768 / 75 --->
 	left = a / 437; 
 	right = b / 437;
	if(!peak_counter --) {
		peak_counter = 35;
		left_peak = left;
		right_peak = right;
	} else {
		if(left > left_peak) left_peak = left;
		if(right > right_peak) right_peak = right;
	}	
	move(1,3);
	bar(left, left_peak);
	move(3,3);
	bar(right, right_peak);

	// record long term max...
	max_peaks[cur_avg_index++] = 
		left_peak > right_peak ? left_peak : right_peak;
	short_peaks[short_index++] = 
		left_peak > right_peak ? left_peak : right_peak;
	cur_avg_index = cur_avg_index % average_window;
	short_index = short_index % SHORT_AVG_SLOTS;

	int sum = 0;
	for ( i=0; i<average_window; i++ ) {
		sum += max_peaks[i];
	}
	total_avg = sum / average_window;

	sum = 0;
	for ( i=0; i<SHORT_AVG_SLOTS; i++ ) {
		sum += short_peaks[i];
	}
	int short_average = sum / SHORT_AVG_SLOTS;
	int old_diff = last_diff;

	if ( !cur_avg_index ) 
	{
		int diff = target_value - total_avg;
		
		if ( diff > hysteresis )
		{
			last_diff ++;
		}
		else if ( diff < -hysteresis )
		{
			last_diff --;
		}
	}
	if ( short_average > short_avg_limit && !short_index)
		last_diff --;

	if ( last_diff < -limit ) last_diff = -limit;
	else if ( last_diff > limit ) last_diff = limit;

	if ( last_diff != old_diff ) 
	{
		char buf[200] = ""; 
		sprintf(buf, "amixer -- set Capture,0 %ddB >/dev/null", last_diff );
		system(buf);
	}

	move(5,3); bar( total_avg, short_average );
	move(6,3); bar( target_value, short_avg_limit );
}
void handle_key(int ch)
{
	if( ch < 0 ) return;
	switch ( ch ) 
	{
	case '+':
		target_value ++;
		if ( target_value < 0) target_value = 0;
		break;
	case '-':
		target_value --;
		if (target_value > 74) target_value = 74;
		break;
	case KEY_LEFT:
		average_window --;
		if (average_window < 10) average_window = 10;
		break;
	case KEY_RIGHT:
		average_window ++;
		if (average_window > MAX_AVG_SLOTS) average_window = MAX_AVG_SLOTS;
		break;
	case KEY_DOWN:
		hysteresis --;
		if ( hysteresis < 2 ) hysteresis = 2;
		break;
	case KEY_UP:
		hysteresis ++;
		if ( hysteresis > 30 ) hysteresis = 30;
		break;
	case 'q':
		limit --;
		if ( limit < 1 ) limit = 1;
		break;
	case 'w':
		limit ++;
		if ( limit > 23 ) limit = 23;
		break;
	case 'a':
		short_avg_limit --;
		if ( short_avg_limit < 1 ) limit = 1;
		break;
	case 's':
		short_avg_limit ++;
		if ( short_avg_limit > 74 ) limit = 74;
		break;
	}
}
void draw_info(time_t * start_time)
{
	int i;
	char buf[1024];
	time_t now;
	char * ptr;
	int diff;
	move(0,38);
	time(&now);
	diff = difftime(now, *start_time);	
	ptr = ctime(&now);
	sprintf(buf, "up for %3d:%02d - %s", diff/60, diff%60, ptr);

	draw_string(buf, COLOR_PAIR(4));

	sprintf(buf, "Peak average: %2d, target: %2d, level correction: %2ddB (-%d...%ddB)", total_avg, target_value, last_diff, limit, limit );
	move( 7, 0 );
	draw_string(buf, COLOR_PAIR(4));

	sprintf(buf, "Window: %2d (%d-%d), hysteresis: %d (2-30), short limit: %2d (1-74)", average_window, 10, MAX_AVG_SLOTS, hysteresis, short_avg_limit  );
	move( 8, 0 );
	draw_string(buf, COLOR_PAIR(4));
	for(i=0; i<num_encoders; i++) {
		move(i*3+10,0);
		sprintf(buf, "%d: %4dkbit %6s, %6dkB written",
			i + 1,	
			encoders[i]->bitrate,
			encoders[i]->mono ? "mono" : "stereo",
			encoders[i]->produced / 1024);
		draw_string(buf, COLOR_PAIR(4));
		move(i*3+11,0);
		sprintf(buf, "File: %s - Streaming: %s", 
			encoders[i]->file_fd==-1 ? "[none]" : encoders[i]->file_name,
			encoders[i]->server_fd == -1 ? "no" : "yes");
		draw_string(buf, 0);
	}
}

void fatal(const char *fmt,...)
{
	va_list ap;

	va_start(ap,fmt);

	vfprintf(stderr,fmt,ap);

	va_end(ap);

	fputc('\n',stderr);
	fflush(stderr);

	exit(1);
}

int main(int argc,char **argv)
{
	int i;
	FILE *fp;
	time_t started;

	time(&started);

	if (!(argc == 2 || argc == 3))
		fatal("Usage: %s [-multimedia] <configfilename>",argv[0]);

	fprintf(stderr,"Lametus version %s\n",VERSION_STRING);
	fprintf(stderr,"Using Lame version %s as encoder backend\n\n",get_lame_version());

	if(!strcmp(argv[1], "-multimedia")) {
		use_multimedia = 1;
		argv ++;
	}

	fprintf(stderr,"Loading configuration from file \"%s\"\n",argv[1]);

	fp = fopen(argv[1],"r");
	if (!fp)
		fatal("Could not open configuration file");

	parse_file(fp);

	signal(SIGPIPE,SIG_IGN);

	if (!source)
		fatal("No audio source specified");

	if (!num_encoders)
		fatal("No encoders specified");

	audio_source_init(source);

	for (i=0; i<num_encoders; i++)
	{
		encoder_init(source,encoders[i]);
	}
	if(use_multimedia)
		init_curses();
	while (!quit)
	{
		short tmpbuf[4096*2];
		if(use_multimedia) {
			int ch = getch();
			handle_key(ch);
			audio_source_read(source,
					  (unsigned char *)tmpbuf,4096*4);
			max_stereo(tmpbuf, 2048);
			refresh();
			max_stereo(tmpbuf+2048, 2048);
			draw_info(&started);
			refresh();
		}
		for (i=0; i<num_encoders; i++)
			encoder_run(encoders[i],tmpbuf,4096);
		
	}

	return 0;
}
