#include "scene/osg/scene.h"
#include "scene/osg/hud_camera.h"
#include "scene/osg/text_matrix.h"
#include "track_geometry/track_geometry.h"
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osg/Vec3>
#include <osg/StateAttribute>
#include <osg/Texture2D>
#include <osg/Depth>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgParticle/ExplosionEffect>
#include <osgText/Font>
#include <osgText/Text>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <iostream>
#include <osg/ShapeDrawable>

#define NUM_SCENERY_MODELS 11
#define NUM_TRACK_QUADS 2048

static osg::ref_ptr<osg::Geode> osg_scene_build_title_screen();
static osg::ref_ptr<osg::Geode> osg_scene_build_track();
static osg::ref_ptr<osg::Geode> osg_scene_build_game_over();

static osg::ref_ptr<osg::StateSet> create_road_texture_stateset(const char *filename);
static osg::ref_ptr<osg::PositionAttitudeTransform> osg_scene_add_scenery_object_internal(double world_coordinates_x, double world_coordinates_y, double rotation_radians, int model_index);

static osg::ref_ptr<osg::PositionAttitudeTransform> moving_object_pat[12];
static osg::ref_ptr<osg::Node> moving_object_nodes[4];
static osg::ref_ptr<osg::Group> root;
static osg::ref_ptr<osgGA::TrackballManipulator> tb;
static osg::ref_ptr<osgViewer::Viewer> viewer;
static osg::ref_ptr<osg::Group> shadow_casters;
static osg::ref_ptr<osg::Node> scenery_object_nodes[NUM_SCENERY_MODELS];
static osg::ref_ptr<osgShadow::ShadowedScene> shadowed_scene;
static osg::ref_ptr<osg::Group> gantry_group;

static osg::ref_ptr<osg::Geode> text_matrix;
static osg::ref_ptr<osg::Camera> hud_camera;
static osg::ref_ptr<osg::Geode> title_screen;
static osg::ref_ptr<osg::Geode> game_over;
static osg::ref_ptr<osg::Node> gantry_lights[2][4];

static float saved_camera_x;
static float saved_camera_y;

static const char * const scenery_model_filenames[NUM_SCENERY_MODELS] = {
	"models/highsign-amusement.osgt",    // 0
	"models/highsign-atari.osgt",        // 1
	"models/highsign-centipede.osgt",    // 2
	"models/highsign-digdug.osgt",       // 3
	"models/highsign-leftarrow.osgt",    // 4
	"models/highsign-poleposition.osgt", // 5
	"models/highsign-rightarrow.osgt",   // 6
	"models/highsign-usa.osgt",          // 7
	"models/lowsign-atari.osgt",         // 8
	"models/lowsign-namco.osgt",         // 9
	"models/startline.osgt"              // 10
};


const int ReceivesShadowTraversalMask = 0x1;
const int CastsShadowTraversalMask = 0x2;

