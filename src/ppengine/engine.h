#ifndef __ENGINE_H
#define __ENGINE_H

#include <inttypes.h>
#include "ppengine/structs.h"

#define PLAYER_CAR_OBJECT_INDEX 11

extern struct movingobject moving_objects[32];
extern struct sceneryobject scenery_objects[24];
extern struct hudentry hud_content[HUD_CONTENT_LENGTH];

extern void(*sound_effect_callback)(int);

extern uint16_t qualifying_initial_timer_switch;
extern uint16_t race_initial_timer_switch_1;
extern uint16_t race_initial_timer_switch_2;
extern uint16_t required_qualifying_times_switch;
extern uint16_t machine_uptime;
extern uint16_t current_cycling_colour;
extern uint16_t jump_table_function_number;
extern uint16_t jump_table_subfunction_number;
extern uint16_t extended_play_frames_remaining;
extern int16_t opponent_car_grinding_sideways_movement;
extern uint32_t forward_position;
extern uint32_t high_score;
extern uint32_t lap_time_bcd_displayed_outside_gameplay;
extern uint16_t displayed_speed_outside_gameplay;
extern uint32_t current_score_outside_gameplay;
extern int16_t steering_or_car_orientation;
extern uint16_t ticks_remaining;
extern uint16_t engine_sound_active;
extern uint32_t current_race_lap;
extern uint32_t fastest_ever_lap_bcd;
extern uint16_t steering_wheel_rotation;
extern uint16_t full_race_distance_completed;
extern uint32_t unknown_828c;
extern uint32_t unknown_8290;
extern uint16_t unknown_8292;
extern uint16_t cars_passing_tracking_enabled;
extern uint32_t current_score;
extern uint16_t unknown_82a6;
extern int16_t cpu_car_spawning_mode;
extern uint16_t session_seconds_updates_enabled;
extern uint16_t frames_until_next_countdown_update;
extern uint16_t scoring_enabled_flag;
extern int16_t lap_completion_events_counted;
extern uint16_t number_of_cpu_cars_in_use;
extern uint16_t lap_completion_events_in_single_game;
extern uint16_t second_fractions_remaining;
extern uint16_t seconds_remaining;
extern int16_t player_has_passed_start_line_in_current_session;
extern uint16_t lap_time_hundredths;
extern uint16_t ticks_until_next_lap_time_tenths_change;
extern uint16_t lap_time_tenths;
extern uint16_t lap_time_seconds;
extern uint32_t current_lap_time_bcd;
extern uint16_t previous_lap_time_display_ticks_remaining;
extern uint16_t qualifying_engine_started;
extern int32_t current_speed_8_bit_candidate_3;
extern uint16_t unknown_8020;
extern uint16_t session_end_animation_ticks_remaining;
extern uint16_t waiting_for_coin;
extern uint16_t unknown_82c2;
extern uint32_t previous_lap_time_bcd;
extern uint32_t fastest_session_lap_bcd;
extern int16_t high_precision_speed;
extern uint16_t session_engine_started;
extern int16_t target_engine_revs;
extern uint16_t internal_accel_pedal;
extern uint16_t unknown_8222;
extern int16_t clipped_steering;
extern int16_t clipped_steering_candidate_2;
extern uint32_t background_position;
extern uint16_t seconds_into_session;
extern uint16_t session_top_speed;
extern uint16_t steering_wheel_rotation_candidate_2;
extern uint16_t unknown_8022;
extern uint16_t unknown_8030;
extern uint32_t function_number_seconds_bcd;
extern uint16_t qualifying_session_state;
extern uint16_t race_hundredths_elapsed;
extern uint16_t race_tenths_elapsed;
extern uint16_t race_seconds_elapsed;
extern uint16_t unknown_a852;
extern uint32_t race_time_elapsed_bcd;
extern uint16_t qualifying_position_minus_one;
extern int16_t car_slowdown_factor;
extern uint16_t player_car_stopped_at_session_end;
extern int16_t unknown_81be;
extern uint16_t qualifying_complete_flag;
extern uint16_t cars_passed;
extern uint16_t gantry_and_starting_lights_appearance;
extern uint16_t sample_player_1;
extern uint16_t sample_player_2;
extern uint16_t new_lap_just_started;
extern uint16_t safe_to_change_gantry_appearance;
extern int16_t curve_at_player_forward_position;
extern uint16_t display_road_vertical_scroll;
extern uint16_t display_background_horizontal_scroll;
extern uint32_t current_score_times_100_bcd;
extern uint32_t high_score_bcd;
extern int32_t current_speed_8_bit;
extern uint32_t current_score_outside_gameplay_bcd;
extern int16_t target_actual_revs_relationship;
extern uint16_t engine_sound_pitch;
extern uint16_t current_speed_8_bit_candidate_2;
extern uint16_t unknown_80f2;
extern uint16_t unknown_822c;
extern uint16_t gear_hi_5_lo_a;
extern int16_t target_revs_increase;
extern uint16_t gear_binary;
extern int16_t actual_engine_revs;
extern int16_t unknown_8240;
extern uint16_t internal_brake_pedal;
extern int16_t unknown_8236;
extern int16_t unknown_8238;
extern int16_t unknown_823a;
extern int16_t unknown_824c;
extern int16_t unknown_823e;
extern int32_t unknown_8268;
extern int16_t sideways_pull;
extern int16_t unknown_8248;
extern uint16_t steering_multiplier;
extern uint16_t skidding_volume;
extern int16_t change_to_speed;
extern int16_t unknown_827a;
extern int16_t steering_wheel_frame_delta;
extern int16_t high_precision_sideways_position;
extern uint16_t off_track_sound_effect_pitch;
extern uint16_t slow_cpu_cars_ahead;
extern uint16_t pseudorandom_number;
extern uint16_t frame_counter;
extern uint16_t unknown_80e2;
extern uint16_t post_respawn_countdown;
extern uint16_t session_top_speed_bcd;
extern uint16_t qualifying_bonus;
extern uint16_t qualifying_outcome_cycling_value_tracker;
extern uint16_t unknown_80e8;
extern uint16_t unknown_82a6;
extern int16_t time_bonus;
extern uint32_t unknown_8282;
extern uint16_t unknown_8298;

// extensions
extern uint32_t credits_remaining;
extern uint32_t demo_frames;
extern uint32_t extended_play_visible;

void engine_initialise();
void engine_execute_frame();
void engine_register_sound_effect_callback(void(*func)(int));

#endif
