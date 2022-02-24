#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::printAllEnemies_T_enemy()
{
    vector_T_enemy.clear();

    qDebug() << "\nEnemies in db:";
    QSqlQuery query("SELECT * FROM zrk");
    int id_key_zrk = query.record().indexOf("key_zrk");
    int id_zrk_name = query.record().indexOf("zrk_name");
    int id_targeting_system = query.record().indexOf("targeting_system");
    int id_min_destr_range = query.record().indexOf("min_destr_range");
    int id_max_destr_range = query.record().indexOf("max_destr_range");
    int id_AAGM_velocity = query.record().indexOf("AAGM_velocity");
    int id_max_height = query.record().indexOf("max_height");

    while (query.next())
    {
        QString key_zrk = query.value(id_key_zrk).toString();
        QString zrk_name = query.value(id_zrk_name).toString();
        QString targeting_system = query.value(id_targeting_system).toString();
        QString min_destr_range = query.value(id_min_destr_range).toString();
        QString max_destr_range = query.value(id_max_destr_range).toString();
        QString AAGM_velocity = query.value(id_AAGM_velocity).toString();
        QString max_height = query.value(id_max_height).toString();

        qDebug() << "\t*" << key_zrk
                 << "\t*" << zrk_name
                 << "\t*" << targeting_system
                 << "\t*" << min_destr_range
                 << "\t*" << max_destr_range
                 << "\t*" << AAGM_velocity
                 << "\t*" << max_height;

        T_enemy temp;
        temp.key_zrk = key_zrk;
        temp.zrk_name = zrk_name;
        temp.targeting_system = targeting_system;
        temp.min_destr_range = min_destr_range;
        temp.max_destr_range = max_destr_range;
        temp.AAGM_velocity = AAGM_velocity;
        temp.max_height = max_height;
        vector_T_enemy.append(temp);
    }
    qDebug() << "\nvector_T_enemy size is " << vector_T_enemy.size() << "\n";

    FromDB_T_enemy();
}
