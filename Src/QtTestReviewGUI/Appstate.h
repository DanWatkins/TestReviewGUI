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
    static QString openFilePath;//TODO bring in ValpineBase so this can be a fancy Property<QString>!
};

#endif
