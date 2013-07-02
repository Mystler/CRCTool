/*==LICENSE==
This file is part of CRCTool.
Copyright (C) 2013 Florian Meißner

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
==LICENSE==*/

#ifndef CRCTool_h
#define CRCTool_h

#include "ui_crctool.h"

class CRCTool : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

public:
    CRCTool(QMainWindow* parent = nullptr);
    static void setConfig(const QString& key, const QString& value);
    static QString getConfig(const QString& key, const QString& defaultVal);

private:
    quint32 crc32(const QByteArray& data);

private slots:
    void on_btnFile_clicked();
    void on_btnCRC_clicked();
    void on_btnGenerate_clicked();
    void on_btnValidate_clicked();
    void on_actLangEn_triggered();
    void on_actLangDe_triggered();
    void on_actAbout_triggered();
    void on_actClearLog_triggered();
};
#endif
