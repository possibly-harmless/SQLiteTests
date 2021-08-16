#ifndef DB_SQL_INCLUDED
#define DB_SQL_INCLUDED

char* CREATE_TABLE_SQL = 
          "DROP TABLE IF EXISTS COMPANY;"
          "CREATE TABLE COMPANY("
          "ID INT PRIMARY KEY NOT NULL,"
          "NAME TEXT NOT NULL,"
          "AGE INT NOT NULL,"
          "ADDRESS CHAR(50),"
          "SALARY REAL );";

char * INSERT_DATA_SQL = 
          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
          "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "

          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
          "VALUES (2, 'Allen', 25, 'Texas', 15000.00 );      "

          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
          "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );     "

          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
          "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 ); ";

char * SELECT_DATA_SQL = "SELECT * from COMPANY";

#endif