#include "kb.h"
#include "kb_typedefs.h"
#include "kb_debug.h"
#include "sensiml_recognition.h"

static char str_buffer[512];
static int last_model_result;
static int last_class_result;
static int last_segment_length;
static int last_feature_bank_number;

int get_last_segment_length()
{
    return last_segment_length;
}

int get_last_feature_bank_number()
{
    return last_feature_bank_number;
}

int get_last_result_model()
{
    return last_model_result;
}

int get_last_result_class()
{
    return last_class_result;
}

void sml_output_results(int model_index, int classification)
{
    last_model_result = model_index;
    last_class_result = classification;
    sml_get_segment_length(model_index, &last_segment_length);
    sml_get_feature_bank_number(model_index, &last_feature_bank_number);
    kb_print_model_result(model_index, classification, str_buffer, 0, NULL);
    printf("%s\r\n", str_buffer);
}

int sensiml_recognition(signed short *data, int number_packets, int num_sensors, int model_index)
{
    int ret = -1;
    int feature_bank_number = 0;
    int compIdx = 0;
    sml_get_feature_bank_number(model_index, &feature_bank_number);

    for (int i = 0; i < number_packets; i++)
    {

        if (feature_bank_number > 1)
        {
            ret = kb_run_model((SENSOR_DATA_T *)data, num_sensors, model_index);
        }
        else
        {
            ret = kb_run_model_with_cascade_features((SENSOR_DATA_T *)data[compIdx], num_sensors, model_index);
        }

        if (ret >= 0)
        {
            sml_output_results(model_index, ret);
            kb_reset_model(model_index);
        };
        compIdx += num_sensors;
    }
    return ret;
}

void sensiml_init()
{
    kb_model_init();
}
