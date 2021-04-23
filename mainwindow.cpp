#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bisness_logic.h>

#include <QFile>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setFixedSize(QSize(956, 640));
    CsvItemModel = new QStandardItemModel(this);
    CsvItemModel->setColumnCount(7);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStandardItemModel *csv_main_model = new QStandardItemModel;
QStringList headers;

void mdlcopy(QStandardItemModel* first, QStandardItemModel* second){
       second->clear();
       for (int rows = 0 ; rows < first->rowCount() ; rows++){
          QList<QStandardItem *> result;
          for (int columns = 0; columns < first->columnCount(); columns++){
              result.append(new QStandardItem(first->item(rows, columns)->text()));
          }
           second->appendRow(result);
       }
}

bool is_normal_file(QString file){
    bool flag;
    flag = file.contains(".csv");
    return flag;
}

void MainWindow::on_load_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (is_normal_file(file)){
    std::vector<std::vector<std::string>> csv = read_csv(file.toStdString());
    CsvItemModel->clear();
    CsvItemModel->setColumnCount(csv.at(0).size());
    headers.clear();
    for (std::string str : csv.at(0)) {
      headers.push_back(QString::fromStdString(str));
    }
    CsvItemModel->setHorizontalHeaderLabels(headers);

    bool is_header = true;
    for (std::vector<std::string> item_list : csv) {
        if (is_header){
            is_header = false;
            continue;
        }
        QList<QStandardItem *> standardItemsList;
        for (std::string item_str : item_list){
            QString q_item_str = QString::fromStdString(item_str);
            standardItemsList.append(new QStandardItem(q_item_str));
        }
        CsvItemModel->insertRow(CsvItemModel->rowCount(), standardItemsList);
    }
    ui->tableView->setModel(CsvItemModel);}
    else {
        ui->metrics->setText("Ошибка при чтении\nфайла");
    }
}

bool check_for_correct_input(QString region, QString column){
    bool flag = true;
    bool ok;
    if (region == "" || column  == ""){
        flag = false;
    } else {
        int colum_num = column.toInt(&ok);
        if (ok){
            if (colum_num < 1 || colum_num > 7 || colum_num == 2){
                flag = false;
            }}}
    return flag;
}

void MainWindow::on_calculate_clicked()
{
    QString region = ui->region->text();
    QString column = ui->line_input->text();
    if (check_for_correct_input(region, column)){
        float minimum = 0;
        float maximum = 0;
        float medium = 0;
        int column_number  = column.toInt() -  1;

        csv_main_model->clear();
        csv_main_model->setColumnCount(7);
        csv_main_model->setHorizontalHeaderLabels(headers);

        for (int row = 0; row < CsvItemModel->rowCount(); row++){
            if (CsvItemModel->item(row, 1)->text() == region){
               QList<QStandardItem *> result;
               for (int columns = 0; columns < CsvItemModel->columnCount(); columns++){
                   result.append(new QStandardItem(CsvItemModel->item(row, columns)->text()));
               }
               csv_main_model->insertRow(csv_main_model->rowCount(), result);
            }
        }
        ui->tableView->setModel(csv_main_model);

        std::vector<float> arr;
        for (int row = 0; row < csv_main_model->rowCount(); ++row){
            if (is_normal_metric(csv_main_model->item(row, column_number)->text())){
            arr.push_back(csv_main_model->item(row, column_number)->text().toFloat());
            }
        }
        calculate_metrics(arr, &minimum, &maximum, &medium);
        QString final_text = "Минимум: "+ QString::number(minimum) +"\nМаксимум: "+ QString::number(maximum)
                +"\nМедиана: "+ QString::number(medium);
        ui->metrics->setText(final_text);
    } else {
        ui->metrics->setText("Введены неверные\nзначения!");
    }
}
