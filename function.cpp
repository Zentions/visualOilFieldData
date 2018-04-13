#include "function.h"
void createTexture2D(osg::StateSet &s,osg::ref_ptr<osg::Image> image)
{
    osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D;
    texture->setImage(image);
    texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
    texture->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_BORDER);
    texture->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_BORDER);
    texture->setBorderColor(osg::Vec4(0.0,1.0,0.0,1.0));

    s.setTextureAttributeAndModes(0,texture.get());
}
osg::ref_ptr<osg::Geode> getProfileGeode(QString filename){
    //创建一个叶节点对象
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    //创建一个几何体对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    //创建顶点数组，注意定点的添加顺序是逆时针的
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

    //创建纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

    //添加数据
    v->push_back(osg::Vec3(20629200.0f,4124330.0f,0.0f));
         vt->push_back(osg::Vec2(0.0f,0.0f));

         v->push_back(osg::Vec3(20629200.0f,4124330.0f,1000.0f));
         vt->push_back(osg::Vec2(0.0f,1.0f));


         v->push_back(osg::Vec3(20636700.0f,4119960.0f,0.0f));
         vt->push_back(osg::Vec2(0.615f,0.0f));

         v->push_back(osg::Vec3(20636700.0f,4119960.0f,1000.0f));
         vt->push_back(osg::Vec2(0.615,1.0f));

         v->push_back(osg::Vec3(20641800.0f,4118830.0f,0.0f));
          vt->push_back(osg::Vec2(1.0f,0.0f));

         v->push_back(osg::Vec3(20641800.0f,4118830.0f,1000.0f));
         vt->push_back(osg::Vec2(1.0f,1.0f));



    //设置顶点数据
    geom->setVertexArray(v.get());

    //设置纹理坐标
    geom->setTexCoordArray(0,vt.get());

    //创建法线数组
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    //添加法线
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    //设置法线数组
    geom->setNormalArray(nc.get());
    //设置法线的绑定方式为全部顶点
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);


    //添加图元，绘图基元为多边形
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,6));

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(osgDB::readImageFile(filename.toStdString()));
    texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
    texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
    geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,texture);

    //设置渲染优先级
    geom->getOrCreateStateSet()->setRenderBinDetails(-2, "RenderBin");

    //添加到叶节点
    geode->addDrawable(geom.get());

    return geode.get();
}


