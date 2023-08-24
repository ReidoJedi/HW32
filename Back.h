#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "mysql.h"
using namespace std;

class DBConnection {
public:
    void openDB(const char* Login, const char* Password);
    void closeDB();
    void execQueryDB();

};

void  DBConnection::openDB(const char* Login, const char* Password) {
    MYSQL mysql;
    mysql_init(&mysql);


    if (&mysql == NULL) {
        cout << "Error: can't create MySQL-descriptor" << endl;
    }


    if (!mysql_real_connect(&mysql, "localhost", Login, Password, "testdb", 0, NULL, 0)) {
        cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
    }
    else {
        cout << "Success!" << endl;
    }

}

void  DBConnection::closeDB() {
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_close(&mysql);
    system("Pause");
}

void  DBConnection::execQueryDB() {
    MYSQL mysql;
    mysql_init(&mysql);
    MYSQL_RES* res;
    MYSQL_ROW row;
    int i = 0;
    mysql_query(&mysql, "SELECT * FROM test");

    if (res = mysql_store_result(&mysql)) {
        while (row = mysql_fetch_row(res)) {
            for (i = 0; i < mysql_num_fields(res); i++) {
                cout << row[i] << "  ";
            }
            cout << endl;
        }
    }
    else
        cout << "Ошибка MySql номер " << mysql_error(&mysql);
}

class ClassThatUsesDB : DBConnection {
public:
    ClassThatUsesDB() {};
    virtual  ~ClassThatUsesDB() {};

    virtual void openConnection(const char* Login, const char* Password);
    virtual void useConnection();
    virtual void closeonnection();

};

void  ClassThatUsesDB::openConnection(const char* Login, const char* Password) {
    cout << "Connection attempt " << endl;
    const char* Login = "root";
    const char* password = "root2";
    openDB(Login, Password);
}

void  ClassThatUsesDB::useConnection() {
    execQueryDB();
}

void  ClassThatUsesDB::closeonnection() {
    closeDB();
}

class MockTesting : public ClassThatUsesDB, public DBConnection {
public:
    MOCK_METHOD(void openConnection(const char* Login, const char* Password), (override));
    MOCK_METHOD(void useConnection, (), (override));
    MOCK_METHOD(void, closeonnection, (), (override));

};
