#include "processingmodels.h"
#include "globals.h"
#include <QRegularExpression>

processingModels::processingModels() {}

void processingModels::processingModelA()
{
    std::sort(parsedDataA.begin(), parsedDataA.end(), [](const std::vector<QString>& a, const std::vector<QString>& b) {

        QRegularExpression regex(R"(([a-z])(\d+)\.(\d+))");

        QRegularExpressionMatch matchA = regex.match(a[0]);
        QRegularExpressionMatch matchB = regex.match(b[0]);

        if (matchA.hasMatch() && matchB.hasMatch()) {
            QString symbolA = matchA.captured(1);
            int numberA = matchA.captured(2).toInt();
            int decimalA = matchA.captured(3).toInt();

            QString symbolB = matchB.captured(1);
            int numberB = matchB.captured(2).toInt();
            int decimalB = matchB.captured(3).toInt();

            if (symbolA == symbolB) {
                if (numberA == numberB) {
                    return decimalA < decimalB;
                }
                return numberA < numberB;
            }
            return symbolA < symbolB;
        }
        return false;
    });
}

void processingModels::processingModelB()
{
    std::sort(parsedDataB.begin(), parsedDataB.end(), [](const std::vector<QString>& a, const std::vector<QString>& b) {

        QRegularExpression regex(R"(([a-z])(\d+)\.(\d+))");

        QRegularExpressionMatch matchA = regex.match(a[0]);
        QRegularExpressionMatch matchB = regex.match(b[0]);

        if (matchA.hasMatch() && matchB.hasMatch()) {
            QString symbolA = matchA.captured(1);
            int numberA = matchA.captured(2).toInt();
            int decimalA = matchA.captured(3).toInt();

            QString symbolB = matchB.captured(1);
            int numberB = matchB.captured(2).toInt();
            int decimalB = matchB.captured(3).toInt();

            if (symbolA == symbolB) {
                if (numberA == numberB) {
                    return decimalA < decimalB;
                }
                return numberA < numberB;
            }
            return symbolA < symbolB;
        }
        return false;
    });
}

void processingModels::processingModelD()
{
    std::sort(parsedDataD.begin(), parsedDataD.end(), [](const QString &a, const QString &b) {
        QString keyA = a.split(" & ")[0];
        QString keyB = b.split(" & ")[0];

        QRegularExpression re("([A-Za-z]*)(\\d+)\\.(\\d+)");
        QRegularExpressionMatch matchA = re.match(keyA);
        QRegularExpressionMatch matchB = re.match(keyB);

        if (matchA.hasMatch() && matchB.hasMatch()) {
            QString letterA = matchA.captured(1);
            QString letterB = matchB.captured(1);
            int numA = matchA.captured(2).toInt();
            int subNumA = matchA.captured(3).toInt();
            int numB = matchB.captured(2).toInt();
            int subNumB = matchB.captured(3).toInt();

            if (letterA != letterB)
                return letterA < letterB;

            if (numA != numB)
                return numA < numB;

            return subNumA < subNumB;
        }

        return keyA < keyB;
    });
}

void processingModels::processingModelD1()
{
    std::sort(parsedDataD1.begin(), parsedDataD1.end(), [](const std::vector<QString>& a, const std::vector<QString>& b) {

        QRegularExpression regex(R"(A(\d+)\.(\d+))");

        QRegularExpressionMatch matchA = regex.match(a[0]);
        QRegularExpressionMatch matchB = regex.match(b[0]);

        if (matchA.hasMatch() && matchB.hasMatch()) {
            int groupA = matchA.captured(1).toInt();
            int numberA = matchA.captured(2).toInt();
            int groupB = matchB.captured(1).toInt();
            int numberB = matchB.captured(2).toInt();

            if (groupA == groupB)
                return numberA < numberB;
            return groupA < groupB;
        }
        return false;
    });
}

void processingModels::processingModelD2()
{
    std::sort(parsedDataD2.begin(), parsedDataD2.end(), [](const std::vector<QString>& a, const std::vector<QString>& b) {

        QRegularExpression regex(R"(([a-z])(\d+)\.(\d+))");

        QRegularExpressionMatch matchA = regex.match(a[0]);
        QRegularExpressionMatch matchB = regex.match(b[0]);

        if (matchA.hasMatch() && matchB.hasMatch()) {
            QString symbolA = matchA.captured(1);
            int numberA = matchA.captured(2).toInt();
            int decimalA = matchA.captured(3).toInt();

            QString symbolB = matchB.captured(1);
            int numberB = matchB.captured(2).toInt();
            int decimalB = matchB.captured(3).toInt();

            if (symbolA == symbolB) {
                if (numberA == numberB) {
                    return decimalA < decimalB;
                }
                return numberA < numberB;
            }
            return symbolA < symbolB;
        }
        return false;
    });
}
