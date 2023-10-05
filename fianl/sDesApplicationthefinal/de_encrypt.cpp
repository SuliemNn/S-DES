#include "de_encrypt.h"
#include "ui_de_encrypt.h"
#include "s_des.h"
using namespace std;

de_encrypt::de_encrypt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::de_encrypt)
{
    ui->setupUi(this);
    // 连接按钮点击事件到槽函数
    connect(ui->pushButton, &QPushButton::clicked, this, &de_encrypt::encrypt);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &de_encrypt::decrypt);
}

de_encrypt::~de_encrypt()
{
    delete ui;
}
// 加密槽函数
void de_encrypt::encrypt()
{
    QString plaintextStr = ui->lineEdit->text();
    QString keyStr = ui->lineEdit_2->text();

    // 将QString转换为std::string
    std::string plaintext = plaintextStr.toStdString();
    std::string key = keyStr.toStdString();

    // 将std::string转换为bitset<8>和bitset<10>
    std::bitset<8> plaintextBits(plaintext);
    std::bitset<10> keyBits(key);

    // 执行S-DES加密
    std::bitset<8> ciphertext = S_Des::sDesEncrypt(plaintextBits, keyBits);

    // 显示密文
    ui->lineEdit_3->setText(QString::fromStdString(ciphertext.to_string()));
}

// 解密槽函数
void de_encrypt::decrypt()
{
    QString ciphertextStr = ui->lineEdit_4->text();
    QString keyStr = ui->lineEdit_5->text();

    // 将QString转换为std::string
    std::string ciphertext = ciphertextStr.toStdString();
    std::string key = keyStr.toStdString();

    // 将std::string转换为bitset<8>和bitset<10>
    std::bitset<8> ciphertextBits(ciphertext);
    std::bitset<10> keyBits(key);

    // 执行S-DES解密
    std::bitset<8> plaintext = S_Des::sDesDecrypt(ciphertextBits, keyBits);

    // 显示明文
    ui->lineEdit_6->setText(QString::fromStdString(plaintext.to_string()));
}

