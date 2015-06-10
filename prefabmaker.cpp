#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include "prefabmaker.h"

prefabMaker::prefabMaker()
{
    Open_Files();
    Read_Lines();
    Close_Files();
}


void prefabMaker::Open_Files()
{
    QFile file("D://Test_files//utes-house-template-1.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Unable to open " << file.fileName();
        exit (1);
    }

    QFile file2("D://Test_files//deletemesomuch.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Unable to open " << file2.fileName();
        exit (1);
    }
}


void prefabMaker::Read_Lines()
{
    QTextStream in(&file);
    QTextStream out(&file2);
    // read first line, which always must be our seed house
    line = in.readLine();
    list = line.split(";");
    qDebug() << "Seed House: " << list[0] << " " << list[1] << " " << list[2];
    p3dobj = list[0];
    seedX = list[1].toFloat(&ok);
    seedY = list[2].toFloat(&ok);
    out << p3dobj << ";" << "SEED;SEED;" << list[3] << ";" << list[4] << ";\n";

    while (!in.atEnd())
    {
        // read all the additional decoration objects
        line = in.readLine();
        list = line.split(";");
        //qDebug() << list[0] << " " << list[1] << " " << list[2];

        // decor p3d name
        p3dobj = list[0];
        // coordinates
        xposstr = list[1];
        yposstr = list[2];
        // elevation
        elev = list[3];
        // rotation
        rotastr = list[4];

        // convert coordinates to float
        float xPos = xposstr.toFloat(&ok);
        float yPos = yposstr.toFloat(&ok);

        // calculate the relative position
        float x_new = (seedX - xPos);
        float y_new = (seedY - yPos);

        out << p3dobj << ";" << x_new << ";" << y_new << ";" << elev << ";" << rotastr << ";\n";
    }
}


void prefabMaker::Close_Files()
{
    file.close();
    file2.close();
}
