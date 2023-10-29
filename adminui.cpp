#include "adminui.h"
#include "ui_adminui.h"
#include<QPixmap>
#include <QTableView>
#include<QStandardItemModel>
#include"logindialog.h"
#include<QMessageBox>
#include<QDebug>
#include<QSqlError>
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDateTime>
#include<QDebug>


AdminUi::AdminUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminUi)
{
    ui->setupUi(this);
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_6->setAlignment(Qt::AlignCenter);
    //表格1设计
    ui->tableView->horizontalHeader()->setStyleSheet(R"(
        QHeaderView::section {
            background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));
            color: white;
            border: none;
            font-size: 20px;
            font-family: "微软雅黑";
            padding-top: 5;
            padding-bottom: 5;
        }
    )");
    ui->tableView->verticalHeader()->setStyleSheet(R"(
        QHeaderView::section {
            background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));
            color: white;
            border: none;
            font-size: 20px;
            font-family: "微软雅黑";
        }
    )");
    ui->tableView->viewport()->setStyleSheet("background-color: lightblue;");

    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    //表格2
    ui->tableView_2->horizontalHeader()->setStyleSheet(R"(
       QHeaderView::section {
           background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));
           color: white;
           border: none;
           font-size: 20px;
           font-family: "微软雅黑";
           padding-top: 5;
           padding-bottom: 5;
       }
    )");
    ui->tableView_2->verticalHeader()->setStyleSheet(R"(
       QHeaderView::section {
           background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));
           color: white;
           border: none;
           font-size: 20px;
           font-family: "微软雅黑";
       }
    )");
    ui->tableView_2->viewport()->setStyleSheet("background-color: lightblue;");
    ui->tableView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);

    //表格3
    ui->tableView_3->setStyleSheet(
        "QHeaderView::section {"
            "color: white;"
            "border: none;"
            "font-size: 20px;"
            "font-family: '微软雅黑';"
            "background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));"
            "padding-top: 5;"
            "padding-bottom: 5;"
        "}"
        "QTableView {"
            "background-color: rgba(224, 224, 224, 0.5);"
            "selection-background-color: rgba(76, 175, 80, 0.5);"
        "}"
        "QTableView::item {"
            "padding: 5px;"
        "}"
    );

    ui->tableView_3->verticalHeader()->setVisible(false);
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_3->horizontalHeader()->setHighlightSections(false);
    ui->tableView_3->setShowGrid(false);
    ui->tableView_3->setFrameStyle(QFrame::NoFrame);
    ui->tableView_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //初始化数据库
    db2_ = QSqlDatabase::addDatabase("QMYSQL");
   //连接数据库
   db2_.setHostName("127.0.0.1");
   db2_.setUserName("HWH");
   db2_.setPassword("@MySql668931hwh");
   db2_.setDatabaseName("login");
   if(!db2_.open())//数据库打开失败
   {
       QMessageBox::warning(this,"错误",db2_.lastError().text());
       qDebug()<<db2_.lastError().text();
       return;
   }

   model = new QSqlTableModel(this,db2_);
   model->setTable("books");
   ui->tableView->setModel(model);
   model->select();







   //查询功能
  //页面跳转
   connect(ui->pushButton, &QPushButton::clicked, [this]()
   {
       ui->stackedWidget->setCurrentIndex(0);
   });
   // 设置下拉列表的内容
   ui->comboBox->addItems(QStringList() << "书名" << "作者名" << "ISBN" << "索书号" << "出版社"<<"丛书名");
   // 连接查询按钮的点击事件到查询函数
   connect(ui->pushButton_8, &QPushButton::clicked, this, &AdminUi::searchBook);




   //借书模块
   //翻页
   connect(ui->pushButton_2, &QPushButton::clicked, [this]()
   {
       ui->stackedWidget->setCurrentIndex(1);
   });
   connect(ui->pushButton_11, &QPushButton::clicked, this, &AdminUi::borrowBook);
   //还书
    connect(ui->pushButton_12, &QPushButton::clicked, this, &AdminUi::returnBook);

    //查看及修改预约信息
    connect(ui->pushButton_3, &QPushButton::clicked, [this]()
    {
        ui->stackedWidget->setCurrentIndex(2);
    });
    model2 = new QSqlTableModel(this,db2_);
    model2->setTable("reserve");
    ui->tableView_2->setModel(model2);
    model2->select();
    connect(ui->pushButton_13, &QPushButton::clicked, this, &AdminUi::Delete);
    connect(ui->pushButton_14, &QPushButton::clicked, this, &AdminUi::confirm);
    connect(ui->pushButton_15, &QPushButton::clicked, this, &AdminUi::cancel);
    //
    connect(ui->pushButton_10, &QPushButton::clicked, [this]()
    {
        ui->stackedWidget->setCurrentIndex(3);
    });
    //查看并修改所有违约记录
    model3 = new QSqlTableModel(this,db2_);
    model3->setTable("violation");
    ui->tableView_3->setModel(model3);
    model3->select();
    connect(ui->pushButton_16, &QPushButton::clicked, this, &AdminUi::add);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &AdminUi::Delete);
    connect(ui->pushButton_18, &QPushButton::clicked, this, &AdminUi::confirm);
    connect(ui->pushButton_19, &QPushButton::clicked, this, &AdminUi::cancel);




}

