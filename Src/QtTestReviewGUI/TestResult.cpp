//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include "TestResult.h"
#include <QtCore/QMetaEnum>

QString TestResult::statusAsString() const
{
    const QMetaObject &mo = TestResult::staticMetaObject;
    QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Status"));
    return me.valueToKey(this->status);
}
