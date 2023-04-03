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
int sml_recognition_run(signed short *data, int num_sensors);

#ifdef __cplusplus
}
#endif
#endif //__SML_RECOGNITION_RUN_H__
