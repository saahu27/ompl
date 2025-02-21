#include "GLViewer.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <GL/glu.h>

GLViewer::GLViewer(QWidget *parent)
    : QOpenGLWidget(parent), timer(new QTimer(this)),
      environmentListId(0), robotListId(0),
      scale(1.0f), viewHeight(1.0f), pathIndex(0),
      animate(true), drawPlannerData(false), plannerDataList(0), cameraTranslation(0.0f, 0.0f, 0.0f) {
    setFocusPolicy(Qt::StrongFocus);
    cameraPose = QVector<float>(6, 0.0f);
    startPose = QVector<float>(6, 0.0f);
    goalPose = QVector<float>(6, 0.0f);
    timer->start(100);
    connect(timer, &QTimer::timeout, this, [this]() {
        if (!solutionPath.isEmpty()) {
            pathIndex = (pathIndex + 1) % solutionPath.size();
            update();
        }
    });
}

GLViewer::~GLViewer() {
    makeCurrent();
    if (environmentListId) glDeleteLists(environmentListId, 1);
    if (robotListId) glDeleteLists(robotListId, 1);
    doneCurrent();
}

QVector3D GLViewer::getBoundsLow() const {
    return boundsLow;
}

QVector3D GLViewer::getBoundsHigh() const {
    return boundsHigh;
}


QSize GLViewer::minimumSizeHint() const { return QSize(500, 300); }

void GLViewer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_LINE_SMOOTH);
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);

}

void GLViewer::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(width)/height, 0.1, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLViewer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera setup
    // gluLookAt(0, 0, 10, 0, 0, -5, 0, 1, 0);
    glTranslatef(0.0f, 0.0f, -10.0f);

    updateCameraTransform();

    // World transformation
    glScalef(scale, scale, scale);
    glTranslatef(-center.x(), -center.y(), -center.z());

    // Draw bounds
    if (!boundsLow.isNull() && !boundsHigh.isNull()) drawBounds();

    // Environment
    if (environmentListId) {
        glCallList(environmentListId);

    }

    // Robot
    if (robotListId) {
        // Start pose
        glPushMatrix();
        applyTransform(startPose);
        glCallList(robotListId);
        glPopMatrix();

        // Solution path
        if (!solutionPath.isEmpty()) {
            if (animate) {
                glPushMatrix();
                glMultMatrixf(solutionPath[pathIndex].constData());
                glCallList(robotListId);
                glPopMatrix();
            } else {
                int step = solutionPath.size() < 100 ? 1 : solutionPath.size() / 100;
                for (int i = 0; i < solutionPath.size(); i += step) {
                    glPushMatrix();
                    glMultMatrixf(solutionPath[i].constData());
                    glCallList(robotListId);
                    glPopMatrix();
                }
            }
        }

        // Goal pose
        glPushMatrix();
        applyTransform(goalPose);
        glCallList(robotListId);
        glPopMatrix();
    }

    // Draw planner data (states and edges)
    if (drawPlannerData && plannerDataList) {
        glCallList(plannerDataList); // corrected from previous erroneous arithmetic
    }


    glFlush();
}

void GLViewer::mousePressEvent(QMouseEvent *event) { lastPos = event->pos(); }

void GLViewer::mouseMoveEvent(QMouseEvent *event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::MiddleButton) {
        cameraTranslation.setX(cameraTranslation.x() + dx * 0.1f);
        cameraTranslation.setY(cameraTranslation.y() - dy * 0.1f);
    }

    if (event->buttons() & Qt::LeftButton) {
        if (event->modifiers() & Qt::ShiftModifier) {
            center.setX(center.x() + dx / scale);
            center.setY(center.y() - dy / scale);
        } else {
            cameraPose[1] += dx * 0.5f; // Y-axis rotation
            cameraPose[0] += dy * 0.5f; // X-axis rotation
        }
    } else if (event->buttons() & Qt::RightButton) {
        cameraPose[2] += dx * 0.5f; // Z-axis rotation
        cameraPose[0] += dy * 0.5f; // X-axis rotation
    }

    lastPos = event->pos();
    update();
}

