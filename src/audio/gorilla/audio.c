#include "audio/gorilla/audio.h"
#include "gorilla/ga.h"
#include "gorilla/gau.h"

#define ENGINE_SOUND_COUNT 8

gau_Manager* manager;
ga_Mixer* mixer;
ga_Sound* engine_sound;
ga_Sound* skidding_sound;
ga_Handle* engine_handles[ENGINE_SOUND_COUNT];
ga_Handle* skidding_handle;
gau_SampleSourceLoop* engine_loop_source;
gau_SampleSourceLoop* skidding_loop_source;

void gorilla_audio_open() {
	int index;

	gc_initialize(0); 
	manager=gau_manager_create(); 
	mixer=gau_manager_mixer(manager);

	engine_sound=gau_load_sound_file("sounds/f1sound1.ogg", "ogg");
	for (index=0; index<ENGINE_SOUND_COUNT; index++) {
    	engine_handles[index]=gau_create_handle_sound(mixer,engine_sound,0,0,&engine_loop_source);
	}

	skidding_sound=gau_load_sound_file("sounds/skidding.wav","wav");
	skidding_handle=gau_create_handle_sound(mixer,skidding_sound,0,0,&skidding_loop_source);	
}

void gorilla_audio_start_engine_loop(int object_index) {
	ga_handle_play(engine_handles[object_index]); 
}

void gorilla_audio_stop_engine_loop(int object_index) {
	ga_handle_stop(engine_handles[object_index]); 
}

void gorilla_audio_set_engine_attributes(int object_index, uint32_t pitch,uint16_t pan,int32_t volume) {
	ga_Handle *engine_handle;

	engine_handle=engine_handles[object_index];
	ga_handle_setParamf(engine_handle,GA_HANDLE_PARAM_PITCH,0.5+float(pitch/65536)/128);
	ga_handle_setParamf(engine_handle,GA_HANDLE_PARAM_PAN,float(pan)/32768); 
	ga_handle_setParamf(engine_handle,GA_HANDLE_PARAM_GAIN,(float)volume/256);
}

void gorilla_audio_start_skidding_loop() {
	ga_handle_play(skidding_handle); 
}

void gorilla_audio_stop_skidding_loop() {
	ga_handle_stop(skidding_handle); 
}

void gorilla_audio_set_skidding_loop_volume(int skidding_volume) {
	ga_handle_setParamf(skidding_handle,GA_HANDLE_PARAM_GAIN,(float)skidding_volume/8);
}

void gorilla_audio_update() {
	gau_manager_update(manager); 
}

void gorilla_audio_close() {
	// TODO: delete engine sound
	// TODO: delete engine handles
	gau_manager_destroy(manager);
	gc_shutdown();
}

