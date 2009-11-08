/****************************************************************************
** Meta object code from reading C++ file 'mainwindowimpl.h'
**
** Created: Sat Nov 7 22:37:58 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindowimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindowimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindowImpl[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      27,   15,   15,   15, 0x08,
      47,   40,   15,   15, 0x08,
      67,   61,   15,   15, 0x08,
      86,   80,   15,   15, 0x08,
     101,   15,   15,   15, 0x08,
     116,   15,   15,   15, 0x08,
     137,  131,   15,   15, 0x08,
     159,   15,   15,   15, 0x08,
     172,   15,   15,   15, 0x08,
     187,   15,   15,   15, 0x08,
     198,   15,   15,   15, 0x08,
     211,   15,   15,   15, 0x08,
     228,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindowImpl[] = {
    "MainWindowImpl\0\0OnFreqUp()\0OnFreqDown()\0"
    "volume\0OnVolume(int)\0muted\0OnMute(bool)\0"
    "start\0OnRecord(bool)\0OnBandChange()\0"
    "OnSavePreset()\0index\0OnPreset(QModelIndex)\0"
    "OnSettings()\0OnLevelTimer()\0OnFastUp()\0"
    "OnFastDown()\0OnRemovePreset()\0"
    "OnCheckRadiosharkTimer()\0"
};

const QMetaObject MainWindowImpl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindowImpl,
      qt_meta_data_MainWindowImpl, 0 }
};

const QMetaObject *MainWindowImpl::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindowImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindowImpl))
        return static_cast<void*>(const_cast< MainWindowImpl*>(this));
    if (!strcmp(_clname, "Ui::MainWindow"))
        return static_cast< Ui::MainWindow*>(const_cast< MainWindowImpl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindowImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnFreqUp(); break;
        case 1: OnFreqDown(); break;
        case 2: OnVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: OnMute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: OnRecord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: OnBandChange(); break;
        case 6: OnSavePreset(); break;
        case 7: OnPreset((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: OnSettings(); break;
        case 9: OnLevelTimer(); break;
        case 10: OnFastUp(); break;
        case 11: OnFastDown(); break;
        case 12: OnRemovePreset(); break;
        case 13: OnCheckRadiosharkTimer(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
