#include "FileSelector.h"
#include "ModelSelection.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include "globals.h"

FileSelector::FileSelector(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    fileLabel = new QLabel("Выберите файл (.is2)", this);
    fileLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(fileLabel);

    QPushButton *selectFileButton = new QPushButton("Выбрать файл", this);
    layout->addWidget(selectFileButton);
    connect(selectFileButton, &QPushButton::clicked, this, &FileSelector::selectFile);

    nextButton = new QPushButton("Далее", this);
    nextButton->setEnabled(false);
    layout->addWidget(nextButton);
    connect(nextButton, &QPushButton::clicked, this, &FileSelector::goToNextPage);

    setLayout(layout);
}

void FileSelector::selectFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выбор файла", "", "IS2 Files (*.is2)");
    if (!filePath.isEmpty()) {
        selectedFile = filePath;
        fileLabel->setText("Выбран файл: " + filePath);
        nextButton->setEnabled(true);
    }
}

void FileSelector::goToNextPage() {
    ModelSelection *modelSelection = new ModelSelection();
    modelSelection->show();
    this->close();
}
