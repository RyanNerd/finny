#include <QApplication>
#include "mainwindowimpl.h"

/*GSTREAMER INCLUDE*/
#include <gst/gst.h>

//
int main(int argc, char ** argv)
{
	//Init Gstreamer lib
	gst_init (&argc, &argv);

	QApplication app( argc, argv );
	MainWindowImpl win;
	win.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
