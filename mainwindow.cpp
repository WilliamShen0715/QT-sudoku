#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

Sudoku::Sudoku(){
    for(int i=0;i<81;++i) map[i]=0;
}
Sudoku::Sudoku(const int init_map[]){
    for(int i=0;i<81;++i) map[i]=init_map[i];
}
void Sudoku::setMap(const int set_map[]){
    for(int i=0;i<81;++i) map[i]=set_map[i];
}
int Sudoku::getElement(int i){
    return map[i];
}
bool Sudoku::checkUnity(int arr[]){
    int unity[9];
    for(int i=0;i<9;++i) unity[i]=0;
    for(int i=0;i<9;++i) ++unity[arr[i]-1];
    for(int i=0;i<9;++i){
        if(unity[i]!=1) return false;
    }
    return true;
}
bool Sudoku::isCorrect(){
    bool result;
    int ck_arr[9],location;
    for(int i=0;i<81;i+=9){
        for(int j=0;j<9;++j){
            ck_arr[j]=map[i+j];
        }
        result=checkUnity(ck_arr);
        if(result==false) {
            return false;
        }
    }
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j) ck_arr[j]=map[i+9*j];
        result=checkUnity(ck_arr);
        if(result==false) {
            return false;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0; j<9; ++j){
            location = 27*(i/3) + 3*(i%3)+9*(j/3) + (j%3);
            ck_arr[j] = map[location];
        }
        result = checkUnity(ck_arr);
        if(result==false) {
            return false;
        }
    }
    return true;
}
void Sudoku::setElement(int i,int value){
    map[i]=value;
}
int Sudoku::getFirstZeroIndex(){
    for(int i=0;i<81;++i) if(map[i]==0) return i;
    return -1;
}
bool solve(Sudoku question,Sudoku &answer){
    int firstZero = question.getFirstZeroIndex();
    if(firstZero==-1){
        if(question.isCorrect()){
            answer=question;
            return true;
        }
        else return false;
    }else{
//solve
        for(int i=1;i<=9;++i){
//check middle
            for(int j=10;j<=70;j+=3){
                if(firstZero==j){
                    if(question.getElement(firstZero-10)==j) continue;
                    if(question.getElement(firstZero+10)==j) continue;
                    if(question.getElement(firstZero-8)==j) continue;
                    if(question.getElement(firstZero+8)==j) continue;
                }
                if(j==16||j==43) j+=18;
            }
//check around
            if(firstZero%9!=0) if(question.getElement(firstZero-1)==i) continue;
            if(firstZero%9!=8) if(question.getElement(firstZero+1)==i) continue;
            if(firstZero>8) if(question.getElement(firstZero-9)==i) continue;
            if(firstZero<72) if(question.getElement(firstZero+9)==i) continue;
//solve
            question.setElement(firstZero,i);
            if(solve(question,answer)) return true;
        }
        return false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    Sudoku ques,ans;
    int num[81];
    for(int i=0;i<81;i++){
        int raw = i/9;
        int col = i%9;
        QTableWidgetItem *item = ui->tableWidget->item(raw,col);
        if(item){
            QString inNum = item->text();
            num[i] = inNum.toInt();
        }else{
            num[i]=0;
        }
    }
    ques.setMap(num);
    if(solve(ques,ans)){
            for(int i=0;i<81;++i){
                QString str = QString::number(ans.getElement(i));
                QTableWidgetItem *item = new QTableWidgetItem(str);
                ui->tableWidget->setItem(i/9,i%9,item);
            }
        }else{
            ui->lineEdit->setText("Someting wrong.");
        }
}

void MainWindow::on_pushButton_2_clicked()
{
    int tmplate[81] = {
        8,6,5,3,2,9,4,1,7,
        2,4,3,1,7,5,8,6,9,
        1,9,7,6,8,4,5,2,3,
        3,1,9,2,5,8,6,7,4,
        4,2,6,7,9,1,3,5,8,
        5,7,8,4,3,6,1,9,2,
        7,5,4,9,1,3,2,8,6,
        6,8,2,5,4,7,9,3,1,
        9,3,1,8,6,2,7,4,5};
    for(int i=0;i<81;++i){
        QString str = QString::number(tmplate[i]);
        QTableWidgetItem *item = new QTableWidgetItem(str);
        if(rand()%15==0) ui->tableWidget->setItem(i/9,i%9,0);
        else ui->tableWidget->setItem(i/9,i%9,item);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int tmplate[81] = {
        8,6,5,3,2,9,4,1,7,
        2,4,3,1,7,5,8,6,9,
        1,9,7,6,8,4,5,2,3,
        3,1,9,2,5,8,6,7,4,
        4,2,6,7,9,1,3,5,8,
        5,7,8,4,3,6,1,9,2,
        7,5,4,9,1,3,2,8,6,
        6,8,2,5,4,7,9,3,1,
        9,3,1,8,6,2,7,4,5};
    for(int i=0;i<81;++i){
        QString str = QString::number(tmplate[i]);
        QTableWidgetItem *item = new QTableWidgetItem(str);
        if(rand()%14==0) ui->tableWidget->setItem(i/9,i%9,0);
        else ui->tableWidget->setItem(i/9,i%9,item);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int tmplate[81] = {
        8,6,5,3,2,9,4,1,7,
        2,4,3,1,7,5,8,6,9,
        1,9,7,6,8,4,5,2,3,
        3,1,9,2,5,8,6,7,4,
        4,2,6,7,9,1,3,5,8,
        5,7,8,4,3,6,1,9,2,
        7,5,4,9,1,3,2,8,6,
        6,8,2,5,4,7,9,3,1,
        9,3,1,8,6,2,7,4,5};
    for(int i=0;i<81;++i){
        QString str = QString::number(tmplate[i]);
        QTableWidgetItem *item = new QTableWidgetItem(str);
        if(rand()%13==0) ui->tableWidget->setItem(i/9,i%9,0);
        else ui->tableWidget->setItem(i/9,i%9,item);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int tmplate[81] = {
        8,6,5,3,2,9,4,1,7,
        2,4,3,1,7,5,8,6,9,
        1,9,7,6,8,4,5,2,3,
        3,1,9,2,5,8,6,7,4,
        4,2,6,7,9,1,3,5,8,
        5,7,8,4,3,6,1,9,2,
        7,5,4,9,1,3,2,8,6,
        6,8,2,5,4,7,9,3,1,
        9,3,1,8,6,2,7,4,5};
    for(int i=0;i<81;++i){
        QString str = QString::number(tmplate[i]);
        QTableWidgetItem *item = new QTableWidgetItem(str);
        if(rand()%12==0) ui->tableWidget->setItem(i/9,i%9,0);
        else ui->tableWidget->setItem(i/9,i%9,item);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    int flag=0;
    int check[81];
    int tmplate[81] = {
        8,6,5,3,2,9,4,1,7,
        2,4,3,1,7,5,8,6,9,
        1,9,7,6,8,4,5,2,3,
        3,1,9,2,5,8,6,7,4,
        4,2,6,7,9,1,3,5,8,
        5,7,8,4,3,6,1,9,2,
        7,5,4,9,1,3,2,8,6,
        6,8,2,5,4,7,9,3,1,
        9,3,1,8,6,2,7,4,5};
    for(int i=0;i<81;i++){
        int raw = i/9;
        int col = i%9;
        QTableWidgetItem *item = ui->tableWidget->item(raw,col);
        if(item){
            QString inNum = item->text();
            check[i] = inNum.toInt();
        }else{
            check[i]=0;
        }
    }
    for(int i=0;i<81;i++){
        if(check[i]!=tmplate[i]){
            ui->lineEdit->setText("Lose.");
            flag=1;
            break;
        }
    }
    if(flag==0) ui->lineEdit->setText("Win.");
    else ui->lineEdit->setText("Lose!");
}
