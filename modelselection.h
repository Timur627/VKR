#ifndef MODELSELECTION_H
#define MODELSELECTION_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>

class ModelSelection : public QWidget {
    Q_OBJECT

public:
    explicit ModelSelection(QWidget *parent = nullptr);

private slots:
    void updateNextButtonState();
    void goToNextPage();

private:
    QPushButton *nextButton;
    QList<QCheckBox*> checkboxes;
};

#endif
