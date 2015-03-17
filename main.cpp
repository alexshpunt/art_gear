#include "ageditor.h"

#include <QDebug>
#include <QStyle>
#include <QStyleFactory>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setStyle( "Fusion" );
	AGEditor editor; 
	return editor.run( app );
}
