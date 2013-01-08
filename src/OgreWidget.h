#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <OGRE/Ogre.h>
#include <QGLWidget>
#include <QX11Info>

#include "BaseApplication.h"

class OgreWidget : public QGLWidget, public BaseApplication
{
  Q_OBJECT;

 public:
  OgreWidget( QWidget *parent=0 );


  virtual ~OgreWidget();

  virtual void paintEvent(QPaintEvent *);
  virtual void resizeEvent(QResizeEvent* event);

 public slots:
  void goForward();
  void goBackward();


 protected:
  virtual void bindToWindow(void);
  virtual void createScene(void);

 private:
  Ogre::SceneNode* headNode;
  double xMod;
};

#endif // OGREWIDGET_H
