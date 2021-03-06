﻿//DpoCreateRootWidget.h by Emercoin developers
#pragma once
#include "NameValueLineEdits.h"

class DpoCreateRootWidget: public QScrollArea {
	public:
		DpoCreateRootWidget();
		void updateSettings(bool save);
		NameValueLineEdits* _NVPair = 0;
    protected:
		QLineEdit* _editName = 0;
		QPlainTextEdit* _editOther = 0;
		QList<QLineEdit*> _edits;
		void recalcValue();
		QLineEdit* addLineEdit(QFormLayout*form, const QString& name, const QString& text, const QString& tooltip, bool readOnly = false);
};