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

#include "CRCTool.h"
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

// QSettings
#define REG_TITLE "CRCTool"
#define REG_AUTHOR "Mystler"

#define CRC_POLY 0xEDB88320

CRCTool::CRCTool(QMainWindow* parent) : QMainWindow(parent)
{
    setupUi(this);
}

void CRCTool::setConfig(const QString& key, const QString& value)
{
    QSettings(REG_AUTHOR, REG_TITLE).setValue(key, value);
}

QString CRCTool::getConfig(const QString& key, const QString& defaultVal)
{
    return QSettings(REG_AUTHOR, REG_TITLE).value(key, defaultVal).toString();
}

quint32 CRCTool::crc32(const QByteArray& data)
{
    quint32 rem = ~0;
    for (quint8 byte: data) {
        rem ^= byte;
        for (quint8 i = 0; i < 8; i++)
            rem = (rem >> 1) ^ (rem & 1) * CRC_POLY;
    }
    return ~rem;
}

void CRCTool::on_btnGenerate_clicked()
{
    // Open and read file
    QFile file(edFile->text());
    if (!file.open(QIODevice::ReadOnly)) {
        txtLog->append(tr("ERROR: File not found"));
        return;
    }
    statusbar->showMessage(tr("Reading file..."));
    txtLog->append(tr("Generating CRC for %1").arg(edFile->text()));
    QByteArray data = file.readAll();
    file.close();

    // Calculate CRC
    statusbar->showMessage(tr("Calculating CRC..."));
    quint32 fcs = crc32(data);
    statusbar->clearMessage();
    txtLog->append("CRC: 0x" + QString::number(fcs, 16));

    // Write to output file, if specified
    QFile crc(edCRC->text());
    if (crc.open(QIODevice::WriteOnly)) {
        QDataStream out(&crc);
        out << fcs;
        crc.close();
        txtLog->append(tr("The checksum has been written to %1").arg(edCRC->text()));
    }
}

void CRCTool::on_btnValidate_clicked()
{
    // Open and read files
    QFile file(edFile->text());
    if (!file.open(QIODevice::ReadOnly)) {
        txtLog->append(tr("ERROR: File not found"));
        return;
    }
    QFile crc(edCRC->text());
    if (!crc.open(QIODevice::ReadOnly)) {
        txtLog->append(tr("ERROR: CRC-File not found"));
        file.close();
        return;
    }
    statusbar->showMessage(tr("Reading files..."));
    txtLog->append(tr("Validating CRC for %1").arg(edFile->text()));
    QByteArray data = file.readAll();
    file.close();
    QDataStream in(&crc);
    quint32 fcs;
    in >> fcs;
    crc.close();

    // Validate CRC
    txtLog->append("CRC: 0x" + QString::number(fcs, 16));
    statusbar->showMessage(tr("Validating CRC..."));
    if (crc32(data) == fcs)
        txtLog->append(tr("SUCCESS: Checksum is valid"));
    else
        txtLog->append(tr("WARNING: Checksum is invalid"));
    statusbar->clearMessage();
}

void CRCTool::on_btnFile_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select File"));
    if (!file.isEmpty())
        edFile->setText(file);
}

void CRCTool::on_btnCRC_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Select Destination"),
            "", "", nullptr, QFileDialog::DontConfirmOverwrite);
    if (!file.isEmpty())
        edCRC->setText(file);
}

void CRCTool::on_actLangEn_triggered()
{
    setConfig("lang", "en");
    QMessageBox::information(this, "Language changed",
            "You have to restart the program for the change to take effect.");
}

void CRCTool::on_actLangDe_triggered()
{
    setConfig("lang", "de");
    QMessageBox::information(this, "Sprache geändert",
            "Sie müssen das Programm neustarten, damit die Änderung aktiv ist.");
}

void CRCTool::on_actAbout_triggered()
{
    QMessageBox::about(this, tr("About CRCTool"),
            "CRCTool\nVersion 1.0.0\n" +
            tr("Using Qt %1").arg(QT_VERSION_STR) + "\n" +
            tr("Created by") + " Florian Meißner 2013");
}

void CRCTool::on_actClearLog_triggered()
{
    txtLog->clear();
}
