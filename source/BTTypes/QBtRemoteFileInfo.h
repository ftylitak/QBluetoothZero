#ifndef QBTREMOTEFILEINFO_H
#define QBTREMOTEFILEINFO_H

#include <QString>
#include <QObject>
#include <QBtGlobal.h>
#include <QDate>

QBT_NAMESPACE_BEGIN

class DLL_EXPORT QBtRemoteFileInfo : public QObject{
	Q_OBJECT
public:
	QBtRemoteFileInfo(QObject* parent=0);
	QBtRemoteFileInfo(const QBtRemoteFileInfo& fileInfo);
	QString toString();
	QBtRemoteFileInfo& operator=(const QBtRemoteFileInfo& fileInfo);

public:
	QString absolutePath;
	QString fileName;
	QString path;
	bool isDir;
	int type;
	int size;

	QDate creationTime;
	QDate lastAccessTime;
	QDate lastWriteTime;
};

QBT_NAMESPACE_END

Q_DECLARE_METATYPE(QBT_PREPEND_NAMESPACE(QBtRemoteFileInfo))

#endif // QBTREMOTEFILEINFO_H