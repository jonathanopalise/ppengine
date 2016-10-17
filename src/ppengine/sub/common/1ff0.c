#include <stdlib.h>
#include <stdio.h>
#include "ppengine/sub/common/1ff0.h"
#include "ppengine/sub/data/acceleration_lookup.h"
#include "ppengine/sub/data/loc_223e_lookup.h"
#include "ppengine/engine.h"

void common_2058();
void common_212c();
void common_2174();
void common_21b4();
void common_221a();
void common_227c();
void common_231e();
void common_235e();
void common_239e();
void common_244c();
void common_24b0();
void common_260c();
void common_263c();

void common_1ff0() {
	int16_t current_speed_8_bit_candidate_3_high_word;
	uint16_t revs_divider;

	common_2058();
	common_212c();
	common_2174();
	common_21b4();
	common_221a();
	common_227c();
	common_231e();
	common_235e();
	common_244c();
	common_24b0();
	common_260c();
	common_263c();

	if (race_initial_timer_switch_2<=3) {
		revs_divider=0x4e;
	} else if (race_initial_timer_switch_2<=5) {
		revs_divider=0x48;
	} else {
		revs_divider=0x42;
	}

	// loc_2024
	engine_sound_pitch=target_engine_revs/revs_divider;

	current_speed_8_bit_candidate_3_high_word=current_speed_8_bit_candidate_3>>16;
	if (current_speed_8_bit_candidate_3_high_word<0) {
		current_speed_8_bit_candidate_3_high_word=0;
	} else if (current_speed_8_bit_candidate_3_high_word>0xff) {
		current_speed_8_bit_candidate_3_high_word=0xff;
	}

	// loc_204a
	current_speed_8_bit_candidate_2=current_speed_8_bit_candidate_3_high_word;
	unknown_80f2=unknown_822c;
}

void common_2058() {
	int16_t absolute_target_engine_revs_difference;
	int16_t target_engine_revs_difference;
	int16_t potential_target_revs;

	if (!session_engine_started) {
		// loc_20e4
		target_actual_revs_relationship=0;
		potential_target_revs=((target_revs_increase-9)*10)+target_engine_revs;
		if (potential_target_revs>0) {
			target_engine_revs=potential_target_revs;
		} else {
			target_engine_revs=0;
		}
	} else {
		if (waiting_for_coin) {
			if ((current_speed_8_bit_candidate_3>>16)<0x64) {
				gear_hi_5_lo_a=0xa;
			} else {
				gear_hi_5_lo_a=0x5;
			}
		} else if (gear_binary&1) {
			gear_hi_5_lo_a=0x5;
		} else {
			gear_hi_5_lo_a=0xa;
		}

		// loc_2086
		target_engine_revs_difference=actual_engine_revs-target_engine_revs;
		absolute_target_engine_revs_difference=abs(target_engine_revs_difference);

		// loc_2094
		if (absolute_target_engine_revs_difference>=0xc8) {
			// loc_209a
			target_actual_revs_relationship=1;
			if (target_engine_revs_difference>=0) {
				target_engine_revs+=(target_revs_increase+10)*6;
			} else {
				// loc_20c4
				target_engine_revs+=(target_revs_increase-60)*6;
			}
			if (target_engine_revs<0) {
				target_engine_revs=0;
			}
		} else {
			// loc_210c
			target_actual_revs_relationship=-1;
			target_engine_revs=actual_engine_revs;
		}
	}

	// loc_211a
	actual_engine_revs=(high_precision_speed*gear_hi_5_lo_a)/4;
}

void common_212c() {
	uint16_t acceleration_lookup_offset;
	uint8_t acceleration_lookup_value;

	acceleration_lookup_offset=target_engine_revs>>10;
	if (acceleration_lookup_offset<0x0e) {
		if (race_initial_timer_switch_2<=3) {
			acceleration_lookup_value=acceleration_lookup_1[acceleration_lookup_offset];
		} else if (race_initial_timer_switch_2<=5) {
			acceleration_lookup_value=acceleration_lookup_2[acceleration_lookup_offset];
		} else {
			acceleration_lookup_value=acceleration_lookup_3[acceleration_lookup_offset];
		}
		target_revs_increase=(internal_accel_pedal*acceleration_lookup_value)>>3;
	} else {
		target_revs_increase=0;
	}
}

