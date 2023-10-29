#include "libraryui.h"
#include "ui_libraryui.h"
#include<QPixmap>
#include <QTableView>
#include<QStandardItemModel>
#include"logindialog.h"
#include<QMessageBox>
#include<QDebug>
#include<QSqlError>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDateTime>

LibraryUi::LibraryUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LibraryUi)
{
    ui->setupUi(this);



    //初始化数据库
    db2 = QSqlDatabase::addDatabase("QMYSQL", "connection2");
   //连接数据库
   db2.setHostName("127.0.0.1");
   db2.setUserName("HWH");
   db2.setPassword("@MySql668931hwh");
   db2.setDatabaseName("login");
    // 初始化 QSqlQuery 对象
   query3 = new QSqlQuery(db2);


    //查询功能
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


   //表格4
   ui->tableView_4->setStyleSheet(
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
   ui->tableView_4->verticalHeader()->setVisible(false);
   ui->tableView_4->horizontalHeader()->setStretchLastSection(true);
   ui->tableView_4->horizontalHeader()->setHighlightSections(false);
   ui->tableView_4->setShowGrid(false);
   ui->tableView_4->setFrameStyle(QFrame::NoFrame);






   //页面跳转
    connect(ui->pushButton_1, &QPushButton::clicked, [this]()
    {
        ui->stackedWidget->setCurrentIndex(0);
    });
    // 设置下拉列表的内容
    ui->comboBox->addItems(QStringList() << "书名" << "作者" << "ISBN" << "索书号" << "出版社"<<"丛书名");
    // 连接查询按钮的点击事件到查询函数
    connect(ui->pushButton_6, &QPushButton::clicked, this, &LibraryUi::searchBook);




    //预约功能
    connect(ui->pushButton_reserve, &QPushButton::clicked, this, &LibraryUi::reserveBook);
     //页面跳转
    connect(ui->pushButton_2, &QPushButton::clicked, [this]()
    {
        ui->stackedWidget->setCurrentIndex(1);
    });



    //当前状态功能
    connect(ui->pushButton_7, &QPushButton::clicked, this, &LibraryUi::updateCurrentStatus);
    connect(ui->pushButton, &QPushButton::clicked, this, &LibraryUi::borrowAgain);






    //书籍推荐
     connect(ui->pushButton_3, &QPushButton::clicked, [this]()
     {
             ui->stackedWidget->setCurrentIndex(2);
             recommend();

         });








    //报失功能
    //页面跳转
     connect(ui->pushButton_4, &QPushButton::clicked, [this]()
     {
         ui->stackedWidget->setCurrentIndex(3);
     });
    // 报失键
    connect(ui->pushButton_8, &QPushButton::clicked, this, &LibraryUi::reportLostBook);
}
void LibraryUi::recommend()
{
    model4x = new QSqlTableModel(this,db2);
    model4x->setTable("history");
    model4x->select();
    model4x->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_4->setModel(model4x);
    model4x->select();


}

void LibraryUi::initializeDb()
{


    if(!db2.open())//数据库打开失败
    {
        QMessageBox::warning(this,"错误",db2.lastError().text());
        qDebug()<<db2.lastError().text();
        return;
    }
    else
    {
        //创建只读数据库模型


        query3->prepare("SELECT * FROM stuinfo WHERE 一卡通号 = :cardNum");
        query3->bindValue(":cardNum", cardnumber);

        if (query3->exec())
        {
            queryModel = new QSqlQueryModel(this);
            queryModel->setQuery(*query3);
            ui->tableView->setModel(queryModel);

            //表格1设计
            ui->tableView->setColumnHidden(1, true);
            ui->tableView->setStyleSheet(
                "QTableView {"
                "   selection-background-color: #87bdd8;"  // 设置选择行的背景颜色
                "   gridline-color: #c1c1c1;"              // 设置网格线颜色
                "   background-color: #f5f5f5;"            // 设置背景色
                "}"
                "QTableView QHeaderView::section {"
                "   background-color: #3e3e3e;"            // 设置头部背景色
                "   color: white;"                         // 设置头部文字颜色
                "   padding: 5px;"                         // 设置头部内边距
                "   border: 1px solid #6c6c6c;"            // 设置头部边框
                "   font-weight: bold;"                    // 设置头部字体为粗体
                "}"
            );
            ui->tableView->horizontalHeader()->setStretchLastSection(true);  // 伸展最后一列
            ui->tableView->verticalHeader()->setStretchLastSection(true);    // 伸展最后一行
            ui->tableView->horizontalHeader()->setStyleSheet(R"(
                QHeaderView::section {
                    color: white;
                    border: none;
                    font-size: 20px;
                    font-family: "微软雅黑";
                    background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255, 1), stop:1 rgba(52, 246, 177, 1));
                    padding-top: 5px;
                    padding-bottom: 5px;
                }
            )");
            ui->tableView->resizeColumnsToContents();
            ui->tableView->setRowHeight(50,40);

           ui->tableView->verticalHeader()->setVisible(false);
            ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ui->tableView->viewport()->setStyleSheet("background-color: lightblue;");

        }
        else
        {
            qDebug() << "Error querying database: " << query3->lastError();
        }
    }
}

