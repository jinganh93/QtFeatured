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
#include <QJsonObject>
#include <QJsonDocument>
#include <QLineEdit>
#include <QMessageBox>


class Widget : public QWidget
{
    Q_OBJECT

public:
    QLabel          *wtgingBtnLbl; // 澆水標籤
    QLabel          *illumBtnLbl; // 光照標籤

    QCheckBox       *autoModeCheckBox1; //澆水模式

    QPushButton     *wateringBtn; // 澆水
    QPushButton     *wtgSetTimeBtn; // 時間設定

    QHBoxLayout     *vBtnAndLbl1; // 澆水
    QHBoxLayout     *mainLayout; //

    QGroupBox       *controlGp; //
    QVBoxLayout     *ctrlGpLayout; //

    //全域變數
    QDateTime       _wtgDateTime; // 澆水時間
    QDateTime       _illContTime; // 光照持續時間
    QDateTime       _wtgInrTime; // 澆水間隔時間



    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void CheckMode();
    void updateData(); // 更新
    void realTimeIrrigation(); // 即時澆水
    void openTimeDialog();
    QJsonObject getCurrentData();


};
#endif // WIDGET_H
