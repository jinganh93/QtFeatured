#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化按鈕
    wateringBtn = new QPushButton(QStringLiteral("即時澆水"), this); // 澆水
    wtgSetTimeBtn = new QPushButton(QStringLiteral("時間設定"), this); // 時間設定

    // 初始化標籤
    wtgingBtnLbl = new QLabel(QStringLiteral("澆水："), this);

    // 初始化自動模式選擇框
    autoModeCheckBox1 = new QCheckBox(QStringLiteral("自動模式"), this);
    wtgSetTimeBtn->setEnabled(false);

    // 初始化佈局
    controlGp = new QGroupBox(QStringLiteral("控制區"), this);
    ctrlGpLayout = new QVBoxLayout(controlGp);
    vBtnAndLbl1 = new QHBoxLayout(); // 澆水區域

    // 配置佈局
    vBtnAndLbl1->addWidget(wtgingBtnLbl);
    vBtnAndLbl1->addWidget(autoModeCheckBox1);
    vBtnAndLbl1->addWidget(wateringBtn);
    vBtnAndLbl1->addWidget(wtgSetTimeBtn);

    // 添加到控制區域佈局
    ctrlGpLayout->addLayout(vBtnAndLbl1);

    // 添加到主佈局
    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(controlGp);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // 設置信號與槽
    connect(autoModeCheckBox1, &QCheckBox::toggled, this, &Widget::CheckMode);
    connect(wtgSetTimeBtn, &QCheckBox::clicked, this, &Widget::openTimeDialog);
    connect(wateringBtn, &QCheckBox::clicked, this, &Widget::realTimeIrrigation);

    //connect(wtgSetTimeBtn, &QPushButton::clicked, this, [this]() { openTimeDialog("澆水"); });

    // 主佈局
    setLayout(mainLayout);
}

// 模式檢測
void Widget::CheckMode() {
    if (autoModeCheckBox1->isChecked()) {
        wateringBtn->setEnabled(false);
        wtgSetTimeBtn->setEnabled(true);
    } else {
        wateringBtn->setEnabled(true);
        wtgSetTimeBtn->setEnabled(false);
    }
}

//即時澆水
void Widget::realTimeIrrigation() {
    QJsonObject json;

    // 獲取當前時間
    QDateTime currentDateTime = QDateTime::currentDateTime();
    _wtgDateTime = currentDateTime;

    /*QString timeString = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    // 插入到 JSON
    json["currentTime"] = timeString;

    // 打印 JSON 数据
    qDebug() << QJsonDocument(json).toJson(QJsonDocument::Indented);*/

    // 打印当前日期和时间
    qDebug() << "Current Date and Time:" << currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
}


// 選擇時間
void Widget::openTimeDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle(QStringLiteral("選擇時間"));

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // 澆水欄 -------------------------------------------
    QHBoxLayout *dwtgLayout = new QHBoxLayout();
    QLabel *dwtgLabel = new QLabel(QStringLiteral("澆水："));
    dwtgLabel->setAlignment(Qt::AlignLeft); // 文字居中
    dwtgLabel->setStyleSheet(
        "QLabel {"
        "   letter-spacing: 10px;" // 文字間隔
        "}"
        );
    dwtgLayout->addWidget(dwtgLabel);

    // 澆水時間選擇器
    QTimeEdit *dwtgTimeEdit = new QTimeEdit(QTime::currentTime());
    dwtgTimeEdit->setDisplayFormat("HH:mm");
    dwtgLayout->addWidget(dwtgTimeEdit);

    // 文字輸入框:澆水時間間隔
    QLineEdit *dwtgLineEdit = new QLineEdit();
    dwtgLineEdit->setPlaceholderText(QStringLiteral("輸入澆水間格時間"));
    dwtgLayout->addWidget(dwtgLineEdit);

    layout->addLayout(dwtgLayout);

    //光照欄 -----------------------------------
    QHBoxLayout *dillLayout = new QHBoxLayout();
    QLabel *dillLabel = new QLabel(QStringLiteral("光照開始時間選擇："));
    dillLabel->setAlignment(Qt::AlignLeft); // 文字居中
    dillLabel->setStyleSheet(
        "QLabel {"
        "   letter-spacing: 5px;" // 文字間隔
        "}"
        );
    dillLayout->addWidget(dillLabel);

    // 光照時間選擇器(起始時間)
    QTimeEdit *dillTimeEdit = new QTimeEdit(QTime::currentTime());
    dillTimeEdit->setDisplayFormat("HH:mm");
    dillLayout->addWidget(dillTimeEdit);

    layout->addLayout(dillLayout);

    //狀態欄(光照持續時間)
    QHBoxLayout *dStateLayout = new QHBoxLayout();
    QLabel *dStateLabel = new QLabel(QStringLiteral("狀態："));
    dStateLabel->setAlignment(Qt::AlignLeft); // 文字居中
    dStateLabel->setStyleSheet(
        "QLabel {"
        "   letter-spacing: 10px;" // 文字間隔
        "}"
        );
    dStateLayout->addWidget(dStateLabel);

    QLabel *dillState = new QLabel(QStringLiteral("光照持續時間"));
    dillState->setAlignment(Qt::AlignHCenter); // 文字居中
    dStateLayout->addWidget(dillState);

    layout->addLayout(dStateLayout);

    // 送出按鈕
    QHBoxLayout *dBtnLayout = new QHBoxLayout();
    QPushButton *pushData = new QPushButton(QStringLiteral("送出"), &dialog);
    dBtnLayout->addWidget(pushData);
    layout->addLayout(dBtnLayout);

    // 信號
    connect(pushData, &QCheckBox::clicked, this, &Widget::updateData);

    if (dialog.exec() == QDialog::Accepted) {
        //QTime selectedTime = timeEdit->time();
        QTime wtgTime = dwtgTimeEdit->time();
        QTime illTime = dillTimeEdit->time();
        QString inputText = dwtgLineEdit->text();

        //取得當前日期
        QDate currentDate = QDate::currentDate();
        //日期時間合併
        QDateTime wtgDateTime(currentDate, wtgTime);

        //qDebug() << timeType << "Selected Time:" << selectedTime.toString("HH:mm");
        //qDebug() << "DWTG Time:" << dwtgTime.toString("HH:mm");
        //qDebug() << "Input Text:" << inputText;
    }
}

void Widget::updateData(){

}

QJsonObject Widget::getCurrentData() {
    QJsonObject json;

    // 設備 ID（此處假設你有設備 ID 可以設置）
    json["id"] = "設備ID"; // 請根據實際情況設置設備 ID

    // 設定命令
    json["command"] = "設定命令"; // 這裡可以設置實際的指令，例如"光照" 或 "澆水"

    // 假設已經保存了選擇的澆水時間（假設選擇時間為 selectedWateringTime）
    QTime selectedWateringTime = QTime::currentTime(); // 替換為實際選擇的時間
    json["wateringTime"] = selectedWateringTime.toString("HH:mm"); // 澆水時間

    // 假設已經保存了光照開始時間（假設選擇時間為 selectedLightStartTime）
    QTime selectedLightStartTime = QTime::currentTime(); // 替換為實際選擇的時間
    json["lightStart"] = selectedLightStartTime.toString("HH:mm"); // 光照開始時間

    // 假設已經保存了光照持續時間（假設為 60 分鐘）
    int lightDuration = 720; // 替換為實際選擇的持續時間
    json["duration"] = lightDuration; // 光照持續時間

    return json;
}

Widget::~Widget() {}
