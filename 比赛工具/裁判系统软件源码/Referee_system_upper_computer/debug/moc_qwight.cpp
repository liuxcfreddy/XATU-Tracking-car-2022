/****************************************************************************
** Meta object code from reading C++ file 'qwight.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qwight.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwight.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Qwight_t {
    QByteArrayData data[14];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Qwight_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Qwight_t qt_meta_stringdata_Qwight = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Qwight"
QT_MOC_LITERAL(1, 7, 22), // "on_StartButton_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 21), // "on_StopButton_clicked"
QT_MOC_LITERAL(4, 53, 10), // "timerEvent"
QT_MOC_LITERAL(5, 64, 20), // "on_scan_uart_clicked"
QT_MOC_LITERAL(6, 85, 20), // "on_open_uart_clicked"
QT_MOC_LITERAL(7, 106, 7), // "messlot"
QT_MOC_LITERAL(8, 114, 21), // "on_close_uart_clicked"
QT_MOC_LITERAL(9, 136, 26), // "on_uart_data_clean_clicked"
QT_MOC_LITERAL(10, 163, 21), // "on_clean_time_clicked"
QT_MOC_LITERAL(11, 185, 21), // "on_actionPlay_clicked"
QT_MOC_LITERAL(12, 207, 18), // "on_ALL_pin_clicked"
QT_MOC_LITERAL(13, 226, 18) // "on_esc_ALL_clicked"

    },
    "Qwight\0on_StartButton_clicked\0\0"
    "on_StopButton_clicked\0timerEvent\0"
    "on_scan_uart_clicked\0on_open_uart_clicked\0"
    "messlot\0on_close_uart_clicked\0"
    "on_uart_data_clean_clicked\0"
    "on_clean_time_clicked\0on_actionPlay_clicked\0"
    "on_ALL_pin_clicked\0on_esc_ALL_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Qwight[] = {

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
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void,

       0        // eod
};

void Qwight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Qwight *_t = static_cast<Qwight *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_StartButton_clicked(); break;
        case 1: _t->on_StopButton_clicked(); break;
        case 2: _t->timerEvent(); break;
        case 3: _t->on_scan_uart_clicked(); break;
        case 4: _t->on_open_uart_clicked(); break;
        case 5: _t->messlot(); break;
        case 6: _t->on_close_uart_clicked(); break;
        case 7: _t->on_uart_data_clean_clicked(); break;
        case 8: _t->on_clean_time_clicked(); break;
        case 9: _t->on_actionPlay_clicked(); break;
        case 10: _t->on_ALL_pin_clicked(); break;
        case 11: _t->on_esc_ALL_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Qwight::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Qwight.data,
      qt_meta_data_Qwight,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Qwight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Qwight::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Qwight.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Qwight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