void osg_scene_open() {
	int index;

	root=new osg::Group();
	tb=new osgGA::TrackballManipulator;
	viewer=new osgViewer::Viewer();
	//viewer->getCamera()->setClearColor(osg::Vec4(0.878, 0.737, 0.0, 1.0)); 
	viewer->setUpViewInWindow(100,100,512,448); 
	viewer->setRunFrameScheme(osgViewer::ViewerBase::ON_DEMAND);
	viewer->setRunMaxFrameRate(30.0);
    //viewer->setSceneData(root);
	viewer->setCameraManipulator(tb);
	//viewer->realize();
	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	osg::ref_ptr<osg::Group> group;

	shadowed_scene=new osgShadow::ShadowedScene();
    shadowed_scene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
    shadowed_scene->setCastsShadowTraversalMask(CastsShadowTraversalMask);

	shadow_casters=new osg::Group();
	shadowed_scene->addChild(shadow_casters);

	osg::ref_ptr<osg::Light> light=new osg::Light;
	light->setAmbient(osg::Vec4(1.0,1.0,1.0,1.0));
	light->setDiffuse(osg::Vec4d (1.0, 1.0, 0.0, 1.0));
	light->setSpecular(osg::Vec4d (0.0, 1.0, 1.0, 1.0)); 
	light->setPosition(osg::Vec4(1000.0,1000.0,600.0,0.0));

	osg::ref_ptr<osg::LightSource> lightSource=new osg::LightSource;
	lightSource->setLight(light);
	root->addChild(lightSource);

    osg::ref_ptr<osgShadow::ShadowMap> st = new osgShadow::ShadowMap();
	st->setTextureSize(osg::Vec2s(2048.0,2048.0));
	st->setAmbientBias(osg::Vec2(0.75,0.25));
	st->setLight(light);
    shadowed_scene->setShadowTechnique(st.get());

	for (index=0; index<12; index++) {
		pat=new osg::PositionAttitudeTransform();
		group=new osg::Group();
		pat->addChild(group);
		group=new osg::Group();
		pat->addChild(group);
		pat->setPosition(osg::Vec3d(0.0,0.0,0.0));
		pat->setNodeMask(0);
		shadow_casters->addChild(pat);
		moving_object_pat[index]=pat;
	}

	std::string filename="models/car1.osgt";
	for (index=0; index<4; index++) {
	    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		filename[10]=index+49;
		osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(filename); 
		moving_object_nodes[index]=model;
	}

	shadowed_scene->addChild(osg_scene_build_track());

	for (index=0; index<NUM_SCENERY_MODELS; index++) {
		scenery_object_nodes[index]=osgDB::readNodeFile(scenery_model_filenames[index]);
	}

	osg::ref_ptr <osg::PositionAttitudeTransform> mountains_pat=new osg::PositionAttitudeTransform();
	mountains_pat->setScale(osg::Vec3d(2500.0,2500.0,2500.0));
	osg::ref_ptr<osg::Node> mountains=osgDB::readNodeFile("models/mountains.osgt");
	mountains_pat->addChild(mountains);
	shadowed_scene->addChild(mountains_pat);

	osg::ref_ptr<osg::StateSet> state_one=new osg::StateSet();
	state_one->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	osg::ref_ptr<osg::Depth> depth = new osg::Depth();
	depth->setWriteMask(false);
	state_one->setAttributeAndModes(depth,osg::StateAttribute::ON);
	state_one->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	state_one->setRenderBinDetails(-1,"RenderBin"); 
	mountains->setStateSet(state_one);
	mountains->setNodeMask(ReceivesShadowTraversalMask);

	//shadowed_scene->setNodeMask(0);
	root->addChild(shadowed_scene);

	hud_camera=osg_hud_create_camera();

	text_matrix=osg_text_matrix_create_geode();
	text_matrix->setNodeMask(0);
	hud_camera->addChild(text_matrix);
	game_over=osg_scene_build_game_over();
	game_over->setNodeMask(0);
	hud_camera->addChild(game_over);
	title_screen=osg_scene_build_title_screen();
	title_screen->setNodeMask(0);
	hud_camera->addChild(title_screen);

	root->addChild(hud_camera);

    viewer->setSceneData(root);

}

void osg_scene_add_gantry(double world_coordinates_x,double world_coordinates_y,double rotation_radians) {
	unsigned int node_index;
	unsigned int light_index;
	unsigned int state;
	std::ostringstream required_node_name;
	osg::ref_ptr <osg::Node> current_node;

	osg::ref_ptr <osg::PositionAttitudeTransform> gantry_pat=osg_scene_add_scenery_object_internal(world_coordinates_x,world_coordinates_y,rotation_radians,10);
	gantry_group=gantry_pat->getChild(0)->asGroup();
	std::ostringstream node_name;
	for (state=0; state<2; state++) {
		for (light_index=0; light_index<4; light_index++) {
			required_node_name.str("");
			required_node_name << "Light" << (light_index+1) << ( state ? "On" : "Off"); 

			for (node_index=0; node_index<gantry_group->getNumChildren(); node_index++) {
				current_node=gantry_group->getChild(node_index);
				if (current_node->getName()==required_node_name.str()) {
					gantry_lights[state][light_index]=current_node;
				}
			}
		}
	}
}

void osg_scene_set_gantry_light_illumination(int light_index, int illuminated) {
	gantry_lights[0][light_index]->setNodeMask(illuminated ? 0 : 0xffffffff);
	gantry_lights[1][light_index]->setNodeMask(illuminated ? 0xffffffff : 0);
}

void osg_scene_set_gantry_texture(int texture_index) {
}

void osg_scene_add_scenery_object(double world_coordinates_x,double world_coordinates_y,double rotation_radians,int model_index) {
	osg_scene_add_scenery_object_internal(world_coordinates_x,world_coordinates_y,rotation_radians,model_index);
}

