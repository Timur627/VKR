#ifndef WRITEMODEL_H
#define WRITEMODEL_H

#include <QWidget>

class WriteModel
{
public:
    WriteModel();
    void writeModelA(QTextStream &out);
    void writeModelB(QTextStream &out);
    void writeModelD(QTextStream &out);
    void writeModelD1(QTextStream &out);
    void writeModelD2(QTextStream &out);
};

#endif // WRITEMODEL_H
