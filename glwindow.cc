#include "glwindow.hh"
#include <QCoreApplication>

GLWindow::GLWindow()
  : m_c(nullptr)
  , m_pendingUpdate(false)
{
  setSurfaceType(QWindow::OpenGLSurface);
}

GLWindow::~GLWindow()
{
}

void GLWindow::renderNow()
{
  if (!isExposed())
    return;

  bool needsInitialize = false;

  if (!m_c) {
    m_c = new QOpenGLContext(this);
    m_c->setFormat(requestedFormat());
    m_c->create();

    needsInitialize = true;
  }

  m_c->makeCurrent(this);

  if (needsInitialize) {
    initializeGL();
    resizeGL(width(), height());
  }

  paintGL();

  m_c->swapBuffers(this);
}

void GLWindow::updateGL()
{
  if (!m_pendingUpdate) {
    m_pendingUpdate = true;
    QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
  }
}

void GLWindow::initializeGL()
{
}

void GLWindow::paintGL()
{
}

void GLWindow::resizeGL(int, int)
{
}

void GLWindow::exposeEvent(QExposeEvent*)
{
  if (isExposed())
    renderNow();
}

bool GLWindow::event(QEvent* ev)
{
  switch (ev->type()) {
  case QEvent::UpdateRequest:
    m_pendingUpdate = false;
    renderNow();
    return true;
  default:
    return QWindow::event(ev);
  }
}

#include <QResizeEvent>
void GLWindow::resizeEvent(QResizeEvent* ev)
{
  if (isExposed()) {
    bool needsInitialize = false;

    if (!m_c) {
      m_c = new QOpenGLContext(this);
      m_c->setFormat(requestedFormat());
      m_c->create();

      needsInitialize = true;
    }

    m_c->makeCurrent(this);

    if (needsInitialize) {
      initializeGL();
    }

    resizeGL(ev->size().width(), ev->size().height());
    paintGL();

    m_c->swapBuffers(this);
  }
}