static osg::ref_ptr<osg::PositionAttitudeTransform> osg_scene_add_scenery_object_internal(double world_coordinates_x, double world_coordinates_y, double rotation_radians, int model_index) {
	osg::ref_ptr<osg::PositionAttitudeTransform> pat=new osg::PositionAttitudeTransform();
	pat->setPosition(osg::Vec3d(world_coordinates_x,world_coordinates_y,0.0));
	pat->setAttitude(osg::Quat(rotation_radians,osg::Vec3(0.0, 0.0, 1.0)));
	pat->addChild(scenery_object_nodes[model_index]);
	shadow_casters->addChild(pat);
	return pat;
}

void osg_scene_set_moving_object_attributes(int object_index,double world_coordinates_x,double world_coordinates_y,double rotation_radians,int moving_object_model,int visible) {
	osg::ref_ptr<osg::PositionAttitudeTransform> current_object_pat;
	osg::ref_ptr<osg::Group> current_object_pat_car_group;
	osg::ref_ptr<osg::Group> current_object_pat_explosion_group;

	current_object_pat=moving_object_pat[object_index];
	current_object_pat_car_group=current_object_pat->getChild(0)->asGroup();

	current_object_pat->setPosition(osg::Vec3d(world_coordinates_x,world_coordinates_y,0.0));
	current_object_pat->setAttitude(osg::Quat(rotation_radians,osg::Vec3(0.0, 0.0, 1.0)));
	if (current_object_pat_car_group->getNumChildren()==1) {
		current_object_pat_car_group->removeChildren(0,1);
	}
	current_object_pat_car_group->addChild(moving_object_nodes[moving_object_model]);
	if (visible) {
		current_object_pat->setNodeMask(CastsShadowTraversalMask);
	} else {
		current_object_pat->setNodeMask(0);
	}
	if ((object_index<8) || (object_index==11)) {
		current_object_pat_explosion_group=current_object_pat->getChild(1)->asGroup();
		if (current_object_pat_explosion_group->getNumChildren()==1) {
			dynamic_cast<osgParticle::ExplosionEffect *>(current_object_pat_explosion_group->getChild(0))->setPosition(current_object_pat->getPosition());
		}
	}
}

void osg_scene_start_car_explosion(int object_index) {
	osg::ref_ptr<osg::PositionAttitudeTransform> current_object_pat;
	osg::ref_ptr<osg::Group> current_object_pat_explosion_group;

   	osg::Vec3 wind(0.0f,0.0f,0.0f); 
 	osg::ref_ptr<osgParticle::ExplosionEffect> explosion = new osgParticle::ExplosionEffect(wind, 3.0f,2.0f);
	explosion->setTextureFileName("textures/explosion.png");
    explosion->setWind(wind);
	explosion->setPosition(moving_object_pat[object_index]->getPosition());

	current_object_pat=moving_object_pat[object_index];
	current_object_pat_explosion_group=current_object_pat->getChild(1)->asGroup();
	current_object_pat_explosion_group->addChild(explosion);
}

void osg_scene_end_car_explosion(int object_index) {
	moving_object_pat[object_index]->getChild(1)->asGroup()->removeChildren(0,1);
}

void osg_scene_set_camera_position(double camera_x, double camera_y,double object_x, double object_y) {
	saved_camera_x=camera_x;
	saved_camera_y=camera_y;
	tb->setHomePosition(osg::Vec3f(camera_x,camera_y,4.5),osg::Vec3f(object_x,object_y,4.5),osg::Vec3f(0.0,0.0,1.0));
}

void osg_scene_close() {
	int index;

	for (index=0; index<12; index++) {
		moving_object_pat[index]=NULL;
	}
	for (index=0; index<4; index++) {
		moving_object_nodes[index]=NULL;
	}
	root=NULL;
	tb=NULL;
	viewer=NULL;
	shadow_casters=NULL;
	for (index=0; index<NUM_SCENERY_MODELS; index++) {
		scenery_object_nodes[index]=NULL;
	}
	shadowed_scene=NULL;
	gantry_group=NULL;
	text_matrix=NULL;
	hud_camera=NULL;
	title_screen=NULL;
	game_over=NULL;
}

void osg_scene_generate_frame() {	
	osg::ref_ptr<osg::PositionAttitudeTransform> current_object_pat;
	current_object_pat=moving_object_pat[0];
	osg::Vec3 position;
	float distance;
	float distance_x;
	float distance_y;
	unsigned int index;

	for (index=0; index<shadow_casters->getNumChildren(); index++) {
		current_object_pat=dynamic_cast<osg::PositionAttitudeTransform *>(shadow_casters->getChild(index));
		position=current_object_pat->getPosition();	
		distance_x=saved_camera_x-position.x();
		distance_y=saved_camera_y-position.y();
		distance=sqrt(distance_x*distance_x+distance_y*distance_y);
		if (distance>200) {
			if (current_object_pat->getNodeMask()>0) {
				current_object_pat->setNodeMask(128);
			}
		} else {
			if (current_object_pat->getNodeMask()>0) {
				current_object_pat->setNodeMask(3);
			}
		}
	}

	viewer->home();
	viewer->frame();
}

