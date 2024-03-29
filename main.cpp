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

#include <QApplication>
#include <QTranslator>
#include "CRCTool.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Localization
    QLocale loc = CRCTool::getConfig("lang", QLocale::system().name());
    QTranslator translator;
    translator.load(loc, "lang", "_");
    app.installTranslator(&translator);

    // Load program
    CRCTool tool;
    tool.show();
    return app.exec();
}
