/*
 * MatchWindow.h
 *
 *  Created on: Jul 6, 2015
 *      Author: sujiwo
 */

#ifndef MATCHWINDOW_H_
#define MATCHWINDOW_H_


#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QImage>
#include <QtGui/QPushButton>
#include <string>
#include <opencv2/core/core.hpp>
#include "Math.h"



using std::string;



class LabelWithTextBox: public QWidget
{
Q_OBJECT
public:
	LabelWithTextBox (const string &textlabel, QWidget *parent=NULL);
	void setText (const string &text)
	{ textEntry->setText(QString::fromStdString(text)); }
	void setText (const QString &txt)
	{ textEntry->setText (txt); }
	void setText (const double &num)
	{
		QString t = QString::number(num);
		textEntry->setText(t);
	}

public slots:
	void plusClick ();
	void minusClick ();
signals:
	void doPoseChange (QString buttonGroupName, int btnType);


protected:
	QLineEdit *textEntry;
	QPushButton *plus, *minus;
	string text;
};


static const float
	dX = 0.1,
	dY = 0.1,
	dZ = 0.1,
	dR = M_PI/180.0,
	dP = M_PI/180.0,
	dYw = M_PI/180.0;


class RenderWidget;
class ImageDisplay;
class VectorMap;
class PointSolver;


class MatchWindow: public QMainWindow {
	Q_OBJECT

public:
	MatchWindow ();
	virtual ~MatchWindow();

	void updatePoseText ();
	void setImageSource (const cv::Mat &image);

	bool isClosed ()
	{ return closed; }
	int getImageWidth ()
	{ return defaultImageWidth; }
	int getImageHeight ()
	{ return defaultImageHeight; }

	void setPose (const Point3 &position, const Quaternion &orientation);

	void update ();

	RenderWidget *canvas() { return glcanvas; }
	ImageDisplay *display() { return imageDisplay; }

	/* XXX: Please keep aspect ratio to be 4/3 */
	static const int defaultImageWidth = 640,
			defaultImageHeight = 480;

	enum PoseTuneButton {
		Plus, Minus
	};


signals:

public slots:
	void captureClicked (void);
	void PoseChangeManual (QString btnId, int btn);
	void searchButtonClicked (void);
	void resetButtonClicked (void);


protected:
	QWidget *centralWidget;
	QVBoxLayout *mainLayout;

	QWidget *imagesContainer;

	ImageDisplay *imageDisplay;
	RenderWidget *glcanvas;

	// position & orientation
	LabelWithTextBox *wposx, *wposy, *wposz;
	LabelWithTextBox *wroll, *wpitch, *wyaw;

	bool closed;
	void closeEvent (QCloseEvent *event);

	//sensor_msgs::CameraInfo cameraInfo;

	VectorMap *vmap;
	PointSolver *cameraFix;
};



#endif /* MATCHWINDOW_H_ */