void osg_scene_register_event_handler(osg::ref_ptr<osgGA::GUIEventHandler> eventHandler) {
	viewer->addEventHandler(eventHandler); 
}

static osg::ref_ptr<osg::Geode> osg_scene_build_game_over() {
	osg::ref_ptr<osg::Geometry> geom=new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> vertices=new osg::Vec3Array;
	vertices->push_back(osg::Vec3(0.23,0.35,0.0));
	vertices->push_back(osg::Vec3(0.23,0.29,0.0));
	vertices->push_back(osg::Vec3(0.77,0.29,0.0));
	vertices->push_back(osg::Vec3(0.77,0.35,0.0));
	geom->setVertexArray(vertices);

	osg::ref_ptr<osg::DrawElementsUInt> strip=new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS,0);
	strip->push_back(0);
	strip->push_back(1);
	strip->push_back(2);
	strip->push_back(3);
	geom->addPrimitiveSet(strip);

	osg::ref_ptr<osg::Vec2Array> tex_coords=new osg::Vec2Array();
	tex_coords->push_back(osg::Vec2(0.0,1.0));
	tex_coords->push_back(osg::Vec2(0.0,0.0));
	tex_coords->push_back(osg::Vec2(1.0,0.0));
	tex_coords->push_back(osg::Vec2(1.0,1.0));
	geom->setTexCoordArray(0,tex_coords);

	geom->setStateSet(create_road_texture_stateset("models/textures/gameover.png"));
    osg::StateSet* stateset = geom->getOrCreateStateSet();
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	
    osg::ref_ptr<osg::Geode> geom_geode = new osg::Geode;
    geom_geode->addDrawable(geom);

	return geom_geode;
}

static osg::ref_ptr<osg::Geode> osg_scene_build_title_screen() {
	osg::ref_ptr<osg::Geometry> geom=new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> vertices=new osg::Vec3Array;
	vertices->push_back(osg::Vec3(0.0,0.0,0.0));
	vertices->push_back(osg::Vec3(0.0,1.0,0.0));
	vertices->push_back(osg::Vec3(1.0,1.0,0.0));
	vertices->push_back(osg::Vec3(1.0,0.0,0.0));
	geom->setVertexArray(vertices);

	osg::ref_ptr<osg::DrawElementsUInt> strip=new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS,0);
	strip->push_back(0);
	strip->push_back(1);
	strip->push_back(2);
	strip->push_back(3);
	geom->addPrimitiveSet(strip);

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.5f,0.5f,0.5f,1.0f));
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL); 

	osg::ref_ptr<osg::StateSet> state_one=new osg::StateSet();
	state_one->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	state_one->setRenderBinDetails(-1,"RenderBin"); 

	osg::ref_ptr<osg::Material> material = new osg::Material();
	material->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0, 1.0, 1.0, 1.0));
	state_one->setAttribute(material,osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    osg::ref_ptr<osg::Geode> geom_geode = new osg::Geode;
	geom_geode->setStateSet(state_one);
    geom_geode->addDrawable(geom);
	geom_geode->setNodeMask(ReceivesShadowTraversalMask);

	return geom_geode;
}

