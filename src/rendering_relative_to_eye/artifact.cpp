/*
* This example shows the shaking artifact that using large vertex value in OpenGL
* Because most graphics cards use 32-bit floating-point numbers, which leads to insufficient precision for handling larger numerical values
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


int main()
{
	const float g_pos = 70000000;	// 7000KM
	// create a box with a very large vertex value
	osg::ref_ptr<osg::Shape> triangle = new osg::Box(osg::Vec3(g_pos, g_pos, g_pos), 300.0f);
	osg::ref_ptr<osg::ShapeDrawable> triangleDrawable = new osg::ShapeDrawable(triangle);
	osg::ref_ptr<osg::Geode> triangleGeode = new osg::Geode;
	osg::ref_ptr<osg::Group> root = new osg::Group;

	root->addChild(triangleGeode);
	triangleGeode->addChild(triangleDrawable);
	
	// create viewer
	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));

	// 运行OSG查看器
	viewer.run();
}