void common_2174() {
	int16_t target_engine_revs_plus_one;
	int16_t actual_engine_revs_plus_one;

	target_engine_revs_plus_one=target_engine_revs+1;
	actual_engine_revs_plus_one=actual_engine_revs+1;
	if (target_engine_revs_plus_one>=actual_engine_revs_plus_one) {
		// loc_219c
		unknown_8236=(0-(actual_engine_revs_plus_one*150/target_engine_revs_plus_one))+250;
		unknown_8238=0;
	} else {
		unknown_8238=(0-(target_engine_revs_plus_one*150/actual_engine_revs_plus_one))+250;
		unknown_8236=0;
	}
}

void common_21b4() {
	int32_t unknown_derived_value;
	if (target_actual_revs_relationship==0) {
		// loc_21ea
		unknown_822c=0;
		// loc_21f0
		unknown_823a=0;
	} else if (target_actual_revs_relationship>0) {
		// loc_21f8
		unknown_822c=(target_revs_increase*unknown_8236)/100;
		unknown_823a=(unknown_8238*20)/100;
	} else {
		unknown_822c=target_revs_increase;
		unknown_derived_value=((target_revs_increase*gear_hi_5_lo_a)<<5)-unknown_824c;
		if (unknown_derived_value>=0) {
			// loc_21f0
			unknown_823a=0;
		} else {
			unknown_823a=((0-(unknown_derived_value>>2))&0xf)+5;
		}
	}
}

void common_221a() {
	// TODO: continue reviewing this at 2248
	int32_t unknown_8240_temp;
	uint16_t r0;
	uint16_t r2;
	uint16_t r3;

	unknown_8240_temp=unknown_8240;
	unknown_8240_temp=abs(unknown_8240_temp);
	unknown_8240_temp&=0x0000ffff;
	if ((internal_brake_pedal==0) || (unknown_823a==0)) {
		// loc_223e
		unknown_8240_temp=(unknown_8240_temp-8000)/80;
	} else {
		unknown_8240_temp=(unknown_8240_temp-10000)/120;
	}

	// loc_2248
	r2=r0=loc_223e_lookup[(qualifying_engine_started&1)|(race_initial_timer_switch_2&6)];
	r3=r0>>1;
	r0-=(uint16_t)unknown_8240_temp;
	if (r0>r2) {
		r0=r2;
	}
	if (r0<r3) {
		r0=r3;
	}
	unknown_823e=r0;
}

void common_227c() {
	int32_t rr0;

	rr0=(((unknown_822c-unknown_823a)*gear_hi_5_lo_a)<<5)-(internal_brake_pedal*1300);
	if (rr0>12000) {
		rr0=10000;
	}
	if (rr0<-15000) {
		rr0=-12000;
	}

	// loc_22b2
	unknown_8240=rr0&0xffff;
	unknown_8268=(high_precision_speed/100)*(high_precision_speed/100);
	sideways_pull=(((unknown_8268>>8)&0xffff)*clipped_steering_candidate_2)/14;

	if (unknown_8222==0) {
		// loc_22f6
		unknown_8248=1;
		steering_multiplier=10;
		skidding_volume=0;
	} else if ((unknown_8222&2)==2) {
		// loc_230a
		unknown_8248=10;
		steering_multiplier=5;
		skidding_volume=8;
	} else {
		unknown_8248=3;
		steering_multiplier=9;
		skidding_volume=4;
	}
}

void common_231e() {
	uint32_t change_to_speed_as_int32;

	unknown_824c=((unknown_8248*1200)+unknown_8268)>>1;
	change_to_speed_as_int32=(unknown_8240-unknown_824c)>>2;
	change_to_speed=change_to_speed_as_int32&0xffff;
	high_precision_speed+=(change_to_speed_as_int32>>6);
	if (high_precision_speed<0) {
		high_precision_speed=0;
	}
}

