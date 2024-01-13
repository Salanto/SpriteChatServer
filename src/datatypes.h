#ifndef DATATYPES_H
#define DATATYPES_H

#include <QObject>

namespace Datatypes {
    Q_NAMESPACE

    struct Background {
        QString name;
        QStringList sides;
    };
};

#endif // DATATYPES_H
