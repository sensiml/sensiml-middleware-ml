#ifndef __SML_RECOGNITION_RUN_H__
#define __SML_RECOGNITION_RUN_H__

#ifdef __cplusplus
extern "C" {
#endif

int get_last_segment_length();
int get_last_result_model();
int get_last_result_class();
int get_last_feature_bank_number();
void sml_output_results(int model, int classification);
int sensiml_recognition(signed short *data, int number_packets, int num_sensors,
                        int model_index);
void sensiml_init();

#ifdef __cplusplus
}
#endif
#endif //__SML_RECOGNITION_RUN_H__
