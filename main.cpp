#include <QApplication>
#include "FileSelector.h"
#include "globals.h"

QString selectedFile = "";
QStringList selectedModels;
QString selectedFont = "Tempora";
QString selectedSize = "14";
std::vector<std::vector<QString>> parsedDataA;
std::vector<std::vector<QString>> parsedDataB;
QList<QString> parsedDataD;
std::vector<std::vector<QString>> parsedDataD1;
std::vector<std::vector<QString>> parsedDataD2;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FileSelector window;
    window.setWindowTitle("Выбор файла");
    window.resize(300, 150);
    window.show();
    return app.exec();
}
