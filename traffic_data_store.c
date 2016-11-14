#include <stdio.h>
#include <sqlite3.h>
#include <time.h>

#include "traffic_resolv.h"

/*static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	int i;
	for(i=0; i&lt;argc; i++)
	{
		printf("%s = %s\n", azColName[i],argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}
*/
int  insert_to_database(char* Time, char* Rxtotal, char* Txtotal)
{
	int out = 0;
	sqlite3 *db = 0;
	char *pErrMsg;
	int ret = sqlite3_open("/usr/db/tunnel_flow.db",&db);
	if( ret != SQLITE_OK )
	{
			fprintf(stderr, "无法打开数据库: %s", sqlite3_errmsg(db));
			return 1;
	}
	printf("数据库连接成功!\n");
	
	char buf[128]="";
	snprintf(buf,128,"INSERT INTO main"\
			" VALUES('%s','%s','%s');",Time, Rxtotal, Txtotal);
	out = sqlite3_exec( db, buf, 0, 0, &pErrMsg);
	if(out == SQLITE_OK)
	{
		printf("插入数据成功\n");
		sqlite3_close(db);
		return 0;
	}
	fprintf(stderr, "SQL error:%s\n", pErrMsg);
	sqlite3_close(db);
	return -1;
}

char* speed_store(char* Time, char* Rx, char* Tx)
{
	int end;
	end = insert_to_database(Time, Rx, Tx);
	if( end == 0)
	{
		return "success";
	}
	else
	{
		return "fail";
	}
}