void common_235e() {
	int16_t sideways_pull_temp;
	int16_t unknown_823e_temp;
	int16_t r1;
	uint16_t destination;

	sideways_pull_temp=abs(sideways_pull)*5;
	unknown_823e_temp=unknown_823e*3;

	if ((uint16_t)unknown_823e_temp>=(uint16_t)sideways_pull_temp) {
		destination=0x23e4;
	} else {
		unknown_8222&=0xfffe; // res 0x8222,#0
		unknown_823e_temp+=unknown_823e; // add r2,r0
		if ((uint16_t)unknown_823e_temp>=(uint16_t)sideways_pull_temp) { // cmp r2,r1
			destination=0x23ea; // jr nc,loc_23ea
		} else {
			unknown_8222|=1; // set 0x8222,#0
			unknown_823e_temp+=unknown_823e; // add r2,r0
			if ((uint16_t)unknown_823e_temp>=(uint16_t)sideways_pull_temp) { // cp r2,r1
				destination=0x23ea; // jr nc,loc_23ea
			} else {
				if ((unknown_8222&2)==0) {
					destination=0x23d0;
				} else {
					unknown_8222=3;
					destination=0x239e;
				}
			}
		}
	}

	if (destination==0x239e) {
		common_239e();
	} else if (destination==0x23d0) {
		// loc_23d0
		unknown_8222=3;
		unknown_827a=clipped_steering_candidate_2;
		clipped_steering=clipped_steering_candidate_2;
	} else {
		if (destination==0x23e4) {
			unknown_8222=0;
		}
		if ((unknown_8222&2)==2) {
			common_239e();
		} else {
			if (abs(clipped_steering-unknown_827a)<=5) {
				unknown_827a=clipped_steering_candidate_2;
				clipped_steering=clipped_steering_candidate_2;
			} else {
				unknown_827a=clipped_steering_candidate_2;
				r1=high_precision_speed;
				if (clipped_steering_candidate_2-clipped_steering<0) {
					r1=-r1;
				}
				r1=(r1/600)+clipped_steering;
				if (r1<-127) {
					r1=-127;
				}
				if (r1>127) {
					r1=127;
				}
				clipped_steering=r1;
			}
		}
	}
}

void common_239e() {
	unknown_827a=clipped_steering_candidate_2;
	clipped_steering+=(sideways_pull/32);
	if (clipped_steering<-127) {
		clipped_steering=-127;
	} else if (clipped_steering>127) {
		clipped_steering=127;
	}
}

void common_244c() {
	int16_t proposed_high_precision_sideways_position;
	int16_t old_proposed_high_precision_sideways_position;

	int16_t proposed_steering_wheel_frame_delta;
	uint16_t old_steering_wheel_rotation_candidate_2;
	int overflow;

	// TODO: review these two lines
	old_steering_wheel_rotation_candidate_2=steering_wheel_rotation_candidate_2;
	steering_wheel_rotation_candidate_2=steering_wheel_rotation;

	proposed_steering_wheel_frame_delta=(int8_t)((old_steering_wheel_rotation_candidate_2&0xff)-(steering_wheel_rotation&0xff));
	if (abs(proposed_steering_wheel_frame_delta)>0xa) {
		steering_wheel_frame_delta=0;
	} else {
		steering_wheel_frame_delta=proposed_steering_wheel_frame_delta;
	}

	steering_or_car_orientation=clipped_steering;
	proposed_high_precision_sideways_position=(((steering_or_car_orientation*steering_multiplier)/10)-curve_at_player_forward_position);
	proposed_high_precision_sideways_position=-proposed_high_precision_sideways_position;
	proposed_high_precision_sideways_position*=current_speed_8_bit_candidate_3>>16;
	proposed_high_precision_sideways_position>>=3;
	proposed_high_precision_sideways_position+=(proposed_high_precision_sideways_position>>1);

	overflow=0;
	old_proposed_high_precision_sideways_position=proposed_high_precision_sideways_position;
	proposed_high_precision_sideways_position+=high_precision_sideways_position;
	if ((old_proposed_high_precision_sideways_position>=0) && (high_precision_sideways_position>=0)) {
		if (proposed_high_precision_sideways_position<0) {
			overflow=1;
		}
	} else if ((old_proposed_high_precision_sideways_position<0) && (high_precision_sideways_position<0)) {
		if (proposed_high_precision_sideways_position>=0) {
			overflow=1;
		}		
	}

	if (!overflow) {
		high_precision_sideways_position=proposed_high_precision_sideways_position;
		if (high_precision_sideways_position<0) {
			high_precision_sideways_position+=1;
		}
	}
}

