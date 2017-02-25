#include "GlobalApplication.h"
#include <QKeyEvent>
#include <QDebug>

MyApplication::MyApplication(int &argc, char **argv) :
QApplication(argc, argv), widget(0)
{

}

void MyApplication::setWindowInstance(QWidget *wid)
{
	widget = wid;
}

bool MyApplication::notify(QObject *obj, QEvent *e)
{
	const QMetaObject* objMeta = obj->metaObject();
	QString clName = objMeta->className();
	if ((e->type() == QEvent::KeyPress) && (clName != "QLineEdit"))
	{
		if (widget)
		{
			QKeyEvent*keyEvent = static_cast<QKeyEvent *>(e);
			widget->keyPress(keyEvent);
		}
	}
	return QApplication::notify(obj, e);
}