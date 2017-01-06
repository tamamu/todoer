#ifndef _INCLUDE_EXTERNAL_
#define _INCLUDE_EXTERNAL_

char *_strcat(const char *s,const char *t);
char *endcut(char s[]);

#endif

//TODO関係変数
extern DIR *t_dp;				/* TODO格納ディレクトリポインタ */
extern FILE *t_cfgp;			/* TODO設定ファイルポインタ */
extern FILE *t_fp;				/* TODOファイルポインタ */
extern FILE *t_updp;			/* TODOファイル更新用ポインタ */
extern char *t_dn;			/* TODO格納ディレクトリ名 */
//		t_cfgn;			/* TODO設定ファイル名 ".todoerc" */
extern char *t_fn;				/* TODOファイル名 */

extern char td_type;			/* TODOデータ_タイプ */
extern char td_tag[16];		/* TODOデータ_タグ */
extern char td_thing[280];/* TODOデータ_内容 */
extern struct tm td_date;	/* TODOデータ_締切り日付 */
//////////////////

//動作に関わる変数
extern char a_opt;				/* コマンドラインオプション */
extern char a_cmd;			/* 実行コマンド */
extern int a_dmo;				/* 一致しなかったオプション数 */
extern int num;
///////////////////

//一時的な変数
extern char *o_hdn;			/* HOMEディレクトリ名 */
extern time_t o_t;				/* 現在時刻処理用変数 */
extern struct tm *o_now;	/* 現在の日付 */
///////////////

//格納用変数
extern char s_cfgl[512];			/* 設定ファイル読み出し用 */
extern char *s_temp;
/////////////
