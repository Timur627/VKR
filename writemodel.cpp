#include "writemodel.h"
#include "globals.h"

WriteModel::WriteModel() {}

void WriteModel::writeModelA(QTextStream &out)
{
    out << "\\begin{center}\n";
    out << "\\textbf{Форма A: Кодирование последовательностей}\n";
    out << "\\end{center}\n";

    out << "\\begin{longtable}{|p{3cm}|p{3cm}|p{3cm}|p{4cm}|}\n";
    out << "\\hline\n";
    out << "Код ПД1 & Код ПД2 & Код ПД3 & Вид компоновки \\\\\n";
    out << "\\hline\n";
    out << "\\endfirsthead\n";
    out << "\\hline\n";
    out << "Код ПД1 & Код ПД2 & Код ПД3 & Вид компоновки \\\\\n";
    out << "\\hline\n";
    out << "\\endhead\n";

    out << "\\renewcommand{\\arraystretch}{1.5}\n";

    for (const auto &entry : parsedDataA) {
        out << entry[0] << " & " << entry[1] << " & " << entry[2] << " & " << entry[3] << " \\\\\n";
        out << "\\hline\n";
    }

    out << "\\end{longtable}\n";
}

void WriteModel::writeModelB(QTextStream &out)
{
    out << "\\begin{center}\n";
    out << "\\textbf{Форма В: Описание действий предметной задачи}\n";
    out << "\\end{center}\n";

    out << "\\begin{longtable}{|p{1cm}|p{6cm}|p{2cm}|p{2cm}|}\n";
    out << "\\hline\n";
    out << "Код & Наименование & Статус & Степень Формализации \\\\\n";
    out << "\\hline\n";
    out << "\\endfirsthead\n";
    out << "\\hline\n";
    out << "Код & Наименование & Статус & Степень Формализации \\\\\n";
    out << "\\hline\n";
    out << "\\endhead\n";

    out << "\\renewcommand{\\arraystretch}{1.5}\n";

    for (const auto &entry : parsedDataB) {
        out << entry[0] << " & " << entry[1] << " & " << entry[2] << " & " << entry[3] << " \\\\\n";
        out << "\\hline\n";
    }

    out << "\\end{longtable}\n";
}

void WriteModel::writeModelD(QTextStream &out)
{
    out << "\\begin{center}\n";
    out << "\\textbf{Форма D: Функции и параметры}\n";
    out << "\\end{center}\n";

    out << "\\begin{longtable}{|p{1.5cm}|p{3cm}|p{1.5cm}|p{3.5cm}|p{3.5cm}|p{3cm}|}\n";
    out << "\\hline\n";
    out << "Код ПД & Наименование & Форм. & Функция & Аргументы & Примечание \\\\\n";
    out << "\\hline\n";
    out << "\\endfirsthead\n";
    out << "\\hline\n";
    out << "Код ПД & Наименование & Форм. & Функция & Аргументы & Примечание \\\\\n";
    out << "\\hline\n";
    out << "\\endhead\n";

    // Выводим отсортированные строки
    for (const QString &latexRow : parsedDataD) {
        out << latexRow;
        out << "\\hline\n";
    }

    out << "\\end{longtable}\n";
}

void WriteModel::writeModelD1(QTextStream &out)
{
    out << "\\begin{center}\n";
    out << "\\textbf{Форма D1: Описание параметров}\n";
    out << "\\end{center}\n";

    out << "\\begin{longtable}{|p{1cm}|p{6cm}|p{2.5cm}|p{2cm}|}\n";
    out << "\\hline\n";
    out << "Код & Наименование & Обозначение & Объект \\\\\n";
    out << "\\hline\n";
    out << "\\endfirsthead\n";
    out << "\\hline\n";
    out << "Код & Наименование & Обозначение & Объект \\\\\n";
    out << "\\hline\n";
    out << "\\endhead\n";

    out << "\\renewcommand{\\arraystretch}{1.5}\n";

    for (const auto &entry : parsedDataD1) {
        out << entry[0] << " & " << entry[1] << " & " << entry[2] << " & " << entry[3] << " \\\\\n";
        out << "\\hline\n";
    }

    out << "\\end{longtable}\n";
}

void WriteModel::writeModelD2(QTextStream &out)
{
    out << "\\begin{center}\n";
    out << "\\textbf{Форма D2: Функции и параметры}\n";
    out << "\\end{center}\n";

    out << "\\begin{longtable}{|p{3cm}|p{3cm}|p{4cm}|}\n";
    out << "\\hline\n";
    out << "Код ПД & Код параметра & Роль параметра \\\\\n";
    out << "\\hline\n";
    out << "\\endfirsthead\n";
    out << "\\hline\n";
    out << "Код ПД & Код параметра & Роль параметра \\\\\n";
    out << "\\hline\n";
    out << "\\endhead\n";

    for (const auto &entry : parsedDataD2) {
        out << entry[0] << " & " << entry[1] << " & " << entry[2] << " \\\\\n";
        out << "\\hline\n";
    }

    out << "\\end{longtable}\n";
}
