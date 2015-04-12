#include "raywindow.hh"

RayWindow::RayWindow()
{
  m_ks = 0;
  m_track = false;
}

void RayWindow::initializeGL()
{
  initializeOpenGLFunctions();

  m_p = new QOpenGLShaderProgram(this);
  m_p->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl.vert");
  m_p->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl.frag");
  m_p->bindAttributeLocation("vertex", 0);
  m_p->link();

  m_p->bind();

  m_p->setUniformValue("anglevalue", 1.428f);
  m_p->setUniformValue("light", -0.3/1.0863, 1.0/1.0863, 0.3/1.0863);
  m_p->setUniformValue("light", 0.5773502691896258, 0.5773502691896258, 0.5773502691896258);

  // transparente
  m_p->setUniformValue("spheres[0].center", 0.0, 0.0, -3.0);
  m_p->setUniformValue("spheres[0].radius", 1.0f);
  m_p->setUniformValue("spheres[0].mat.phong_factor", 0.0f);
  m_p->setUniformValue("spheres[0].mat.ambiant", 0.0, 0.0, 0.0);
  m_p->setUniformValue("spheres[0].mat.diffuse", 0.0, 0.0, 0.0);
  m_p->setUniformValue("spheres[0].mat.eta", 1.3f);

  // rouge
  m_p->setUniformValue("spheres[1].center", -1.5, 2.0, -5.5);
  m_p->setUniformValue("spheres[1].radius", 1.0f);
  m_p->setUniformValue("spheres[1].mat.phong_factor", 1.f);
  m_p->setUniformValue("spheres[1].mat.ambiant", 0.3, 0.0, 0.0);
  m_p->setUniformValue("spheres[1].mat.diffuse", 0.9, 0.0, 0.0);
  m_p->setUniformValue("spheres[1].mat.eta", 0.0f);

  // transparente
  m_p->setUniformValue("spheres[2].center", 5.0, 0.0, -10);
  m_p->setUniformValue("spheres[2].radius", 2.5f);
  m_p->setUniformValue("spheres[2].mat.phong_factor", 0.0f);
  m_p->setUniformValue("spheres[2].mat.ambiant", 0.0, 0.0, 0.0);
  m_p->setUniformValue("spheres[2].mat.diffuse", 0.0, 0.0, 0.0);
  m_p->setUniformValue("spheres[2].mat.eta", 1.2f);

  // transparente
  m_p->setUniformValue("spheres[3].center", -2.5, -1.5, -20);
  m_p->setUniformValue("spheres[3].radius", 2.0f);
  m_p->setUniformValue("spheres[3].mat.phong_factor", 0.0f);
  m_p->setUniformValue("spheres[3].mat.ambiant", 0.0, 0.0, 0.0);
  m_p->setUniformValue("spheres[3].mat.diffuse", 0.0, 0.0, 0.0);
  m_p->setUniformValue("spheres[3].mat.eta", 1.5f);

  m_p->setUniformValue("planes[0].point", 0.0, -2.5, -8.0);
  m_p->setUniformValue("planes[0].normal", 1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[0].width", 0.0, 0.0, -5.0);
  m_p->setUniformValue("planes[0].height", 0.0, 5.0, 0.0);
  m_p->setUniformValue("planes[0].mat.phong_factor", 0.0f);
  m_p->setUniformValue("planes[0].mat.ambiant", 0.5, 0.0, 0.0);
  m_p->setUniformValue("planes[0].mat.diffuse", 1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[0].mat.eta", 1.3f);

  m_p->setUniformValue("planes[1].point", -5.0, -2.5, -8.0);
  m_p->setUniformValue("planes[1].normal", 0.0, 0.0, 1.0);
  m_p->setUniformValue("planes[1].width", 5.0, 0.0, 0.0);
  m_p->setUniformValue("planes[1].height", 0.0, 5.0, 0.0);
  m_p->setUniformValue("planes[1].mat.phong_factor", 0.0f);
  m_p->setUniformValue("planes[1].mat.ambiant", 0.5, 0.0, 0.0);
  m_p->setUniformValue("planes[1].mat.diffuse", 1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[1].mat.eta", 1.3f);

  m_p->setUniformValue("planes[2].point", -5.0, 2.5, -8.0);
  m_p->setUniformValue("planes[2].normal", 0.0, 1.0, 0.0);
  m_p->setUniformValue("planes[2].width", 5.0, 0.0, 0.0);
  m_p->setUniformValue("planes[2].height", 0.0, 0.0, -5.0);
  m_p->setUniformValue("planes[2].mat.phong_factor", 0.0f);
  m_p->setUniformValue("planes[2].mat.ambiant", 0.5, 0.0, 0.0);
  m_p->setUniformValue("planes[2].mat.diffuse", 1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[2].mat.eta", 1.3f);

  m_p->setUniformValue("planes[3].point", -5.0, -2.5, -8.0);
  m_p->setUniformValue("planes[3].normal", 0.0, -1.0, 0.0);
  m_p->setUniformValue("planes[3].width", 5.0, 0.0, 0.0);
  m_p->setUniformValue("planes[3].height", 0.0, 0.0, -5.0);
  m_p->setUniformValue("planes[3].mat.phong_factor", 0.0f);
  m_p->setUniformValue("planes[3].mat.ambiant", 0.5, 0.0, 0.0);
  m_p->setUniformValue("planes[3].mat.diffuse", 1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[3].mat.eta", 1.3f);

  m_p->setUniformValue("planes[4].point", -5.0, -2.5, -8.0);
  m_p->setUniformValue("planes[4].normal", -1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[4].width", 0.0, 0.0, -5.0);
  m_p->setUniformValue("planes[4].height", 0.0, 5.0, 0.0);
  m_p->setUniformValue("planes[4].mat.phong_factor", 0.0f);
  m_p->setUniformValue("planes[4].mat.ambiant", 0.5, 0.0, 0.0);
  m_p->setUniformValue("planes[4].mat.diffuse", 1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[4].mat.eta", 1.3f);

  m_p->setUniformValue("planes[5].point", -5.0, -2.5, -13.0);
  m_p->setUniformValue("planes[5].normal", 0.0, 0.0, -1.0);
  m_p->setUniformValue("planes[5].width", 5.0, 0.0, 0.0);
  m_p->setUniformValue("planes[5].height", 0.0, 5.0, 0.0);
  m_p->setUniformValue("planes[5].mat.phong_factor", 0.0f);
  m_p->setUniformValue("planes[5].mat.ambiant", 0.5, 0.0, 0.0);
  m_p->setUniformValue("planes[5].mat.diffuse", 1.0, 0.0, 0.0);
  m_p->setUniformValue("planes[5].mat.eta", 1.3f);

  m_p->setUniformValue("tex", 1);
  m_p->release();


  m_sky = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
  m_sky->create();
  QImage sky(":/skybox.jpeg");
  sky = sky.convertToFormat(QImage::Format_RGBA8888);
  int a = sky.width() / 4;

  m_sky->setSize(a, a);
  m_sky->setFormat(QOpenGLTexture::RGB32F);
  m_sky->allocateStorage();

  QOpenGLTexture::PixelFormat format = QOpenGLTexture::RGBA;
  QOpenGLTexture::PixelType type = QOpenGLTexture::UInt8;

  m_sky->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, format, type,
                 sky.copy(0,   a, a, a).constBits());
  m_sky->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, format, type,
               sky.copy(2*a, a, a, a).constBits());

  m_sky->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, format, type,
                 sky.copy(a, 0,   a, a).mirrored(true, true).constBits());
  m_sky->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, format, type,
                 sky.copy(a, 2*a, a, a).mirrored(true, true).constBits());

  m_sky->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, format, type,
               sky.copy(3*a, a, a, a).constBits());
  m_sky->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, format, type,
               sky.copy(a,   a, a, a).constBits());
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);

//  m_t->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
//  m_t->setWrapMode(QOpenGLTexture::DirectionR, QOpenGLTexture::ClampToEdge);
//  m_t->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);

//  m_sky->setMinificationFilter(QOpenGLTexture::Linear);
//  m_sky->setMagnificationFilter(QOpenGLTexture::Linear);

  startTimer(0);
  m_ti.start();
}

