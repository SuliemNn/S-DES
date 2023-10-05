#ifndef FIGUREOUT_H
#define FIGUREOUT_H

#include <QWidget>

namespace Ui {
class figureout;
}

class figureout : public QWidget
{
    Q_OBJECT

public:
    explicit figureout(QWidget *parent = nullptr);
    ~figureout();

private slots:
    void getkey();

private:
    Ui::figureout *ui;
};

#endif // FIGUREOUT_H

