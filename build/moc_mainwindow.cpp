/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[448];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "on_bt_aabb_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 27), // "on_bt_calchistogram_clicked"
QT_MOC_LITERAL(4, 59, 27), // "on_bt_openplyfolder_clicked"
QT_MOC_LITERAL(5, 87, 21), // "on_bt_saveply_clicked"
QT_MOC_LITERAL(6, 109, 36), // "on_actionSelect_ply_folder_tr..."
QT_MOC_LITERAL(7, 146, 34), // "on_plyfiles_treeWidget_itemCl..."
QT_MOC_LITERAL(8, 181, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(9, 198, 4), // "item"
QT_MOC_LITERAL(10, 203, 6), // "column"
QT_MOC_LITERAL(11, 210, 43), // "on_plyfiles_treeWidget_itemSe..."
QT_MOC_LITERAL(12, 254, 22), // "on_bt_resetcam_clicked"
QT_MOC_LITERAL(13, 277, 20), // "on_bt_viewup_clicked"
QT_MOC_LITERAL(14, 298, 22), // "on_bt_viewdown_clicked"
QT_MOC_LITERAL(15, 321, 22), // "on_bt_viewleft_clicked"
QT_MOC_LITERAL(16, 344, 23), // "on_bt_viewright_clicked"
QT_MOC_LITERAL(17, 368, 18), // "on_bt_xrot_clicked"
QT_MOC_LITERAL(18, 387, 18), // "on_bt_yrot_clicked"
QT_MOC_LITERAL(19, 406, 18), // "on_bt_zrot_clicked"
QT_MOC_LITERAL(20, 425, 22) // "on_bt_planeseg_clicked"

    },
    "MainWindow\0on_bt_aabb_clicked\0\0"
    "on_bt_calchistogram_clicked\0"
    "on_bt_openplyfolder_clicked\0"
    "on_bt_saveply_clicked\0"
    "on_actionSelect_ply_folder_triggered\0"
    "on_plyfiles_treeWidget_itemClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_plyfiles_treeWidget_itemSelectionChanged\0"
    "on_bt_resetcam_clicked\0on_bt_viewup_clicked\0"
    "on_bt_viewdown_clicked\0on_bt_viewleft_clicked\0"
    "on_bt_viewright_clicked\0on_bt_xrot_clicked\0"
    "on_bt_yrot_clicked\0on_bt_zrot_clicked\0"
    "on_bt_planeseg_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    2,   99,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    0,  110,    2, 0x08 /* Private */,
      18,    0,  111,    2, 0x08 /* Private */,
      19,    0,  112,    2, 0x08 /* Private */,
      20,    0,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   10,
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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_bt_aabb_clicked(); break;
        case 1: _t->on_bt_calchistogram_clicked(); break;
        case 2: _t->on_bt_openplyfolder_clicked(); break;
        case 3: _t->on_bt_saveply_clicked(); break;
        case 4: _t->on_actionSelect_ply_folder_triggered(); break;
        case 5: _t->on_plyfiles_treeWidget_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->on_plyfiles_treeWidget_itemSelectionChanged(); break;
        case 7: _t->on_bt_resetcam_clicked(); break;
        case 8: _t->on_bt_viewup_clicked(); break;
        case 9: _t->on_bt_viewdown_clicked(); break;
        case 10: _t->on_bt_viewleft_clicked(); break;
        case 11: _t->on_bt_viewright_clicked(); break;
        case 12: _t->on_bt_xrot_clicked(); break;
        case 13: _t->on_bt_yrot_clicked(); break;
        case 14: _t->on_bt_zrot_clicked(); break;
        case 15: _t->on_bt_planeseg_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
