#include "headers.h"

char *_strcat(const char *s,const char *t){
	static char *newstr;
	char *p;
	p = (char *)malloc(strlen(s)+strlen(t)+1);
	newstr = p;
	
	while(*s != '\0'){
		*p++ = *s++;
	}
	while(*t != '\0'){
		*p++ = *t++;
	}
	*p = '\0';
	return newstr;
}

char *endcut(char s[]){
	if(s[strlen(s)-1]=='\n')s[strlen(s)-1]='\0';
	return s;
}

char *fstrtok(FILE *fp,const char t,int bytes){
	static char *fstp;
	char *po;
	char one;
	po = (char *)malloc(bytes+1);
	fstp = po;
	
	while( (one = fgetc(fp)) != t){
		if(one == EOF){
			*po = '\0';
			return fstp;
		}
		*po++ = one;
	}
	*po = '\0';
	return fstp;
}

int natoi(const char *s,const int chs){
	int i,r=0;
	
	int rais(const int n,const int m){
		if(m==0)return 0;
		if(m==1)return n;
		int cn,tm;
		tm=n;
		for(cn=0;cn<m-1;cn++){
			tm*=n;
		}
		return tm;
	}
	
	for(i=0;i<chs;i++){
		if(iscntrl(s[i+1])){
			r+=s[i]-'0';
			return r;
		}
		if(isdigit(s[i])){
			r+=(s[i]-'0')*(rais(10,chs-i-1));
		}else{
			return r;
		}
	}
	return r;
}

int ercheck(const char *argv[],const int argc,const int a,const int b,const int c){	//0=引数なし 1=数値 2=文字列
	switch(a){
		case 1:
			if(isdigit(argv[argc+1][0])==0)return 0;
			break;
		case 2:
			if(strlen(argv[argc+1])==0)return 0;
			break;
		default:
			return 0;
			break;
	}
		if(b==0)return 1;
	switch(b){
		case 1:
			if(isdigit(argv[argc+2][0])==0)return 0;
			break;
		case 2:
			if(strlen(argv[argc+1])==0)return 0;
			break;
		default:
			return 0;
			break;
	}
		if(c==0)return 1;
	switch(c){
		case 1:
			if(isdigit(argv[argc+3][0])==0)return 0;
			break;
		case 2:
			if(strlen(argv[argc+1])==0)return 0;
			break;
		default:
			return 0;
			break;
	}
	return 1;
}
