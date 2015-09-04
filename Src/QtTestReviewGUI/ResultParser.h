//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef ResultParser_h
#define ResultParser_h

#include "TestResult.h"

class ResultParser : public QObject
{
public:
    bool parseFile(const QString &filepath, TestResultsMap *testResultsMap);

private:
    TestResultsMap *mTestResultsMap;

    void parseTestClassJsonObject(const QJsonObject &testClassJsonObject);
};

#endif
