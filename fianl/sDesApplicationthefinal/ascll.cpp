#include "ascll.h"
#include "ui_ascll.h"
#include "s_des.h"
using namespace std;
ascll::ascll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ascll)
{
    ui->setupUi(this);
   // connect(ui->pushButton,&QPushButton::clicked,this,&ascll::handleInput);
}

ascll::~ascll()
{
    delete ui;
}
void ascll::handleInput(){
    QString text = ui->lineEdit->text();
    QByteArray byteArray = text.toUtf8();
    std::string stdString = byteArray.toStdString();
    const char *charArray = stdString.c_str();
    std::bitset<8> asciiArray[8];
    std::bitset<8> desArray[8];
    S_Des::convertToASCII(charArray,asciiArray,8);
    S_Des::convertToDes(desArray,asciiArray,8);
    for (const auto& bitset : desArray)
    {
    QString bitsetString = QString::fromStdString(bitset.to_string());
    ui->textBrowser->append(bitsetString);
    }
}
