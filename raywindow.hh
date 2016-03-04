#ifndef RAYWINDOW_HH
#define RAYWINDOW_HH

#include "glwindow.hh"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLFunctions_3_0>
#include <QTime>
#include <QQuaternion>

class RayWindow : public GLWindow
{
public:
  RayWindow();
  ~RayWindow();

  void setTrack(bool track);

protected:
  QOpenGLFunctions_3_0 OpenGL;

  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);

  void mousePressEvent(QMouseEvent* ev);
  void mouseMoveEvent(QMouseEvent* ev);

  void wheelEvent(QWheelEvent* ev);

  void moveEvent(QMoveEvent* ev);
  void resizeEvent(QResizeEvent* ev);
  void hideEvent(QHideEvent* ev);

  void keyPressEvent(QKeyEvent* ev);
  void keyReleaseEvent(QKeyEvent* ev);
  void timerEvent(QTimerEvent* ev);

private:
  QOpenGLShaderProgram* m_p;
  QOpenGLTexture* m_sky;

  QQuaternion m_rot;
  QMatrix4x4 m_view;
  bool m_track;

  enum {
    KeyToward     = 0x01,
    KeyBackward   = 0x02,
    KeyLeft       = 0x04,
    KeyRight      = 0x08,
    KeyTLeft      = 0x10,
    KeyTRight     = 0x20,
    KeyUp         = 0x40,
    KeyDown       = 0x80,
    KeyTurnLeft   = 0x100,
    KeyTurnRight  = 0x200,
    KeySpeedup    = 0x400
  };
  int m_ks;
  QTime m_ti;

  GLfloat m_anglevalue;
};

#endif // RAYWINDOW_HH
