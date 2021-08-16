#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "parson.h"
#include "db_sql.h"

#define DB_PATH "test.db"
#define SUCCESS 0
#define FAILURE 1


static int callback(void *data, int argc, char **argv, char **azColName);

static int create_and_test_db(sqlite3 *conn);



int db_connect_verbose(char* db_path, sqlite3 ** connection_ptr);
int db_sql_execute_verbose(sqlite3 *conn, const char* sql, const char* success_msg);




int main(int argc, char *argv[])

{

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char *data = "Callback function called";

    /* Open database */

    if(db_connect_verbose(DB_PATH, &db) != SQLITE_OK){
      exit(EXIT_FAILURE);  
    }

    if(create_and_test_db(db) != SUCCESS){
      exit(EXIT_FAILURE);  
    }
    


    sqlite3_close(db);
    return 0;
}

static int callback(void *data, int argc, char **argv, char **azColName)
{
  int i;
  fprintf(stderr, "%s: \n", (const char *)data);
  for (i = 0; i < argc; i++)
  {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int db_connect_verbose(char* db_path, sqlite3 ** connection_ptr){
  int result;
  result = sqlite3_open(db_path, connection_ptr);
  if (result){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*connection_ptr)); 
  } else{
    fprintf(stderr, "Opened database successfully\n");
  }
  return result;
}

int db_sql_execute_verbose(sqlite3 *conn, const char* sql, const char* success_msg){
  int result;
  char *zErrMsg = 0;
  const char *data = "Callback function called";

  if(!success_msg){
    success_msg = "Operation was successful";
  }

  result = sqlite3_exec(conn, sql, callback, (void *) data, &zErrMsg);
  if (result != SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
  } else {
      fprintf(stdout, "%s\n", success_msg);
  }
  return result;
}


static int create_and_test_db(sqlite3 *conn){
  if(db_sql_execute_verbose(
        conn, CREATE_TABLE_SQL, "Table created successfully"
      ) != SQLITE_OK){
      return FAILURE;
    }
  
    if(db_sql_execute_verbose(
        conn, INSERT_DATA_SQL, "Records inserted successfully") != SQLITE_OK
      ){
      return FAILURE;
    }

    if(db_sql_execute_verbose(
        conn, SELECT_DATA_SQL, "Operation done successfully\n") != SQLITE_OK
      ){
      return FAILURE;
    }
    return SUCCESS;
}