static osg::ref_ptr<osg::Geode> osg_scene_build_track() {
	struct segment *current_segment;
	int index;

	osg::ref_ptr<osg::Geometry> road_geom=new osg::Geometry();
	osg::ref_ptr<osg::Geometry> start_line_geom=new osg::Geometry();

	current_segment=track_geometry_get_segments();
	osg::ref_ptr<osg::Vec3Array> road_vertices=new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> start_line_vertices=new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> vertices;

	for (index=0; index<=NUM_TRACK_QUADS; index++) {
		if (index==(NUM_TRACK_QUADS-1)) {
			vertices=start_line_vertices;
		} else {
			vertices=road_vertices;
		}
		vertices->push_back(osg::Vec3(current_segment->track_left_edge.x,current_segment->track_left_edge.y,0.0));
		vertices->push_back(osg::Vec3(current_segment->track_right_edge.x,current_segment->track_right_edge.y,0.0));
		if (index==(NUM_TRACK_QUADS-1)) {
			current_segment=track_geometry_get_segments();
		} else {
			current_segment+=32;
		}
		vertices->push_back(osg::Vec3(current_segment->track_left_edge.x,current_segment->track_left_edge.y,0.0));
		vertices->push_back(osg::Vec3(current_segment->track_right_edge.x,current_segment->track_right_edge.y,0.0));
	}
	road_geom->setVertexArray(road_vertices);
	start_line_geom->setVertexArray(start_line_vertices);

	osg::ref_ptr<osg::Vec2Array> tex_coords=new osg::Vec2Array;
	float texture_start_v=0;
	for (index=0; index<(NUM_TRACK_QUADS-1); index++) {
		texture_start_v=(float)(index/2&3)/4;
		tex_coords->push_back(osg::Vec2(0.0,texture_start_v));
		tex_coords->push_back(osg::Vec2(1.0,texture_start_v));
		tex_coords->push_back(osg::Vec2(0.0,texture_start_v+0.25));
		tex_coords->push_back(osg::Vec2(1.0,texture_start_v+0.25));
	}
	road_geom->setTexCoordArray(0,tex_coords);

	tex_coords=new osg::Vec2Array();
	tex_coords->push_back(osg::Vec2(0.0,0.0));
	tex_coords->push_back(osg::Vec2(1.0,0.0));
	tex_coords->push_back(osg::Vec2(0.0,1.0));
	tex_coords->push_back(osg::Vec2(1.0,1.0));
	start_line_geom->setTexCoordArray(0,tex_coords);

	for (index=0; index<((NUM_TRACK_QUADS*4)-4); index+=4) {
		osg::ref_ptr<osg::DrawElementsUInt> road_strip=new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS,0);
		road_strip->push_back(index+2);
		road_strip->push_back(index+3);
		road_strip->push_back(index+1);
		road_strip->push_back(index);
		road_geom->addPrimitiveSet(road_strip);
	}

	osg::ref_ptr<osg::DrawElementsUInt> road_strip=new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS,0);
	road_strip->push_back(2);
	road_strip->push_back(3);
	road_strip->push_back(1);
	road_strip->push_back(0);
	start_line_geom->addPrimitiveSet(road_strip);

    osg::ref_ptr<osg::Geode> geom_geode = new osg::Geode;
	road_geom->setStateSet(create_road_texture_stateset("images/road_texture.png"));
	start_line_geom->setStateSet(create_road_texture_stateset("images/road_texture2.png"));
    geom_geode->addDrawable(road_geom);
	geom_geode->addDrawable(start_line_geom);

	geom_geode->setNodeMask(ReceivesShadowTraversalMask);

	return geom_geode;
}

static osg::ref_ptr<osg::StateSet> create_road_texture_stateset(const char *filename) {
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
	texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::CLAMP_TO_EDGE);
	texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::CLAMP_TO_EDGE);
	texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::NEAREST_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::NEAREST);
	osg::ref_ptr<osg::Image> texture_image=osgDB::readImageFile(filename);
	texture->setImage(texture_image);
	osg::ref_ptr<osg::StateSet> texture_state=new osg::StateSet();

	osg::ref_ptr<osg::Material> material = new osg::Material();
	material->setDiffuse(osg::Material::FRONT,osg::Vec4(1.0, 1.0, 1.0, 1.0));
	texture_state->setAttribute(material,osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	texture_state->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
	texture_state->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	return texture_state;
}

void osg_scene_update_hud_character(int hud_x,int hud_y,uint8_t character,uint8_t attribute) {
	osg_text_matrix_set_character_and_attribute(hud_x,hud_y,character,attribute);
}

void osg_scene_set_display_channel(int display_mode) {
	switch(display_mode) {
		case DISPLAY_CHANNEL_TITLE_SCREEN:
			title_screen->setNodeMask(0xffffffff);
			text_matrix->setNodeMask(0);
			shadowed_scene->setNodeMask(0);	
		break;
		case DISPLAY_CHANNEL_IN_GAME:
			title_screen->setNodeMask(0);
			text_matrix->setNodeMask(0xffffffff);
			shadowed_scene->setNodeMask(0xffffffff);
		break;
	}
}

void osg_scene_set_game_over_visibility(int visible) {
	if (visible) {
		game_over->setNodeMask(0xffffffff);
	} else {
		game_over->setNodeMask(0);
	}
}

int osg_scene_active() {
	return !viewer->done();
}
