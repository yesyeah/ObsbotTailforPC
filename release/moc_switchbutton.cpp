/****************************************************************************
** Meta object code from reading C++ file 'switchbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../desktopApp/switchbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'switchbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SwitchButton_t {
    QByteArrayData data[25];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SwitchButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SwitchButton_t qt_meta_stringdata_SwitchButton = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SwitchButton"
QT_MOC_LITERAL(1, 13, 14), // "checkedChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "checked"
QT_MOC_LITERAL(4, 37, 11), // "updateValue"
QT_MOC_LITERAL(5, 49, 10), // "setChecked"
QT_MOC_LITERAL(6, 60, 14), // "setButtonStyle"
QT_MOC_LITERAL(7, 75, 11), // "ButtonStyle"
QT_MOC_LITERAL(8, 87, 11), // "buttonStyle"
QT_MOC_LITERAL(9, 99, 10), // "setBgColor"
QT_MOC_LITERAL(10, 110, 10), // "bgColorOff"
QT_MOC_LITERAL(11, 121, 9), // "bgColorOn"
QT_MOC_LITERAL(12, 131, 14), // "setSliderColor"
QT_MOC_LITERAL(13, 146, 14), // "sliderColorOff"
QT_MOC_LITERAL(14, 161, 13), // "sliderColorOn"
QT_MOC_LITERAL(15, 175, 12), // "setTextColor"
QT_MOC_LITERAL(16, 188, 12), // "textColorOff"
QT_MOC_LITERAL(17, 201, 11), // "textColorOn"
QT_MOC_LITERAL(18, 213, 7), // "setText"
QT_MOC_LITERAL(19, 221, 7), // "textOff"
QT_MOC_LITERAL(20, 229, 6), // "textOn"
QT_MOC_LITERAL(21, 236, 8), // "setSpace"
QT_MOC_LITERAL(22, 245, 5), // "space"
QT_MOC_LITERAL(23, 251, 13), // "setRectRadius"
QT_MOC_LITERAL(24, 265, 10) // "rectRadius"

    },
    "SwitchButton\0checkedChanged\0\0checked\0"
    "updateValue\0setChecked\0setButtonStyle\0"
    "ButtonStyle\0buttonStyle\0setBgColor\0"
    "bgColorOff\0bgColorOn\0setSliderColor\0"
    "sliderColorOff\0sliderColorOn\0setTextColor\0"
    "textColorOff\0textColorOn\0setText\0"
    "textOff\0textOn\0setSpace\0space\0"
    "setRectRadius\0rectRadius"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SwitchButton[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   67,    2, 0x08 /* Private */,
       5,    1,   68,    2, 0x0a /* Public */,
       6,    1,   71,    2, 0x0a /* Public */,
       9,    2,   74,    2, 0x0a /* Public */,
      12,    2,   79,    2, 0x0a /* Public */,
      15,    2,   84,    2, 0x0a /* Public */,
      18,    2,   89,    2, 0x0a /* Public */,
      21,    1,   94,    2, 0x0a /* Public */,
      23,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor,   10,   11,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor,   13,   14,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::Int,   24,

       0        // eod
};

void SwitchButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SwitchButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updateValue(); break;
        case 2: _t->setChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setButtonStyle((*reinterpret_cast< ButtonStyle(*)>(_a[1]))); break;
        case 4: _t->setBgColor((*reinterpret_cast< QColor(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 5: _t->setSliderColor((*reinterpret_cast< QColor(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 6: _t->setTextColor((*reinterpret_cast< QColor(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 7: _t->setText((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->setSpace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setRectRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SwitchButton::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SwitchButton::checkedChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SwitchButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SwitchButton.data,
    qt_meta_data_SwitchButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SwitchButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SwitchButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SwitchButton.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SwitchButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SwitchButton::checkedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
