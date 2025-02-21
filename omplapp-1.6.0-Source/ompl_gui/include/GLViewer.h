#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QPoint>
#include <QVector3D>
#include <QVector>
#include <QMatrix4x4>
#include <cmath>

#include <ompl/base/PlannerData.h>
#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/base/spaces/SE3StateSpace.h>


class GLViewer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    void setPlannerDataListFromPlannerData(const ompl::base::PlannerData &pd);
    explicit GLViewer(QWidget *parent = nullptr);
    ~GLViewer() override;

    QSize minimumSizeHint() const override;

    void setRotationAngle(int axisIndex, float angle);
    QVector3D getBoundsLow() const;
    QVector3D getBoundsHigh() const;
    void setBounds(const QVector3D &low, const QVector3D &high);
    void updateBounds(const QVector3D &pos);
    void setStartPose(const std::array<double, 6> &pose);
    void setGoalPose(const std::array<double, 6> &pose);
    void showPlannerData(bool show);
    void toggleAnimation(bool enable);
    void setSpeed(int speed);
    void setSolutionPath(const QVector<QVector<float>> &path);
    void setRobot(GLuint robotListId);
    void setEnvironment(GLuint environmentListId);
    void clear(bool deepClean = false);

signals:
    void boundLowChanged(const QVector3D &low);
    void boundHighChanged(const QVector3D &high);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QTimer *timer;
    QPoint lastPos;
    GLuint environmentListId;
    GLuint robotListId;
    QVector3D center;
    float scale;
    float viewHeight;
    QVector<float> cameraPose; // [rx, ry, rz, tx, ty, tz]
    QVector<float> startPose;  // [rx, ry, rz, tx, ty, tz]
    QVector<float> goalPose;   // [rx, ry, rz, tx, ty, tz]
    QVector<QVector<float>> solutionPath;
    int pathIndex;
    bool animate;
    GLuint plannerDataList;
    bool drawPlannerData;
    QVector3D boundsLow;
    QVector3D boundsHigh;

    void drawBounds();
    void applyTransform(const QVector<float> &pose);
    QVector<float> getTransform(const QVector<float> &state) const;
    void updateCameraTransform();

    QVector3D cameraTranslation;
};

#endif // GLVIEWER_H