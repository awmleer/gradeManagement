#include "db.h"
#include <QtSql>
#include <QtDebug>
#include <QApplication>
#include <vector>
#include "student.h"

namespace Db {
QSqlDatabase db;
}

using namespace Db;

bool Db::connect(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    if (!db.open()){
        qDebug() << "Database Error!";
        return false;
    }
    return true;
}

bool Db::init(){
    bool connectResult = Db::connect();
    if (connectResult==false) return false;
    qDebug() << "db connect: " << connectResult;
    QSqlQuery query;
    qDebug() << query.prepare("CREATE TABLE IF NOT EXISTS student ("
                              "id INTEGER PRIMARY KEY,"
                              "name VARCHAR(30),"
                              "type VARCHAR(10),"
                              "enrollmentYear SMALLINT"
                              ");"
                              );
    return query.exec();
}

bool Db::testInsert(){
    QSqlQuery query;
    query.prepare("INSERT INTO student (id, name, type, enrollmentYear) "
                  "VALUES (:id, :name, :type, :enrollmentYear)"
                  );
    query.bindValue(":id", 1001);
    query.bindValue(":name", "Bart");
    query.bindValue(":type", "master");
    query.bindValue(":enrollmentYear",2016);
    return query.exec();
}


vector<Student> Db::test(){
    QSqlQuery query("SELECT * FROM student");
    int idNo = query.record().indexOf("id");
    int nameNo = query.record().indexOf("name");
    int typeNo = query.record().indexOf("type");
    int enrollmentYearNo = query.record().indexOf("enrollmentYear");
    vector<Student> students;
    while (query.next())
    {
        Student student(
                    query.value(idNo).toInt(),
                    query.value(nameNo).toString(),
                    query.value(typeNo).toString(),
                    query.value(enrollmentYearNo).toInt()
                    );
        students.push_back(student);
        //        QString name = query.value(nameNo).toString();
    }
    qDebug() << students.size();
    return students;
}
