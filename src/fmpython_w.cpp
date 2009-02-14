// PythonQt wrapper implementation

#include "fontitem.h"

#include "fmpython_w.h"

#include "typotek.h"
#include "listdockwidget.h"
#include "fmfontdb.h"

#include <QFile>
#include <QDebug>


FMPythonW *FMPythonW::instance = 0;
const QStringList FMPythonW::exposedClasses = (
					       QStringList()    << "FontItem" 
								<< "FMFontDb");

FMPythonW::FMPythonW()
	:tk ( typotek::getInstance() )
{

}


FMPythonW * FMPythonW::getInstance()
{
	if(!instance)
	{
		instance = new FMPythonW;
		Q_ASSERT(instance);
		instance->init();
		instance->doConnect();
	}
	
	return instance;
}

void FMPythonW::init()
{
	PythonQt::init();
}

void FMPythonW::doConnect()
{
// 	connect ( ListDockWidget::getInstance(),
// 	          SIGNAL ( currentChanged() ),
// 	          SIGNAL ( currentChanged() ) );
}
void FMPythonW::run(const QString & pyScript)
{
// 	qDebug()<<"FMPythonW::run"<<pyScript;
		
	PythonQtObjectPtr mainContext = PythonQt::self()->getMainModule();
	PythonQt::self()->registerQObjectClassNames(exposedClasses);
	mainContext.addObject("Fontmatrix", this );
	
	QFile sf(pyScript);
	QString script;
	if(sf.open(QIODevice::ReadOnly))
	{
		
		script = QString::fromUtf8(sf.readAll());
	}
	else
		qDebug()<<"Error: Cannot open"<<pyScript;
	
	mainContext.evalScript(script, Py_file_input);

}


/// "exported" methods

void FMPythonW::nextFace()
{
// 	qDebug()<<"FMPythonW::nextFace";
	ListDockWidget::getInstance()->fontTree->slotNextFont();
}

void FMPythonW::previousFace()
{
// 	qDebug()<<"FMPythonW::previousFace";
	ListDockWidget::getInstance()->fontTree->slotPreviousFont();
}

void FMPythonW::nextFamily()
{
// 	qDebug()<<"FMPythonW::nextFamily";
	ListDockWidget::getInstance()->fontTree->slotNextFamily();
}

void FMPythonW::previousFamily()
{
// 	qDebug()<<"FMPythonW::previousFamily";
	ListDockWidget::getInstance()->fontTree->slotPreviousFamily();
}

QString FMPythonW::currentFontPath()
{
	if ( !tk->getSelectedFont() )
		return QString();
	return tk->getSelectedFont()->path();
}

QString FMPythonW::currentFontFamily()
{
	if ( !tk->getSelectedFont() )
		return QString();
	return tk->getSelectedFont()->family();
}

QString FMPythonW::currentFontStyle()
{
	if ( !tk->getSelectedFont() )
		return QString();
	return tk->getSelectedFont()->variant();
}

void FMPythonW::Debug(QVariant var)
{
	qDebug()<<var;
}

void FMPythonW::Print(QString str)
{
	// TODO redirect Print to a console. 
// 	std::cout<<str.toStdString();
	qDebug()<<str;
}

FMFontDb* FMPythonW::DB()
{
	return FMFontDb::DB();
}



