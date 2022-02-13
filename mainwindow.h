#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QVector>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_exit_clicked();

    void on_listWidget_availableACK_itemSelectionChanged();

    void on_pushButton_clearACK_clicked();

    void on_pushButton_addACK_clicked();

    void on_pushButton_deleteACK_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;

    void add_T_aviation();
    void FromDB_T_aviation();
    void printAllAircrafts_T_aviation();
};

typedef struct
{
    QString key_aviation;
    QString name;
    QString country;
    QString wingspan;
    QString mass;
    QString velocity;
    QString armament_units;
    QString combat_radius;
    QString flight_range;
    QString cost;
} T_aviation;

extern QVector<T_aviation> vector_T_aviation;

#endif // MAINWINDOW_H
