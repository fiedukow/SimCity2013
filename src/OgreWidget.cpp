#include "OgreWidget.h"
#include <iostream>

OgreWidget::OgreWidget(QWidget* parent)
  : QGLWidget(parent),
    xMod(0)
{
  go();
}

OgreWidget::~OgreWidget()
{
}

void OgreWidget::bindToWindow()
{
  std::cout << "BINDING" << std::endl;
  glInit();
  create();
  //== Creating and Acquiring Ogre Window ==//

  // Get the parameters of the window QT created
  Ogre::String winHandle;
#ifdef WIN32
  // Windows code
  winHandle += Ogre::StringConverter::toString((unsigned long)(OgreWidget->parentWidget()->winId()));
#elif MACOS
  // Mac code, tested on Mac OSX 10.6 using Qt 4.7.4 and Ogre 1.7.3
  Ogre::String winHandle  = Ogre::StringConverter::toString(winId());
#else
  // Unix code
  /*QX11Info info = x11Info();
  winHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
  winHandle += ":";
  winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
  winHandle += ":";
  winHandle += Ogre::StringConverter::toString((unsigned long)(winId()));*/
  winHandle = Ogre::StringConverter::toString((unsigned long)(this->window()->winId()));
#endif


  Ogre::NameValuePairList params;
#ifndef MACOS
  std::cout << winHandle << std::endl;
  // code for Windows and Linux
  params["parentWindowHandle"] = winHandle;
  params["externalGLControl"] = "true";
  params["currentGLContext"] = "true";
  mWindow = mRoot->createRenderWindow( "QOgreWidget_RenderWindow",
                           this->width(),
                           this->height(),
                           true,
                           &params );

  mWindow->setActive(true);

  // bug fix, extract geometry
  QRect geo = this->frameGeometry ( );

  // set geometrie infos to new window
  this->setGeometry (geo);
  setMinimumSize(1,1);

#else
  // code for Mac
  params["externalWindowHandle"] = winHandle;
  params["macAPI"] = "cocoa";
  params["macAPICocoaUseNSView"] = "true";
  mWindow = mRoot->createRenderWindow("QOgreWidget_RenderWindow",
      width(), height(), false, &params);
  mWindow->setActive(true);
  makeCurrent();
#endif

  setAttribute( Qt::WA_PaintOnScreen, true );
  setAttribute( Qt::WA_NoSystemBackground );
  setAttribute( Qt::WA_NoBackground );
  setAttribute( Qt::WA_NativeWindow );
}

void OgreWidget::paintEvent(QPaintEvent* event)
{
  QGLWidget::paintEvent(event);
  mRoot->renderOneFrame();
}

void OgreWidget::resizeEvent(QResizeEvent* event)
{
  QGLWidget::resizeEvent(event);

  if(mWindow)
  {
    mWindow->reposition( x(), y() );
    mWindow->resize( width(), height() );
    mWindow->windowMovedOrResized();
  }
}

void OgreWidget::createScene()
{
  // Set the scene's ambient light
  mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

  // Create an Entity
  Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

  // Create a SceneNode and attach the Entity to it
  headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
  headNode->attachObject(ogreHead);

  // Create a Light and set its position
  Ogre::Light* light = mSceneMgr->createLight("MainLight");
  light->setPosition(20.0f, 80.0f, 50.0f);
}

void OgreWidget::goForward()
{
  xMod += 2.0;
  headNode->setPosition(xMod,0.0,0.0);
}

void OgreWidget::goBackward()
{
  xMod -= 2.0;
  std::cout << "BACK" << std::endl;
  headNode->setPosition(xMod,0.0,0.0);
}



