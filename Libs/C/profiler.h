#ifndef __PROFILER_H__
#define __PROFILER_H__
typedef struct ProfilerEntry ProfilerEntry;

struct ProfilerEntry {
	unsigned char id;
	unsigned long time_start;
	unsigned long time_stop;
	unsigned long time_min;
	unsigned long time_max;
	unsigned long time_total;
	unsigned int  entries;
	unsigned int  running;
	ProfilerEntry * next;
};

typedef struct Profiler Profiler;
struct Profiler {
	ProfilerEntry * first;
};

void profiler_print(void);
Profiler * get_profiler(void);
ProfilerEntry * find_profiler_entry(unsigned char id);
ProfilerEntry * add_new_profiler_entry(unsigned char id);
void profiler_start(unsigned char id);
void profiler_count(unsigned char id);
void profiler_end(unsigned char id);	
int profiler_exists(void);

#endif
