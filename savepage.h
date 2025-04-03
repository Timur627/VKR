#ifndef SAVEPAGE_H
#define SAVEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>

class SavePage : public QWidget {
    Q_OBJECT

public:
    explicit SavePage(QWidget *parent = nullptr);
private slots:
    void selectFile();
    void enableFinishButton();
    void finish();

private:
    QPushButton *finishButton;
    QString filePath;
    QLabel *titleLabel;
};

#endif
