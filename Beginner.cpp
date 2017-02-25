#include "Beginner.h"

#include <string>

#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QPixmap>
#include <QtCore>
#include <QCloseEvent> 
#include <Windows.h> 
#include <tlhelp32.h>
#include "Psapi.h"

Beginner *begin;

HHOOK keyHook = NULL;

int hooked = 0;

using std::wstring;

//卸载钩子  
void unHook()
{
	UnhookWindowsHookEx(keyHook);
}

//键盘钩子过程  
LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *)lParam;
	DWORD keycode[44] = {
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z',
		VK_CONTROL,
		VK_LSHIFT,
		VK_RSHIFT,
		VK_RETURN,
		VK_UP,
		VK_DOWN,
		VK_LEFT,
		VK_RIGHT
	};
	for (int i = 0; i < 44; i++){
		if (pkbhs->vkCode == keycode[i]){
			if (i == 40 || i == 41 || i == 42 || i == 43){
				if (begin->key[40]){
					if (wParam == WM_KEYDOWN){
						if (begin->keycount[i] == 0){
							begin->keycount[i]++;
						}
						begin->I(i + 44);
						begin->K(i);
					}
					if (wParam == WM_KEYUP){
						begin->keycount[i]++;
						begin->I(i);
					}
					break;
				}
			}
			else{
				if (begin->key[i]){
					if (wParam == WM_KEYDOWN){
						if (begin->keycount[i] == 0){
							begin->keycount[i]++;
						}
						begin->I(i + 44);
						begin->K(i);
					}
					if (wParam == WM_KEYUP){
						begin->keycount[i]++;
						begin->I(i);
					}
					break;
				}
			}
		}
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

//安装钩子
void setHook()
{
	//底层键盘钩子  
	keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyProc, GetModuleHandle(NULL), 0);
}

//检查进程
int CheckProcess(LPCTSTR name)
{
	PROCESSENTRY32 pe;
	DWORD id = 0;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe))
		return 0;
	do
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot, &pe) == FALSE)
			return 0;
		if (lstrcmp(pe.szExeFile, name) == 0)
		{
			CloseHandle(hSnapshot);
			return 1;
		}
	} while (1);
}

//检查所有进程
void Beginner::check(){
	int judge = 1;
	for (int i = 0; i < prognum; i++){
		wstring str = progname[i].toStdWString() + L".exe";
		LPCTSTR namefxtz = str.c_str();
		if (CheckProcess(namefxtz)){
			begin->setWindowTitle(progname[i]+"运行中");
			judge = 0;
			if (!hooked){
				setHook();
				hooked = 1;
			}
			begin->timeflush();
		}
	}
	if (judge){
		begin->setWindowTitle("无游戏");
		if (hooked){
			unHook();
			hooked = 0;
		}
		begin->stoppedtimeflush();
	}
}

//写文件
void Beginner::Write(QString path, QString filename, QString content){
	QFile file(path.append(filename));

	file.open(QIODevice::WriteOnly);

	QTextStream txtOutput(&file);

	txtOutput << content;
	txtOutput.flush();

	file.close();
}

//读文件
QString Beginner::Read(QString path, QString filename){
	QFile file(path.append(filename));
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream txtInput(&file);
	QString lineStr = txtInput.readLine();
	file.close();
	return lineStr;
}

//thtk文件列表
void Beginner::thtkclicked(){
	QString str = fd->getExistingDirectory();
	Write(str, tr("\\zzz.txt"), List(str));
}

//读取路径的文件列表
QString Beginner::List(QString str){
	QDir dir(str);
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	dir.setSorting(QDir::Size | QDir::Reversed);

	QFileInfoList list = dir.entryInfoList();
	QString strlist = "";
	for (int i = 0; i < list.size(); ++i) {
		strlist.append(list.at(i).filePath());
		strlist.append(" ");
	}
	return strlist;
}

//键盘计数器
void Beginner::K(int i){
	QString name[44] = {
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Ctrl",
		"左Shift",
		"右Shift",
		"回车",
		"上键",
		"下键",
		"左键",
		"右键"
	};
	for (int j = 0; j < 44; j++){
		if (i == j){
			if (i == 40 || i == 41 || i == 42 || i == 43){
				if (key[40]){
					label[i]->setText((name[i] + "：%1次").arg(keycount[i]));
				}
			}else{
				if (key[i]){
					label[i]->setText((name[i] + "：%1次").arg(keycount[i]));
				}
			}
		}
	}
}

