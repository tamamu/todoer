#include "headers.h"

//TODO関係変数
DIR *t_dp;				/* TODO格納ディレクトリポインタ */
FILE *t_cfgp;			/* TODO設定ファイルポインタ */
FILE *t_fp;				/* TODOファイルポインタ */
FILE *t_updp;			/* TODOファイル更新用ポインタ */
char *t_dn;			/* TODO格納ディレクトリ名 */
//		t_cfgn;			/* TODO設定ファイル名 ".todoerc" */
char *t_fn;				/* TODOファイル名 */

char td_type;			/* TODOデータ_タイプ */
char td_tag[16];		/* TODOデータ_タグ */
char td_thing[280];/* TODOデータ_内容 */
struct tm td_date;	/* TODOデータ_締切り日付 */
//////////////////

//動作に関わる変数
char a_opt;				/* コマンドラインオプション */
int a_opopt;			/* コマンドラインオプションオプション */
int a_cn;				/* コマンドラインオプションナンバー */
char a_cmd;			/* 実行コマンド */
int a_dmo;				/* 一致しなかったオプション数 */
int num;
///////////////////

//一時的な変数
char *o_hdn;			/* HOMEディレクトリ名 */
time_t o_t;				/* 現在時刻処理用変数 */
struct tm *o_now;	/* 現在の日付 */
///////////////

//格納用変数
char s_cfgl[512];			/* 設定ファイル読み出し用 */
char s_tag[16];				/* 追加用タグ */
char s_thing[280];			/* 追加用内容 */
struct tm s_date;			/* 追加用日付 */
char *s_temp;
/////////////

