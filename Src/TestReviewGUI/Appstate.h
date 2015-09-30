//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef APPSTATE_H
#define APPSTATE_H

#include <QObject>
#include <QString>

class Appstate : public QObject
{
    Q_OBJECT

public:
	static QString openFilePath;
};

#endif