//键盘图标修改
void Beginner::I(int i){
	QString name[44] = {
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Ctrl",
		"LeftShift",
		"RightShift",
		"Enter",
		"Direction",
		"Direction",
		"Direction",
		"Direction"
	};
	QString clickname[44] = {
		"1R",
		"2R",
		"3R",
		"4R",
		"5R",
		"6R",
		"7R",
		"8R",
		"9R",
		"0R",
		"AR",
		"BR",
		"CR",
		"DR",
		"ER",
		"FR",
		"GR",
		"HR",
		"IR",
		"JR",
		"KR",
		"LR",
		"MR",
		"NR",
		"OR",
		"PR",
		"QR",
		"RR",
		"SR",
		"TR",
		"UR",
		"VR",
		"WR",
		"XR",
		"YR",
		"ZR",
		"CtrlR",
		"LeftShiftR",
		"RightShiftR",
		"EnterR",
		"DirectionUp",
		"DirectionDown",
		"DirectionLeft",
		"DirectionRight"
	};
	for (int j = 0; j < 88; j++){
		if (i == j){
			if (i < 44){
				if (i == 40 || i == 41 || i == 42 || i == 43){
					if (key[40]){
						img[40]->setPixmap(QPixmap(("imgs/" + name[i] + ".jpg")));
					}
				}
				else{
					if (key[i]){
						img[i]->setPixmap(QPixmap(("imgs/" + name[i] + ".jpg")));
					}
				}
			}else{
				if (i == 84 || i == 85 || i == 86 || i == 87){
					if (key[40]){
						img[40]->setPixmap(QPixmap(("imgs/" + clickname[i - 44] + ".jpg")));
					}
				}
				else{
					if (key[i - 44]){
						img[i - 44]->setPixmap(QPixmap(("imgs/" + clickname[i - 44] + ".jpg")));
					}
				}
			}
		}
	}
}

//信息刷新
void Beginner::timeflush(){
	if (second == 59){
		second = 0;
		if (minute == 59){
			minute = 0;
			hour++;
		}
		else{
			minute++;
		}
	}
	else{
		second++;
	}
	double sumtime = second + 60 * minute + 3600 * hour;
	double sumaction = 0;
	for (int i = 0; i < 44; i++){
		sumaction += keycount[i];
	}
	APM = 60 * sumaction / sumtime;
	timelabel->setText(tr("%1小时%2分%3秒 APM:%4").arg(hour).arg(minute).arg(second).arg(APM));
}

//停止信息刷新
void Beginner::stoppedtimeflush(){
	timelabel->setText(tr("停止中  %1小时%2分%3秒").arg(hour).arg(minute).arg(second));
}

//存储飞行记录
void Beginner::flyingrecord(){
	QString str = fd->getExistingDirectory();
	QDateTime time = QDateTime::currentDateTime();
	QString currenttime = "/" + time.toString("yyyy年M月d日 hh-mm-ss") + ".txt";
	QString lastingtime = tr("时间：%1小时%2分%3秒 平均APM：%4").arg(hour).arg(minute).arg(second).arg(APM);
	Write(str, currenttime, lastingtime);
	if (str != ""){
		Write(QCoreApplication::applicationDirPath(), "/pathsetting.txt", str);
		info->setText("保存在 " + str);
		dialog->setWindowTitle("已保存");
		dialog->show();
	}
	else{
		info->setText("未保存记录");
		dialog->setWindowTitle("未保存");
		dialog->show();
	}
}

//关闭窗口事件
void Beginner::closeEvent(QCloseEvent *event){
	QFile setting(QCoreApplication::applicationDirPath().append("/pathsetting.txt"));
	if (setting.exists()){
		fd->setDirectory(Read(QCoreApplication::applicationDirPath(), "/pathsetting.txt").append("/"));
	}
	flyingrecord();
}

