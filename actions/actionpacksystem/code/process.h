/*
	Actionaz
	Copyright (C) 2008-2010 Jonathan Mercier-Ganady

	Actionaz is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actionaz is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QScriptEngine>
#include <QProcess>

#include "code/code.h"

namespace Code
{
	class Process : public QObject, public QScriptable
	{
		Q_OBJECT
		Q_PROPERTY(QScriptValue onError READ onError WRITE setOnError)
		Q_PROPERTY(QScriptValue onFinished READ onFinished WRITE setOnFinished)
		Q_PROPERTY(QScriptValue onReadyReadStandardError READ onReadyReadStandardError WRITE setOnReadyReadStandardError)
		Q_PROPERTY(QScriptValue onReadyReadStandardOutput READ onReadyReadStandardOutput WRITE setOnReadyReadStandardOutput)
		Q_PROPERTY(QScriptValue onStarted READ onStarted WRITE setOnStarted)
		Q_PROPERTY(QScriptValue onStateChanged READ onStateChanged WRITE setOnStateChanged)
		Q_ENUMS(QProcess::ProcessError)
		Q_ENUMS(QProcess::ExitStatus)
		Q_ENUMS(QProcess::ProcessState)
		Q_ENUMS(QProcess::ProcessChannel)
		Q_ENUMS(QProcess::ProcessChannelMode)
		Q_FLAGS(QIODevice::OpenMode)

	public:
		static QScriptValue constructor(QScriptContext *context, QScriptEngine *engine);

		static QScriptValue list(QScriptContext *context, QScriptEngine *engine);
		static QScriptValue startDetached(QScriptContext *context, QScriptEngine *engine);
		static QScriptValue thisProcess(QScriptContext *context, QScriptEngine *engine);

		Process();

		void setOnError(const QScriptValue &onError)									{ mOnError = onError; }
		void setOnFinished(const QScriptValue &onFinished)								{ mOnFinished = onFinished; }
		void setOnReadyReadStandardError(const QScriptValue &onReadyReadStandardError)	{ mOnReadyReadStandardError = onReadyReadStandardError; }
		void setOnReadyReadStandardOutput(const QScriptValue &onReadyReadStandardOutput){ mOnReadyReadStandardOutput = onReadyReadStandardOutput; }
		void setOnStarted(const QScriptValue &onStarted)								{ mOnStarted = onStarted; }
		void setOnStateChanged(const QScriptValue &onStateChanged)						{ mOnStateChanged = onStateChanged; }

		QScriptValue onError() const													{ return mOnError; }
		QScriptValue onFinished() const													{ return mOnFinished; }
		QScriptValue onReadyReadStandardError() const									{ return mOnReadyReadStandardError; }
		QScriptValue onReadyReadStandardOutput() const									{ return mOnReadyReadStandardOutput; }
		QScriptValue onStarted() const													{ return mOnStarted; }
		QScriptValue onStateChanged() const												{ return mOnStateChanged; }

		QProcess *process() const														{ return mProcess; }

	public slots:
		QString toString() const														{ return "Process"; }
		QScriptValue handle() const;
		int id() const;
		QScriptValue start();
		QProcess::ProcessState state() const;
		QProcess::ProcessError error() const;
		int exitCode() const;
		QProcess::ExitStatus exitStatus() const;
		QScriptValue readError() const;
		QScriptValue read() const;
		QString readErrorText(Code::Encoding encoding = Code::Native) const;
		QString readText(Code::Encoding encoding = Code::Native) const;
		bool atEnd() const;
		qint64 bytesAvailable() const;
		qint64 bytesToWrite() const;
		bool canReadLine() const;
		QScriptValue write(const QScriptValue &data);
		QScriptValue writeText(const QString &data, Code::Encoding encoding = Code::Native);
		QScriptValue setWorkingDirectory(const QString &workingDirectory);
		QScriptValue setProcessChannelMode(QProcess::ProcessChannelMode channelMode);
		QScriptValue setEnvironment();
		QScriptValue updateEnvironment();
		QScriptValue setReadChannel(QProcess::ProcessChannel channel);
		QScriptValue setStandardErrorFile(const QString &fileName, QIODevice::OpenMode openMode = QIODevice::Truncate);
		QScriptValue setStandardInputFile(const QString &fileName);
		QScriptValue setStandardOutputFile(const QString &fileName, QIODevice::OpenMode openMode = QIODevice::Truncate);
		QScriptValue setStandardOutputProcess(const QScriptValue &processValue);
		QScriptValue waitForFinished(int waitTime = 30000);
		QScriptValue waitForStarted(int waitTime = 30000);
		QScriptValue waitForBytesWritten(int waitTime = 30000);
		QScriptValue waitForReadyRead(int waitTime = 30000);
		QScriptValue close();
		QScriptValue kill();
		QScriptValue terminate();

	private slots:
		void error(QProcess::ProcessError processError);
		void finished(int exitCode, QProcess::ExitStatus exitStatus);
		void readyReadStandardError();
		void readyReadStandardOutput();
		void started();
		void stateChanged(QProcess::ProcessState newState);

	private:
		QProcess *mProcess;
		QScriptValue mOnError;
		QScriptValue mOnFinished;
		QScriptValue mOnReadyReadStandardError;
		QScriptValue mOnReadyReadStandardOutput;
		QScriptValue mOnStarted;
		QScriptValue mOnStateChanged;
		QScriptValue mThisObject;
	};
}

#endif // PROCESS_H