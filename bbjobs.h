#include <lsf/lsf.h>
#include <lsf/lsbatch.h>

#include "printer.h"

#define MAXAFFNITYLEN 16

/* Returns TRUE if jobInfoEnt was ever running
** This is not the same as IS_START as it will also
** Return TRUE for DONE or killed jobs
*/
#define HAS_STATS(x) ( (x)->startTime != 0 && (x)->jRusageUpdateTime != 0)

void xdie(char *msg);

void print_single_job(struct jobInfoEnt *job);
void print_exec_hosts(struct jobInfoEnt *job);

void print_affinity(char *rr);

int get_jobinfo(LS_LONG_INT jobid, int jobidx, int jobopts, char *jobuser);

void pr_duration(char *desc, time_t sec);

int parse_jobidx(char *str);

