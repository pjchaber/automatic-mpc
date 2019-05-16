#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "./profiler.h"

#define MIN_(x,y) ((x)<(y)?(x):(y))
#define MAX_(x,y) ((x)>(y)?(x):(y))

static Profiler * it = NULL;
char tmpstr[100];
char * float2strF(float x){
    int integer = (int)(x);
    int fractional = (int)( (x-integer)*10000 );
    if(fractional < 0) fractional *= -1;
    sprintf(tmpstr, "%d.%04d",integer, fractional);
    return tmpstr;
}

void profiler_print(){
	char str[1000];
	Profiler * p;
	if(!profiler_exists())
		return;
	p = get_profiler();
	ProfilerEntry * e = p->first;
	sprintf(str,"%%%10s | %10s | %10s | %10s | %10s | %10s | %10s\n","id", "time total", "entries", "min", "mean" , "max", "running");
	__write_string(str);
	sprintf(str,"%%%10s-+-%10s-+-%10s-+-%10s-+-%10s-+-%10s-+-%10s\n","----------","----------","----------","----------","----------","----------","----------");
	__write_string(str);
	while(e != NULL){
		if(e->id != 0xFF){
			sprintf(str,"%%%5d (%2X) | %10ld | %10d | %10ld | %10s | %10ld | %1d\n", e->id, e->id, e->time_total, e->entries, e->time_min, float2strF(((float)(e->time_total))/e->entries), e->time_max, e->running);
			__write_string(str);
		}
		e = e->next;
	}
}

int profiler_exists(){
	return (it!=NULL);
}

Profiler * create_profiler(){
	Profiler * it = (Profiler*)malloc(sizeof(Profiler));
	ProfilerEntry * guard = (ProfilerEntry*)malloc(sizeof(ProfilerEntry));
	it->first = guard;
	guard->id = 0xFF;
	guard->next = NULL;
	return it;
}

Profiler * get_profiler(){
	if(it == NULL) it = create_profiler();
	return it;
}

ProfilerEntry * find_profiler_entry(unsigned char id){
	Profiler * p = get_profiler();
	ProfilerEntry * e = p->first;
	while(e != NULL && e->id != id){ e = e->next; };
	return e;
}

ProfilerEntry * find_last(){
	Profiler * p = get_profiler();
	ProfilerEntry * e = p->first;
	while(e->next != NULL){ e = e->next; };
	return e;
}

ProfilerEntry * add_new_profiler_entry(unsigned char id){
	ProfilerEntry * e = find_profiler_entry(id);
	if(e == NULL) {
		e = (ProfilerEntry*)malloc(sizeof(ProfilerEntry));
		find_last()->next = e;
		e->id = id;
		e->next = NULL;
		e->time_total = 0;
		e->entries = 0;
		e->time_start = 0;
		e->time_stop = 0;
		e->time_max = 0;
		e->time_min = LONG_MAX;
	}
	return e;
}

void profiler_start(unsigned char id){
	ProfilerEntry * e = add_new_profiler_entry(id);
	e->running = 1;
	e->time_start = __get_time();
	++(e->entries);
}

void profiler_count(unsigned char id){
	ProfilerEntry * e = add_new_profiler_entry(id);
	++(e->entries);
}

void profiler_end(unsigned char id){
	ProfilerEntry * e = find_profiler_entry(id);
	unsigned long diff;
	if(e == NULL) while(1);//exit(-2);
	e->time_stop = __get_time();
	if(e->time_start <= e->time_stop){
		diff = e->time_stop - e->time_start;
	} else {
		diff = e->time_stop - e->time_start + LONG_MAX;
	}

	e->time_max = MAX_(e->time_max, diff);
	e->time_min = MIN_(e->time_min, diff);

	e->time_total += diff;
	e->running = 0;
}