int main(int argc,char *argv[]){

	//コマンドライン処理
	while(argc > 1){
		argc--;
		
		if(argv[argc][0] == '-'){
			if(argv[argc][1] == 'a' && argv[argc][2] == '\0'){
				a_opt = 'a';
			}else if(argv[argc][1] == 'i' && argv[argc][2] == '\0'){
				a_opt = 'i';
			}else if(argv[argc][1] == 'u' && argv[argc][2] == '\0'){
				a_opt = 'u';
			}else if(argv[argc][1] == 'h' && argv[argc][2]=='\0'){
				a_opt = 'h';
			}
		}else if(cmd("add") && a_dmo>=2){
			a_cmd = 'a';
			if( (a_dmo!=3 && ercheck(argv,argc,2,2,0) == 0 ) || (a_dmo==3 && ercheck(argv,argc,2,2,1) == 0) ){
				printf("エラー: コマンド引数の形式が違います。\n");
				return 1;
			}
			strcpy(s_tag,argv[argc+1]);
			strcpy(s_thing,argv[argc+2]);
			if(a_dmo==3){
				a_opopt=1;a_dmo--;
				s_date.tm_year = atoi(strtok(argv[argc+3],"/"))-1900;
				s_date.tm_mon = atoi(strtok(NULL,"/"))-1;
				s_date.tm_mday = atoi(strtok(NULL," "));
			}
			a_dmo -=2;
		}else if(cmd("delete") && a_dmo>=1){
			if(ercheck(argv,argc,1,0,0) == 0){
				printf("エラー: コマンド引数の形式が違います。\n");
				return 1;
			}
			a_cmd = 'd';
			a_cn=argc+1;
			a_dmo -=1;
		}else if(cmd("comp") && a_dmo>=1){
			if(ercheck(argv,argc,1,0,0) == 0){
				printf("エラー: コマンド引数の形式が違います。\n");
				return 1;
			}
			a_cmd = 'c';
			a_cn=argc+1;
			a_dmo -=1;
		}else{
			a_dmo++;
		}
			
		
	}
	
	//一致しないオプションが残っていたらエラー
	if(a_dmo > 0 || a_opt == 'h'){
		printf("使用法: todoer [オプション] [コマンド] [コマンド引数]...\n");
		printf("設定されたTODOリストを表示します (デフォルトは$HOME/ToDo/todo.txt)。\n");
		printf("設定はHOMEか実行ファイルのあるディレクトリの.todoercを参照します。\n");
		printf("\n");
		printf("オプション :\n");
		printf("\t-a\t\t全てのTODOを表示。\n");
		printf("\t-i\t\t実行中のTODOのみ表示。\n");
		printf("\t-u\t\tTODOファイルの更新。\n");
		printf("\t-h\t\tこのヘルプを表示。\n");
		printf("コマンド :\n");
		printf("\tadd\t\t新規TODO追加。\n");
		printf("\t\ttodoer add tag thing\ttagというタグでthingという内容のTODOを追加。\n");
		printf("\t\ttodoer add tag thing YYYY/MM/DD\ttagというタグでthingという内容の期限付きTODOを追加。\n");
		printf("\tdelete\t\t指定した番号のTODOを削除。\n");
		printf("\t\ttodoer delete 3\t3番のTODOを削除。\n");
		printf("\tcomp\t\t指定した番号のTODOに完了印をつける。\n");
		printf("\t\ttodoer comp 3\t3番のTODOに完了印。\n");
		return 1;
	}
	
	startup();//.
	
	if(rcopen())rcview();//.
	if(tdopen() == 0){return 1;}//.

	if(a_opt == 'u'){	//update
		t_updp = fopen(_strcat(_strcat(t_dn,t_fn),".temp"),"a+");
		while(tdview(td_date)){
			if(td_type == '~' || td_type == '?' || td_type == '!'){
				if(cdate(td_date,o_now)){
					fprintf(t_updp,"%c%s %d/%d/%d %s\n",td_type,td_tag,td_date.tm_year+1900,td_date.tm_mon+1,td_date.tm_mday,td_thing);
				}
			}else{
				fprintf(t_updp,"%c%s %s\n",td_type,td_tag,td_thing);
			}
		}
		fclose(t_updp);
		fclose(t_fp);
		remove(_strcat(t_dn,t_fn));
		rename(_strcat(_strcat(t_dn,t_fn),".temp"),_strcat(t_dn,t_fn));
		t_fp = fopen(_strcat(t_dn,t_fn),"a+");
	}
	if(a_cmd == 'a'){	//add
		printf("add command\n");
		if(a_opopt==1){
			fprintf(t_fp,"%c%s %d/%d/%d %s\n",'~',s_tag,s_date.tm_year+1900,s_date.tm_mon+1,s_date.tm_mday,s_thing);
		}else{
			fprintf(t_fp,"%c%s %s\n",'@',s_tag,s_thing);
		}
	}
	if(a_cmd == 'd'){	//delete
		printf("delete command\n");
		num=0;
		t_updp = fopen(_strcat(_strcat(t_dn,t_fn),".temp"),"a+");
		while(tdview()){
			if(atoi(argv[a_cn])==num){
				continue;
			}
			updw();
		}
		fclose(t_updp);
		remove(_strcat(t_dn,t_fn));
		rename(_strcat(_strcat(t_dn,t_fn),".temp"),_strcat(t_dn,t_fn));
		t_fp = freopen(_strcat(t_dn,t_fn),"a+",t_fp);
	}
	if(a_cmd == 'c'){
		t_updp = fopen(_strcat(_strcat(t_dn,t_fn),".temp"),"a+");
		num=0;
		while(tdview()){
			if(atoi(argv[a_cn])==num){
				fprintf(t_updp,"%c%s %d/%d/%d %s\n",'!',td_tag,o_now->tm_year+1900,o_now->tm_mon+1,o_now->tm_mday,td_thing);
				continue;
			}
			updw();
		}
		fclose(t_updp);
		remove(_strcat(t_dn,t_fn));
		rename(_strcat(_strcat(t_dn,t_fn),".temp"),_strcat(t_dn,t_fn));
		t_fp = freopen(_strcat(t_dn,t_fn),"a+",t_fp);
	}
	if(a_opt == 'a'){	//viewall
		printf("viewall option\n");
		num=0;
		fseek(t_fp,0,SEEK_SET);
		while(feof(t_fp)==0){
			switch(tdview(td_date)){
				case '@':
					printf("%d:%-36s\t%-16s\n",num,td_thing,td_tag);
				break;
				case '~':
					printf("%d:%-36s\t%-16s\t〜%d/%d/%d\n",num,td_thing,td_tag,td_date.tm_year+1900,td_date.tm_mon+1,td_date.tm_mday);
				break;
				default:
				break;
			}
		}
		num=0;
		fseek(t_fp,0,SEEK_SET);
		while(feof(t_fp)==0){
			if(tdview(td_date)=='?'){
				printf("%d:%-36s\t%-16s\t〜%d/%d/%d\n",num,td_thing,td_tag,td_date.tm_year+1900,td_date.tm_mon+1,td_date.tm_mday);
			}
		}
		num=0;
		fseek(t_fp,0,SEEK_SET);
		while(feof(t_fp)==0){
			if(tdview(td_date)=='!'){
				printf("%d:%-36s\t%-16s\t %d/%d/%d complete.\n",num,td_thing,td_tag,td_date.tm_year+1900,td_date.tm_mon+1,td_date.tm_mday);
			}
		}
	}
	if(a_opt == 'i'){	//viewinternal
		printf("viewinternal option\n");
		fseek(t_fp,0,SEEK_SET);
		while(feof(t_fp)==0){
			switch(tdview(td_date)){
				case '@':
					printf("%d:%s\t\t%s\n",num,td_thing,td_tag);
				break;
				case '~':
					printf("%d:%s\t\t%s\t〜%d/%d/%d\n",num,td_thing,td_tag,td_date.tm_year+1900,td_date.tm_mon+1,td_date.tm_mday);
				break;
				default:
				break;
			}
		}
	}
	
	closedir(t_dp);
	fcloseall();
	//終了処理
	return 0;
}
