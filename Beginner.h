#ifndef BEGINNER_H
#define BEGINNER_H

#pragma execution_character_set("utf-8")

#include <QLabel>
#include <QFile>
#include <QAction>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>
#include <QDir>
#include <QFileDialog>
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QMenu>
#include <QMenuBar>
#include <QListWidget>  
#include <QListWidgetItem>
#include <QLineEdit>
#include <Windows.h> 

class Beginner : public QWidget
{
	Q_OBJECT

public :
	Beginner(QWidget *parent = 0);

	void closeEvent(QCloseEvent *event);

	void timeflush();

	void stoppedtimeflush();

	void K(int i);

	void I(int i);

	//键盘参数数组
	int key[41];

	//键盘计数数组
	int keycount[44];

	//进程参数数组
	QString progname[100];

private slots:
	void Write(QString str, QString filename, QString content);

	QString Read(QString path, QString filename);

	void thtkclicked();

	QString List(QString str);

	void flyingrecord();

	void initKey();

	void initKeysetting();

	void resetKeysetting();

	void setKeysetting();

	int setHeight();

	void initProg();

	void initProgsetting();

	void initaddProg();

	void addProg();

	void delProg();

	void setProgsetting();

	void addimg(int num, int x, int y);

	void addimgs();

	void addlabel(int num, int x, int y);

	void addlabels();

	void check();

private:
	//检测键值数
	int linenum;
	int keynum;

	//实际进程数
	int prognum;

	//检测进程列表
	QListWidget *proglist;
	QListWidgetItem *progs[100];

	QPushButton *button;
	QFileDialog *fd;
	QDialog *dialog;
	QLabel *info;
	QLabel *proginfo;
	QDialog *keysetting;
	QDialog *progsetting;
	QDialog *addprog;
	QMenu *menu;
	QAction *keyact;
	QAction *progact;
	QLineEdit *progline;
	QMenuBar *total;

	//键值设置单选框数组
	QCheckBox *keybox[41];

	//键盘控件数组
	QLabel *label[44];

	//键盘图标控件数组
	QLabel *img[41];

	//计时器
	QTimer *timer;
	QLabel *timelabel;
	int second;
	int minute;
	int hour;
	double APM;
};

#endif
