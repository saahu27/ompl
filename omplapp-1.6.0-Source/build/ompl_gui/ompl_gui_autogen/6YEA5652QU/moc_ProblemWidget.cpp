/****************************************************************************
** Meta object code from reading C++ file 'ProblemWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../ompl_gui/include/ProblemWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProblemWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProblemWidget_t {
    QByteArrayData data[12];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProblemWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProblemWidget_t qt_meta_stringdata_ProblemWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ProblemWidget"
QT_MOC_LITERAL(1, 14, 12), // "startChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "std::array<double,6>"
QT_MOC_LITERAL(4, 49, 4), // "pose"
QT_MOC_LITERAL(5, 54, 11), // "goalChanged"
QT_MOC_LITERAL(6, 66, 12), // "setStartPose"
QT_MOC_LITERAL(7, 79, 4), // "is3D"
QT_MOC_LITERAL(8, 84, 11), // "setGoalPose"
QT_MOC_LITERAL(9, 96, 15), // "startPoseChange"
QT_MOC_LITERAL(10, 112, 5), // "value"
QT_MOC_LITERAL(11, 118, 14) // "goalPoseChange"

    },
    "ProblemWidget\0startChanged\0\0"
    "std::array<double,6>\0pose\0goalChanged\0"
    "setStartPose\0is3D\0setGoalPose\0"
    "startPoseChange\0value\0goalPoseChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProblemWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   50,    2, 0x0a /* Public */,
       8,    2,   55,    2, 0x0a /* Public */,
       9,    1,   60,    2, 0x08 /* Private */,
      11,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    7,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Void, 0x80000000 | 3,   10,

       0        // eod
};

void ProblemWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProblemWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startChanged((*reinterpret_cast< const std::array<double,6>(*)>(_a[1]))); break;
        case 1: _t->goalChanged((*reinterpret_cast< const std::array<double,6>(*)>(_a[1]))); break;
        case 2: _t->setStartPose((*reinterpret_cast< const std::array<double,6>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->setGoalPose((*reinterpret_cast< const std::array<double,6>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->startPoseChange((*reinterpret_cast< const std::array<double,6>(*)>(_a[1]))); break;
        case 5: _t->goalPoseChange((*reinterpret_cast< const std::array<double,6>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProblemWidget::*)(const std::array<double,6> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProblemWidget::startChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProblemWidget::*)(const std::array<double,6> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProblemWidget::goalChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ProblemWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ProblemWidget.data,
    qt_meta_data_ProblemWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProblemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProblemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProblemWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ProblemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ProblemWidget::startChanged(const std::array<double,6> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProblemWidget::goalChanged(const std::array<double,6> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
