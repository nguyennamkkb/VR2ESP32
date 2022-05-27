/****************************************************************************
** Meta object code from reading C++ file 'udp_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../udp_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udp_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Udp_thread_t {
    QByteArrayData data[18];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Udp_thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Udp_thread_t qt_meta_stringdata_Udp_thread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Udp_thread"
QT_MOC_LITERAL(1, 11, 14), // "new_udp_signal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "socket_send"
QT_MOC_LITERAL(4, 39, 2), // "ba"
QT_MOC_LITERAL(5, 42, 7), // "fix_len"
QT_MOC_LITERAL(6, 50, 1), // "n"
QT_MOC_LITERAL(7, 52, 3), // "len"
QT_MOC_LITERAL(8, 56, 9), // "bcast_out"
QT_MOC_LITERAL(9, 66, 8), // "udp_send"
QT_MOC_LITERAL(10, 75, 3), // "cmd"
QT_MOC_LITERAL(11, 79, 7), // "page_id"
QT_MOC_LITERAL(12, 87, 7), // "get_bcc"
QT_MOC_LITERAL(13, 95, 1), // "k"
QT_MOC_LITERAL(14, 97, 7), // "ip_scan"
QT_MOC_LITERAL(15, 105, 7), // "ip_test"
QT_MOC_LITERAL(16, 113, 9), // "wifi_read"
QT_MOC_LITERAL(17, 123, 5) // "Timer"

    },
    "Udp_thread\0new_udp_signal\0\0socket_send\0"
    "ba\0fix_len\0n\0len\0bcast_out\0udp_send\0"
    "cmd\0page_id\0get_bcc\0k\0ip_scan\0ip_test\0"
    "wifi_read\0Timer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Udp_thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   77,    2, 0x0a /* Public */,
       5,    2,   80,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    3,   86,    2, 0x0a /* Public */,
      12,    2,   93,    2, 0x0a /* Public */,
      14,    0,   98,    2, 0x0a /* Public */,
      15,    0,   99,    2, 0x0a /* Public */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Short, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Short,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Short, QMetaType::Short, QMetaType::Short,   10,    7,   11,
    QMetaType::QByteArray, QMetaType::QByteArray, QMetaType::UChar,    4,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Udp_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Udp_thread *_t = static_cast<Udp_thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->new_udp_signal((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->new_udp_signal((*reinterpret_cast< qint16(*)>(_a[1]))); break;
        case 2: _t->socket_send((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: { QString _r = _t->fix_len((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: _t->bcast_out(); break;
        case 5: _t->udp_send((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2])),(*reinterpret_cast< qint16(*)>(_a[3]))); break;
        case 6: { QByteArray _r = _t->get_bcc((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 7: _t->ip_scan(); break;
        case 8: _t->ip_test(); break;
        case 9: _t->wifi_read(); break;
        case 10: _t->Timer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Udp_thread::*_t)(qint16 , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Udp_thread::new_udp_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Udp_thread::*_t)(qint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Udp_thread::new_udp_signal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Udp_thread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Udp_thread.data,
      qt_meta_data_Udp_thread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Udp_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Udp_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Udp_thread.stringdata0))
        return static_cast<void*>(const_cast< Udp_thread*>(this));
    return QObject::qt_metacast(_clname);
}

int Udp_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Udp_thread::new_udp_signal(qint16 _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Udp_thread::new_udp_signal(qint16 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
