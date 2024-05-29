/*
* 
*/
#include <iostream>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/vec3>
#include <osg/Vec3f>
#include <osgGA/StateSetManipulator>
#include <osg/MatrixTransform>
#include <osgViewer/ViewerEventHandlers>
#include <osg/StateSet>
#include <osg/BlendFunc>
#include <osg/Depth>


int main()
{
	// create a box with a very large vertex value
	osg::ref_ptr<osg::Shape> triangle = new osg::Box(osg::Vec3(0.0, 0.0, 0.0), 300.0f);
	osg::ref_ptr<osg::ShapeDrawable> triangleDrawable = new osg::ShapeDrawable(triangle);
	triangleDrawable->setColor(osg::Vec4(1.0, 0.0, 0.0, 0.3));
	osg::ref_ptr<osg::Geode> triangleGeode = new osg::Geode;
	osg::ref_ptr<osg::MatrixTransform> triangleMt = new osg::MatrixTransform;
	triangleGeode->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc(), osg::StateAttribute::ON);
	triangleGeode->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(), osg::StateAttribute::ON);
	osg::ref_ptr<osg::Group> root = new osg::Group;

	root->addChild(triangleMt);
	triangleMt->addChild(triangleGeode);
	triangleGeode->addChild(triangleDrawable);

	// create viewer
	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	viewer.addEventHandler(new osgViewer::StatsHandler);
	// 运行OSG查看器
	viewer.run();
}