void RayWindow::paintGL()
{
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT);

  m_p->bind();
  m_p->setUniformValue("view", m_view);
  m_p->setUniformValue("nview", m_view.normalMatrix());

  glActiveTexture(GL_TEXTURE0);
  m_p->setUniformValue("cubemap", 0);
  m_sky->bind();

  glBegin(GL_QUADS);
  m_p->setAttributeValue(0, -1., -1.);
  m_p->setAttributeValue(0, +1., -1.);
  m_p->setAttributeValue(0, +1., +1.);
  m_p->setAttributeValue(0, -1., +1.);
  glEnd();

  m_p->release();
}

void RayWindow::resizeGL(int w, int h)
{
  m_p->bind();
  m_p->setUniformValue("aspect", GLfloat(w) / GLfloat(h?h:1));
  m_p->release();
}

#include <QMouseEvent>
void RayWindow::mousePressEvent(QMouseEvent* ev)
{
  if (ev->button() == Qt::LeftButton) {
    m_track = !m_track;

    QCursor c = cursor();
    c.setShape(m_track ? Qt::BlankCursor : Qt::ArrowCursor);
    setCursor(c);

    if (m_track) {
      QPoint middle(width()/2, height()/2);
      cursor().setPos(mapToGlobal(middle));
    }
  }

  if (ev->button() == Qt::RightButton) {
    setWindowState(Qt::WindowState(windowState() ^ Qt::WindowFullScreen));
  }
}

