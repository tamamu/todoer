#include "headers.h"

/*
extern char td_type;
extern char td_tag[16];
extern char td_thing[280];
extern struct tm *td_date;
*/


char tdview(){
	num++;
	if((td_type = fgetc(t_fp)) == '@'){
			strcpy(td_tag,(char *)fstrtok(t_fp,' ',16));
			strcpy(td_thing,(char *)fstrtok(t_fp,'\n',280));
			return '@';
	}else if(td_type == '~' || td_type == '?' || td_type == '!'){
			strcpy(td_tag,(char *)fstrtok(t_fp,' ',16));
			td_date.tm_year=natoi((char *)fstrtok(t_fp,'/',4),4)-1900;
			td_date.tm_mon=natoi((char *)fstrtok(t_fp,'/',2),2)-1;
			td_date.tm_mday=natoi((char *)fstrtok(t_fp,' ',2),2);
			strcpy(td_thing,(char *)fstrtok(t_fp,'\n',280));
			return td_type;
	}
	
	return 0;
}

int cdate(const struct tm a,struct tm *b){
	if(a.tm_year<b->tm_year){return 0;
	}else if( (a.tm_year<=b->tm_year) && (a.tm_mon<b->tm_mon ) ){return 0;
	}else if( (a.tm_year<=b->tm_year) && (a.tm_mon<=b->tm_mon) && (a.tm_mday<b->tm_mday) ){return 0;}
	
	return 1;
}

void updw(){
	if(td_type=='~' || td_type=='?' || td_type=='!'){
		fprintf(t_updp,"%c%s %d/%d/%d %s\n",td_type,td_tag,td_date.tm_year+1900,td_date.tm_mon+1,td_date.tm_mday,td_thing);
	}else{
		fprintf(t_updp,"%c%s %s\n",td_type,td_tag,td_thing);
	}
}
