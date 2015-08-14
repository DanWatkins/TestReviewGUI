#include "TestResult.h"
#include <QtCore/QMetaEnum>

QString TestResult::statusAsString() const
{
    const QMetaObject &mo = TestResult::staticMetaObject;
    QMetaEnum me = mo.enumerator(mo.indexOfEnumerator("Status"));
    return me.valueToKey(this->status);
}
