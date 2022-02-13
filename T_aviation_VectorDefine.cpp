#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::printAllAircrafts_T_aviation()
{
    vector_T_aviation.clear();

    qDebug() << "\nAircrafts in db:";
    QSqlQuery query("SELECT * FROM aviation");
    int id_key_aviation = query.record().indexOf("key_aviation");
    int id_name = query.record().indexOf("name");
    int id_country = query.record().indexOf("country");
    int id_wingspan = query.record().indexOf("wingspan");
    int id_mass = query.record().indexOf("mass");
    int id_velocity = query.record().indexOf("velocity");
    int id_armament_units = query.record().indexOf("armament_units");
    int id_combat_radius = query.record().indexOf("combat_radius");
    int id_flight_range = query.record().indexOf("flight_range");
    int id_cost = query.record().indexOf("cost");

    while (query.next())
    {
        QString key_aviation = query.value(id_key_aviation).toString();
        QString name = query.value(id_name).toString();
        QString country = query.value(id_country).toString();
        QString wingspan = query.value(id_wingspan).toString();
        QString mass = query.value(id_mass).toString();
        QString velocity = query.value(id_velocity).toString();
        QString armament_units = query.value(id_armament_units).toString();
        QString combat_radius = query.value(id_combat_radius).toString();
        QString flight_range = query.value(id_flight_range).toString();
        QString cost = query.value(id_cost).toString();

        qDebug() << "\t*" << key_aviation
                 << "\t*" << name
                 << "\t*" << country
                 << "\t*" << wingspan
                 << "\t*" << mass
                 << "\t*" << velocity
                 << "\t*" << armament_units
                 << "\t*" << combat_radius
                 << "\t*" << flight_range
                 << "\t*" << cost;

        T_aviation temp;
        temp.key_aviation = key_aviation;
        temp.name = name;
        temp.country = country;
        temp.wingspan = wingspan;
        temp.mass = mass;
        temp.velocity = velocity;
        temp.armament_units = armament_units;
        temp.combat_radius = combat_radius;
        temp.flight_range = flight_range;
        temp.cost = cost;
        vector_T_aviation.append(temp);
    }
    qDebug() << "\nvector_T_aviation size is " << vector_T_aviation.size() << "\n";

    FromDB_T_aviation();
}