void GLViewer::wheelEvent(QWheelEvent *event) {
    scale *= pow(2.0, -event->angleDelta().y() / 240.0);
    update();
}

void GLViewer::drawBounds() {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);

    QVector3D p[8] = {
        {boundsLow.x(), boundsLow.y(), boundsLow.z()},
        {boundsLow.x(), boundsLow.y(), boundsHigh.z()},
        {boundsLow.x(), boundsHigh.y(), boundsLow.z()},
        {boundsLow.x(), boundsHigh.y(), boundsHigh.z()},
        {boundsHigh.x(), boundsLow.y(), boundsLow.z()},
        {boundsHigh.x(), boundsLow.y(), boundsHigh.z()},
        {boundsHigh.x(), boundsHigh.y(), boundsLow.z()},
        {boundsHigh.x(), boundsHigh.y(), boundsHigh.z()}
    };

    const int edges[12][2] = {{0,1},{1,3},{3,2},{2,0},{4,5},{5,7},{7,6},{6,4},{0,4},{1,5},{2,6},{3,7}};
    for (const auto &edge : edges) {
        glVertex3f(p[edge[0]].x(), p[edge[0]].y(), p[edge[0]].z());
        glVertex3f(p[edge[1]].x(), p[edge[1]].y(), p[edge[1]].z());
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void GLViewer::applyTransform(const QVector<float> &pose) {
    if (pose.size() < 6) return;
    glTranslatef(pose[3], pose[4], pose[5]);
    glRotatef(pose[2], 0.0f, 0.0f, 1.0f); // Z-axis
    glRotatef(pose[1], 0.0f, 1.0f, 0.0f); // Y-axis
    glRotatef(pose[0], 1.0f, 0.0f, 0.0f); // X-axis
}

QVector<float> GLViewer::getTransform(const QVector<float> &state) const {
    QVector<float> matrix(16, 0.0f);
    if (state.size() == 7) {
        // Assume state = [x, y, z, qx, qy, qz, qw]
        float x = state[0], y = state[1], z = state[2];
        float qx = state[3], qy = state[4], qz = state[5], qw = state[6];
        // Normalize quaternion (if needed)
        float norm = std::sqrt(qx*qx + qy*qy + qz*qz + qw*qw);
        qx /= norm; qy /= norm; qz /= norm; qw /= norm;
        // Convert quaternion to 4x4 rotation matrix (column–major order)
        matrix[0] = 1 - 2*qy*qy - 2*qz*qz;
        matrix[1] = 2*qx*qy + 2*qz*qw;
        matrix[2] = 2*qx*qz - 2*qy*qw;
        matrix[3] = 0;
        
        matrix[4] = 2*qx*qy - 2*qz*qw;
        matrix[5] = 1 - 2*qx*qx - 2*qz*qz;
        matrix[6] = 2*qy*qz + 2*qx*qw;
        matrix[7] = 0;
        
        matrix[8] = 2*qx*qz + 2*qy*qw;
        matrix[9] = 2*qy*qz - 2*qx*qw;
        matrix[10] = 1 - 2*qx*qx - 2*qy*qy;
        matrix[11] = 0;
        
        matrix[12] = x;
        matrix[13] = y;
        matrix[14] = z;
        matrix[15] = 1;
        //qDebug() << "getTransform (7): x:" << x << "y:" << y << "z:" << z;
    } else if (state.size() == 3) {
        // SE2 case (if you have 3 elements)
        float theta = -state[2];
        matrix[0] = cos(theta);  matrix[4] = -sin(theta); matrix[8] = 0;  matrix[12] = state[0];
        matrix[1] = sin(theta);  matrix[5] = cos(theta);  matrix[9] = 0;  matrix[13] = state[1];
        matrix[2] = 0;           matrix[6] = 0;           matrix[10] = 1; matrix[14] = 0;
        matrix[3] = 0;           matrix[7] = 0;           matrix[11] = 0; matrix[15] = 1;
    } else if (state.size() == 6) {
        // Existing SE3 case with Euler angles (if you ever use that)
        float rx = state[0] * M_PI/180.0f;
        float ry = state[1] * M_PI/180.0f;
        float rz = state[2] * M_PI/180.0f;
        float cx = cos(rx), sx = sin(rx);
        float cy = cos(ry), sy = sin(ry);
        float cz = cos(rz), sz = sin(rz);
        matrix[0] = cz*cy;
        matrix[1] = cz*sy*sx - sz*cx;
        matrix[2] = cz*sy*cx + sz*sx;
        matrix[3] = 0;
        matrix[4] = sz*cy;
        matrix[5] = sz*sy*sx + cz*cx;
        matrix[6] = sz*sy*cx - cz*sx;
        matrix[7] = 0;
        matrix[8] = -sy;
        matrix[9] = cy*sx;
        matrix[10] = cy*cx;
        matrix[11] = 0;
        matrix[12] = state[3];
        matrix[13] = state[4];
        matrix[14] = state[5];
        matrix[15] = 1;
    }
    return matrix;
}

void GLViewer::setBounds(const QVector3D &low, const QVector3D &high) {
    boundsLow = low;
    boundsHigh = high;
    center = (boundsLow + boundsHigh) * 0.5f;
    QVector3D size = boundsHigh - boundsLow;
    float max_dim = qMax(size.x(), qMax(size.y(), size.z()));
    scale = max_dim > 0 ? 2.0f / max_dim : 1.0f;
    // scale = size.length() > 0 ? 2.0f / size.length() : 1.0f;
    viewHeight = size.z() * scale * 3;
    emit boundLowChanged(boundsLow);
    emit boundHighChanged(boundsHigh);
    update();
}

void GLViewer::updateBounds(const QVector3D &pos) {
    if (boundsLow.isNull() || boundsHigh.isNull()) {
        boundsLow = boundsHigh = pos;
    } else {
        boundsLow.setX(std::min(pos.x(), boundsLow.x()));
        boundsLow.setY(std::min(pos.y(), boundsLow.y()));
        boundsLow.setZ(std::min(pos.z(), boundsLow.z()));
        boundsHigh.setX(std::max(pos.x(), boundsHigh.x()));
        boundsHigh.setY(std::max(pos.y(), boundsHigh.y()));
        boundsHigh.setZ(std::max(pos.z(), boundsHigh.z()));
    }
    setBounds(boundsLow, boundsHigh);
}

void GLViewer::updateCameraTransform() {
    glTranslatef(0.0f, 0.0f, -10.0f);
    glTranslatef(cameraTranslation.x(), cameraTranslation.y(), cameraTranslation.z());
    glRotatef(cameraPose[0], 1.0f, 0.0f, 0.0f);
    glRotatef(cameraPose[1], 0.0f, 1.0f, 0.0f);
    glRotatef(cameraPose[2], 0.0f, 0.0f, 1.0f);
}

// Remaining setter implementations
void GLViewer::setStartPose(const std::array<double, 6> &pose) { 
    startPose = QVector<float>(pose.begin(), pose.end()); 
    updateBounds(QVector3D(pose[3], pose[4], pose[5])); 
    update();
}

void GLViewer::setGoalPose(const std::array<double, 6> &pose) { 
    goalPose = QVector<float>(pose.begin(), pose.end());
    updateBounds(QVector3D(pose[3], pose[4], pose[5])); 
    update();
}

void GLViewer::setSolutionPath(const QVector<QVector<float>> &path) {
    qDebug() << "setSolutionPath called with path.size() =" << path.size();
    solutionPath.clear();
    for (const auto &state : path)
        solutionPath.append(getTransform(state));
    pathIndex = 0;
    update();
}

void GLViewer::setRobot(GLuint listId) { 
    if (robotListId) glDeleteLists(robotListId, 1);
    robotListId = listId; 
    update();
}

void GLViewer::setEnvironment(GLuint listId) { 
    if (environmentListId && glIsList(environmentListId)) {
        glDeleteLists(environmentListId, 1);
    }
    environmentListId = listId; 
    update();
}

void GLViewer::clear(bool deepClean) {
    solutionPath.clear();
    pathIndex = 0;
    if (deepClean) {
        setRobot(0);
        setEnvironment(0);
        boundsLow = QVector3D();
        boundsHigh = QVector3D();
    }
    update();
}

void GLViewer::showPlannerData(bool show) { drawPlannerData = show; update(); }

void GLViewer::toggleAnimation(bool enable) { 
    animate = enable; 
    if (enable) {
    timer->start();
    } else {
        timer->stop();
    } 
    update(); 
}
void GLViewer::setSpeed(int speed) { timer->setInterval(1000/(speed+1)); }

void GLViewer::setPlannerDataListFromPlannerData(const ompl::base::PlannerData &pd) {
    // Delete previous list if it exists.
    if (plannerDataList && glIsList(plannerDataList))
        glDeleteLists(plannerDataList, 1);
    plannerDataList = glGenLists(1);
    glNewList(plannerDataList, GL_COMPILE);
    
    // Draw vertices as points.
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (unsigned int i = 0; i < pd.numVertices(); ++i) {
        const ompl::base::PlannerDataVertex &v = pd.getVertex(i);
        // Directly get the state pointer (no need to call hasState())
        const ompl::base::State *state = v.getState();
        if (!state)
            continue;
        // Try to cast to an SE2 state.
        const ompl::base::SE2StateSpace::StateType *se2 = dynamic_cast<const ompl::base::SE2StateSpace::StateType*>(state);
        if (se2) {
            glVertex3f(static_cast<GLfloat>(se2->getX()),
                       static_cast<GLfloat>(se2->getY()),
                       0.0f);
        } else {
            // Otherwise, try to cast to an SE3 state.
            const ompl::base::SE3StateSpace::StateType *se3 = dynamic_cast<const ompl::base::SE3StateSpace::StateType*>(state);
            if (se3) {
                glVertex3f(static_cast<GLfloat>(se3->getX()),
                           static_cast<GLfloat>(se3->getY()),
                           static_cast<GLfloat>(se3->getZ()));
            }
        }
    }
    glEnd();
    
    // Draw edges as lines.
    glBegin(GL_LINES);
    // Iterate over all vertices.
    for (unsigned int i = 0; i < pd.numVertices(); ++i) {
        const ompl::base::PlannerDataVertex &v = pd.getVertex(i);
        const ompl::base::State *s = v.getState();
        if (!s)
            continue;
        
        std::vector<unsigned int> neighbors;
        pd.getEdges(i, neighbors);
        
        float sx = 0, sy = 0, sz = 0;
        if (const auto *s2 = dynamic_cast<const ompl::base::SE2StateSpace::StateType*>(s)) {
            sx = static_cast<float>(s2->getX());
            sy = static_cast<float>(s2->getY());
            sz = 0.0f;
        } else if (const auto *s3 = dynamic_cast<const ompl::base::SE3StateSpace::StateType*>(s)) {
            sx = static_cast<float>(s3->getX());
            sy = static_cast<float>(s3->getY());
            sz = static_cast<float>(s3->getZ());
        }
        // Draw an edge from vertex i to each neighbor.
        for (unsigned int j : neighbors) {
            const ompl::base::PlannerDataVertex &v2 = pd.getVertex(j);
            const ompl::base::State *t = v2.getState();
            if (!t)
                continue;
            float tx = 0, ty = 0, tz = 0;
            if (const auto *t2 = dynamic_cast<const ompl::base::SE2StateSpace::StateType*>(t)) {
                tx = static_cast<float>(t2->getX());
                ty = static_cast<float>(t2->getY());
                tz = 0.0f;
            } else if (const auto *t3 = dynamic_cast<const ompl::base::SE3StateSpace::StateType*>(t)) {
                tx = static_cast<float>(t3->getX());
                ty = static_cast<float>(t3->getY());
                tz = static_cast<float>(t3->getZ());
            }
            glVertex3f(sx, sy, sz);
            glVertex3f(tx, ty, tz);
        }
    }
    glEnd();
    
    glEndList();
    update();
}
