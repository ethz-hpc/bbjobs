#include "lsb_strings.h"

/*
** Retuns a string describing the current job status
** This was 'stolen' from cmd.job.c as this function is
** not available from LSFs shared libraries
*/
char * get_job_status_desc(struct jobInfoEnt *job) {
	char *status;
	
	switch (job->status) {
		case JOB_STAT_NULL:
			status = "NULL";
			break;
		case JOB_STAT_PEND:
			status = "PENDING";
			break;
		case JOB_STAT_PSUSP:
			status = "PENDING JOB SUSPENDED";
			break;
		case JOB_STAT_RUN:
			status = "RUNNING";
			break;
		case JOB_STAT_RUN | JOB_STAT_WAIT:
			status = "WAITING";
			break;
		case JOB_STAT_SSUSP:
			status = "SUSPENDED BY SYSTEM";
			break;
		case JOB_STAT_USUSP:
			status = "SUSPENDED";
			break;
		case JOB_STAT_EXIT:
			if (job->reasons & EXIT_ZOMBIE)
				status = "ZOMBIE";
			else
				status = "EXITED";
			break;
		case JOB_STAT_DONE:
		case JOB_STAT_DONE|JOB_STAT_PDONE:
		case JOB_STAT_DONE|JOB_STAT_WAIT:
		case JOB_STAT_DONE|JOB_STAT_PERR:
			status = "DONE";
			break;
		case JOB_STAT_UNKWN:
			status = "UNKNOWN STATUS";
			break;
		default:
			status = "ERROR";
	}
	
	return status;
}


/*
** Parses LSF's RR string and extracts mem=XXXX
** WARNING: THIS RETURNS MB - MOST OTHER VALUES ARE IN KB
*/
int get_rr_mem(char *rr) {
	char match[] = "mem=";      /* prefix to search                         */
	char *scr = NULL;           /* scratch buffer-pointer                   */
	int rmem = -1;              /* return value -> requested memory         */
	int xoff = 0;               /* offset of first integer value after mem= */
	int mlen = strlen(match);
	int rlen = strlen(rr);
	int i;
	
	
	for(i=mlen;i<rlen;i++) {
		if(xoff == 0 && memcmp(&rr[i-mlen], match, mlen) == 0) {
			xoff = i;
		}
		else if(xoff && (rr[i] < '0' || rr[i] > '9')) {
			break;
		}
	}
	
	if(xoff) { /* hit is between i <-> xoff */
		if( (scr = malloc( 1+i-xoff )) != NULL &&
		       (snprintf(scr, 1+i-xoff, "%s", &rr[xoff])) > 0 ) {
			rmem = atoi(scr);
		}
	}
	
	if(scr != NULL)
		free(scr);
	
	return rmem;
}

/*
 * ** Parses LSF's RR string and extracts scratch=XXXX
 * ** WARNING: THIS RETURNS MB - MOST OTHER VALUES ARE IN KB
 * */
int get_rr_scratch(char *rr) {
        char match[] = "scratch=";      /* prefix to search                         */
        char *scr = NULL;           /* scratch buffer-pointer                   */
        int rscr = -1;              /* return value -> requested scratch         */
        int xoff = 0;               /* offset of first integer value after scratch= */
        int slen = strlen(match);
        int rlen = strlen(rr);
        int i;


        for(i=slen;i<rlen;i++) {
                if(xoff == 0 && memcmp(&rr[i-slen], match, slen) == 0) {
                        xoff = i;
                }
                else if(xoff && (rr[i] < '0' || rr[i] > '9')) {
                        break;
                }
        }

        if(xoff) { /* hit is between i <-> xoff */
                if( (scr = malloc( 1+i-xoff )) != NULL &&
                       (snprintf(scr, 1+i-xoff, "%s", &rr[xoff])) > 0 ) {
                        rscr = atoi(scr);
                }
        }

        if(scr != NULL)
                free(scr);

        return rscr;
}

/*
 * ** Parses LSF's RR string and extracts if it has affinity
 * */
int has_affinity(char *rr) {
        char match[] = "affinity";  /* prefix to search                         */
        int raff = 0;              /* return value -> affinity setting         */

        if(strstr(rr,match) != NULL)
		raff = 1;

        return raff;
}

