ifndef GORILLA_AUDIO_PATH
$(error Please set GORILLA_AUDIO_PATH to the path of your compiled Gorilla Audio installation. See http://code.google.com/p/gorilla-audio/ for more information.)
endif

CC = gcc
CFLAGS = -O3 -I src
CXX = g++
CXXFLAGS = -O3 -std=c++98 -g -Wall -Wno-narrowing -I src -I $(GORILLA_AUDIO_PATH)/include -I /home/jonathan/f1-hotshot/src/ppengine
OSGFLAGS = -losg -losgDB -losgFX -losgGA -losgParticle -losgSim -losgText -losgUtil -losgTerrain -losgManipulator -losgViewer -losgWidget -losgShadow -losgAnimation -losgVolume -lOpenThreads -lpthread
OPENALFLAGS = -lalut -lopenal

PPENGINE_COMMONDEPS = src/ppengine/engine.o src/ppengine/sub/framehandlerdispatch.o src/ppengine/lib/hud.o src/ppengine/sub/framehandler/unimplemented.o src/ppengine/sub/framehandler/316.o src/ppengine/sub/framehandler/3a8.o src/ppengine/sub/framehandler/3d0.o src/ppengine/sub/framehandler/42a.o src/ppengine/sub/framehandler/456.o src/ppengine/sub/framehandler/46c.o src/ppengine/sub/framehandler/4d6.o src/ppengine/sub/framehandler/4ec.o src/ppengine/sub/framehandler/602.o src/ppengine/sub/framehandler/66a.o src/ppengine/sub/framehandler/72a.o src/ppengine/sub/framehandler/808.o src/ppengine/sub/framehandler/852.o src/ppengine/sub/framehandler/8cc.o src/ppengine/sub/framehandler/9e0.o src/ppengine/sub/framehandler/a2e.o src/ppengine/sub/framehandler/aba.o src/ppengine/sub/framehandler/b2c.o src/ppengine/sub/framehandler/bd0.o src/ppengine/sub/framehandler/c34.o src/ppengine/sub/framehandler/c68.o src/ppengine/sub/framehandler/c86.o src/ppengine/sub/common/6a8.o src/ppengine/sub/common/1ad2.o src/ppengine/sub/common/1ad8.o src/ppengine/sub/common/72a.o src/ppengine/sub/common/7b6.o src/ppengine/sub/common/a2e.o src/ppengine/sub/common/aba.o src/ppengine/sub/common/1572.o src/ppengine/sub/common/bc6.o src/ppengine/sub/common/1ff0.o src/ppengine/sub/common/1406.o src/ppengine/sub/common/187e.o src/ppengine/sub/common/18f4.o src/ppengine/sub/common/353a.o src/ppengine/sub/common/148e.o src/ppengine/sub/common/1906.o src/ppengine/sub/common/1844.o src/ppengine/sub/common/1b2e.o src/ppengine/sub/common/165a.o src/ppengine/sub/common/16be.o src/ppengine/sub/common/1b92.o src/ppengine/sub/common/1786.o src/ppengine/sub/common/1ba4.o src/ppengine/sub/common/840.o src/ppengine/sub/common/1928.o src/ppengine/sub/common/199e.o src/ppengine/sub/common/1708.o src/ppengine/sub/common/a6a.o src/ppengine/sub/common/1310.o src/ppengine/sub/common/bc8.o src/ppengine/sub/common/1a0a.o src/ppengine/sub/common/1a26.o src/ppengine/sub/common/17da.o src/ppengine/sub/common/12a2.o src/ppengine/sub/common/1c48.o src/ppengine/sub/common/18dc.o src/ppengine/sub/common/18c4.o src/ppengine/sub/lib/bcd.o src/ppengine/sub/data/race_seconds_lookup.o src/ppengine/sub/data/track_curve_data.o src/ppengine/sub/data/acceleration_lookup.o src/ppengine/sub/data/loc_223e_lookup.o src/ppengine/sub/data/required_qualifying_times.o src/ppengine/sub/data/qualifying_bonus_lookup.o src/ppengine/sub2/framehandler.o src/ppengine/sub2/functionqueue.o src/ppengine/sub2/queuedfunctions/1e6.o src/ppengine/sub2/queuedfunctions/40c.o src/ppengine/sub2/queuedfunctions/476.o src/ppengine/sub2/queuedfunctions/554.o src/ppengine/sub2/queuedfunctions/59e.o src/ppengine/sub2/queuedfunctions/24d8.o src/ppengine/sub2/perframefunctions/playercarmovement.o src/ppengine/sub2/perframefunctions/cpucarmovement.o src/ppengine/sub2/perframefunctions/cpucarspawning.o src/ppengine/sub2/perframefunctions/cpucarai.o src/ppengine/sub2/perframefunctions/cpucarhiding.o src/ppengine/sub2/perframefunctions/carcollisions.o src/ppengine/sub2/perframefunctions/scenerycollisions.o src/ppengine/sub2/perframefunctions/puddlecollisions.o src/ppengine/sub2/perframefunctions/carexplosions.o src/ppengine/sub2/perframefunctions/common/random.o src/ppengine/sub2/data/sub_1886_lookup.o

TRACK_GEOMETRY_COMMONDEPS = src/track_geometry/points.o src/track_geometry/subpoints.o src/track_geometry/segments.o src/track_geometry/track_geometry.o

SCENE_COMMONDEPS = src/scene/scene.o src/scene/osg/scene.o src/scene/osg/hud_camera.o src/scene/osg/text_matrix.o

INPUT_COMMONDEPS = src/input/input.o src/input/keyboard_queue.o src/input/keyboard_handler.o

AUDIO_COMMONDEPS = src/audio/audio.o src/audio/gorilla/audio.o $(GORILLA_AUDIO_PATH)/bin/linux/Release/libgorilla.a

default: client

clean:
	rm `find src/ -name '*.o'` -rf

client: src/client.c src/client.h $(PPENGINE_COMMONDEPS) $(TRACK_GEOMETRY_COMMONDEPS) $(SCENE_COMMONDEPS) $(INPUT_COMMONDEPS) src/geometry/vertex2d.o $(AUDIO_COMMONDEPS)
	$(CXX) $(CXXFLAGS) src/client.c -o client $(PPENGINE_COMMONDEPS) $(TRACK_GEOMETRY_COMMONDEPS) $(SCENE_COMMONDEPS) $(INPUT_COMMONDEPS) src/geometry/vertex2d.o $(AUDIO_COMMONDEPS) -lm $(OSGFLAGS) $(OPENALFLAGS)

#####################################
# geometry                          #
#####################################

GEOMETRY_COMMONDEPS = src/geometry/vertex2d.o

src/geometry/vertex2d.o: src/geometry/vertex2d.c src/geometry/vertex2d.h
	$(CXX) $(CXXFLAGS) -c src/geometry/vertex2d.c -o src/geometry/vertex2d.o

#####################################
# track_geometry                    #
#####################################

src/track_geometry/points.o: src/track_geometry/points.c src/track_geometry/points.h src/geometry/vertex2d.h
	$(CXX) $(CXXFLAGS) -c src/track_geometry/points.c -o src/track_geometry/points.o

src/track_geometry/subpoints.o: src/track_geometry/subpoints.c src/track_geometry/subpoints.h src/geometry/vertex2d.h
	$(CXX) $(CXXFLAGS) -c src/track_geometry/subpoints.c -o src/track_geometry/subpoints.o

src/track_geometry/segments.o: src/track_geometry/segments.c src/track_geometry/segments.h src/geometry/vertex2d.h
	$(CXX) $(CXXFLAGS) -c src/track_geometry/segments.c -o src/track_geometry/segments.o

src/track_geometry/track_geometry.o: src/track_geometry/track_geometry.c src/track_geometry/track_geometry.h
	$(CXX) $(CXXFLAGS) -c src/track_geometry/track_geometry.c -o src/track_geometry/track_geometry.o

#####################################
# scene                             #
#####################################

src/scene/scene.o: src/scene/scene.c src/scene/scene.h
	$(CXX) $(CXXFLAGS) -c src/scene/scene.c -o src/scene/scene.o

src/scene/osg/scene.o: src/scene/osg/scene.c src/scene/osg/scene.h src/scene/osg/hud_camera.h src/scene/osg/text_matrix.h
	$(CXX) $(CXXFLAGS) -c src/scene/osg/scene.c -o src/scene/osg/scene.o

src/scene/osg/hud_camera.o: src/scene/osg/hud_camera.c src/scene/osg/hud_camera.h
	$(CXX) $(CXXFLAGS) -c src/scene/osg/hud_camera.c -o src/scene/osg/hud_camera.o

src/scene/osg/text_matrix.o: src/scene/osg/text_matrix.c src/scene/osg/text_matrix.h
	$(CXX) $(CXXFLAGS) -c src/scene/osg/text_matrix.c -o src/scene/osg/text_matrix.o

#####################################
# input                             #
#####################################

src/input/input.o: src/input/input.c src/input/input.h src/input/keyboard_queue.h src/input/keyboard_handler.h src/scene/osg/scene.h
	$(CXX) $(CXXFLAGS) -c src/input/input.c -o src/input/input.o

src/input/keyboard_queue.o: src/input/keyboard_queue.c src/input/keyboard_queue.h
	$(CXX) $(CXXFLAGS) -c src/input/keyboard_queue.c -o src/input/keyboard_queue.o

src/input/keyboard_handler.o: src/input/keyboard_handler.c src/input/keyboard_handler.h
	$(CXX) $(CXXFLAGS) -c src/input/keyboard_handler.c -o src/input/keyboard_handler.o

#####################################
# audio                             #
#####################################

src/audio/audio.o: src/audio/audio.c src/audio/audio.h
	$(CXX) $(CXXFLAGS) -c src/audio/audio.c -o src/audio/audio.o

src/audio/gorilla/audio.o: src/audio/gorilla/audio.c src/audio/gorilla/audio.h
	$(CXX) $(CXXFLAGS) -c src/audio/gorilla/audio.c -o src/audio/gorilla/audio.o

#####################################
# ppengine                          #
#####################################

src/ppengine/engine.o: src/ppengine/engine.c src/ppengine/engine.h src/ppengine/sub/framehandlerdispatch.h src/ppengine/sub2/functionqueue.h src/ppengine/sub2/framehandler.h
	$(CC) $(CFLAGS)  -c src/ppengine/engine.c -o src/ppengine/engine.o

src/ppengine/lib/hud.o: src/ppengine/lib/hud.c src/ppengine/lib/hud.h
	$(CC) $(CFLAGS)  -c src/ppengine/lib/hud.c -o src/ppengine/lib/hud.o

src/ppengine/sub/framehandlerdispatch.o: src/ppengine/sub/framehandlerdispatch.c src/ppengine/sub/framehandlerdispatch.h src/ppengine/sub/framehandler/unimplemented.h src/ppengine/sub/framehandler/316.h src/ppengine/sub/framehandler/3a8.h src/ppengine/sub/framehandler/3d0.h src/ppengine/sub/framehandler/42a.h src/ppengine/sub/framehandler/456.h src/ppengine/sub/framehandler/46c.h src/ppengine/sub/framehandler/4d6.h src/ppengine/sub/framehandler/4ec.h src/ppengine/sub/framehandler/602.h src/ppengine/sub/framehandler/66a.h src/ppengine/sub/framehandler/72a.h src/ppengine/sub/framehandler/808.h src/ppengine/sub/framehandler/852.h src/ppengine/sub/framehandler/8cc.h src/ppengine/sub/framehandler/9e0.h src/ppengine/sub/framehandler/a2e.h src/ppengine/sub/framehandler/aba.h src/ppengine/sub/framehandler/b2c.h src/ppengine/sub/framehandler/bd0.h src/ppengine/sub/framehandler/c34.h src/ppengine/sub/framehandler/c68.h src/ppengine/sub/framehandler/c86.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandlerdispatch.c -o src/ppengine/sub/framehandlerdispatch.o

src/ppengine/sub/framehandler/unimplemented.o: src/ppengine/sub/framehandler/unimplemented.c src/ppengine/sub/framehandler/unimplemented.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/unimplemented.c -o src/ppengine/sub/framehandler/unimplemented.o

src/ppengine/sub/framehandler/316.o: src/ppengine/sub/framehandler/316.c src/ppengine/sub/framehandler/316.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/316.c -o src/ppengine/sub/framehandler/316.o

src/ppengine/sub/framehandler/3a8.o: src/ppengine/sub/framehandler/3a8.c src/ppengine/sub/framehandler/3a8.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/3a8.c -o src/ppengine/sub/framehandler/3a8.o

src/ppengine/sub/framehandler/3d0.o: src/ppengine/sub/framehandler/3d0.c src/ppengine/sub/framehandler/3d0.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/3d0.c -o src/ppengine/sub/framehandler/3d0.o

src/ppengine/sub/framehandler/42a.o: src/ppengine/sub/framehandler/42a.c src/ppengine/sub/framehandler/42a.h src/ppengine/sub/common/6a8.h src/ppengine/engine.h src/ppengine/sub/detectinsertedcoin.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/42a.c -o src/ppengine/sub/framehandler/42a.o

src/ppengine/sub/framehandler/456.o: src/ppengine/sub/framehandler/456.c src/ppengine/sub/framehandler/456.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/456.c -o src/ppengine/sub/framehandler/456.o

src/ppengine/sub/framehandler/46c.o: src/ppengine/sub/framehandler/46c.c src/ppengine/sub/framehandler/46c.h src/ppengine/sub/common/a2e.h src/ppengine/engine.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/46c.c -o src/ppengine/sub/framehandler/46c.o

src/ppengine/sub/framehandler/4d6.o: src/ppengine/sub/framehandler/4d6.c src/ppengine/sub/framehandler/4d6.h src/ppengine/sub/common/aba.h src/ppengine/sub/common/1c48.h src/ppengine/engine.h src/ppengine/sub/detectinsertedcoin.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/4d6.c -o src/ppengine/sub/framehandler/4d6.o

src/ppengine/sub/framehandler/4ec.o: src/ppengine/sub/framehandler/4ec.c src/ppengine/sub/framehandler/4ec.h src/ppengine/sub/common/148e.h src/ppengine/sub/common/1572.h src/ppengine/sub/common/1ff0.h src/ppengine/sub/common/1906.h src/ppengine/sub/common/1844.h src/ppengine/sub/common/1b2e.h src/ppengine/sub/common/165a.h src/ppengine/sub/common/16be.h src/ppengine/sub/detectinsertedcoin.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/4ec.c -o src/ppengine/sub/framehandler/4ec.o

src/ppengine/sub/framehandler/602.o: src/ppengine/sub/framehandler/602.c src/ppengine/sub/framehandler/602.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/602.c -o src/ppengine/sub/framehandler/602.o

src/ppengine/sub/framehandler/66a.o: src/ppengine/sub/framehandler/66a.c src/ppengine/sub/framehandler/66a.h src/ppengine/sub/common/6a8.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/66a.c -o src/ppengine/sub/framehandler/66a.o

src/ppengine/sub/framehandler/72a.o: src/ppengine/sub/framehandler/72a.c src/ppengine/sub/framehandler/72a.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/72a.c -o src/ppengine/sub/framehandler/72a.o

src/ppengine/sub/framehandler/808.o: src/ppengine/sub/framehandler/808.c src/ppengine/sub/framehandler/808.h src/ppengine/sub/common/bc6.h src/ppengine/sub/common/840.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/808.c -o src/ppengine/sub/framehandler/808.o

src/ppengine/sub/framehandler/852.o: src/ppengine/sub/framehandler/852.c src/ppengine/sub/framehandler/852.h src/ppengine/sub/common/1572.h src/ppengine/sub/common/bc6.h src/ppengine/sub/common/1ff0.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/852.c -o src/ppengine/sub/framehandler/852.o

src/ppengine/sub/framehandler/8cc.o: src/ppengine/sub/framehandler/8cc.c src/ppengine/sub/framehandler/8cc.h src/ppengine/sub/common/148e.h src/ppengine/sub/common/1572.h src/ppengine/sub/common/1ff0.h src/ppengine/sub/common/1906.h src/ppengine/sub/common/1928.h src/ppengine/sub/common/bc6.h src/ppengine/sub/common/1b2e.h src/ppengine/sub/common/165a.h src/ppengine/sub/common/16be.h src/ppengine/sub2/functionqueue.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/8cc.c -o src/ppengine/sub/framehandler/8cc.o

src/ppengine/sub/framehandler/9e0.o: src/ppengine/sub/framehandler/9e0.c src/ppengine/sub/framehandler/9e0.h src/ppengine/sub/common/bc6.h src/ppengine/sub/lib/bcd.h src/ppengine/lib/hud.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/9e0.c -o src/ppengine/sub/framehandler/9e0.o

src/ppengine/sub/framehandler/a2e.o: src/ppengine/sub/framehandler/a2e.c src/ppengine/sub/framehandler/a2e.h src/ppengine/sub/common/a2e.h src/ppengine/sub/common/840.h src/ppengine/sub/common/1ad2.h src/ppengine/sub/common/a6a.h src/ppengine/sub2/functionqueue.h src/ppengine/sub/data/race_seconds_lookup.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/a2e.c -o src/ppengine/sub/framehandler/a2e.o

src/ppengine/sub/framehandler/b2c.o: src/ppengine/sub/framehandler/b2c.c src/ppengine/sub/framehandler/b2c.h src/ppengine/sub/common/148e.h src/ppengine/sub/common/1572.h src/ppengine/sub/common/1ff0.h src/ppengine/sub/common/1906.h src/ppengine/sub/common/1928.h src/ppengine/sub/common/199e.h src/ppengine/sub/common/bc6.h src/ppengine/sub/common/1b2e.h src/ppengine/sub/common/165a.h src/ppengine/sub/common/16be.h src/ppengine/lib/hud.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/b2c.c -o src/ppengine/sub/framehandler/b2c.o

src/ppengine/sub/framehandler/aba.o: src/ppengine/sub/framehandler/aba.c src/ppengine/sub/framehandler/aba.h src/ppengine/sub/common/aba.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/aba.c -o src/ppengine/sub/framehandler/aba.o

src/ppengine/sub/framehandler/bd0.o: src/ppengine/sub/framehandler/bd0.c src/ppengine/sub/framehandler/bd0.h src/ppengine/sub/common/1ff0.h src/ppengine/sub/common/1906.h src/ppengine/sub/common/1928.h src/ppengine/sub/common/199e.h src/ppengine/sub/common/bc6.h src/ppengine/sub/common/165a.h src/ppengine/sub/common/16be.h src/ppengine/sub/common/1310.h src/ppengine/sub/common/1b92.h src/ppengine/sub/common/1786.h src/ppengine/sub/common/1ba4.h src/ppengine/sub2/functionqueue.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/bd0.c -o src/ppengine/sub/framehandler/bd0.o

src/ppengine/sub/framehandler/c34.o: src/ppengine/sub/framehandler/c34.c src/ppengine/sub/framehandler/c34.h src/ppengine/sub/common/bc8.h src/ppengine/sub/common/1310.h src/ppengine/lib/hud.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/c34.c -o src/ppengine/sub/framehandler/c34.o

src/ppengine/sub/framehandler/c68.o: src/ppengine/sub/framehandler/c68.c src/ppengine/sub/framehandler/c68.h src/ppengine/sub/common/bc8.h src/ppengine/sub/common/12a2.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/c68.c -o src/ppengine/sub/framehandler/c68.o

src/ppengine/sub/framehandler/c86.o: src/ppengine/sub/framehandler/c86.c src/ppengine/sub/framehandler/c86.h src/ppengine/sub/common/bc8.h src/ppengine/sub/common/18dc.h src/ppengine/sub/common/12a2.h src/ppengine/sub/common/18f4.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/framehandler/c86.c -o src/ppengine/sub/framehandler/c86.o

src/ppengine/sub/common/6a8.o: src/ppengine/sub/common/6a8.c src/ppengine/sub/common/6a8.h src/ppengine/sub/common/1ad2.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/6a8.c -o src/ppengine/sub/common/6a8.o

src/ppengine/sub/common/1ad2.o: src/ppengine/sub/common/1ad2.c src/ppengine/sub/common/1ad2.h src/ppengine/sub/common/1ad8.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1ad2.c -o src/ppengine/sub/common/1ad2.o

src/ppengine/sub/common/1ad8.o: src/ppengine/sub/common/1ad8.c src/ppengine/sub/common/1ad8.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1ad8.c -o src/ppengine/sub/common/1ad8.o

src/ppengine/sub/common/72a.o: src/ppengine/sub/common/72a.c src/ppengine/sub/common/72a.h src/ppengine/sub/common/7b6.h src/ppengine/sub/common/a6a.h src/ppengine/engine.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/72a.c -o src/ppengine/sub/common/72a.o

src/ppengine/sub/common/7b6.o: src/ppengine/sub/common/7b6.c src/ppengine/sub/common/7b6.h src/ppengine/sub/common/7b6.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/7b6.c -o src/ppengine/sub/common/7b6.o

src/ppengine/sub/common/a2e.o: src/ppengine/sub/common/a2e.c src/ppengine/sub/common/a2e.h src/ppengine/sub/common/1ad2.h src/ppengine/sub/common/840.h src/ppengine/sub/data/race_seconds_lookup.h src/ppengine/engine.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/a2e.c -o src/ppengine/sub/common/a2e.o

src/ppengine/sub/common/aba.o: src/ppengine/sub/common/aba.c src/ppengine/sub/common/aba.h src/ppengine/sub/common/1572.h src/ppengine/sub/common/bc6.h src/ppengine/sub/common/1ff0.h src/ppengine/sub/common/1406.h src/ppengine/engine.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/aba.c -o src/ppengine/sub/common/aba.o

src/ppengine/sub/common/1572.o: src/ppengine/sub/common/1572.c src/ppengine/sub/common/1572.h src/ppengine/sub/data/track_curve_data.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1572.c -o src/ppengine/sub/common/1572.o

src/ppengine/sub/common/bc6.o: src/ppengine/sub/common/bc6.c src/ppengine/sub/common/bc6.h src/ppengine/sub/common/187e.h src/ppengine/sub/common/bc8.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/bc6.c -o src/ppengine/sub/common/bc6.o

src/ppengine/sub/common/1ff0.o: src/ppengine/sub/common/1ff0.c src/ppengine/sub/common/1ff0.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1ff0.c -o src/ppengine/sub/common/1ff0.o

src/ppengine/sub/common/1406.o: src/ppengine/sub/common/1406.c src/ppengine/sub/common/1406.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1406.c -o src/ppengine/sub/common/1406.o

src/ppengine/sub/common/187e.o: src/ppengine/sub/common/187e.c src/ppengine/sub/common/187e.h src/ppengine/sub/common/18f4.h src/ppengine/sub/common/353a.h src/ppengine/sub/common/1c48.h src/ppengine/sub/common/18c4.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/187e.c -o src/ppengine/sub/common/187e.o

src/ppengine/sub/common/18f4.o: src/ppengine/sub/common/18f4.c src/ppengine/sub/common/18f4.h src/ppengine/sub/lib/bcd.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/18f4.c -o src/ppengine/sub/common/18f4.o

src/ppengine/sub/common/353a.o: src/ppengine/sub/common/353a.c src/ppengine/sub/common/353a.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/353a.c -o src/ppengine/sub/common/353a.o

src/ppengine/sub/common/148e.o: src/ppengine/sub/common/148e.c src/ppengine/sub/common/148e.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/148e.c -o src/ppengine/sub/common/148e.o

src/ppengine/sub/common/1906.o: src/ppengine/sub/common/1906.c src/ppengine/sub/common/1906.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1906.c -o src/ppengine/sub/common/1906.o

src/ppengine/sub/common/1844.o: src/ppengine/sub/common/1844.c src/ppengine/sub/common/1844.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1844.c -o src/ppengine/sub/common/1844.o

src/ppengine/sub/common/1b2e.o: src/ppengine/sub/common/1b2e.c src/ppengine/sub/common/1b2e.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1b2e.c -o src/ppengine/sub/common/1b2e.o

src/ppengine/sub/common/165a.o: src/ppengine/sub/common/165a.c src/ppengine/sub/common/165a.h src/ppengine/sub/data/required_qualifying_times.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/165a.c -o src/ppengine/sub/common/165a.o

src/ppengine/sub/common/16be.o: src/ppengine/sub/common/16be.c src/ppengine/sub/common/16be.h src/ppengine/sub/common/1ad8.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/16be.c -o src/ppengine/sub/common/16be.o

src/ppengine/sub/common/1b92.o: src/ppengine/sub/common/1b92.c src/ppengine/sub/common/1b92.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1b92.c -o src/ppengine/sub/common/1b92.o

src/ppengine/sub/common/1786.o: src/ppengine/sub/common/1786.c src/ppengine/sub/common/1786.h src/ppengine/engine.h src/ppengine/sub2/functionqueue.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1786.c -o src/ppengine/sub/common/1786.o

src/ppengine/sub/common/1ba4.o: src/ppengine/sub/common/1ba4.c src/ppengine/sub/common/1ba4.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1ba4.c -o src/ppengine/sub/common/1ba4.o

src/ppengine/sub/common/840.o: src/ppengine/sub/common/840.c src/ppengine/sub/common/840.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/840.c -o src/ppengine/sub/common/840.o

src/ppengine/sub/common/1928.o: src/ppengine/sub/common/1928.c src/ppengine/sub/common/1928.h src/ppengine/sub/common/1ad2.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1928.c -o src/ppengine/sub/common/1928.o

src/ppengine/sub/common/199e.o: src/ppengine/sub/common/199e.c src/ppengine/sub/common/199e.h src/ppengine/sub/common/353a.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/199e.c -o src/ppengine/sub/common/199e.o

src/ppengine/sub/common/1708.o: src/ppengine/sub/common/1708.c src/ppengine/sub/common/1708.h src/ppengine/sub/data/race_seconds_lookup.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1708.c -o src/ppengine/sub/common/1708.o

src/ppengine/sub/common/a6a.o: src/ppengine/sub/common/a6a.c src/ppengine/sub/common/a6a.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/a6a.c -o src/ppengine/sub/common/a6a.o

src/ppengine/sub/common/1310.o: src/ppengine/sub/common/1310.c src/ppengine/sub/common/1310.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1310.c -o src/ppengine/sub/common/1310.o

src/ppengine/sub/common/bc8.o: src/ppengine/sub/common/bc8.c src/ppengine/sub/common/bc8.h src/ppengine/sub/common/1a0a.h src/ppengine/sub/common/1a26.h src/ppengine/sub/common/17da.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/bc8.c -o src/ppengine/sub/common/bc8.o

src/ppengine/sub/common/1a0a.o: src/ppengine/sub/common/1a0a.c src/ppengine/sub/common/1a0a.h src/ppengine/engine.h src/ppengine/lib/hud.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1a0a.c -o src/ppengine/sub/common/1a0a.o

src/ppengine/sub/common/1a26.o: src/ppengine/sub/common/1a26.c src/ppengine/sub/common/1a26.h src/ppengine/lib/hud.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1a26.c -o src/ppengine/sub/common/1a26.o

src/ppengine/sub/common/17da.o: src/ppengine/sub/common/17da.c src/ppengine/sub/common/17da.h src/ppengine/sub/common/1844.h src/ppengine/sub/lib/bcd.h src/ppengine/lib/hud.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/17da.c -o src/ppengine/sub/common/17da.o

src/ppengine/sub/common/12a2.o: src/ppengine/sub/common/12a2.c src/ppengine/sub/common/12a2.h src/ppengine/lib/hud.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/12a2.c -o src/ppengine/sub/common/12a2.o

src/ppengine/sub/common/1c48.o: src/ppengine/sub/common/1c48.c src/ppengine/sub/common/1c48.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/1c48.c -o src/ppengine/sub/common/1c48.o

src/ppengine/sub/common/18dc.o: src/ppengine/sub/common/18dc.c src/ppengine/sub/common/18dc.h src/ppengine/sub/common/1c48.h src/ppengine/sub/common/18c4.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/18dc.c -o src/ppengine/sub/common/18dc.o

src/ppengine/sub/common/18c4.o: src/ppengine/sub/common/18c4.c src/ppengine/sub/common/18c4.h src/ppengine/sub/common/1c48.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/common/18c4.c -o src/ppengine/sub/common/18c4.o

src/ppengine/sub/lib/bcd.o: src/ppengine/sub/lib/bcd.c src/ppengine/sub/lib/bcd.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/lib/bcd.c -o src/ppengine/sub/lib/bcd.o

src/ppengine/sub/data/race_seconds_lookup.o: src/ppengine/sub/data/race_seconds_lookup.c src/ppengine/sub/data/race_seconds_lookup.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/data/race_seconds_lookup.c -o src/ppengine/sub/data/race_seconds_lookup.o

src/ppengine/sub/data/track_curve_data.o: src/ppengine/sub/data/track_curve_data.c src/ppengine/sub/data/track_curve_data.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/data/track_curve_data.c -o src/ppengine/sub/data/track_curve_data.o

src/ppengine/sub/data/acceleration_lookup.o: src/ppengine/sub/data/acceleration_lookup.c src/ppengine/sub/data/acceleration_lookup.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/data/acceleration_lookup.c -o src/ppengine/sub/data/acceleration_lookup.o

src/ppengine/sub/data/loc_223e_lookup.o: src/ppengine/sub/data/loc_223e_lookup.c src/ppengine/sub/data/loc_223e_lookup.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/data/loc_223e_lookup.c -o src/ppengine/sub/data/loc_223e_lookup.o

src/ppengine/sub/data/required_qualifying_times.o: src/ppengine/sub/data/required_qualifying_times.c src/ppengine/sub/data/required_qualifying_times.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/data/required_qualifying_times.c -o src/ppengine/sub/data/required_qualifying_times.o

src/ppengine/sub/data/qualifying_bonus_lookup.o: src/ppengine/sub/data/qualifying_bonus_lookup.c src/ppengine/sub/data/qualifying_bonus_lookup.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub/data/qualifying_bonus_lookup.c -o src/ppengine/sub/data/qualifying_bonus_lookup.o

src/ppengine/sub2/framehandler.o: src/ppengine/sub2/framehandler.c src/ppengine/sub2/framehandler.h src/ppengine/sub2/perframefunctions/playercarmovement.h src/ppengine/sub2/perframefunctions/cpucarmovement.h src/ppengine/sub2/perframefunctions/cpucarspawning.h src/ppengine/sub2/perframefunctions/cpucarai.h src/ppengine/sub2/perframefunctions/cpucarhiding.h src/ppengine/sub2/perframefunctions/carcollisions.h src/ppengine/sub2/perframefunctions/scenerycollisions.h src/ppengine/sub2/perframefunctions/puddlecollisions.h src/ppengine/sub2/perframefunctions/carexplosions.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/framehandler.c -o src/ppengine/sub2/framehandler.o 

src/ppengine/sub2/functionqueue.o: src/ppengine/sub2/functionqueue.c src/ppengine/sub2/functionqueue.h src/ppengine/sub2/queuedfunctions/1e6.h src/ppengine/sub2/queuedfunctions/40c.h src/ppengine/sub2/queuedfunctions/476.h src/ppengine/sub2/queuedfunctions/554.h src/ppengine/sub2/queuedfunctions/59e.h src/ppengine/sub2/queuedfunctions/24d8.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/functionqueue.c -o src/ppengine/sub2/functionqueue.o 

src/ppengine/sub2/queuedfunctions/1e6.o: src/ppengine/sub2/queuedfunctions/1e6.c src/ppengine/sub2/queuedfunctions/1e6.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/queuedfunctions/1e6.c -o src/ppengine/sub2/queuedfunctions/1e6.o 

src/ppengine/sub2/queuedfunctions/40c.o: src/ppengine/sub2/queuedfunctions/40c.c src/ppengine/sub2/queuedfunctions/40c.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/queuedfunctions/40c.c -o src/ppengine/sub2/queuedfunctions/40c.o 

src/ppengine/sub2/queuedfunctions/476.o: src/ppengine/sub2/queuedfunctions/476.c src/ppengine/sub2/queuedfunctions/476.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/queuedfunctions/476.c -o src/ppengine/sub2/queuedfunctions/476.o 

src/ppengine/sub2/queuedfunctions/554.o: src/ppengine/sub2/queuedfunctions/554.c src/ppengine/sub2/queuedfunctions/554.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/queuedfunctions/554.c -o src/ppengine/sub2/queuedfunctions/554.o 

src/ppengine/sub2/queuedfunctions/59e.o: src/ppengine/sub2/queuedfunctions/59e.c src/ppengine/sub2/queuedfunctions/59e.h src/ppengine/sub2/queuedfunctions/1e6.h src/ppengine/sub2/queuedfunctions/24d8.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/queuedfunctions/59e.c -o src/ppengine/sub2/queuedfunctions/59e.o 

src/ppengine/sub2/queuedfunctions/24d8.o: src/ppengine/sub2/queuedfunctions/24d8.c src/ppengine/sub2/queuedfunctions/24d8.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/queuedfunctions/24d8.c -o src/ppengine/sub2/queuedfunctions/24d8.o 

src/ppengine/sub2/perframefunctions/playercarmovement.o: src/ppengine/sub2/perframefunctions/playercarmovement.c src/ppengine/sub2/perframefunctions/playercarmovement.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/playercarmovement.c -o src/ppengine/sub2/perframefunctions/playercarmovement.o 

src/ppengine/sub2/perframefunctions/cpucarmovement.o: src/ppengine/sub2/perframefunctions/cpucarmovement.c src/ppengine/sub2/perframefunctions/cpucarmovement.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/cpucarmovement.c -o src/ppengine/sub2/perframefunctions/cpucarmovement.o 

src/ppengine/sub2/perframefunctions/cpucarspawning.o: src/ppengine/sub2/perframefunctions/cpucarspawning.c src/ppengine/sub2/perframefunctions/cpucarspawning.h src/ppengine/sub2/perframefunctions/common/random.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/cpucarspawning.c -o src/ppengine/sub2/perframefunctions/cpucarspawning.o 

src/ppengine/sub2/perframefunctions/cpucarai.o: src/ppengine/sub2/perframefunctions/cpucarai.c src/ppengine/sub2/perframefunctions/cpucarai.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/cpucarai.c -o src/ppengine/sub2/perframefunctions/cpucarai.o 

src/ppengine/sub2/perframefunctions/cpucarhiding.o: src/ppengine/sub2/perframefunctions/cpucarhiding.c src/ppengine/sub2/perframefunctions/cpucarhiding.h src/ppengine/sub2/perframefunctions/common/random.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/cpucarhiding.c -o src/ppengine/sub2/perframefunctions/cpucarhiding.o

src/ppengine/sub2/perframefunctions/carcollisions.o: src/ppengine/sub2/perframefunctions/carcollisions.c src/ppengine/sub2/perframefunctions/carcollisions.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/carcollisions.c -o src/ppengine/sub2/perframefunctions/carcollisions.o

src/ppengine/sub2/perframefunctions/scenerycollisions.o: src/ppengine/sub2/perframefunctions/scenerycollisions.c src/ppengine/sub2/perframefunctions/scenerycollisions.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/scenerycollisions.c -o src/ppengine/sub2/perframefunctions/scenerycollisions.o

src/ppengine/sub2/perframefunctions/puddlecollisions.o: src/ppengine/sub2/perframefunctions/puddlecollisions.c src/ppengine/sub2/perframefunctions/puddlecollisions.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/puddlecollisions.c -o src/ppengine/sub2/perframefunctions/puddlecollisions.o

src/ppengine/sub2/perframefunctions/carexplosions.o: src/ppengine/sub2/perframefunctions/carexplosions.c src/ppengine/sub2/perframefunctions/carexplosions.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/carexplosions.c -o src/ppengine/sub2/perframefunctions/carexplosions.o

src/ppengine/sub2/perframefunctions/common/random.o: src/ppengine/sub2/perframefunctions/common/random.c src/ppengine/sub2/perframefunctions/common/random.h src/ppengine/engine.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/perframefunctions/common/random.c -o src/ppengine/sub2/perframefunctions/common/random.o 

src/ppengine/sub2/data/sub_1886_lookup.o: src/ppengine/sub2/data/sub_1886_lookup.c src/ppengine/sub2/data/sub_1886_lookup.h
	$(CC) $(CFLAGS)  -c src/ppengine/sub2/data/sub_1886_lookup.c -o src/ppengine/sub2/data/sub_1886_lookup.o 


