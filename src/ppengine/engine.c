#include "ppengine/engine.h"
#include "ppengine/sub/framehandlerdispatch.h"
#include "ppengine/sub2/functionqueue.h"
#include "ppengine/sub2/framehandler.h"

void(*sound_effect_callback)(int);

struct movingobject moving_objects[32];
struct sceneryobject scenery_objects[]={
	{0xee05,0xf500,0,0,0}, // highsign-amusement
	{0xe500,0x0b00,0,0,0}, // highsign-amusement
	{0xdc04,0xf500,0,0,5}, // highsign-poleposition
	{0xd401,0x0b00,0,0,1}, // highsign-atari
	{0xc608,0x0c00,0,0,3}, // highsign-digdug
	{0xbb00,0x0b00,0,0,8}, // lowsign-atari
	{0xb002,0xf500,0,0,5}, // highsign-poleposition
	{0xa505,0xf500,0,0,7}, // highsign-usa
	{0x9a01,0x0b00,0,0,0}, // highsign-amusement
	{0x9004,0xf500,0,0,3}, // highsign-digdug
	{0x8509,0x0c00,0,0,1}, // highsign-atari
	{0x8003,0xf500,0,0,9}, // lowsign-namco
	{0x7f00,0x0b00,0,0,2}, // highsign-centipede
	{0x7006,0x0b00,0,0,4}, // highsign-leftarrow
	{0x6908,0x0c00,0,0,8}, // lowsign-atari
	{0x6001,0x0b00,0,0,3}, // highsign-digdug
	{0x5609,0x0c00,0,0,9}, // lowsign-namco
	{0x4905,0xf500,0,0,0}, // highsign-amusement
	{0x4603,0xf500,0,0,2}, // highsign-centipede
	{0x3404,0xf500,0,0,1}, // highsign-atari
	{0x2f00,0x0b00,0,0,5}, // highsign-poleposition
	{0x2407,0x0b00,0,0,6}, // highsign-rightarrow
	{0x1d03,0xf500,0,0,2}, // highsign-centipede
	{0x1401,0x0b00,0,0,3}  // highsign-digdug
};

struct hudentry hud_content[HUD_CONTENT_LENGTH];

