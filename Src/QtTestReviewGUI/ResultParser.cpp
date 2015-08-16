//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <QtCore/QFile>
#include <QtCore/QUrl>

#include "ResultParser.h"

ResultParser::ResultParser()
{

}

void ResultParser::parseFile(const QString &filepath,
                             TestResultsTableModel *model)
{
    mCurrentModel = model;
    mCurrentModel->mTestResults.clear();

    //QUrl(filepath).toLocalFile()
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream ts(&file);
    QStringList lines;

    while (!ts.atEnd())
        lines.append(ts.readLine());

    TestResult *previousTestResult = nullptr;

    for (const QString line : lines)
    {
        if ((previousTestResult != nullptr) &&
            (previousTestResult->status == TestResult::Status::Failed))
        {
            //next line will show the filepath/line number for the failed test
            QStringList chunks = line.split(" ")[0].split("(");
            previousTestResult->filePath = chunks[0];
            previousTestResult->fileLineNumber
                    = chunks[1].left(chunks[1].count()-1).toInt();
            previousTestResult = nullptr;
        }
        else
        {
            previousTestResult = parseLine(line);
        }
    }
}

//returns character position where the testName ends in line
//TODO do all this with QRegularExpression later. I'm too dumb right now and need this tool ASAP.
TestResult* ResultParser::parseClassNameAndTestName(const QString &line)
{
    TestResult *testResult = new TestResult(this);

    int nameStartPos = line.indexOf(":")+2;
    int scopeResPos = line.indexOf("::")+2;
    int spaceAfterTestNamePos = line.indexOf(" ", scopeResPos);

#define INBOUNDS(pos) (pos > 0 && pos < line.count())

    if (INBOUNDS(nameStartPos) && INBOUNDS(scopeResPos))
    {
        testResult->className = line.mid(nameStartPos,
                                         scopeResPos-nameStartPos-2);

        testResult->testName = line.mid(scopeResPos,
                                        spaceAfterTestNamePos-scopeResPos)
                                .replace("()", "");
    }

    if (INBOUNDS(spaceAfterTestNamePos))
        testResult->message = line.mid(spaceAfterTestNamePos);

#undef INBOUNDS

    return testResult;
}


TestResult* ResultParser::parseLine(const QString &line)
{
    if (line.startsWith("PASS   :"))
    {
        auto testResult = parseClassNameAndTestName(line);
        testResult->status = TestResult::Status::Passed;
        mCurrentModel->mTestResults.append(testResult);
    }
    else if (line.startsWith(("FAIL!  :")))
    {
        auto testResult = parseClassNameAndTestName(line);
        testResult->status = TestResult::Status::Failed;
        mCurrentModel->mTestResults.append(testResult);
    }
    else
        return nullptr;

    return mCurrentModel->mTestResults.last();
}
