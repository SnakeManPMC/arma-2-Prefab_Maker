#ifndef PREFABMAKER_H
#define PREFABMAKER_H
#include <QFile>
#include <QStringList>

class prefabMaker
{
public:
    prefabMaker();
    void Open_Files();
    void Read_Lines();
    void Close_Files();

private:
    QString line, xposstr, yposstr, rotastr, p3dobj, elev;
    QStringList list;
    bool ok;

    // seed house coords
    float seedX, seedY;

    QFile file;
    QFile file2;
};

#endif // PREFABMAKER_H
