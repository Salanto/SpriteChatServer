#ifndef HELPER_H
#define HELPER_H

#include <QDebug>
#include <QFile>
#include <memory>

#include <QJsonDocument>

namespace Helper {

    std::unique_ptr<QFile> openFile(const QString &f_file, const QIODevice::OpenMode &f_mode)
    {
        auto l_file = std::make_unique<QFile>(f_file);
        if (!l_file->open(f_mode)) {
            qDebug() << "Unable to open file" << l_file->fileName();
            return std::unique_ptr<QFile>(nullptr);
        }
        return l_file;
    }

    QJsonDocument validateJSON(const QByteArray &f_data)
    {
        QJsonParseError l_error;
        QJsonDocument l_document = QJsonDocument::fromJson(f_data, &l_error);
        if (l_error.error != QJsonParseError::NoError) {
            qDebug() << "Error parsing JSON document. Error:" << l_error.errorString();
            return l_document;
        }
        return l_document;
    }
}

#endif // HELPER_H
