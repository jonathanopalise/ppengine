
#define DETECT_INSERTED_COIN \
if (credits_remaining>0) {\
	credits_remaining--;\
	waiting_for_coin=0;\
	ticks_remaining=0;\
	jump_table_function_number=2;\
	jump_table_subfunction_number=0;\
	return;\
}
