#ifndef DEVICELISTWINDOW_H
#define DEVICELISTWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
namespace Ui {
class devicelistwindow;
}

class devicelistwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit devicelistwindow(QWidget *parent = nullptr);
    ~devicelistwindow();

    bool deviceListShow(std::vector<std::string> info_list);
private:
    Ui::devicelistwindow *ui;

    QStringListModel *Model;
    QStandardItemModel *ItemModel;
};

#endif // DEVICELISTWINDOW_H
