#include "ascll.h"
#include "de_encrypt.h"
#include "figureout.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ascll as;
    de_encrypt de;
    figureout fi;

    as.show();
    de.show();
    fi.show();
    return a.exec();
}
