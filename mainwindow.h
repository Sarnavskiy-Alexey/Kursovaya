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

    void on_listWidget_enemy_itemSelectionChanged();

    void on_pushButton_addEnemy_clicked();

    void on_pushButton_deleteEnemy_clicked();

    void on_pushButton_clearEnemy_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;

    void add_T_aviation();
    void FromDB_T_aviation();
    void FromDB_T_enemy();
    void printAllAircrafts_T_aviation();
    void printAllEnemies_T_enemy();
    bool checkAircrafts_T_aviation();
    bool checkEnemies_T_enemy();
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

typedef struct
{
    QString key_zrk;
    QString zrk_name;
    QString targeting_system;
    QString min_destr_range;
    QString max_destr_range;
    QString AAGM_velocity;
    QString max_height;
} T_enemy;

extern QVector<T_aviation> vector_T_aviation;
extern QVector<T_enemy> vector_T_enemy;

#endif // MAINWINDOW_H
