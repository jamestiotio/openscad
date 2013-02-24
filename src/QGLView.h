#ifndef QGLVIEW_H_
#define QGLVIEW_H_

#include "system-gl.h"
#include <QGLWidget>
#include <QLabel>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include "GLView.h"
#include "renderer.h"

class QGLView : public QGLWidget, public GLView
{
	Q_OBJECT
	Q_PROPERTY(bool showFaces READ showFaces WRITE setShowFaces);
	Q_PROPERTY(bool showEdges READ showEdges WRITE setShowEdges);
	Q_PROPERTY(bool showAxes READ showAxes WRITE setShowAxes);
	Q_PROPERTY(bool showCrosshairs READ showCrosshairs WRITE setShowCrosshairs);
	Q_PROPERTY(bool orthoMode READ orthoMode WRITE setOrthoMode);

public:
	QGLView(QWidget *parent = NULL);
	QGLView(const QGLFormat & format, QWidget *parent = NULL);
#ifdef ENABLE_OPENCSG
	bool hasOpenCSGSupport() { return this->opencsg_support; }
#endif
	// Properties
	bool showFaces() const { return this->showfaces; }
	void setShowFaces(bool enabled) { this->showfaces = enabled; }
	bool showEdges() const { return this->showedges; }
	void setShowEdges(bool enabled) { this->showedges = enabled; }
	bool showAxes() const { return this->showaxes; }
	void setShowAxes(bool enabled) { this->showaxes = enabled; }
	bool showCrosshairs() const { return this->showcrosshairs; }
	void setShowCrosshairs(bool enabled) { this->showcrosshairs = enabled; }
	bool orthoMode() const { return this->orthomode; }
	void setOrthoMode(bool enabled) { this->orthomode = enabled; }
	std::string getRendererInfo() const;
	bool save(const char *filename);

public:
	QLabel *statusLabel;
	GLint shaderinfo[11];

#ifdef ENABLE_OPENCSG
	bool opencsg_support;
	int opencsg_id;
#endif

private:
	void init();

	std::string rendererInfo;

	bool showcrosshairs;

	bool mouse_drag_active;
	QPoint last_mouse;

	void keyPressEvent(QKeyEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	void initializeGL();
	void resizeGL(int w, int h);

/*	void setGimbalCamera(const Eigen::Vector3d &pos, const Eigen::Vector3d &rot, double distance);
	void setupGimbalPerspective();
	void setupGimbalOrtho(double distance,bool offset=false);

  void setCamera(const Eigen::Vector3d &pos, const Eigen::Vector3d &center);
	void setupPerspective();
	void setupOrtho(bool offset=false);
*/

	void paintGL();
	void normalizeAngle(GLdouble& angle);

#ifdef ENABLE_OPENCSG
  bool is_opencsg_capable;
  bool has_shaders;
private slots:
	void display_opencsg_warning();
#endif

signals:
	void doAnimateUpdate();
};

#endif
