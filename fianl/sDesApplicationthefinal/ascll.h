#ifndef ASCLL_H
#define ASCLL_H

#include <QWidget>

namespace Ui {
class ascll;
}

class ascll : public QWidget
{
    Q_OBJECT

public:
    explicit ascll(QWidget *parent = nullptr);
    ~ascll();

private slots:
    void handleInput();

private:
    Ui::ascll *ui;
};

#endif // ASCLL_H
