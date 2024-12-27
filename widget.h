#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QTimeEdit>
#include <QDialog>
#include <QTabWidget>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    QLabel          *wtgingBtnLbl;
    QLabel          *illumBtnLbl;

    QCheckBox       *autoModeCheckBox1;
    QCheckBox       *autoModeCheckBox2;

    QPushButton     *wateringBtn;//澆水
    QPushButton     *illumBtn;//光照
    QPushButton     *wtgSetTimeBtn;//時間設定
    QPushButton     *illSetTimeBtn;//時間設定

    QHBoxLayout     *hBtnAndLbl1;//澆水
    QHBoxLayout     *hBtnAndLbl2;//光照
    QVBoxLayout     *mainLayout;



    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void CheckMode();
    void openTimeDialog(const QString &Type);


};
#endif // WIDGET_H
