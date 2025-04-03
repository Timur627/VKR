#include "ModelSelection.h"
#include "SettingsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include "globals.h"
#include "getmodel.h"

ModelSelection::ModelSelection(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Выберите начальные модели:", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QGroupBox *modelGroup = new QGroupBox(this);
    QVBoxLayout *modelLayout = new QVBoxLayout(modelGroup);

    QStringList modelNames = {"A", "B", "D", "D1", "D2"};
    for (const QString &name : modelNames) {
        QCheckBox *checkBox = new QCheckBox(name, this);
        modelLayout->addWidget(checkBox);
        checkboxes.append(checkBox);
        connect(checkBox, &QCheckBox::stateChanged, this, &ModelSelection::updateNextButtonState);
    }

    modelGroup->setLayout(modelLayout);
    layout->addWidget(modelGroup);

    nextButton = new QPushButton("Далее", this);
    nextButton->setEnabled(false);
    layout->addWidget(nextButton);
    connect(nextButton, &QPushButton::clicked, this, &ModelSelection::goToNextPage);

    setLayout(layout);
}

void ModelSelection::updateNextButtonState() {
    selectedModels.clear();
    for (QCheckBox *checkBox : checkboxes) {
        if (checkBox->isChecked()) {
            selectedModels.append(checkBox->text());
        }
    }
    nextButton->setEnabled(!selectedModels.isEmpty());
}

void ModelSelection::goToNextPage() {
    GetModel GetModels;
    if (selectedModels.contains("A")) {
        GetModels.GetModelA();
    }
    if (selectedModels.contains("B")) {
        GetModels.GetModelB();
    }
    if (selectedModels.contains("D")) {
        GetModels.GetModelD();
    }
    if (selectedModels.contains("D1")) {
        GetModels.GetModelD1();
    }
    if (selectedModels.contains("D2")) {
        GetModels.GetModelD2();
    }
    SettingsPage *settingsPage = new SettingsPage();
    settingsPage->show();
    this->close();
}
