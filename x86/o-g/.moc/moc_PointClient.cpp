/****************************************************************************
** Meta object code from reading C++ file 'PointClient.hpp'
**
** Created: Fri Feb 22 16:20:54 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/PointClient.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PointClient.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PointClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x08,

 // methods: signature, parameters, type, tag, flags
      51,   12,   12,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_PointClient[] = {
    "PointClient\0\0reply\0requestFinished(QNetworkReply*)\0"
    "initiateRequest()\0"
};

void PointClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PointClient *_t = static_cast<PointClient *>(_o);
        switch (_id) {
        case 0: _t->requestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->initiateRequest(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PointClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PointClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PointClient,
      qt_meta_data_PointClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PointClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PointClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PointClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PointClient))
        return static_cast<void*>(const_cast< PointClient*>(this));
    return QObject::qt_metacast(_clname);
}

int PointClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
