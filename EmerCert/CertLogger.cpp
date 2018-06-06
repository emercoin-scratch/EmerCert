﻿//CertLogger.cpp by Emercoin developers
#include "pch.h"
#include "CertLogger.h"

CertLogger::CertLogger() {
	auto timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this]() {
		_file.flush();
	});
	timer->start(1000);
}
void CertLogger::append(const QString & s) {
	QTextBrowser::append(s);
	if(!_file.isOpen() && !_file.fileName().isEmpty()) {
		if(!_file.open(QFile::WriteOnly|QFile::Truncate))
			QTextBrowser::append(_file.errorString());
	}
	if(_file.isOpen()) {
		QString s2 = s;
		if(!s2.endsWith('\n'))
			s2 += '\n';
		_file.write(s2.toUtf8());
		_file.flush();
	}
	QCoreApplication::processEvents();
}
void CertLogger::clear() {
	QTextBrowser::clear();
	if(_file.isOpen()) {
		_file.close();
	}
}
void CertLogger::setFile(const QString & path) {
	clear();
	_file.setFileName(path);
	if(path.isEmpty())
		return;
	if(!_file.open(QFile::ReadWrite)) {
		QTextBrowser::append(_file.errorString());
	}
	QTextStream stream(&_file);
	QString s = stream.readAll();
	QTextBrowser::append(s);
	_file.close();
}
void CertLogger::closeEvent(QCloseEvent *event) {
	QMessageBox::information(this, "", "");
	QTextBrowser::closeEvent(event);
}