void common_24b0() {
	int16_t r0;
	int16_t r1;
	int16_t r2;
	int16_t r3;
	int16_t r4;
	int16_t r5;
	int16_t r6;

	uint16_t destination;
	uint32_t adds;

	if (full_race_distance_completed || waiting_for_coin) {
		if (seconds_into_session>3) {
			clipped_steering_candidate_2=((0-clipped_steering_candidate_2)>>3)+clipped_steering_candidate_2;;
			clipped_steering_candidate_2=(high_precision_sideways_position/2000)+clipped_steering_candidate_2;
		}
	} else {
		r1=clipped_steering_candidate_2;
		r0=r1;
		r3=steering_wheel_frame_delta;
		r4=machine_uptime&3;
		if (r4==0) {
			r3+=opponent_car_grinding_sideways_movement;
		}
		opponent_car_grinding_sideways_movement=0;
		r2=r3;
		if (qualifying_engine_started) {
			r4=r0-curve_at_player_forward_position;
			if (r4!=0) {
				r5=abs(r4);
				if (r5<0x2) {
					// loc_253a
					r6=0x1f;
					destination=0x2556;
				} else if (r5<0x4) {
					// loc_2540
					r6=0xf;
					destination=0x2556;
				} else if (r5<0x6) {
					// loc_2546
					r6=0x7;
					destination=0x2556;
				} else if (r5<0x8) {
					// loc_254c
					r6=0x3;
					destination=0x2556;
				} else if (r5<0xa) {
					// loc_2552
					r6=0x1;
					destination=0x2556;
				} else if (r5<0x10) {
					// loc_2526
					r6=0x1;
					destination=0x2530;
				} else if (r5<0x20) {
					// loc_252c
					r6=0x2;
					destination=0x2530;
				} else {
					r6=0x3;
					destination=0x2530;
				}
				if (destination==0x2530) {
					if (r4<0) {
						r4=-r6;
					} else {
						r4=r6;
					}
					destination=0x256c;
				} else {
					if (r4>=0) {
						r4=1;
					} else {
						r4=-1;
					}
					destination=0x2562;
				}
			} else {
				destination=0x256a;
			}
			if (destination==0x2562) {
				r5=machine_uptime&r6;
				if (r5!=0) {
					r4=0;
				}
			} else if (destination==0x256a) {
				r4=0;
			}
			// loc_256c 
			r1=abs(r1);
			// loc_2572
			if (r1<0x9) {
				adds=1;
			} else if (r1<0x2d) {
				adds=2;
			} else {
				adds=3;
			}
			while (adds>0) {
				r2+=r3;
				adds--;
			}
			r2+=r0;
			r2-=r4;
			if (r2<-127) {
				r2=-127;
			} else if (r2>127) {
				r2=127;
			}
			clipped_steering_candidate_2=r2;
		} else {
			// loc_25a4
			r4=0;
			r1=abs(r1);
			if (r1<0x9) {
				adds=0;
			} else if (r1<0x2d) {
				adds=1;
			} else {
				adds=3;
			}
			while (adds>0) {
				r2+=r3;
				adds--;
			}
			// loc_25be
			r2+=r0;
			r2-=r4;
			if (r2<-127) {
				r2=-127;
			} else if (r2>127) {
				r2=127;
			}
			// loc_25d8
			clipped_steering_candidate_2=r2;
		}
	}
}

void common_260c() {
	// TODO: implement later - don't think this is core functionality
}

void common_263c() {
	// TODO: implement later - don't think this is core functionality
}

