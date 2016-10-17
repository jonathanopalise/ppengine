#include "scene/osg/hud_camera.h"
#include <osg/Camera>
#include <osgUtil/CullVisitor>
#include <cstdio>

class FGSplashContentProjectionCalback : public osg::NodeCallback {
public:
  virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
  {
    osgUtil::CullVisitor* cullVisitor = static_cast<osgUtil::CullVisitor*>(nv);

    const osg::Viewport* viewport = cullVisitor->getViewport();
    float viewportAspect = float(viewport->width())/float(viewport->height());

    osg::RefMatrix* matrix = new osg::RefMatrix;
 	matrix->makeOrtho2D(0.5-(viewportAspect/2.29),0.5+(viewportAspect/2.29),0.0,1.0);

    cullVisitor->pushProjectionMatrix(matrix);
    traverse(node, nv);
    cullVisitor->popProjectionMatrix();
  }
};

osg::ref_ptr<osg::Camera> osg_hud_create_camera() {
	osg::GraphicsContext::WindowingSystemInterface* wsi =
	osg::GraphicsContext::getWindowingSystemInterface();
	if (!wsi)
	{
		osg::notify(osg::NOTICE)<<"Error, no WindowSystemInterface available, cannot create windows."<<std::endl;
		return 0;
	}

	unsigned int viewportWidth, viewportHeight;
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0),viewportWidth, viewportHeight); 
	printf("viewport width %d, viewport height %d\n",viewportWidth,viewportHeight);

	float viewportAspect = float(viewportHeight)/float(viewportWidth);
	float heightAdjust, widthAdjust;
	if (viewportAspect < 0.875) {
		// viewport is wider than normal aspect - shrink width to fit height
		heightAdjust = 0.5;
		widthAdjust = (0.875/viewportAspect)/2;
	} else {
		// viewport is taller than normal - shrink height to fit width
		heightAdjust = (0.875/viewportAspect)/2;
		widthAdjust = 0.5;
	}
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setCullingActive(false);
	camera->setClearMask(0);
	camera->setAllowEventFocus(false);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setRenderOrder(osg::Camera::POST_RENDER);
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0.5-widthAdjust, 0.5+widthAdjust, 0.5-heightAdjust, 0.5+heightAdjust));

	osg::ref_ptr<osg::StateSet> ss = camera->getOrCreateStateSet();
	ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	ss->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);

	//osg::Group* group = new osg::Group;
  	camera->setCullCallback(new FGSplashContentProjectionCalback);
  	//camera->addChild(group);

	return camera;
}


