#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <string>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

// Create Log class
class Log {
    public:
        //Default constructor
        void OpenLogFile() {
            logFile.setFileName("BookStoreLogs.txt");
            logFile.open(QIODevice::WriteOnly | QIODevice::Append);
        }

        void CloseLogFile() {
            logFile.close();
        }

        // Log string
        void LogItem(QString stringToLog) {
            QTextStream out(&logFile);

            QDateTime date = QDateTime::currentDateTime();
            QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
            QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

            out << "[" << formattedTimeMsg << "] " << stringToLog << "\n";
        }

    private:
        QFile logFile;
};


#endif // LOGGING_H