//初始化key数组和数目
void Beginner::initKey(){
	QFile setting(QCoreApplication::applicationDirPath().append("/keysetting.txt"));
	if (setting.exists()){
		QString str = Read(QCoreApplication::applicationDirPath(), "/keysetting.txt");
		QStringList list = str.split(";");
		for (int i = 0; i < 41; i++){
			key[i] = list.at(i).toInt();
		}
	}else{
		for (int i = 0; i < 41; i++){
			key[i] = 0;
		}
	}
	keynum = 0;
	linenum = 0;
	for (int i = 0; i < 37; i++){
		if (key[i]){
			linenum++;
		}
	}
	for (int j = 37; j < 40; j++){
		if (key[j]){
			linenum+=3;
		}
	}
	for (int k = 0; k < 40; k++){
		if (key[k]){
			keynum++;
		}
	}
	if (key[40]){
		keynum += 4;
	}
}

//键值设置初始化
void Beginner::initKeysetting(){
	initKey();
	keysetting = new QDialog;
	keysetting->setWindowTitle("按键设置");
	keysetting->setFixedSize(360, 240);
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	keysetting->move((width - 360) / 2, (height - 240) / 2);
	keysetting->setWindowFlags(Qt::WindowCloseButtonHint);
	QString name[41] = { 
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Ctrl",
		"左Shift",
		"右Shift",
		"回车",
		"方向键"
	};
	for (int i = 0; i < 41; i++){
		keybox[i] = new QCheckBox(name[i], keysetting);
		keybox[i]->setGeometry(QRect(5 + (i % 6) * 60, i / 6 * 30, 60, 30));
		if (key[i]){
			keybox[i]->setChecked(true);
		}else{
			keybox[i]->setChecked(false);
		}
	}
	QPushButton *confirm = new QPushButton("确定", keysetting);
	confirm->setGeometry(QRect(80, 210, 70, 30));
	QPushButton *reset = new QPushButton("重置", keysetting);
	reset->setGeometry(QRect(210, 210, 70, 30));
	connect(confirm, SIGNAL(clicked()), this, SLOT(setKeysetting()));
	connect(reset, SIGNAL(clicked()), this, SLOT(resetKeysetting()));
	keysetting->show();
}

