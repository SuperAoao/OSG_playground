﻿#include <osg/Geode>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osgDB/WriteFile>
#include <osg/ShapeDrawable>
static osg::Texture2D* buildGaussianDiscTexture(unsigned int log2size)
{
	unsigned int size = 1 << log2size;

	osg::Image* image = new osg::Image;
	image->allocateImage(size, size, 1, GL_LUMINANCE, GL_UNSIGNED_BYTE);
	unsigned char* data = image->data();

	float fwhm = (float) ::pow(2.0f, (float)(log2size)) * 0.3f;
	float power = (float) ::pow(2.0f, (float)log2size);

	float sigma = fwhm / 2.3548f;
	float isig2 = 1.0f / (2.0f * sigma * sigma);
	float s = 1.0f / (sigma * (float) ::sqrt(2.0 * osg::PI));

	for (unsigned int i = 0; i < size; i++)
	{
		float y = (float)i - size / 2;
		for (unsigned int j = 0; j < size; j++)
		{
			float x = (float)j - size / 2;
			float r2 = x * x + y * y;
			float f = s * (float) ::exp(-r2 * isig2) * power;

			data[i * size + j] = (unsigned char)(255.99f * std::min(f, 1.0f));
		}
	}

	osg::Texture2D* texture = new osg::Texture2D;
	texture->setImage(image);
	texture->setInternalFormat(GL_RGB);
	texture->setBorderColor(osg::Vec4(0.0, 0.0, 0.0, 0.0));
	texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_BORDER);
	texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_BORDER);
	// z00593 test begin
	// 输出图像
	osgDB::writeImageFile(*image, "testGaussianDiscTex.png");
	// z00593 test end
	return texture;
}

static osg::Texture2D* buildGaussianGlareTexture(unsigned int log2size)
{
	unsigned int size = 1 << log2size;

	osg::Image* image = new osg::Image;
	image->allocateImage(size, size, 1, GL_LUMINANCE, GL_UNSIGNED_BYTE);
	unsigned char* data = image->data();

	float scale = 25.0f / (float) ::pow(2.0f, (float)log2size);
	float bases = 0.66f;

	for (unsigned int i = 0; i < size; i++)
	{
		float y = (float)i - size / 2;
		for (unsigned int j = 0; j < size; j++)
		{
			float x = (float)j - size / 2;
			float r = (float) ::sqrt(x * x + y * y);
			float f = (float) ::pow(bases, r * scale);
			data[i * size + j] = (unsigned char)(255.99f * std::min(f, 1.0f));
		}
	}

	osg::Texture2D* texture = new osg::Texture2D;
	texture->setImage(image);
	texture->setInternalFormat(GL_RGB);
	texture->setBorderColor(osg::Vec4(0.0, 0.0, 0.0, 0.0));
	texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_BORDER);
	texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_BORDER);
	// z00593 test begin
	// 输出图像
	osgDB::writeImageFile(*image, "testGaussianGlareTex.png");
	// z00593 test end
	return texture;
}


int main(int argc, char** argv) {

#ifdef _DEBUG
	/*osg::setNotifyLevel(osg::NotifySeverity::DEBUG_INFO);
	auto& pathList = osgDB::Registry::instance()->getLibraryFilePathList();
	for (auto const& path : pathList)
	{
		std::cout << path << std::endl;
	}
	pathList.push_front("D:\\DevGitHub\\build\\OSG_playground\\out\\build\\x64-debug\\vcpkg_installed\\x64-windows\\debug\\plugins\\osgPlugins-3.6.5");
	buildGaussianDiscTexture(8);
	buildGaussianGlareTexture(9);*/
#endif // _DEBUG


	osg::ref_ptr<osg::Group> root = new osg::Group;
	// 恒星
	osg::ref_ptr<osg::Sphere> rpShape = new osg::Sphere(osg::Vec3(0, 0, 0), 1.0);
	osg::ref_ptr<osg::Geode> rpGeode = new osg::Geode();
	osg::ref_ptr<osg::ShapeDrawable> rpShapeDrawable = new osg::ShapeDrawable(rpShape);
	rpShapeDrawable->setDataVariance(osg::Object::DYNAMIC);
	rpGeode->addDrawable(rpShapeDrawable.get());

	rpShapeDrawable->setColor(osg::Vec4(1.0,1.0,1.0,1.0));

	rpGeode->setCullingActive(false);
	rpGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	// 光晕
	osg::ref_ptr<osg::Geometry> rpBillboardDrawable = osg::createTexturedQuadGeometry(osg::Vec3(-10.0, 0.0, -10.0),
		osg::Vec3(20.0, 0.0, 0.0),
		osg::Vec3(0.0, 0.0, 20.0));




	root->addChild(rpGeode.get());

	// 创建一个渲染窗口并将根节点添加到场景中
	osgViewer::Viewer viewer;
	viewer.setSceneData(root);

	// 运行OSG查看器
	viewer.run();

	return 0;
}
