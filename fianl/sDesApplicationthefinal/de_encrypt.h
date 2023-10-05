#ifndef DE_ENCRYPT_H
#define DE_ENCRYPT_H

#include <QWidget>

namespace Ui {
class de_encrypt;
}

class de_encrypt : public QWidget
{
    Q_OBJECT

public:
    explicit de_encrypt(QWidget *parent = nullptr);
    ~de_encrypt();

private slots:
    void encrypt();
    void decrypt();

private:
    Ui::de_encrypt *ui;
};

#endif // DE_ENCRYPT_H
