#include "getmodel.h"
#include "globals.h"
#include <QRegularExpression>
#include <QFileDialog>
GetModel::GetModel() {}

void GetModel::GetModelA()
{
    if (selectedFile.isEmpty()) {
        return;
    }

    QFile file(selectedFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();


    QRegularExpression linkRegex(R"(<link afe2=\"(\d+)\" type=\"(\d+)\" afe1=\"(\d+)\" afe3=\"(\d+)\"/>)");
    QRegularExpression pdRegex1(R"(<pd mark=\"[^\"]*\" symbol=\"(\d+)\" type=\"\d+\" status=\"\d+\" id=\"(\d+)\" name=\"[^\"]*\" number=\"(\d+)\" formalization=\"\d+\" level=\"(\d+)\"/>)");
    QRegularExpression pdRegex2(R"(<pd mark=\"[^\"]*\" symbol=\"(\d+)\" type=\"\d+\" status=\"\d+\" id=\"(\d+)\" name=\"[^\"]*\" number=\"(\d+)\" formalization=\"\d+\" level=\"(\d+)\">)");
    QRegularExpression pdRegex3(R"(<pd mark=\"[^\"]*\" symbol=\"(\d+)\" type=\"(\d+)\" status=\"\d+\" id=\"(\d+)\" name=\"[^\"]*\" number=\"(\d+)\" formalization=\"\d+\" level=\"(\d+)\"/>)");

    QRegularExpressionMatchIterator linkIterator = linkRegex.globalMatch(content);

    while (linkIterator.hasNext()) {
        QRegularExpressionMatch linkMatch = linkIterator.next();
        QString afe1 = linkMatch.captured(3);
        QString afe2 = linkMatch.captured(1);
        QString afe3 = linkMatch.captured(4);
        QString type = linkMatch.captured(2);

        if (afe3 != "0") {
            std::vector<QString> symbols;
            std::vector<QString> ids = {afe1, afe2, afe3};
            bool afe1_found_in_pdRegex2 = false;
            QString symbol1, symbol2, symbol3;

            for (const QString &id : ids) {
                bool found = false;
                QRegularExpressionMatchIterator pdIterator1 = pdRegex1.globalMatch(content);
                while (pdIterator1.hasNext()) {
                    QRegularExpressionMatch pdMatch = pdIterator1.next();
                    if (pdMatch.captured(2) == id) {
                        QChar symbolChar(pdMatch.captured(1).toInt());
                        QString level = pdMatch.captured(4);
                        QString number = pdMatch.captured(3);
                        QString symbolString = QString("%1%2.%3").arg(symbolChar).arg(level).arg(number);

                        if (id == afe1) symbol1 = symbolString;
                        else if (id == afe2) symbol2 = symbolString;
                        else if (id == afe3) symbol3 = symbolString;

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    QRegularExpressionMatchIterator pdIterator2 = pdRegex2.globalMatch(content);
                    while (pdIterator2.hasNext()) {
                        QRegularExpressionMatch pdMatch = pdIterator2.next();
                        if (pdMatch.captured(2) == id) {
                            QChar symbolChar(pdMatch.captured(1).toInt());
                            QString level = pdMatch.captured(4);
                            QString number = pdMatch.captured(3);
                            QString symbolString = QString("%1%2.%3").arg(symbolChar).arg(level).arg(number);

                            if (id == afe1) {
                                symbol1 = symbolString;
                                afe1_found_in_pdRegex2 = true;
                            } else if (id == afe2) {
                                symbol2 = symbolString;
                            } else if (id == afe3) {
                                symbol3 = symbolString;
                            }
                            break;
                        }
                    }
                }
            }

            if (!symbol1.isEmpty() && !symbol2.isEmpty() && !symbol3.isEmpty()) {
                if (afe1_found_in_pdRegex2) {
                    parsedDataA.push_back({symbol1, symbol2, "-", "Альтернатива"});
                    parsedDataA.push_back({symbol1, symbol3, "-", "Альтернатива"});
                } else {
                    parsedDataA.push_back({symbol1, symbol2, symbol3, "Последовательность"});
                }
            }
        }
        else if (type == "2") {
            QString symbol1, symbol2;
            bool foundAfe1 = false, foundAfe2 = false;
            QRegularExpressionMatchIterator pdIterator3 = pdRegex3.globalMatch(content);
            while (pdIterator3.hasNext()) {
                QRegularExpressionMatch pdMatch = pdIterator3.next();
                QString id = pdMatch.captured(3);
                QString pdType = pdMatch.captured(2);

                if (id == afe1 && pdType == "3") {
                    QChar symbolChar(pdMatch.captured(1).toInt());
                    QString level = pdMatch.captured(5);
                    QString number = pdMatch.captured(4);
                    symbol1 = QString("%1%2.%3").arg(symbolChar).arg(level).arg(number);
                    foundAfe1 = true;
                }
                else if (id == afe2) {
                    QChar symbolChar(pdMatch.captured(1).toInt());
                    QString level = pdMatch.captured(5);
                    QString number = pdMatch.captured(4);
                    symbol2 = QString("%1%2.%3").arg(symbolChar).arg(level).arg(number);
                    foundAfe2 = true;
                }

                if (foundAfe1 && foundAfe2) break;
            }

            if (foundAfe1 && foundAfe2) {
                parsedDataA.push_back({symbol1, symbol2, "-", "Цикл"});
            }
        }
    }
}

void GetModel::GetModelB()
{
    if (selectedFile.isEmpty()) {
        return;
    }

    QFile file(selectedFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);

    QRegularExpression regex1("<pd mark=\"([^\"]*)\" symbol=\"(\\d+)\" type=\"(\\d+)\" status=\"(\\d+)\" id=\"(\\d+)\" name=\"([^\"]*)\" number=\"(\\d+)\" formalization=\"(\\d+)\" level=\"(\\d+)\"/>");

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatch match = regex1.match(line);

        if (match.hasMatch()) {
            QString symbol = match.captured(2);
            int level = match.captured(9).toInt();
            int number = match.captured(7).toInt();
            QString name = match.captured(6);
            int status = match.captured(4).toInt();
            int formalization = match.captured(8).toInt();

            QChar symbolChar(symbol.toInt());

            QString code = symbolChar.toLower() + QString::number(level) + "." + QString::number(number);

            QString statusStr = (status == 0) ? "Э" : "П";

            QString formalizationStr;
            switch (formalization) {
            case 0:
                formalizationStr = "Ан.";
                break;
            case 1:
                formalizationStr = "Э";
                break;
            case 2:
                formalizationStr = "Ал.";
                break;
            case 3:
                formalizationStr = "С";
                break;
            }

            parsedDataB.push_back({code, name, statusStr, formalizationStr});
        }
    }

    file.seek(0);
    QTextStream in2(&file);

    QRegularExpression regex2("<pd mark=\"([^\"]*)\" symbol=\"(\\d+)\" type=\"(\\d+)\" status=\"(\\d+)\" id=\"(\\d+)\" name=\"([^\"]*)\" number=\"(\\d+)\" formalization=\"(\\d+)\" level=\"(\\d+)\">");

    while (!in2.atEnd()) {
        QString line = in2.readLine();
        QRegularExpressionMatch match = regex2.match(line);

        if (match.hasMatch()) {
            QString symbol = match.captured(2);
            int level = match.captured(9).toInt();
            int number = match.captured(7).toInt();
            QString name = match.captured(6);
            int status = match.captured(4).toInt();
            int formalization = match.captured(8).toInt();

            QChar symbolChar(symbol.toInt());

            QString code = symbolChar.toLower() + QString::number(level) + "." + QString::number(number);

            QString statusStr = (status == 0) ? "Э" : "П";

            QString formalizationStr;
            switch (formalization) {
            case 0:
                formalizationStr = "Ан.";
                break;
            case 1:
                formalizationStr = "Э";
                break;
            case 2:
                formalizationStr = "Ал.";
                break;
            case 3:
                formalizationStr = "С";
                break;
            }

            parsedDataB.push_back({code, name, statusStr, formalizationStr});
        }
    }

    file.close();
}

void GetModel::GetModelD()
{
    if (selectedFile.isEmpty()) {
        return;
    }

    QFile file(selectedFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QRegularExpression aeRegex(R"(<AElement e2=\"(\d+)\" type=\"4\" id=\"0\" char=\"(\d+)\" name=\"\" power=\"1\" e1=\"(\d+)\" e3=\"0\"/>)");
    QRegularExpression pdRegex1(R"(<pd mark=\"([^\"]*)\" symbol=\"(\d+)\" type=\"\d+\" status=\"\d+\" id=\"(\d+)\" name=\"([^\"]*)\" number=\"(\d+)\" formalization=\"(\d+)\" level=\"(\d+)\"/>)");
    QRegularExpression paramRegex(R"(<param group=\"\d+\" o=\"\d+\" id=\"(\d+)\" number=\"\d+\" name=\"([^\"]+)\" codingType=\"\d+\" sign=\"([^\"]+)\"/>)");

    QHash<QString, QList<QString>> e1ToE2Map;
    QHash<QString, QHash<QString, QString>> e1ToE2CharMap;
    QHash<QString, int> e1PositionMap;
    QHash<QString, QPair<QString, QString>> e2ParamMap;
    QHash<QString, QString> e1FormalizationMap;
    QHash<QString, int> e2Position63Map;
    QHash<QString, QPair<QString, QString>> e2Param63Map;

    QRegularExpressionMatchIterator aeIterator = aeRegex.globalMatch(content);
    int position = 0;
    while (aeIterator.hasNext()) {
        QRegularExpressionMatch aeMatch = aeIterator.next();
        QString e1 = aeMatch.captured(3);
        QString e2 = aeMatch.captured(1);
        QString charValue = aeMatch.captured(2);

        if (!e1PositionMap.contains(e1)) {
            e1PositionMap[e1] = position;
        }

        if (charValue == "42" || charValue == "43" || charValue == "46") {
            e1ToE2Map[e1].append(e2);
            e1ToE2CharMap[e1][e2] = charValue;
        }
        else if (charValue == "63") {
            e2Position63Map[e2] = position;
        }
        position += 1;
    }

    QRegularExpressionMatchIterator paramIterator = paramRegex.globalMatch(content);
    while (paramIterator.hasNext()) {
        QRegularExpressionMatch paramMatch = paramIterator.next();
        QString paramId = paramMatch.captured(1);
        QString paramName = paramMatch.captured(2);
        QString paramSign = paramMatch.captured(3);

        e2ParamMap[paramId] = qMakePair(paramName, paramSign);

        if (e2Position63Map.contains(paramId)) {
            e2Param63Map[paramId] = qMakePair(paramName, paramSign);
        }
    }

    QRegularExpressionMatchIterator pdIterator = pdRegex1.globalMatch(content);
    while (pdIterator.hasNext()) {
        QRegularExpressionMatch pdMatch = pdIterator.next();
        QString pdId = pdMatch.captured(3);

        e1FormalizationMap[pdId] = pdMatch.captured(6);
    }


    for (const QString &e1 : e1ToE2Map.keys()) {
        QList<QString> uniqueE2 = e1ToE2Map[e1];
        uniqueE2.removeDuplicates();

        QString pdCode, pdMark, name, formalization;
        QRegularExpressionMatchIterator pdMatchIterator = pdRegex1.globalMatch(content);
        while (pdMatchIterator.hasNext()) {
            QRegularExpressionMatch pdMatch = pdMatchIterator.next();
            if (pdMatch.captured(3) == e1) {
                pdMark = pdMatch.captured(1);
                QString symbol = pdMatch.captured(2);
                name = pdMatch.captured(4);
                formalization = pdMatch.captured(6);

                QChar symbolChar(symbol.toInt());
                pdCode = QString("%1%2.%3").arg(symbolChar).arg(pdMatch.captured(7)).arg(pdMatch.captured(5));
            }
        }

        QString formattedFormalization;
        if (formalization == "0") formattedFormalization = "ан";
        else if (formalization == "1") formattedFormalization = "эм";
        else if (formalization == "2") formattedFormalization = "ал";
        else if (formalization == "3") formattedFormalization = "ст";

        QString functionColumn = "", argumentsColumn = "";
        for (const QString &e2 : uniqueE2) {
            QString charValue = e1ToE2CharMap[e1].value(e2, "Не найден");
            QString paramName = e2ParamMap.contains(e2) ? e2ParamMap[e2].first : "Не найден";
            QString paramSign = e2ParamMap.contains(e2) ? e2ParamMap[e2].second : "Не найден";

            if (charValue == "42") {
                functionColumn = paramName + ", " + paramSign;
            }
            else if (charValue == "43" || charValue == "46") {
                QString argument = paramName + ", " + paramSign;

                if (charValue == "46") {
                    argument = "-/" + argument;
                } else {
                    argument = "-" + argument;
                }
                argumentsColumn += argument;
            }
        }

        for (const QString &e2 : e2Position63Map.keys()) {
            if (e1PositionMap[e1] > e2Position63Map[e2]) {
                QString paramName = e2Param63Map.contains(e2) ? e2Param63Map[e2].first : "Не найден";
                QString paramSign = e2Param63Map.contains(e2) ? e2Param63Map[e2].second : "Не найден";
                argumentsColumn += "-/" + paramName + ", " + paramSign;
            }
        }

        QString escapedPdMark = pdMark;
        escapedPdMark.replace("\\", "\\\\");
        escapedPdMark.replace("&", "\\&");
        escapedPdMark.replace("%", "\\%");
        escapedPdMark.replace("$", "\\$");
        escapedPdMark.replace("_", "\\_");
        escapedPdMark.replace("{", "\\{");
        escapedPdMark.replace("}", "\\}");
        escapedPdMark.replace("#", "\\#");
        escapedPdMark.replace("^", "\\^");
        escapedPdMark.replace("~", "\\~");

        parsedDataD.append(pdCode + " & " + name + " & " + formattedFormalization + " & "
                         + functionColumn + " & " + argumentsColumn + " & "
                         + "\\texttt{" + escapedPdMark + "} \\\\\n");
    }
}

void GetModel::GetModelD1()
{
    if (selectedFile.isEmpty()) {
        return;
    }

    QFile file(selectedFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);

    QRegularExpression regex(R"(<param group=\"(\d+)\" o=\"(\d+)\" id=\"\d+\" number=\"(\d+)\" name=\"([^\"]+)\" codingType=\"\d+\" sign=\"([^\"]+)\"/>)");

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatch match = regex.match(line);

        if (match.hasMatch()) {
            QString group = match.captured(1);
            QString number = match.captured(3);
            QString name = match.captured(4);
            QString sign = match.captured(5);
            QString o = match.captured(2);

            if (o == "2") {
                o = "Узел";
            } else if (o == "3") {
                o = "Деталь";
            } else if (o == "4") {
                o = "Сборочная единица";
            }

            QString code = "A" + group + "." + number;

            parsedDataD1.push_back({code, name, sign, o});
        }
    }

    file.close();
}

void GetModel::GetModelD2()
{
    if (selectedFile.isEmpty()) {
        return;
    }

    QFile file(selectedFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    std::vector<std::pair<int, QString>> char63Params;  // <позиция в файле, код параметра>

    // Регулярные выражения
    QRegularExpression aElementRegex(R"(<AElement e2=\"(\d+)\" type=\"4\" id=\"\d+\" char=\"(42|43|46|63)\" name=\"[^\"]*\" power=\"\d+\" e1=\"(\d+)\" e3=\"\d+\"/>)");
    QRegularExpression pdRegex1(R"(<pd mark=\"[^\"]*\" symbol=\"(\d+)\" type=\"\d+\" status=\"\d+\" id=\"(\d+)\" name=\"[^\"]*\" number=\"(\d+)\" formalization=\"\d+\" level=\"(\d+)\"/>)");
    QRegularExpression pdRegex2(R"(<pd mark=\"[^\"]*\" symbol=\"(\d+)\" type=\"\d+\" status=\"\d+\" id=\"(\d+)\" name=\"[^\"]*\" number=\"(\d+)\" formalization=\"\d+\" level=\"(\d+)\">)");
    QRegularExpression paramRegex(R"(<param group=\"(\d+)\" o=\"(\d+)\" id=\"(\d+)\" number=\"(\d+)\" name=\"([^\"]+)\" codingType=\"\d+\" sign=\"([^\"]+)\"/>)");

    // Сначала находим все <AElement ... /> и запоминаем char=63
    QRegularExpressionMatchIterator aElementIterator = aElementRegex.globalMatch(content);
    int index = 0;

    while (aElementIterator.hasNext()) {
        QRegularExpressionMatch aElementMatch = aElementIterator.next();
        QString e2 = aElementMatch.captured(1);
        QString charValue = aElementMatch.captured(2);
        QString e1 = aElementMatch.captured(3);

        if (charValue == "63") {
            // Ищем код параметра по e2
            QString paramCode;
            QRegularExpressionMatchIterator paramIterator = paramRegex.globalMatch(content);
            while (paramIterator.hasNext()) {
                QRegularExpressionMatch paramMatch = paramIterator.next();
                if (paramMatch.captured(3) == e2) {
                    QString group = paramMatch.captured(1);
                    QString number = paramMatch.captured(4);
                    paramCode = QString("A%1.%2").arg(group).arg(number);
                    break;
                }
            }

            if (!paramCode.isEmpty()) {
                char63Params.push_back({index, paramCode});
            }
        }

        index++;
    }

    // Теперь ищем <AElement ... /> с char=42, 43, 46 и обрабатываем
    aElementIterator = aElementRegex.globalMatch(content);
    index = 0;

    while (aElementIterator.hasNext()) {
        QRegularExpressionMatch aElementMatch = aElementIterator.next();
        QString e2 = aElementMatch.captured(1);
        QString charValue = aElementMatch.captured(2);
        QString e1 = aElementMatch.captured(3);

        if (charValue == "63") {
            index++;
            continue;  // Пропускаем, мы их уже обработали
        }

        // Определяем роль параметра
        QString role;
        if (charValue == "42") role = "Функция";
        else if (charValue == "43") role = "Аргумент";
        else if (charValue == "46") role = "Аргумент по умолчанию";

        // Ищем строку pd по e1
        QString pdCode;
        QRegularExpressionMatchIterator pdIterator1 = pdRegex1.globalMatch(content);
        while (pdIterator1.hasNext()) {
            QRegularExpressionMatch pdMatch = pdIterator1.next();
            if (pdMatch.captured(2) == e1) {
                QChar symbolChar(pdMatch.captured(1).toInt());
                QString level = pdMatch.captured(4);
                QString number = pdMatch.captured(3);
                pdCode = QString("%1%2.%3").arg(symbolChar).arg(level).arg(number);
                break;
            }
        }

        if (pdCode.isEmpty()) {
            QRegularExpressionMatchIterator pdIterator2 = pdRegex2.globalMatch(content);
            while (pdIterator2.hasNext()) {
                QRegularExpressionMatch pdMatch = pdIterator2.next();
                if (pdMatch.captured(2) == e1) {
                    QChar symbolChar(pdMatch.captured(1).toInt());
                    QString level = pdMatch.captured(4);
                    QString number = pdMatch.captured(3);
                    pdCode = QString("%1%2.%3").arg(symbolChar).arg(level).arg(number);
                    break;
                }
            }
        }

        // Ищем строку param по e2
        QString paramCode;
        QRegularExpressionMatchIterator paramIterator = paramRegex.globalMatch(content);
        while (paramIterator.hasNext()) {
            QRegularExpressionMatch paramMatch = paramIterator.next();
            if (paramMatch.captured(3) == e2) {
                QString group = paramMatch.captured(1);
                QString number = paramMatch.captured(4);
                paramCode = QString("A%1.%2").arg(group).arg(number);
                break;
            }
        }

        // Добавляем основную строку
        if (!pdCode.isEmpty() && !paramCode.isEmpty()) {
            parsedDataD2.push_back({pdCode, paramCode, role});

            // **Добавляем доп. строку только если это Функция и ниже char=63**
            if (role == "Функция") {
                for (const auto &char63Entry : char63Params) {
                    if (char63Entry.first < index) {  // Если char=63 выше
                        parsedDataD2.push_back({pdCode, char63Entry.second, "Аргумент по умолчанию"});
                    }
                }
            }
        }

        index++;
    }
}



