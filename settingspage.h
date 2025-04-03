#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>

class SettingsPage : public QWidget {
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

private slots:
    void goToNextPage();

private:
    QComboBox *fontComboBox;
    QComboBox *sizeComboBox;
    QPushButton *nextButton;
};

#endif
