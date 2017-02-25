#define QDBG qDebug()<<__FILE__<<__FUNCTION__<<__LINE__

#include <QtWidgets/QApplication>

class MyApplication : public QApplication
{
public:
	MyApplication(int&argc, char **argv);
	bool notify(QObject*, QEvent *);
	void setWindowInstance(QWidget *wid);
private:
	QWidget *widget;//保存一个你窗体的指针
};