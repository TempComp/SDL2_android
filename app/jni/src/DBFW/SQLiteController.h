//
// Created by yvas on 22.01.2019.
//

#ifndef SDL2_ANDROID_SQLITECONTROLLER_H
#define SDL2_ANDROID_SQLITECONTROLLER_H

class SQLiteController{

private:
    SQLiteController(& SQLiteControlleer );
    SQLiteController operator=(SQLiteController & sqLiteController){};

    static SQLiteController sql_db;

};

#endif //SDL2_ANDROID_SQLITECONTROLLER_H