void RayWindow::mouseMoveEvent(QMouseEvent* ev)
{
  if (m_track) {
    QPoint middle(width()/2, height()/2);
    QPointF d = ev->windowPos() - middle;

    if (!d.isNull()) {
      QMatrix4x4 rotation;
      rotation.rotate(-0.1 * d.manhattanLength(), d.y(), d.x(), 0);

      m_view = m_view * rotation;

      updateGL();

      cursor().setPos(mapToGlobal(middle));
    }
  }
}

#include <QKeyEvent>
void RayWindow::keyPressEvent(QKeyEvent* ev)
{
  switch (ev->key()) {
  case Qt::Key_W:
  case Qt::Key_Up:
    m_ks |= KeyToward;
    break;
  case Qt::Key_S:
  case Qt::Key_Down:
    m_ks |= KeyBackward;
    break;
  case Qt::Key_A:
  case Qt::Key_Left:
    m_ks |= KeyLeft;
    break;
  case Qt::Key_D:
  case Qt::Key_Right:
    m_ks |= KeyRight;
    break;
  case Qt::Key_R:
    m_ks |= KeyUp;
    break;
  case Qt::Key_F:
    m_ks |= KeyDown;
    break;
  case Qt::Key_Q:
    m_ks |= KeyTurnLeft;
    break;
  case Qt::Key_E:
    m_ks |= KeyTurnRight;
    break;
  default:
    break;
  }
}

void RayWindow::keyReleaseEvent(QKeyEvent* ev)
{
  switch (ev->key()) {
  case Qt::Key_W:
  case Qt::Key_Up:
    m_ks &= ~KeyToward;
    break;
  case Qt::Key_S:
  case Qt::Key_Down:
    m_ks &= ~KeyBackward;
    break;
  case Qt::Key_A:
  case Qt::Key_Left:
    m_ks &= ~KeyLeft;
    break;
  case Qt::Key_D:
  case Qt::Key_Right:
    m_ks &= ~KeyRight;
    break;
  case Qt::Key_R:
    m_ks &= ~KeyUp;
    break;
  case Qt::Key_F:
    m_ks &= ~KeyDown;
    break;
  case Qt::Key_Q:
    m_ks &= ~KeyTurnLeft;
    break;
  case Qt::Key_E:
    m_ks &= ~KeyTurnRight;
    break;
  default:
    break;
  }
}

void RayWindow::timerEvent(QTimerEvent *)
{
  double dt = m_ti.restart() / 1000.0;
  double step = 4.0 * dt;
  double angl = 30.0 * dt;

  QMatrix4x4 m;
  if (m_ks & KeyToward) {
    m.translate(0, 0, -step);
  }
  if (m_ks & KeyBackward) {
    m.translate(0, 0, step);
  }
  if (m_ks & KeyLeft) {
    m.translate(-step, 0, 0);
  }
  if (m_ks & KeyRight) {
    m.translate(step, 0, 0);
  }
  if (m_ks & KeyUp) {
    m.translate(0, step, 0);
  }
  if (m_ks & KeyDown) {
    m.translate(0, -step, 0);
  }
  if (m_ks & KeyTurnLeft) {
    m.rotate(angl, 0,0,1);
  }
  if (m_ks & KeyTurnRight) {
    m.rotate(angl, 0,0,-1);
  }

  if (!m.isIdentity()) {
    m_view = m_view * m;

    updateGL();
  }
}
