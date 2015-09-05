//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef ResultParser_h
#define ResultParser_h

#include "TreeItem.h"

class ResultParser : public QObject
{
public:
    bool parseFile(const QString &filepath, QObject *treeItem);

private:
    void parseTestClassJsonObject(const QJsonObject &testClassJsonObject, QObject *treeItem);
};

#endif
