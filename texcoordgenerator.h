#ifndef TEXCOORDGENERATOR
#define TEXCOORDGENERATOR
//纹理坐标生成器，继承自NodeVisitor
class TexCoordGenerator: public osg::NodeVisitor
{
public:
    //遍历所有的子节点
    TexCoordGenerator(): NodeVisitor(NodeVisitor::TRAVERSE_ALL_CHILDREN)
    {
        //
    }

    void apply(osg::Geode& geode)
    {

        //遍历所有几何体，并设置纹理坐标
        for (unsigned i=0; i<geode.getNumDrawables(); ++i)
        {
            osg::Geometry* geo = dynamic_cast<osg::Geometry* >(geode.getDrawable(i));

            if (geo)
            {
                osg::Vec2Array* tc = generate_coords(normalization_coords(geo->getVertexArray(),geode.getBoundingBox()), geo->getNormalArray());

                geo->setTexCoordArray(0, tc);
            }
        }

        NodeVisitor::apply(geode);
    }

protected:

    //计算纹理坐标
    osg::Vec2Array* generate_coords(osg::Array* vx, osg::Array* nx)
    {
        osg::Vec3Array* v3a = dynamic_cast<osg::Vec3Array*>(vx);
        osg::Vec3Array* n3a = dynamic_cast<osg::Vec3Array*>(nx);

        osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
        for (unsigned i=0; i<vx->getNumElements(); ++i) {

            osg::Vec3 P;

            if (v3a) P.set((*v3a)[i].x(), (*v3a)[i].y(), (*v3a)[i].z());

            osg::Vec3 N(0, 0, 1);
            if (n3a) N.set((*n3a)[i].x(), (*n3a)[i].y(), (*n3a)[i].z());


            int axis = 0;
            if (N.y() > N.x() && N.y() > N.z()) axis = 1;
            if (-N.y() > N.x() && -N.y() > N.z()) axis = 1;
            if (N.z() > N.x() && N.z() > N.y()) axis = 2;
            if (-N.z() > N.x() && -N.z() > N.y()) axis = 2;

            osg::Vec2 uv;

            switch (axis) {
                case 0: uv.set(P.y(), P.z()); break;
                case 1: uv.set(P.x(), P.z()); break;
                case 2: uv.set(P.x(), P.y()); break;
                default: ;
            }

            tc->push_back(uv);
        }
        return tc.release();
    }
    //归一化
    osg::Vec3Array* normalization_coords(osg::Array* vx,const osg::BoundingBox &bbox)
    {
        osg::Vec3Array* v3a = dynamic_cast<osg::Vec3Array*>(vx);

        osg::ref_ptr<osg::Vec3Array> tc = new osg::Vec3Array;
        osg::Vec3 min,max;

        if (v3a) min.set(bbox.xMin(), bbox.yMin(), bbox.zMin());
        if (v3a) max.set(bbox.xMax(), bbox.yMax(), bbox.zMax());

        for (unsigned i=0; i<vx->getNumElements(); ++i) {

            osg::Vec3 P;
            if (v3a) P.set(((*v3a)[i].x()-min.x())/(max.x()-min.x()), ((*v3a)[i].y()-min.y())/(max.y()-min.y()), ((*v3a)[i].z()-min.z())/(max.z()-min.z()));

            tc->push_back(P);
        }
        return tc.release();
    }
};
#endif // TEXCOORDGENERATOR

