#include <lsf/lsbatch.h>
#include <string.h>
#include <stdlib.h>

char * get_job_status_desc(struct jobInfoEnt *job);
int get_rr_mem(char *rr);
int get_rr_scratch(char *rr);
int has_affinity(char *rr);
