/****************************************************************************
** Meta object code from reading C++ file 'n_serial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../n_serial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'n_serial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_n_serial_t {
    QByteArrayData data[20];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_n_serial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_n_serial_t qt_meta_stringdata_n_serial = {
    {
QT_MOC_LITERAL(0, 0, 8), // "n_serial"
QT_MOC_LITERAL(1, 9, 14), // "new_serial_msg"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "serial_create"
QT_MOC_LITERAL(4, 39, 7), // "comport"
QT_MOC_LITERAL(5, 47, 10), // "serial_out"
QT_MOC_LITERAL(6, 58, 2), // "ba"
QT_MOC_LITERAL(7, 61, 7), // "get_bcc"
QT_MOC_LITERAL(8, 69, 7), // "quint8*"
QT_MOC_LITERAL(9, 77, 3), // "buf"
QT_MOC_LITERAL(10, 81, 3), // "len"
QT_MOC_LITERAL(11, 85, 8), // "send_ev2"
QT_MOC_LITERAL(12, 94, 11), // "str_fix_len"
QT_MOC_LITERAL(13, 106, 1), // "s"
QT_MOC_LITERAL(14, 108, 16), // "serial2_out_test"
QT_MOC_LITERAL(15, 125, 7), // "get_len"
QT_MOC_LITERAL(16, 133, 1), // "k"
QT_MOC_LITERAL(17, 135, 7), // "Timer_2"
QT_MOC_LITERAL(18, 143, 11), // "serial_test"
QT_MOC_LITERAL(19, 155, 12) // "serial2_test"

    },
    "n_serial\0new_serial_msg\0\0serial_create\0"
    "comport\0serial_out\0ba\0get_bcc\0quint8*\0"
    "buf\0len\0send_ev2\0str_fix_len\0s\0"
    "serial2_out_test\0get_len\0k\0Timer_2\0"
    "serial_test\0serial2_test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_n_serial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   82,    2, 0x0a /* Public */,
       5,    1,   85,    2, 0x0a /* Public */,
       7,    2,   88,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    2,   94,    2, 0x0a /* Public */,
      14,    0,   99,    2, 0x0a /* Public */,
      15,    1,  100,    2, 0x0a /* Public */,
      17,    0,  103,    2, 0x08 /* Private */,
      18,    0,  104,    2, 0x08 /* Private */,
      19,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Short, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Short,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::UChar, 0x80000000 | 8, QMetaType::Int,    9,   10,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::Int,   13,   10,
    QMetaType::Void,
    QMetaType::Short, QMetaType::Short,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void n_serial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        n_serial *_t = static_cast<n_serial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->new_serial_msg((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->new_serial_msg((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 2: _t->serial_create((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->serial_out((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: { quint8 _r = _t->get_bcc((*reinterpret_cast< quint8*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = _r; }  break;
        case 5: _t->send_ev2(); break;
        case 6: { QString _r = _t->str_fix_len((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: _t->serial2_out_test(); break;
        case 8: { qint16 _r = _t->get_len((*reinterpret_cast< qint16(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = _r; }  break;
        case 9: _t->Timer_2(); break;
        case 10: _t->serial_test(); break;
        case 11: _t->serial2_test(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (n_serial::*_t)(qint16 , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&n_serial::new_serial_msg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (n_serial::*_t)(qint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&n_serial::new_serial_msg)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject n_serial::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_n_serial.data,
      qt_meta_data_n_serial,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *n_serial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *n_serial::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_n_serial.stringdata0))
        return static_cast<void*>(const_cast< n_serial*>(this));
    return QObject::qt_metacast(_clname);
}

int n_serial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void n_serial::new_serial_msg(qint16 _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void n_serial::new_serial_msg(qint16 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
