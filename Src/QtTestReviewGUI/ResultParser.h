//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef ResultParser_h
#define ResultParser_h

#include <QObject>

#include "TestResult.h"
#include "TestResultsTableModel.h"

class ResultParser : public QObject
{
    Q_OBJECT

public:
    ResultParser();
    void parseFile(const QString &filepath, TestResultsTableModel *model);

private:
    TestResultsTableModel *mCurrentModel;

    TestResult* parseLine(const QString &line);
    TestResult* parseClassNameAndTestName(const QString &line);
};

#endif
