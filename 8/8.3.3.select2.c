#include<stdlib.h>
#include<stdio.h>

#include"mysql.h"

void display_row();

MYSQL my_connection;
MYSQL_ROW sqlrow;
MYSQL_RES *res_ptr;
int res;
int main(int argc, char *argv[]){
    

    
    mysql_init(&my_connection);
    if (mysql_real_connect(&my_connection, "localhost", "rick","23571113", 
                           "foo", 0, NULL, 0)){
        printf("Connection success\n");

    res = mysql_query(&my_connection, "SELECT childno, fname, age FROM children WHERE age > 5");

    if(res) {
        printf("SELECT error: %s\n", mysql_error(&my_connection));
    } else {
        res_ptr = mysql_use_result(&my_connection);
        if (res_ptr) {
         while ((sqlrow = mysql_fetch_row(res_ptr))) {
             printf("Fetched data...\n");
             display_row();
         }
         if (mysql_errno(&my_connection)) {
             printf("Retrive error: %s\n",mysql_error(&my_connection));
         }
         mysql_free_result(res_ptr);
        }
    }

        mysql_close(&my_connection);
    } else {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(&my_connection)){
            fprintf(stderr, "Connection error %d: %s\n",
                   mysql_errno(&my_connection), mysql_error(&my_connection));
        }
    }
    return EXIT_SUCCESS;
}

void display_row(){
    unsigned int field_count;

    field_count = 0; 
    while (field_count < mysql_field_count(&my_connection)){
        printf("%s ", sqlrow[field_count]);
        field_count++;
    }
    printf("\n");
}
