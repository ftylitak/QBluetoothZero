#include <QtCore/QCoreApplication>
#include <QRegExp>
#include <QTextStream>
#include <iostream>
#include "remotebrowser.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //add the address of your target device
    RemoteBrowser browser = RemoteBrowser(QBtAddress(QString("00:26:69:4F:F9:5E")));
    browser.initializeConnectionData();
    browser.connectToDevice();

    QList<QBtRemoteFileInfo*> selectedFiles;

    QTextStream stream(stdin);
    QString line;
    while (true)
    {
        cout << browser.pwd().toAscii().data() << "> ";
        line = stream.readLine();
        if(line.compare("exit") == 0)
            break;

        QString command(line);
        if(command.contains("cd"))
        {
            command.remove(0,3);
            browser.cd(command);
        }else
            if(command.contains("ls"))
            {
                command.remove(0,3);
                QList<QBtRemoteFileInfo*>& files = browser.ls(command);
                browser.printFileListInfo(files);
            }
            else if(command.contains("pwd"))
                cout << "Working Dir: " << browser.pwd().toAscii().data() << endl;
            else if(command.contains("selectImages"))
            {
                command.remove(0,7);

                QRegExp expression(".jpg$|.jpeg$|.png$|.bmp$");
                expression.setCaseSensitivity(Qt::CaseInsensitive);

                selectedFiles = browser.locateFiles(command, &expression);
                cout << endl << "Images found: " << selectedFiles.size() << endl;
                browser.printFileListInfo(selectedFiles);
            }
			else if (command.contains("select "))
			{
				QStringList commands = command.split(" ");
				if(commands.length() != 3 && commands.length()!=2)
				{
					cout << "Usage: select <REGEX> {<SRC_DIR>}" << endl;
					continue;
				}
					
				QString currentFolder = (commands.length() == 3) ? commands[2] : browser.pwd();

				QRegExp expression(commands[1]);
				expression.setCaseSensitivity(Qt::CaseInsensitive);
				selectedFiles = browser.locateFiles(currentFolder, &expression, false);
				browser.printFileListInfo(selectedFiles);
			}
            else if(command.contains("receive"))
            {
                browser.batchFileRetrieval(selectedFiles, "C:\\receivedFiles", true);
            }
            else if(command.contains("help"))
            {
                cout << "Supported commands:" << endl;
                cout << " cd <DIR>" << endl;
                cout << " ls <DIR>" << endl;
                cout << " pwd" << endl;
				cout << " select <REGEX> {<SRC_DIR>}" << endl;
				cout << " selectImages <SRC_DIR>" << endl;
                cout << " receive" << endl;
                cout << " help" << endl;
            }
    }

    browser.disconnectFromDevice();

    return 0;
}
