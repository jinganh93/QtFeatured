#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化按鈕
    wateringBtn = new QPushButton(QStringLiteral("澆水"), this); // 澆水
    illumBtn = new QPushButton(QStringLiteral("光照"), this);   // 光照
    illSetTimeBtn = new QPushButton(QStringLiteral("時間設定"), this); // 時間設定
    wtgSetTimeBtn = new QPushButton(QStringLiteral("時間設定"), this); // 時間設定

    // 初始化標籤
    illumBtnLbl = new QLabel(QStringLiteral("光照："), this);
    wtgingBtnLbl = new QLabel(QStringLiteral("澆水："), this);

    // 初始化佈局
    hBtnAndLbl1 = new QHBoxLayout(); // 澆水區域
    hBtnAndLbl2 = new QHBoxLayout(); // 光照區域
    mainLayout = new QVBoxLayout(this); // 主佈局

    // 初始化自動模式選擇框
    autoModeCheckBox1 = new QCheckBox(QStringLiteral("自動模式"), this);
    autoModeCheckBox2 = new QCheckBox(QStringLiteral("自動模式"), this);

    // 信號
    connect(autoModeCheckBox1, &QCheckBox::toggled, this, &Widget::CheckMode);
    connect(autoModeCheckBox2, &QCheckBox::toggled, this, &Widget::CheckMode);
    connect(illSetTimeBtn, &QPushButton::clicked, this, [this]() { openTimeDialog("光照"); });
    connect(wtgSetTimeBtn, &QPushButton::clicked, this, [this]() { openTimeDialog("澆水"); });

    // 配置佈局
    hBtnAndLbl1->addWidget(wtgingBtnLbl);
    hBtnAndLbl1->addWidget(autoModeCheckBox1);
    hBtnAndLbl1->addWidget(wateringBtn);
    hBtnAndLbl1->addWidget(wtgSetTimeBtn);


    hBtnAndLbl2->addWidget(illumBtnLbl);
    hBtnAndLbl2->addWidget(autoModeCheckBox2);
    hBtnAndLbl2->addWidget(illumBtn);
    hBtnAndLbl2->addWidget(illSetTimeBtn);

    // 添加到主佈局
    mainLayout->addLayout(hBtnAndLbl1);
    mainLayout->addLayout(hBtnAndLbl2);

    // 設置主佈局
    setLayout(mainLayout);
}

// 模式檢測
void Widget::CheckMode(){
    if(autoModeCheckBox1->isChecked()){
        wateringBtn->setEnabled(false);
        wtgSetTimeBtn->setEnabled(true);

    }else {
        wateringBtn->setEnabled(true);
        wtgSetTimeBtn->setEnabled(false);
    }

    if(autoModeCheckBox2->isChecked()){
        illumBtn->setEnabled(false);
        illSetTimeBtn->setEnabled(true);
    }else {
        illumBtn->setEnabled(true);
        illSetTimeBtn->setEnabled(false);
    }
}

// 選擇時間
void Widget::openTimeDialog(const QString &timeType) {
    QDialog dialog(this);
    dialog.setWindowTitle(QStringLiteral("選擇時間"));

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    // 創建分頁控件
    QTabWidget *tabWidget = new QTabWidget(&dialog);

    // 分頁1：時間選擇 ---------------------------
    QWidget *timeTab = new QWidget();
    QVBoxLayout *timeTabLayout = new QVBoxLayout(timeTab);

    QTimeEdit *timeEdit = new QTimeEdit(QTime::currentTime(), timeTab);
    timeEdit->setDisplayFormat("HH:mm"); // 24H制
    timeTabLayout->addWidget(new QLabel(QStringLiteral("選擇時間："), timeTab));
    timeTabLayout->addWidget(timeEdit);

    // 確定和取消按鈕
    QHBoxLayout *tab1BtnLayout = new QHBoxLayout();
    QPushButton *tab1okBtn = new QPushButton(QStringLiteral("確定"), &dialog);
    QPushButton *tab1cancelBtn = new QPushButton(QStringLiteral("取消"), &dialog);
    tab1BtnLayout->addWidget(tab1okBtn);
    tab1BtnLayout->addWidget(tab1cancelBtn);
    timeTabLayout->addLayout(tab1BtnLayout);

    tabWidget->addTab(timeTab, QStringLiteral("時間選擇"));

    // 信號
    connect(tab1okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(tab1cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    // 分頁2：重複方式 ---------------------------
    QWidget *trpTab = new QWidget();
    QVBoxLayout *trpTabLayout = new QVBoxLayout(trpTab);

    QComboBox *trpComboBox = new QComboBox;
    trpTabLayout->addWidget(new QLabel(QStringLiteral("選擇重複方式："), trpTab));

    trpComboBox->addItem(QStringLiteral("每日"));
    trpComboBox->addItem(QStringLiteral("間隔重複"));

    trpTabLayout->addWidget(trpComboBox);

    // 確定和取消按鈕
    QHBoxLayout *tab2BtnLayout = new QHBoxLayout();
    QPushButton *tab2okBtn = new QPushButton(QStringLiteral("確定"), &dialog);
    QPushButton *tab2cancelBtn = new QPushButton(QStringLiteral("取消"), &dialog);
    tab2BtnLayout->addWidget(tab2okBtn);
    tab2BtnLayout->addWidget(tab2cancelBtn);
    trpTabLayout->addLayout(tab2BtnLayout);

    tabWidget->addTab(trpTab, QStringLiteral("重複方式"));

    // 添加分頁控件到主佈局
    layout->addWidget(tabWidget);

    if (dialog.exec() == QDialog::Accepted) {
        QTime selectedTime = timeEdit->time();
        qDebug() << timeType << " Selected Time:" << selectedTime.toString("HH:mm");
        if (timeType == "光照") {
        } else if (timeType == "澆水") {
        }
    }
}

Widget::~Widget() {}
