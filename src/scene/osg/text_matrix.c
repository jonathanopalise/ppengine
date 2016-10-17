#include <cstdio>
#include <inttypes.h>
#include <osgText/Text>
#include <osgText/Font>
#include <osg/Geode>
#include <osg/Drawable>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/StateSet>

#define TEXT_MATRIX_HEIGHT 28
#define TEXT_MATRIX_WIDTH 32

static osg::ref_ptr<osg::Geode> hud_geode;
static osg::ref_ptr<osgText::Text> letter_matrix[TEXT_MATRIX_HEIGHT][TEXT_MATRIX_WIDTH];

static const osg::Vec4 hud_colours[] = {
	osg::Vec4(1.0,1.0,1.0,1.0),
	osg::Vec4(0.0,0.0,0.0,1.0),
	osg::Vec4(1.0,31.0/255.0,67.0/255.0,1.0),
	osg::Vec4(1.0,1.0,112.0/255.0,1.0),
	osg::Vec4(143.0/255.0,255.0/255.0,112.0/255.0,1.0),
	osg::Vec4(1.0,143.0/255.0,174.0/255.0,1.0)
};

static const uint8_t attribute_to_hud_colour_lookup[] = {0,0,3,4,5};

static int convert_attribute_to_colour_index(int attribute);

osg::ref_ptr<osg::Geode> osg_text_matrix_create_geode() {
	hud_geode = new osg::Geode;
	osg::ref_ptr<osgText::Font> font = osgText::readFontFile("fonts/prstartk.ttf");
	osg::Vec3 cursor = osg::Vec3(0.0f,0.0f,0.0f);
	osg::Vec4 fontSizeColor(0.0f,1.0f,1.0f,1.0f);
	int x,y;
	float cursor_x;
	float cursor_y;

	// TODO: hud optimisation - create scene graph nodes on demand
	osg::ref_ptr<osgText::Text> text;
    cursor_y=0;
    for (y=0; y<TEXT_MATRIX_HEIGHT; y++) {
        cursor_x=0;
        for (x=0; x<TEXT_MATRIX_WIDTH; x++) {
            text=new osgText::Text;
            text->setFont(font);
            text->setColor(fontSizeColor);
            text->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS);
            text->setCharacterSize(1.0f/36);
            cursor.x()=cursor_x;
            cursor.y()=cursor_y;
            text->setPosition(cursor);
            text->setFontResolution(40,40);
            text->setText("A");
			text->setDataVariance(osg::Object::DYNAMIC);
			letter_matrix[(TEXT_MATRIX_HEIGHT-1)-y][x]=text;
            cursor_x+=1.0/TEXT_MATRIX_WIDTH;
        }
        cursor_y+=1.0/TEXT_MATRIX_HEIGHT;
    }

	return hud_geode;
}

void osg_text_matrix_set_character_and_attribute(int character_x, int character_y, char character, int attribute) {
	osg::ref_ptr<osgText::Text> letter_drawable;
	osg::ref_ptr<osg::Geode> geode;
	char null_terminated_character[2] = {0};

	geode=hud_geode;
	letter_drawable=letter_matrix[character_y][character_x];
	if (character==24) {
		if (geode->containsDrawable(letter_drawable)) {
			geode->removeDrawable(letter_drawable);
		}
	} else {
		if (!geode->containsDrawable(letter_drawable)) {
			geode->addDrawable(letter_drawable);
		}
		null_terminated_character[0]=character;
		letter_drawable->setText((const char *)null_terminated_character);
		letter_drawable->setColor(hud_colours[convert_attribute_to_colour_index(attribute)]);
	}
}

static int convert_attribute_to_colour_index(int attribute) {
	int index;
	if ((attribute>0) && (attribute<6)) {
		index=attribute_to_hud_colour_lookup[attribute-1];
	} else if ((attribute>=0x20) && (attribute<=0x26)) {
		index=attribute-0x20;
	} else {
		index=0;
		//printf("warning: unknown attribute %d in hud\n",attribute);
	}
	return index;
}