void  LibraryUi::searchBook()
{
    //查询界面

    QString searchType = ui->comboBox->currentText();
    QString searchText = ui->lineEdit->text();


    QString queryString;

    // 根据选项设置不同的查询语句
    if (searchType == "书名") {
        queryString = "SELECT * FROM books WHERE 书名 LIKE '%" + searchText + "%'";
    } else if (searchType == "作者") {
        queryString = "SELECT * FROM books WHERE 作者名 LIKE '%" + searchText + "%'";
    } else if (searchType == "书目编号") {
        queryString = "SELECT * FROM books WHERE 书目编号 = '" + searchText + "'";
    } else if (searchType == "索书号") {
        queryString = "SELECT * FROM books WHERE 索书号  LIKE '%" + searchText + "%'";
    } else if (searchType == "出版社") {
        queryString = "SELECT * FROM books WHERE 出版社 LIKE '%" + searchText + "%'";
    }else if (searchType == "丛书名") {
        queryString = "SELECT * FROM books WHERE 丛书名 LIKE '%" + searchText + "%'";
    }

    // 执行查询
    if (query3->exec(queryString)) {
        // 使用查询模型展示结果
        QSqlQueryModel *model2 = new QSqlQueryModel;
        model2->setQuery(*query3);
        ui->tableView_2->setModel(model2);


    } else {
        // 输出查询错误
        qDebug() << query3->lastError().text();
    }
}
void LibraryUi::reserveBook()
{
    query3 = new QSqlQuery(db2);

    int selectedRow = ui->tableView_2->currentIndex().row();
    if (selectedRow < 0)
    {
        QMessageBox::warning(this, "错误", "请先选择一个书籍进行预约！");
        return;
    }

    QString bookIndex = ui->tableView_2->model()->data(ui->tableView_2->model()->index(selectedRow, 1)).toString();  // 索书号
    QString bookName = ui->tableView_2->model()->data(ui->tableView_2->model()->index(selectedRow, 0)).toString();    // 书名
    QString bookID = ui->tableView_2->model()->data(ui->tableView_2->model()->index(selectedRow, 10)).toString();    // 书目编号

    // 检查用户违章记录
    query3->prepare("SELECT 违章记录 FROM stuinfo WHERE 一卡通号 = :userCardNumber");
    query3->bindValue(":userCardNumber", cardnumber);
    if (!query3->exec())
    {
        qDebug() << "错误1";
        qDebug() << query3->lastError().text();
        return;
    }
    if (!query3->next() || query3->value(0).toInt() > 0)
    {
        QMessageBox::warning(this, "错误", "你有违章记录，无法预约书籍！");
        return;
    }

    // 检查书的状态
    query3->prepare("SELECT 状态 FROM books WHERE 索书号 = :bookIndex");
    query3->bindValue(":bookIndex", bookIndex);
    if (!query3->exec())
    {
        qDebug() << "错误2";
        qDebug() << query3->lastError().text();
        return;
    }
    if (!query3->next() || query3->value(0).toInt() == 0)
    {
        QMessageBox::warning(this, "错误", "该书已被预约或已被租借！");
        return;
    }

    // 更新书的状态为被预约
     query3->prepare("UPDATE books SET 状态 = 0, 现有数 = 现有数 - 1 WHERE 索书号 = :bookIndexUpdate");
    query3->bindValue(":bookIndexUpdate", bookIndex);
    if (!query3->exec())
    {
        qDebug() << "错误3";
        qDebug() << query3->lastError().text();
        return;
    }

    // 在reserve表中增加预约记录
    query3->prepare("INSERT INTO reserve (一卡通号, 索书号, 学生姓名, 书名, 图书编号, 预约时间) VALUES (:cardnumber, :bookIndex, (SELECT 学生姓名 FROM stuinfo WHERE 一卡通号 = :cardnumber), :bookName, :bookID, :reserveTime)");
    query3->bindValue(":cardnumber", cardnumber);
    query3->bindValue(":bookIndex", bookIndex);
    query3->bindValue(":bookName", bookName);
    query3->bindValue(":bookID", bookID);
    query3->bindValue(":reserveTime", QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss.zzz"));
    if (!query3->exec())
    {
        qDebug() << "错误4";
        qDebug() << query3->lastError().text();
        return;
    }

    QMessageBox::information(this, "成功", "预约成功！");
}

void LibraryUi::updateCurrentStatus()
{
    // 使用存有的一卡通号进行查询
    QString queryString = QString("SELECT 条码号, 一卡通号, 借阅时间, 应还时间, 书名, 可续借次数 FROM stucurrent WHERE 一卡通号 = '%1'").arg(cardnumber);

    if (query3->exec(queryString)) {
        // 使用查询模型展示结果
        QSqlQueryModel *modelCurrent = new QSqlQueryModel;
        modelCurrent->setQuery(*query3);
        ui->tableView_3->setModel(modelCurrent);
        ui->tableView_3->hideColumn(1);


    } else {
        // 输出查询错误
        qDebug() << query3->lastError().text();
    }
}
void LibraryUi::borrowAgain()
{
    QModelIndex currentIndex = ui->tableView_3->currentIndex();
       if (!currentIndex.isValid()) {
           QMessageBox::warning(this, "警告", "请选择一个记录以续借！");
           return;
       }

       QString borrowTimeStr = ui->tableView_3->model()->data(ui->tableView_3->model()->index(currentIndex.row(), 2)).toString();
       QDateTime borrowTime = QDateTime::fromString(borrowTimeStr, "yyyy-MM-ddTHH:mm:ss.zzz");
       QDateTime now = QDateTime::currentDateTime();
       qDebug()<<borrowTime.daysTo(now);

       if (borrowTime.daysTo(now) <= 25) {
           QMessageBox::warning(this, "警告", "尚未到达续借时间！");
           return;
       }

       QDateTime newReturnTime = borrowTime.addDays(55); // 增加的30天
       QString barCode = ui->tableView_3->model()->data(ui->tableView_3->model()->index(currentIndex.row(), 0)).toString();

       int renewTimes = ui->tableView_3->model()->data(ui->tableView_3->model()->index(currentIndex.row(), 5)).toInt(); // 取得可续借次数
       renewTimes--;

       if (!db2.isOpen() && !db2.open()) {
           QMessageBox::critical(this, "错误", "数据库连接失败：" + db2.lastError().text());
           return;
       }

       query5 = new QSqlQuery(db2);
       query5->prepare("UPDATE stucurrent SET 应还时间=:newReturnTime, 可续借次数=:renewTimes WHERE 条码号=:barCode");
       query5->bindValue(":newReturnTime", newReturnTime.toString("yyyy-MM-ddTHH:mm:ss.zzz"));
       query5->bindValue(":renewTimes", renewTimes);
       query5->bindValue(":barCode", barCode);

       if (!query5->exec()) {
           QMessageBox::warning(this, "错误", query5->lastError().text());
           return;
       }

       updateCurrentStatus(); // 刷新视图
       QMessageBox::information(this, "信息", "续借成功！");
}


void LibraryUi::reportLostBook()
{
    // 1. 从 QLineEdit 获取书籍的条码号
    QString bookLog = ui->lineEdit_2->text().trimmed();

    if (bookLog.isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入书籍条码号！");
        return;
    }

    // 2. 检查用户是否借阅了这本书
    query3->prepare("SELECT COUNT(*) FROM stucurrent WHERE 一卡通号 = :cardNumber AND 条码号 = :log");
    query3->bindValue(":cardNumber", cardnumber);
    query3->bindValue(":log", bookLog);

    if (!query3->exec())
    {
        qDebug() << "数据库查询错误：" << query3->lastError().text();
        return;
    }

    if (query3->next() && query3->value(0).toInt() > 0)
    {
        // 3. 允许用户报失，且将用户的违章次数增加1
        query3->prepare("UPDATE stuinfo SET 违章记录 = 违章记录 + 1 WHERE 一卡通号 = :cardNumber");
        query3->bindValue(":cardNumber", cardnumber);

        if (!query3->exec())
        {
            qDebug() << "更新违章记录错误：" << query3->lastError().text();
            return;
        }

        // 4. 获取学生姓名
        QString studentName;
        query3->prepare("SELECT 学生姓名 FROM stuinfo WHERE 一卡通号 = :cardNumber");
        query3->bindValue(":cardNumber", cardnumber);
        if (query3->exec() && query3->next())
        {
            studentName = query3->value("学生姓名").toString();
        }
        else
        {
            qDebug() << "查询学生姓名错误：" << query3->lastError().text();
            return;
        }

        // 5. 在violation表中增加违约记录
        query3->prepare("INSERT INTO violation (一卡通号, 学生姓名, 违约时间, 违约原因) "
                        "VALUES (:cardNumber, :studentName, :violationTime, '书籍报失')");
        query3->bindValue(":cardNumber", cardnumber);
        query3->bindValue(":studentName", studentName);
        query3->bindValue(":violationTime", QDateTime::currentDateTime());

        if (!query3->exec())
        {
            qDebug() << "在violation表中增加记录错误：" << query3->lastError().text();
            return;
        }

        QMessageBox::information(this, "成功", "书籍报失成功，你的违章记录已更新。");

    }
    else
    {
        // 6. 提示用户并返回
        QMessageBox::warning(this, "错误", "你没有借阅这本书，不能报失。");
    }
}


void LibraryUi::setInfo(const QString&cardnumber,const QString&password)
{
    this->cardnumber = cardnumber;
    this->password = password;
    initializeDb() ;

}

LibraryUi::~LibraryUi()
{
    if (QSqlDatabase::contains("connection2"))
       {
           QSqlDatabase::database("connection2").close();
           QSqlDatabase::removeDatabase("connection2");
       }
    if (QSqlDatabase::contains("connection3"))
       {
           QSqlDatabase::database("connection3").close();
           QSqlDatabase::removeDatabase("connection3");
       }
    delete ui;
    if(query3)delete query3;
    if(queryModel)delete queryModel;

}
