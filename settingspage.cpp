#include "SettingsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>
#include "SavePage.h"
#include "globals.h"
#include "processingmodels.h"

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Настройки обработки:", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    fontComboBox = new QComboBox(this);
    QStringList fonts = {"Tempora", "PT Serif", "Linux Libertine", "PT Sans", "Open Sans"};
    fontComboBox->addItems(fonts);
    fontComboBox->setCurrentText("Tempora");
    layout->addWidget(fontComboBox);

    sizeComboBox = new QComboBox(this);
    for (int i = 10; i <= 30; ++i) {
        sizeComboBox->addItem(QString::number(i));
    }
    sizeComboBox->setCurrentText("14");
    layout->addWidget(sizeComboBox);

    nextButton = new QPushButton("Далее", this);
    nextButton->setEnabled(true);
    layout->addWidget(nextButton);
    connect(nextButton, &QPushButton::clicked, this, &SettingsPage::goToNextPage);

    setLayout(layout);
}

void SettingsPage::goToNextPage() {
    selectedFont = fontComboBox->currentText();
    selectedSize = sizeComboBox->currentText();

    processingModels processingModel;

    if (selectedModels.contains("A")) {
        processingModel.processingModelA();
    }
    if (selectedModels.contains("B")) {
        processingModel.processingModelB();
    }
    if (selectedModels.contains("D")) {
        processingModel.processingModelD();
    }
    if (selectedModels.contains("D1")) {
        processingModel.processingModelD1();
    }
    if (selectedModels.contains("D2")) {
        processingModel.processingModelD2();
    }
    SavePage *savePage = new SavePage();
    savePage->show();
    this->close();
}
