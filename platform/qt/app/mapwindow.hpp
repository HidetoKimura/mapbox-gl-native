#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QMapboxGL>

#include <QOpenGLWidget>
#include <QPropertyAnimation>
#include <QScopedPointer>
#include <QtGlobal>

#include <QLocalSocket>

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

class MapWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    MapWindow(const QMapboxGLSettings &);
    ~MapWindow();

    void selfTest();

signals:

public slots:

    void connected_callback();
    void disconnected_callback();
    void bytesWritten_callback (qint64 bytes);
    void readyRead_callback();

protected slots:
    void animationValueChanged();
    void animationFinished();

private:
    void changeStyle();
    qreal pixelRatio();

    // QWidget implementation.
    void keyPressEvent(QKeyEvent *ev) final;
    void mousePressEvent(QMouseEvent *ev) final;
    void mouseMoveEvent(QMouseEvent *ev) final;
    void wheelEvent(QWheelEvent *ev) final;

    // Q{,Open}GLWidget implementation.
    void initializeGL() final;
    void paintGL() final;

    QPointF m_lastPos;

    QMapboxGLSettings m_settings;
    QScopedPointer<QMapboxGL> m_map;

    QLocalSocket* m_socket;

    QDataStream m_stream;
    quint32 m_blockSize;

    QPropertyAnimation *m_bearingAnimation;
    QPropertyAnimation *m_zoomAnimation;

    unsigned m_animationTicks = 0;
    unsigned m_frameDraws = 0;

    QVariant m_symbolAnnotationId;
    QVariant m_lineAnnotationId;
    QVariant m_fillAnnotationId;

    bool m_sourceAdded = false;
};

#endif
