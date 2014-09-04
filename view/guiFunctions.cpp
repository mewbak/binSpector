#include <QPlainTextEdit>
#include <QFontMetrics>
#include <QtCore/QDir.h>

namespace view
{
inline void setHeight(QPlainTextEdit *edit, int nRows)
{
    QFontMetrics m(edit->font());
    int rowHeight = m.lineSpacing();
    edit -> setFixedHeight(nRows * rowHeight);
}

inline std::string exec(const char *cmd)
{
    FILE *pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

//https://qt.gitorious.org/qt-creator/qt-creator/source/1a37da73abb60ad06b7e33983ca51b266be5910e:src/app/main.cpp#L13-189
// taken from utils/fileutils.cpp. We can not use utils here since that depends app_version.h.
inline static bool copyRecursively(const QString &srcFilePath,
                                   const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir())
    {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString & fileName, fileNames)
        {
            const QString newSrcFilePath
                = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath
                = tgtFilePath + QLatin1Char('/') + fileName;
            if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    }
    else
    {
        if (!QFile::copy(srcFilePath, tgtFilePath))
            return false;
    }
    return true;
}
} // view