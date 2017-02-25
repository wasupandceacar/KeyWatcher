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

	//���̲�������
	int key[41];

	//���̼�������
	int keycount[44];

	//���̲�������
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
	//����ֵ��
	int linenum;
	int keynum;

	//ʵ�ʽ�����
	int prognum;

	//�������б�
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

	//��ֵ���õ�ѡ������
	QCheckBox *keybox[41];

	//���̿ؼ�����
	QLabel *label[44];

	//����ͼ��ؼ�����
	QLabel *img[41];

	//��ʱ��
	QTimer *timer;
	QLabel *timelabel;
	int second;
	int minute;
	int hour;
	double APM;
};

#endif
