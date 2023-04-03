#include "kb.h"
#include "kb_typedefs.h"
#include "kb_debug.h"
#include "sensiml_recognition.h"
#ifdef SML_USE_TEST_DATA
#include "testdata.h"
int td_index = 0;
#endif // SML_USE_TEST_DATA

#define SML_MODEL_INDEX 0

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

void sml_output_results(int model, int classification)
{
    last_model_result = model;
    last_class_result = classification;
    sml_get_segment_length(model, &last_segment_length);
    sml_get_feature_bank_number(model, &last_feature_bank_number);
    kb_print_model_result(model, classification, str_buffer, 0, NULL);
    printf("%s\r\n", str_buffer);
}

int sensiml_recognition(signed short *data, int num_sensors)
{
    int ret = -1;
    int feature_bank_number = 0;
    sml_get_feature_bank_number(SML_MODEL_INDEX, &feature_bank_number);

#ifdef SML_USE_TEST_DATA
    data = (SENSOR_DATA_T *)&testdata[td_index];

    if (td_index++ > TD_NUMROWS)
    {
        td_index = 0;
    }
#endif // SML_USE_TEST_DATA

    if (feature_bank_number > 1)
    {
        ret = kb_run_model((SENSOR_DATA_T *)data, num_sensors, SML_MODEL_INDEX);
    }
    else
    {
        ret = kb_run_model_with_cascade_features((SENSOR_DATA_T *)data, num_sensors, SML_MODEL_INDEX);
    }

    if (ret >= 0)
    {
        sml_output_results(SML_MODEL_INDEX, ret);
        kb_reset_model(SML_MODEL_INDEX);
    };
    return ret;
}

void sensiml_init()
{
    kb_model_init();
}