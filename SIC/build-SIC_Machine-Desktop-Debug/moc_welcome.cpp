/****************************************************************************
** Meta object code from reading C++ file 'welcome.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SIC_Machine/welcome.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'welcome.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Welcome_t {
    QByteArrayData data[10];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Welcome_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Welcome_t qt_meta_stringdata_Welcome = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Welcome"
QT_MOC_LITERAL(1, 8, 18), // "on_exe_btn_clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(4, 52, 23), // "on_actionLoad_triggered"
QT_MOC_LITERAL(5, 76, 27), // "on_actionAssemble_triggered"
QT_MOC_LITERAL(6, 104, 28), // "on_actionList_File_triggered"
QT_MOC_LITERAL(7, 133, 30), // "on_actionObject_File_triggered"
QT_MOC_LITERAL(8, 164, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(9, 191, 31) // "on_actionLoad_Srcfile_triggered"

    },
    "Welcome\0on_exe_btn_clicked\0\0"
    "on_actionSave_triggered\0on_actionLoad_triggered\0"
    "on_actionAssemble_triggered\0"
    "on_actionList_File_triggered\0"
    "on_actionObject_File_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_actionLoad_Srcfile_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Welcome[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Welcome::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Welcome *_t = static_cast<Welcome *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_exe_btn_clicked(); break;
        case 1: _t->on_actionSave_triggered(); break;
        case 2: _t->on_actionLoad_triggered(); break;
        case 3: _t->on_actionAssemble_triggered(); break;
        case 4: _t->on_actionList_File_triggered(); break;
        case 5: _t->on_actionObject_File_triggered(); break;
        case 6: _t->on_actionSave_as_triggered(); break;
        case 7: _t->on_actionLoad_Srcfile_triggered(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Welcome::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Welcome.data,
      qt_meta_data_Welcome,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Welcome::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Welcome::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Welcome.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Welcome::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
