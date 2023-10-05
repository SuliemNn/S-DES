#include "figureout.h"
#include "ui_figureout.h"
#include "s_des.h"

figureout::figureout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::figureout)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &figureout::getkey);
}

figureout::~figureout()
{
    delete ui;
}
void figureout::getkey()
{
    QString plaintextStr = ui->lineEdit->text();
    QString ciphertextstr = ui->lineEdit_2->text();

    // 将QString转换为std::string
    std::string plaintext = plaintextStr.toStdString();
    std::string ciphertext = ciphertextstr.toStdString();

    // 将std::string转换为bitset<8>和bitset<10>
    std::bitset<8> plaintextBits(plaintext);
    std::bitset<8> ciphertextBits(ciphertext);

    bitset<10> result[10];
    int count = 0;
    S_Des::figureOut(plaintextBits, ciphertextBits,10,result,&count);

    for(int i=0;i<count;i++){
        // 显示密钥
        ui->textBrowser->append(QString::fromStdString(result[i].to_string()));
    }

}
