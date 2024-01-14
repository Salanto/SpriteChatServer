#ifndef HELPER_H
#define HELPER_H

#include <QFile>
#include <QDebug>
#include <memory>

namespace Helper {

std::unique_ptr<QFile> openFile(const QString &f_file, const QIODevice::OpenMode& f_mode)
{
    auto l_file =  std::make_unique<QFile>(f_file);
    if (l_file->open(f_mode))
    {
        qDebug() << "Unable to open file" << l_file->fileName();
        return nullptr;
    }
    return l_file;
}

}

#endif // HELPER_H
