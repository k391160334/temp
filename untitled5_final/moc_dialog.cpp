/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_t {
    QByteArrayData data[15];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Dialog"
QT_MOC_LITERAL(1, 7, 12), // "showRotation"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 1), // "a"
QT_MOC_LITERAL(4, 23, 23), // "on_pushButton_p_pressed"
QT_MOC_LITERAL(5, 47, 25), // "on_pushButton_put_pressed"
QT_MOC_LITERAL(6, 73, 21), // "on_pushButton_pressed"
QT_MOC_LITERAL(7, 95, 23), // "on_pushButton_N_pressed"
QT_MOC_LITERAL(8, 119, 24), // "on_pushButton_N_released"
QT_MOC_LITERAL(9, 144, 23), // "on_pushButton_S_pressed"
QT_MOC_LITERAL(10, 168, 24), // "on_pushButton_S_released"
QT_MOC_LITERAL(11, 193, 23), // "on_pushButton_E_pressed"
QT_MOC_LITERAL(12, 217, 24), // "on_pushButton_E_released"
QT_MOC_LITERAL(13, 242, 23), // "on_pushButton_W_pressed"
QT_MOC_LITERAL(14, 266, 24) // "on_pushButton_W_released"

    },
    "Dialog\0showRotation\0\0a\0on_pushButton_p_pressed\0"
    "on_pushButton_put_pressed\0"
    "on_pushButton_pressed\0on_pushButton_N_pressed\0"
    "on_pushButton_N_released\0"
    "on_pushButton_S_pressed\0"
    "on_pushButton_S_released\0"
    "on_pushButton_E_pressed\0"
    "on_pushButton_E_released\0"
    "on_pushButton_W_pressed\0"
    "on_pushButton_W_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    0,   77,    2, 0x08 /* Private */,
       5,    0,   78,    2, 0x08 /* Private */,
       6,    0,   79,    2, 0x08 /* Private */,
       7,    0,   80,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showRotation((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_p_pressed(); break;
        case 2: _t->on_pushButton_put_pressed(); break;
        case 3: _t->on_pushButton_pressed(); break;
        case 4: _t->on_pushButton_N_pressed(); break;
        case 5: _t->on_pushButton_N_released(); break;
        case 6: _t->on_pushButton_S_pressed(); break;
        case 7: _t->on_pushButton_S_released(); break;
        case 8: _t->on_pushButton_E_pressed(); break;
        case 9: _t->on_pushButton_E_released(); break;
        case 10: _t->on_pushButton_W_pressed(); break;
        case 11: _t->on_pushButton_W_released(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog.data,
      qt_meta_data_Dialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