void AdminUi::setInfo(const QString&Id,const QString&password)
{
    this->Id = Id;
    this->password = password;
}
void  AdminUi::searchBook()
{
    QString searchType = ui->comboBox->currentText();
        QString searchText = ui->lineEdit->text();

        QString queryString;

        if (searchType == "书名") {
            queryString = "书名 LIKE '%" + searchText + "%'";
        } else if (searchType == "作者名") {
            queryString = "作者名 LIKE '%" + searchText + "%'";
        } else if (searchType == "书目编号") {
            queryString = "书目编号 = '" + searchText + "'";
        } else if (searchType == "索书号") {
            queryString = "索书号  LIKE '%" + searchText + "%'";
        } else if (searchType == "出版社") {
            queryString = "出版社 LIKE '%" + searchText + "%'";
        }else if (searchType == "丛书名") {
            queryString = " 丛书名 LIKE '%" + searchText + "%'";
        }


        model->setFilter(queryString);
        model->select();
}
void AdminUi::add()
{
    int newRow = model->rowCount();
    model->insertRow(newRow);
    ui->tableView->selectRow(newRow);
    ui->tableView->setFocus();
}
void AdminUi::Delete()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if (select->hasSelection())
    {
        model->removeRow(select->currentIndex().row());
    }
}
void AdminUi::confirm()
{
    model->submitAll();
}
void AdminUi::cancel()
{
    model->revertAll();
}
void AdminUi::borrowBook()
{
    QString bookID = ui->lineEdit_2->text();
    QString studentID = ui->lineEdit_3->text();
    QString studentName;
    QString bookName;
    int bookStatus;

    query = new QSqlQuery(db2_);
    query->prepare("SELECT 书名, 状态 FROM books WHERE 条码号 = :bookID");
    query->bindValue(":bookID", bookID);

    if (!query->exec() || !query->next())
    {
        QMessageBox::warning(this, "错误", query->lastError().text());
        return;
    }

    bookName = query->value(0).toString();
    bookStatus = query->value(1).toInt();

    // 检查学生信息
    QSqlQuery studentQuery(db2_);
    studentQuery.prepare("SELECT 学生姓名 FROM stuinfo WHERE 一卡通号 = :studentID");
    studentQuery.bindValue(":studentID", studentID);
    if (!studentQuery.exec() || !studentQuery.next())
    {
        QMessageBox::warning(this, "错误", "找不到学生信息!");
        return;
    }
    studentName = studentQuery.value(0).toString();

    if (bookStatus == 1)
    {
        // 书存在
        QSqlQuery updateQuery(db2_);
        updateQuery.prepare("UPDATE books SET 状态 = 0 WHERE 条码号 = :bookID"); // 状态为0
        updateQuery.bindValue(":bookID", bookID);
        if (!updateQuery.exec())
        {
            QMessageBox::warning(this, "错误", updateQuery.lastError().text());
            return;
        }
        // 减少库存
        QSqlQuery decreaseInventoryQuery(db2_);
        decreaseInventoryQuery.prepare("UPDATE books SET 现有数 = 现有数 - 1 WHERE 书名 = :bookName AND 现有数 > 0");
        decreaseInventoryQuery.bindValue(":bookName", bookName);
        if (!decreaseInventoryQuery.exec())
        {
            QMessageBox::warning(this, "错误", decreaseInventoryQuery.lastError().text());
            return;
        }
    }
    else if (bookStatus == 0)
    {
        // 检查是否预定
        QSqlQuery reserveQuery(db2_);
        reserveQuery.prepare("SELECT 一卡通号 FROM reserve WHERE 书名 = :bookName");
        reserveQuery.bindValue(":bookName", bookName);
        if (!reserveQuery.exec() || !reserveQuery.next())
        {
            QMessageBox::warning(this, "错误", "这本书不可借阅!");
            return;
        }
        QString reservedStudentId = reserveQuery.value(0).toString();
        if (reservedStudentId != studentID)
        {
            QMessageBox::warning(this, "错误", "这本书已被其他学生预约!");
            return;
        }
        // 更新书的状态
        QSqlQuery updateQuery(db2_);
        updateQuery.prepare("UPDATE books SET 状态 = 0 WHERE 条码号 = :bookID"); // Setting status to borrowed
        updateQuery.bindValue(":bookID", bookID);
        if (!updateQuery.exec())
        {
            QMessageBox::warning(this, "错误", updateQuery.lastError().text());
            return;
        }
        // 减少库存
        QSqlQuery decreaseInventoryQuery(db2_);
        decreaseInventoryQuery.prepare("UPDATE books SET 现有数 = 现有数 - 1 WHERE 书名 = :bookName AND 现有数 > 0");
        decreaseInventoryQuery.bindValue(":bookName", bookName);
        if (!decreaseInventoryQuery.exec())
        {
            QMessageBox::warning(this, "错误", decreaseInventoryQuery.lastError().text());
            return;
        }
    }
    else
    {
        QMessageBox::warning(this, "错误", "这本书不可借阅!");
        return;
    }

    // 储存相关信息
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime returnDateTime = currentDateTime.addDays(30); // 借书时间是30天
    QSqlQuery insertQuery(db2_);
    insertQuery.prepare("INSERT INTO stucurrent (一卡通号, 学生姓名, 借阅时间, 应还时间, 书名, 条码号,可续借次数) "
                        "VALUES (:studentID, :studentName, :borrowDate, :returnDate, :bookName, :bookCode, :time)");
    insertQuery.bindValue(":studentID", studentID);
    insertQuery.bindValue(":studentName", studentName);
    insertQuery.bindValue(":borrowDate", currentDateTime);
    insertQuery.bindValue(":returnDate", returnDateTime);
    insertQuery.bindValue(":bookName", bookName);
    insertQuery.bindValue(":bookCode", bookID);
    insertQuery.bindValue(":time", 4);
    if (!insertQuery.exec())
    {
        QMessageBox::warning(this, "错误", insertQuery.lastError().text());
        return;
    }
    QMessageBox::information(this, "成功", "借书成功!");
}
void AdminUi::returnBook()
{
    QString bookID = ui->lineEdit_4->text();
    QString studentID = ui->lineEdit_5->text();

    // 检查学生是否借书了
    QSqlQuery checkBorrowedQuery(db2_);
    checkBorrowedQuery.prepare("SELECT 应还时间, 学生姓名 FROM stucurrent WHERE 一卡通号 = :studentID AND 条码号 = :bookID");
    checkBorrowedQuery.bindValue(":studentID", studentID);
    checkBorrowedQuery.bindValue(":bookID", bookID);

    if (!checkBorrowedQuery.exec())
    {
        QMessageBox::warning(this, "错误", checkBorrowedQuery.lastError().text());
        return;
    }

    if (!checkBorrowedQuery.next())
    {
        QMessageBox::warning(this, "错误", "该学生没有借阅这本书或已还书!");
        return;
    }

    QDateTime returnDate = checkBorrowedQuery.value(0).toDateTime();
    QString studentName = checkBorrowedQuery.value(1).toString();
    QDateTime currentDate = QDateTime::currentDateTime();

    // 判断是否超期
    if (currentDate > returnDate)
    {
        int lateDays = returnDate.daysTo(currentDate);
        double fine = lateDays * 1.0; // 每天罚款1元

        // 在violation表中增加违约记录
        QSqlQuery violationQuery(db2_);
        violationQuery.prepare("INSERT INTO violation (一卡通号, 学生姓名, 违约时间, 违约原因) "
                               "VALUES (:studentID, :studentName, :currentDate, '超期还书')");
        violationQuery.bindValue(":studentID", studentID);
        violationQuery.bindValue(":studentName", studentName);
        violationQuery.bindValue(":currentDate", currentDate);

        if (!violationQuery.exec())
        {
            qDebug() << "在violation表中增加记录错误：" << violationQuery.lastError().text();
        }

        QMessageBox::warning(this, "欠款提示", QString("你已超期%1天，需缴纳罚款%2元。").arg(lateDays).arg(fine));
    }

    // 更新books表中的状态
    QSqlQuery updateStatusQuery(db2_);
    updateStatusQuery.prepare("UPDATE books SET 状态 = 1 WHERE 条码号 = :bookID");
    updateStatusQuery.bindValue(":bookID", bookID);

    if (!updateStatusQuery.exec())
    {
        QMessageBox::warning(this, "错误", updateStatusQuery.lastError().text());
        return;
    }

    // 更新books表中的现有数
    QSqlQuery increaseInventoryQuery(db2_);
    increaseInventoryQuery.prepare("UPDATE books SET 现有数 = 现有数 + 1 WHERE 条码号 = :bookID");
    increaseInventoryQuery.bindValue(":bookID", bookID);

    if (!increaseInventoryQuery.exec())
    {
        QMessageBox::warning(this, "错误", increaseInventoryQuery.lastError().text());
        return;
    }

    // 从stucurrent表中删除记录
    QSqlQuery deleteRecordQuery(db2_);
    deleteRecordQuery.prepare("DELETE FROM stucurrent WHERE 一卡通号 = :studentID AND 条码号 = :bookID");
    deleteRecordQuery.bindValue(":studentID", studentID);
    deleteRecordQuery.bindValue(":bookID", bookID);

    if (!deleteRecordQuery.exec())
    {
        QMessageBox::warning(this, "错误", deleteRecordQuery.lastError().text());
        return;
    }

    QMessageBox::information(this, "成功", "还书成功!");
}

AdminUi::~AdminUi()
{
    delete ui;
    if(model)delete model;
    if(query)delete query;
    if(query2)delete query2;
    if(query3)delete query3;


}
