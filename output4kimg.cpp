#include <osg/Geode>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osgDB/WriteFile>

int main(int argc, char** argv) {

    // 创建根节点
    osg::ref_ptr<osg::Group> root = new osg::Group;

    // 创建一个立方体几何体
    osg::ref_ptr<osg::Box> box = new osg::Box(osg::Vec3(0, 0, 0), 1.0f);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;

    // 将几何体添加到根节点
    root->addChild(geode);

    // 创建一个渲染窗口并将根节点添加到场景中
    osgViewer::Viewer viewer;
    viewer.setSceneData(root);

    // 运行OSG查看器
    viewer.run();
	
	return 0;
}