//保存键值设置
void Beginner::setKeysetting(){
	QString str = "";
	for (int i = 0; i < 41; i++){
		if (keybox[i]->isChecked()){
			str += "1;";
		}else{
			str += "0;";
		}
		Write(QCoreApplication::applicationDirPath(), "/keysetting.txt", str);
	}
	keysetting->close();
	qApp->quit();
	QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

//清空键值设置
void Beginner::resetKeysetting(){
	for (int i = 0; i < 41; i++){
		keybox[i]->setChecked(false);
	}
}

//计算程序高度
int Beginner::setHeight(){
	int height = 50;
	height += 40 * ((linenum+2)/3);
	if (key[40]){
		height += 45;
	}
	height += 20;
	height += 20 * keynum;
	height += 60;
	return height;
}

//添加图像
void Beginner::addimg(int num, int x, int y){
	img[num] = new QLabel(this);
	QString name[41] = {
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Ctrl",
		"LeftShift",
		"RightShift",
		"Enter",
		"Direction"
	};
	img[num]->setPixmap(QPixmap(("imgs/"+name[num]+".jpg")));
	if (num == 37 || num == 38){
		img[num]->setGeometry(QRect(x, y, 83, 34));
	}else if (num == 39){
		img[num]->setGeometry(QRect(x, y, 64, 34));
	}else if (num == 40){
		img[num]->setGeometry(QRect(x, y, 112, 39));
	}else{
		img[num]->setGeometry(QRect(x, y, 35, 34));
	}
}

//添加所有图像
void Beginner::addimgs(){
	int currentHeight = 50;
	int row = 0;
	if (key[40]){
		addimg(40, 15, currentHeight);
		currentHeight += 45;
	}
	for (int i = 37; i < 40; i++){
		if (key[i]){
			addimg(i, 15, currentHeight);
			currentHeight += 40;
		}
	}
	for (int j = 0; j < 37; j++){
		if (key[j]){
			if (row == 3){
				row = 0;
				currentHeight += 40;
				addimg(j, 15, currentHeight);
			}else{
				addimg(j, 15 + 40 * row, currentHeight);
				row++;
			}
		}
	}
}

//添加标签
void Beginner::addlabel(int num, int x, int y){
	label[num] = new QLabel(this);
	QString name[44] = {
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Ctrl",
		"左Shift",
		"右Shift",
		"回车",
		"上键",
		"下键",
		"左键", 
		"右键"
	};
	label[num]->setText((name[num]+"：0次"));
	label[num]->setGeometry(QRect(x, y, 110, 20));
}

//添加所有标签
void Beginner::addlabels(){
	int currentHeight = 50;
	currentHeight += 40 * ((linenum + 2) / 3);
	if (key[40]){
		currentHeight += 45;
	}
	currentHeight += 20;
	if (key[40]){
		addlabel(40, 15, currentHeight);
		currentHeight += 20;
		addlabel(41, 15, currentHeight);
		currentHeight += 20;
		addlabel(42, 15, currentHeight);
		currentHeight += 20;
		addlabel(43, 15, currentHeight);
		currentHeight += 20;
	}
	for (int i = 0; i < 40; i++){
		if (key[i]){
			addlabel(i, 15, currentHeight);
			currentHeight += 20;
		}
	}
}

//程序数目初始化
void Beginner::initProg(){
	QFile setting(QCoreApplication::applicationDirPath().append("/progsetting.txt"));
	if (setting.exists()){
		QString str = Read(QCoreApplication::applicationDirPath(), "/progsetting.txt");
		QStringList list = str.split(";");
		prognum = list.length() - 1;
		for (int i = 0; i < prognum; i++){
			progname[i] = list.at(i);
		}
	}
}

//程序设置初始化
void Beginner::initProgsetting(){
	progsetting = new QDialog;
	progsetting->setWindowTitle("进程设置");
	progsetting->setFixedSize(200, 140);
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	progsetting->move((width - 200) / 2, (height - 140) / 2);
	progsetting->setWindowFlags(Qt::WindowCloseButtonHint);
	proglist = new QListWidget(progsetting);
	proglist->setGeometry(QRect(0, 20, 160, 120));
	QFile setting(QCoreApplication::applicationDirPath().append("/progsetting.txt"));
	if (setting.exists()){
		QString str = Read(QCoreApplication::applicationDirPath(), "/progsetting.txt");
		QStringList list = str.split(";");
		prognum = list.length() - 1;
		for (int i = 0; i < prognum; i++){
			progs[i] = new QListWidgetItem(list.at(i), proglist);
		}
	}
	if (prognum){
		proglist->setItemSelected(proglist->item(0), true);
	}
	QPushButton *add = new QPushButton("新增", progsetting);
	add->setGeometry(QRect(160, 0, 40, 25));
	QPushButton *del = new QPushButton("删除", progsetting);
	del->setGeometry(QRect(160, 25, 40, 25));
	proginfo = new QLabel(progsetting);
	proginfo->setText("已监控" + QString::number(prognum) + "个程序（最多100个）");
	proginfo->setGeometry(QRect(0, 0, 160, 20));
	QPushButton *confirm = new QPushButton("确定", progsetting);
	confirm->setGeometry(QRect(160, 115, 40, 25));
	connect(add, SIGNAL(clicked()), this, SLOT(initaddProg()));
	connect(del, SIGNAL(clicked()), this, SLOT(delProg()));
	connect(confirm, SIGNAL(clicked()), this, SLOT(setProgsetting()));
	progsetting->show();
}

//增加进程初始化
void Beginner::initaddProg(){
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	if (prognum >= 100){
		info->setText("监控达到上限");
		dialog->setWindowTitle("溢出");
		dialog->show();
	}else{
		addprog = new QDialog;
		addprog->setWindowTitle("增加进程");
		addprog->setFixedSize(160, 40);
		addprog->move((width - 160) / 2, (height - 40) / 2);
		addprog->setWindowFlags(Qt::WindowCloseButtonHint);
		progline = new QLineEdit(addprog);
		progline->setGeometry(QRect(10, 10, 90, 25));
		QPushButton *con = new QPushButton("确定", addprog);
		con->setGeometry(QRect(110, 10, 40, 25));
		connect(con, SIGNAL(clicked()), this, SLOT(addProg()));
		addprog->show();
	}
}

//增加进程
void Beginner::addProg(){
	QString name = progline->text();
	initProg();
	if (name != ""){
		progs[prognum] = new QListWidgetItem(name, proglist);
		progname[prognum] = name;
		prognum++;
	}
	QFile setting(QCoreApplication::applicationDirPath().append("/progsetting.txt"));
	if (setting.exists()){
		QString str = Read(QCoreApplication::applicationDirPath(), "/progsetting.txt");
		str += name;
		str += ";";
		Write(QCoreApplication::applicationDirPath(), "/progsetting.txt", str);
	}
	else{
		QString str = name + ";";
		Write(QCoreApplication::applicationDirPath(), "/progsetting.txt", str);
	}
	proginfo->setText("已监控" + QString::number(prognum) + "个程序（最多100个）");
	addprog->close();
}

//删除进程
void Beginner::delProg(){
	int current = proglist->currentRow();
	initProg();
	for (int i = current + 1; i < prognum; i++){
		progs[i - 1] = progs[i];
	}
	for (int i = current + 1; i < prognum; i++){
		progname[i - 1] = progname[i];
	}
	QFile setting(QCoreApplication::applicationDirPath().append("/progsetting.txt"));
	if (setting.exists()){
		QString str = Read(QCoreApplication::applicationDirPath(), "/progsetting.txt");
		QStringList list = str.split(";");
		str = "";
		for (int i = 0; i < current; i++){
			str += list.at(i);
			str += ";";
		}
		for (int j = current + 1; j < prognum; j++){
			str += list.at(j);
			str += ";";
		}
		Write(QCoreApplication::applicationDirPath(), "/progsetting.txt", str);
	}
	proglist->takeItem(current);
	initProg();
	proginfo->setText("已监控" + QString::number(prognum) + "个程序（最多100个）");
}

//保存进程设置
void Beginner::setProgsetting(){
	progsetting->close();
}

//构造函数
Beginner::Beginner(QWidget *parent)
	: QWidget(parent)
{
	begin = this;

	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);

	initKey();
	addimgs();
	addlabels();

	initProg();

	for (int i = 0; i < 44; i++){
		keycount[i] = 0;
	}

	//窗口初始化
	this->setWindowTitle("无游戏");
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	this->setWindowIcon(QIcon(":/icon.ico"));
	this->setWindowOpacity(0.4);
	this->setFixedSize(150, setHeight());
	this->move((width - 150) / 2, (height - setHeight()) / 2);

	button = new QPushButton;
	button->setText(tr("生成"));

	fd = new QFileDialog(this, "选择存储记录的文件夹", "C:/");
	fd->setFileMode(QFileDialog::DirectoryOnly);
	fd->move((width - fd->width()) / 2, (height - fd->height()) / 2);

	dialog = new QDialog;
	dialog->setFixedSize(120, 60);
	dialog->setWindowFlags(Qt::WindowCloseButtonHint);
	info = new QLabel(dialog);
	info->setGeometry(QRect(15, 22, 105, 16));
	dialog->move((width - 120) / 2, (height - 60) / 2);

	keyact = new QAction(QIcon("imgs/pusheen1.png"), "按键");
	progact = new QAction(QIcon("imgs/pusheen2.png"),  "进程");
	menu = new QMenu("设置");
	menu->addAction(keyact);
	menu->addAction(progact);
	total = new QMenuBar(this);
	total->addMenu(menu);
	connect(keyact, SIGNAL(triggered()), this, SLOT(initKeysetting()));
	connect(progact, SIGNAL(triggered()), this, SLOT(initProgsetting()));

	//计数器初始化
	timer = new QTimer(this);
	timer->start(1000);
	second = 0;
	minute = 0;
	hour = 0;
	APM = 0;
	timelabel = new QLabel(this);
	timelabel->setText(tr("未检测到游戏运行"));
	timelabel->setGeometry(QRect(15, setHeight()-40, 145, 20));

	connect(button, SIGNAL(clicked()), this, SLOT(thtkclicked()));
	connect(timer, SIGNAL(timeout()), this, SLOT(check()));
}

