#include "SavePage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QApplication>
#include "globals.h"
#include "writemodel.h"

SavePage::SavePage(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Выберите место и имя для сохранения файла:", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QPushButton *selectButton = new QPushButton("Выбрать место", this);
    layout->addWidget(selectButton);
    connect(selectButton, &QPushButton::clicked, this, &SavePage::selectFile);

    finishButton = new QPushButton("Завершить", this);
    finishButton->setEnabled(false);
    layout->addWidget(finishButton);
    connect(finishButton, &QPushButton::clicked, this, &SavePage::finish);

    setLayout(layout);
}

void SavePage::selectFile() {
    filePath = QFileDialog::getSaveFileName(this, "Выберите место для сохранения", "", "LaTeX Files (*.tex)");
    if (!filePath.isEmpty()) {
        enableFinishButton();
        titleLabel->setText("Файл будет сохранён в: " + filePath);
    }
}

void SavePage::enableFinishButton() {
    finishButton->setEnabled(!filePath.isEmpty());
}

void SavePage::finish() {
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            WriteModel WriteModels;

            out << "\\documentclass[a4paper]{article}\n";
            out << "\\usepackage[T2A]{fontenc}\n";
            out << "\\usepackage[utf8]{inputenc}\n";
            out << "\\usepackage[english, russian]{babel}\n";
            out << "\\usepackage{geometry}\n";
            out << "\\usepackage{longtable}\n";
            out << "\\geometry{left=20mm, right=15mm}\n";
            out << "\\setlength\\parindent{0pt}\n";

            if (selectedFont == "Tempora") {
                out << "\\renewcommand{\\rmdefault}{Tempora-TLF}\n";
            } else if (selectedFont == "PT Serif") {
                out << "\\renewcommand{\\rmdefault}{PTSerif-TLF}\n";
            } else if (selectedFont == "Linux Libertine") {
                out << "\\renewcommand{\\rmdefault}{LinuxLibertineT-TLF}\n";
            } else if (selectedFont == "PT Sans") {
                out << "\\renewcommand{\\rmdefault}{PTSans-TLF}\n";
            } else if (selectedFont == "Open Sans") {
                out << "\\renewcommand{\\rmdefault}{fos}\n";  // Для Open Sans используется код 'fos'
            }

            out << "\\begin{document}\n";
            out << "\\fontsize{" << selectedSize << "}{" << selectedSize << "}\\selectfont\n";

            if (selectedModels.contains("A")) {
                WriteModels.writeModelA(out);
            }
            if (selectedModels.contains("B")) {
                WriteModels.writeModelB(out);
            }
            if (selectedModels.contains("D")) {
                WriteModels.writeModelD(out);
            }
            if (selectedModels.contains("D1")) {
                WriteModels.writeModelD1(out);
            }
            if (selectedModels.contains("D2")) {
                WriteModels.writeModelD2(out);
            }
            out << "\\end{document}\n";
            file.close();
        }
    }
    QApplication::quit();
}
