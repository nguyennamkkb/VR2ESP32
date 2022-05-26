/****************************************************************************
** Meta object code from reading C++ file 'fpm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fpm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fpm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_fpm_t {
    QByteArrayData data[31];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fpm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fpm_t qt_meta_stringdata_fpm = {
    {
QT_MOC_LITERAL(0, 0, 3), // "fpm"
QT_MOC_LITERAL(1, 4, 7), // "new_img"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 11), // "new_ser_msg"
QT_MOC_LITERAL(4, 25, 11), // "new_str_msg"
QT_MOC_LITERAL(5, 37, 12), // "get_checksum"
QT_MOC_LITERAL(6, 50, 2), // "ba"
QT_MOC_LITERAL(7, 53, 13), // "get_cmd_array"
QT_MOC_LITERAL(8, 67, 7), // "quint8*"
QT_MOC_LITERAL(9, 75, 3), // "buf"
QT_MOC_LITERAL(10, 79, 3), // "len"
QT_MOC_LITERAL(11, 83, 13), // "get_out_array"
QT_MOC_LITERAL(12, 97, 8), // "pkt_type"
QT_MOC_LITERAL(13, 106, 7), // "buf_out"
QT_MOC_LITERAL(14, 114, 10), // "serial_msg"
QT_MOC_LITERAL(15, 125, 7), // "f_timer"
QT_MOC_LITERAL(16, 133, 7), // "get_int"
QT_MOC_LITERAL(17, 141, 5), // "index"
QT_MOC_LITERAL(18, 147, 5), // "cmd_1"
QT_MOC_LITERAL(19, 153, 3), // "cmd"
QT_MOC_LITERAL(20, 157, 5), // "cmd_2"
QT_MOC_LITERAL(21, 163, 6), // "buf_id"
QT_MOC_LITERAL(22, 170, 5), // "cmd_3"
QT_MOC_LITERAL(23, 176, 2), // "b1"
QT_MOC_LITERAL(24, 179, 2), // "b2"
QT_MOC_LITERAL(25, 182, 5), // "cmd_4"
QT_MOC_LITERAL(26, 188, 7), // "page_id"
QT_MOC_LITERAL(27, 196, 5), // "cmd_5"
QT_MOC_LITERAL(28, 202, 2), // "n1"
QT_MOC_LITERAL(29, 205, 2), // "n2"
QT_MOC_LITERAL(30, 208, 5) // "cmd_6"

    },
    "fpm\0new_img\0\0new_ser_msg\0new_str_msg\0"
    "get_checksum\0ba\0get_cmd_array\0quint8*\0"
    "buf\0len\0get_out_array\0pkt_type\0buf_out\0"
    "serial_msg\0f_timer\0get_int\0index\0cmd_1\0"
    "cmd\0cmd_2\0buf_id\0cmd_3\0b1\0b2\0cmd_4\0"
    "page_id\0cmd_5\0n1\0n2\0cmd_6"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fpm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       3,    2,   99,    2, 0x06 /* Public */,
       4,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,  107,    2, 0x0a /* Public */,
       7,    2,  110,    2, 0x0a /* Public */,
      11,    3,  115,    2, 0x0a /* Public */,
      13,    0,  122,    2, 0x0a /* Public */,
      14,    1,  123,    2, 0x0a /* Public */,
      15,    0,  126,    2, 0x0a /* Public */,
      16,    2,  127,    2, 0x0a /* Public */,
      18,    1,  132,    2, 0x0a /* Public */,
      20,    2,  135,    2, 0x0a /* Public */,
      22,    3,  140,    2, 0x0a /* Public */,
      25,    3,  147,    2, 0x0a /* Public */,
      27,    3,  154,    2, 0x0a /* Public */,
      30,    4,  161,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Short,    2,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Short,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::QByteArray, QMetaType::QByteArray,    6,
    QMetaType::QByteArray, 0x80000000 | 8, QMetaType::Int,    9,   10,
    QMetaType::QByteArray, QMetaType::UChar, 0x80000000 | 8, QMetaType::Int,   12,    9,   10,
    QMetaType::QByteArray,
    QMetaType::Short, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Short, QMetaType::QByteArray, QMetaType::Short,    6,   17,
    QMetaType::QByteArray, QMetaType::UChar,   19,
    QMetaType::QByteArray, QMetaType::UChar, QMetaType::UChar,   19,   21,
    QMetaType::QByteArray, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   19,   23,   24,
    QMetaType::QByteArray, QMetaType::UChar, QMetaType::UChar, QMetaType::Short,   19,   21,   26,
    QMetaType::QByteArray, QMetaType::UChar, QMetaType::Short, QMetaType::Short,   19,   28,   29,
    QMetaType::QByteArray, QMetaType::UChar, QMetaType::UChar, QMetaType::Short, QMetaType::Short,   19,   21,   28,   29,

       0        // eod
};

void fpm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fpm *_t = static_cast<fpm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->new_img((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 1: _t->new_ser_msg((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2]))); break;
        case 2: _t->new_str_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: { QByteArray _r = _t->get_checksum((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 4: { QByteArray _r = _t->get_cmd_array((*reinterpret_cast< quint8*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 5: { QByteArray _r = _t->get_out_array((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 6: { QByteArray _r = _t->buf_out();
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 7: { qint16 _r = _t->serial_msg((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = _r; }  break;
        case 8: _t->f_timer(); break;
        case 9: { qint16 _r = _t->get_int((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = _r; }  break;
        case 10: { QByteArray _r = _t->cmd_1((*reinterpret_cast< quint8(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 11: { QByteArray _r = _t->cmd_2((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 12: { QByteArray _r = _t->cmd_3((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 13: { QByteArray _r = _t->cmd_4((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< qint16(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 14: { QByteArray _r = _t->cmd_5((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< qint16(*)>(_a[2])),(*reinterpret_cast< qint16(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 15: { QByteArray _r = _t->cmd_6((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< qint16(*)>(_a[3])),(*reinterpret_cast< qint16(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (fpm::*_t)(QByteArray , qint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&fpm::new_img)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (fpm::*_t)(QByteArray , qint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&fpm::new_ser_msg)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (fpm::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&fpm::new_str_msg)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject fpm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_fpm.data,
      qt_meta_data_fpm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *fpm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fpm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_fpm.stringdata0))
        return static_cast<void*>(const_cast< fpm*>(this));
    return QObject::qt_metacast(_clname);
}

int fpm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void fpm::new_img(QByteArray _t1, qint16 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void fpm::new_ser_msg(QByteArray _t1, qint16 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void fpm::new_str_msg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
