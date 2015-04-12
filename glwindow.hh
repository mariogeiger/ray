#ifndef GLWINDOW_HH
#define GLWINDOW_HH

#include <QWindow>
#include <QOpenGLContext>

class GLWindow : public QWindow
{
  Q_OBJECT

public:
  GLWindow();
  virtual ~GLWindow();

  void updateGL();

  QOpenGLContext* context() const { return m_c; }

protected:
  virtual void initializeGL();
  virtual void paintGL();
  virtual void resizeGL(int w, int h);

  virtual void exposeEvent(QExposeEvent* ev) override;
  virtual bool event(QEvent *ev) override;
  virtual void resizeEvent(QResizeEvent* ev) override;

private:
  void renderNow();

  QOpenGLContext* m_c;
  bool m_pendingUpdate;
};

#endif // GLWINDOW_HH
