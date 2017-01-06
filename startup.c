#include "headers.h"

void startup(){
	time(&o_t);o_now = localtime(&o_t);	//現在日付取得
	o_hdn = getenv("HOME");					//ホームディレクトリ名取得
	
	t_dn = _strcat(o_hdn,"/ToDo");			//未設定時のため予め設定しておく
	t_fn = _strcat("/","todo.txt");				//					〃
}

int rcopen(){
	if((t_cfgp = fopen(_strcat(o_hdn,RCNAME),"r")) == NULL){
		if((t_cfgp = fopen(RCNAME,"r")) == NULL){
			/* Use default preference. */
			return 0;
		}
		return 1;
	}
	return 1;
}

void rcview(){
	while(fgets(s_cfgl,512,t_fp) != NULL){
		if(strncmp(s_cfgl,"TODODIR=",8) == 0){
			t_dn = _strcat("",&s_cfgl[8]);
			endcut(t_dn);
		}else if(strncmp(s_cfgl,"TODOFILE=",9) == 0){
			t_fn = _strcat("",&s_cfgl[9]);
			endcut(t_dn);
		}
	}
}

int tdopen(){
	if((t_dp = opendir(t_dn)) == NULL){
		if(cmkdir(t_dn) == -1){
			printf("Making tododir is miss.\n");
			return 0;
		}
	}
	t_fp = fopen(_strcat(t_dn,t_fn),"a+");
	return 1;
}
