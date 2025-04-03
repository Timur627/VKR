#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class FileSelector : public QWidget {
    Q_OBJECT

public:
    explicit FileSelector(QWidget *parent = nullptr);

private slots:
    void selectFile();
    void goToNextPage();

private:
    QLabel *fileLabel;
    QPushButton *nextButton;
};

#endif
