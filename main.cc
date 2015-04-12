#include <QGuiApplication>
#include "raywindow.hh"

int main(int argc, char *argv[])
{
  QGuiApplication a(argc, argv);

  RayWindow w;
  w.show();

  return a.exec();
}
