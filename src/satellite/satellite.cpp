/*
*	This demo is a satellite image simulator 
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
#include <osgDB/Registry>
#include <osgDB/ReadFile>

int main()
{
    // add plugin path due to vcpkg's bug
    auto& pathList = osgDB::Registry::instance()->getLibraryFilePathList();
    for (auto const& path : pathList)
    {
        std::cout << path << std::endl;
    }
    pathList.push_front("D:\\DevGitHub\\build\\OSG_playground\\out\\build\\x64-debug\\vcpkg_installed\\x64-windows\\debug\\plugins\\osgPlugins-3.6.5");
    osgViewer::Viewer* viewer = new osgViewer::Viewer;
    osg::ref_ptr<osg::Group> rootBD = new osg::Group;
    osg::ref_ptr<osg::Group> rootBDZYX = new osg::Group;// 前(x)右(y)下(z)，转序就是zyx(321)
    osg::ref_ptr<osg::Node> axesNode = osgDB::readNodeFile("axes.osgt");
    osg::ref_ptr<osg::MatrixTransform> mtScaleNode = new osg::MatrixTransform;
    mtScaleNode->setMatrix(osg::Matrix::scale(10, 10, 10));
    mtScaleNode->addChild(axesNode);

    osg::ref_ptr<osg::MatrixTransform> mtSatellite = new osg::MatrixTransform;
    mtSatellite->addChild(osgDB::readNodeFile("GPS.ive"));
    rootBDZYX->addChild(mtSatellite.get());
    rootBD->addChild(rootBDZYX.get());
    viewer->setSceneData(rootBD.get());


	return viewer->run();
}