uint16_t qualifying_initial_timer_switch;
uint16_t race_initial_timer_switch_1;
uint16_t race_initial_timer_switch_2;
uint16_t required_qualifying_times_switch;
uint16_t machine_uptime;
uint16_t current_cycling_colour;
uint16_t jump_table_function_number;
uint16_t jump_table_subfunction_number;
uint16_t extended_play_frames_remaining;
int16_t opponent_car_grinding_sideways_movement;
uint32_t forward_position;
uint32_t high_score;
uint32_t lap_time_bcd_displayed_outside_gameplay;
uint16_t displayed_speed_outside_gameplay;
uint32_t current_score_outside_gameplay;
int16_t steering_or_car_orientation;
uint16_t ticks_remaining;
uint16_t engine_sound_active;
uint32_t current_race_lap;
uint32_t fastest_ever_lap_bcd;
uint16_t steering_wheel_rotation;
uint16_t full_race_distance_completed;
uint32_t unknown_828c;
uint32_t unknown_8290;
uint16_t unknown_8292;
uint16_t cars_passing_tracking_enabled;
uint32_t current_score;
uint16_t unknown_82a6;
int16_t cpu_car_spawning_mode;
uint16_t session_seconds_updates_enabled;
uint16_t frames_until_next_countdown_update;
uint16_t scoring_enabled_flag;
int16_t lap_completion_events_counted;
uint16_t number_of_cpu_cars_in_use;
uint16_t lap_completion_events_in_single_game;
uint16_t second_fractions_remaining;
uint16_t seconds_remaining;
int16_t player_has_passed_start_line_in_current_session;
uint16_t lap_time_hundredths;
uint16_t ticks_until_next_lap_time_tenths_change;
uint16_t lap_time_tenths;
uint16_t lap_time_seconds;
uint32_t current_lap_time_bcd;
uint16_t previous_lap_time_display_ticks_remaining;
uint16_t qualifying_engine_started;
int32_t current_speed_8_bit_candidate_3;
uint16_t unknown_8020;
uint16_t session_end_animation_ticks_remaining;
uint16_t waiting_for_coin;
uint16_t unknown_82c2;
uint32_t previous_lap_time_bcd;
uint32_t fastest_session_lap_bcd;
int16_t high_precision_speed;
uint16_t session_engine_started;
int16_t target_engine_revs;
uint16_t internal_accel_pedal;
uint16_t unknown_8222;
int16_t clipped_steering;
int16_t clipped_steering_candidate_2;
uint32_t background_position;
uint16_t seconds_into_session;
uint16_t session_top_speed;
uint16_t steering_wheel_rotation_candidate_2;
uint16_t unknown_8022;
uint16_t unknown_8030;
uint32_t function_number_seconds_bcd;
uint16_t qualifying_session_state;
uint16_t race_hundredths_elapsed;
uint16_t race_tenths_elapsed;
uint16_t race_seconds_elapsed;
uint16_t unknown_a852;
uint32_t race_time_elapsed_bcd;
uint16_t qualifying_position_minus_one;
int16_t car_slowdown_factor;
uint16_t player_car_stopped_at_session_end;
int16_t unknown_81be;
uint16_t qualifying_complete_flag;
uint16_t cars_passed;
uint16_t gantry_and_starting_lights_appearance;
uint16_t sample_player_1;
uint16_t sample_player_2;
uint16_t new_lap_just_started;
uint16_t safe_to_change_gantry_appearance;
int16_t curve_at_player_forward_position;
uint16_t display_road_vertical_scroll;
uint16_t display_background_horizontal_scroll;
uint32_t current_score_times_100_bcd;
uint32_t high_score_bcd;
int32_t current_speed_8_bit;
uint32_t current_score_outside_gameplay_bcd;
int16_t target_actual_revs_relationship;
uint16_t engine_sound_pitch;
uint16_t current_speed_8_bit_candidate_2;
uint16_t unknown_80f2;
uint16_t unknown_822c;
uint16_t gear_hi_5_lo_a;
int16_t target_revs_increase;
uint16_t gear_binary;
int16_t actual_engine_revs;
int16_t unknown_8240;
uint16_t internal_brake_pedal;
int16_t unknown_8236;
int16_t unknown_8238;
int16_t unknown_823a;
int16_t unknown_824c;
int16_t unknown_823e;
int32_t unknown_8268;
int16_t sideways_pull;
int16_t unknown_8248;
uint16_t steering_multiplier;
uint16_t skidding_volume;
int16_t change_to_speed;
int16_t unknown_827a;
int16_t steering_wheel_frame_delta;
int16_t high_precision_sideways_position;
uint16_t off_track_sound_effect_pitch;
uint16_t slow_cpu_cars_ahead;
uint16_t pseudorandom_number;
uint16_t frame_counter;
uint16_t unknown_80e2;
uint16_t post_respawn_countdown;
uint16_t session_top_speed_bcd;
uint16_t qualifying_bonus;
uint16_t qualifying_outcome_cycling_value_tracker;
uint16_t unknown_80e8;
int16_t time_bonus;
uint32_t unknown_8282;
uint16_t unknown_8298;

// extensions
uint32_t credits_remaining;
uint32_t demo_frames;
uint32_t extended_play_visible;

void engine_initialise() {
	qualifying_initial_timer_switch=1;
	race_initial_timer_switch_1=1;
	race_initial_timer_switch_2=0;
	required_qualifying_times_switch=0;
	machine_uptime=0;
	jump_table_function_number=0;
	jump_table_subfunction_number=0;
	credits_remaining=0;

	sub_frame_handler_init();
	init_sub2_function_queue();
}

void engine_execute_frame() {
	machine_uptime++;
	current_cycling_colour++;
	if (current_cycling_colour==7) {
		current_cycling_colour=0;
	}

	sub_frame_handler_dispatch();
	sub2_frame_handler_dispatch();
	execute_next_sub2_queued_function();
}

void engine_register_sound_effect_callback(void(*func)(int)) {
	sound_effect_callback=func;
}
