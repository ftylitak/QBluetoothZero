#include <QBtRemoteFileInfo.h>

QBT_NAMESPACE_BEGIN

QBtRemoteFileInfo::QBtRemoteFileInfo(QObject* parent) : QObject(parent){}

QBtRemoteFileInfo::QBtRemoteFileInfo(const QBtRemoteFileInfo& fileInfo) : QObject(fileInfo.parent())
{
	operator=(fileInfo);
}

QString QBtRemoteFileInfo::toString()
{
	return absolutePath;
}

QBtRemoteFileInfo& QBtRemoteFileInfo::operator=(const QBtRemoteFileInfo& fileInfo)
{
	fileName = fileInfo.fileName;
	path = fileInfo.path;
	isDir = fileInfo.isDir;
	type = fileInfo.type;
	size = fileInfo.size;
	creationTime = fileInfo.creationTime;
	lastAccessTime = fileInfo.lastAccessTime;
	lastWriteTime = fileInfo.lastWriteTime;

#if defined(Q_OS_WIN32)
	absolutePath = path + "\\" + fileName;
#else
	absolutePath = path + "/" + fileName;
#endif

	return *this;
}

QBT_NAMESPACE_END