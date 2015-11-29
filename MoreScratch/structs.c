#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tagMATH_NUMERIC {

    char value[100];
    char *error;

} MATH_NUMERIC;

typedef struct tagDEFINED_DS {

    MATH_NUMERIC input;
    MATH_NUMERIC output;

} DEFINED_DS;

void print_ds(DEFINED_DS *);

int main()
{
    double cnv_input, cnv_output;

    char hold_str[100];


    MATH_NUMERIC input_string = { .value = "10.00" };
    MATH_NUMERIC output_string = { .value = "" };

    DEFINED_DS *ds = malloc(sizeof(DEFINED_DS));

    ds->input = input_string;
    ds->output = output_string;

    cnv_input = strtol(ds->input.value, NULL, 10);
    ds->input.error = "ok";

    cnv_output = cnv_input + 10.00;

    fprintf(stdout, "cnv_input: %f\ncnv_output: %f\n", cnv_input, cnv_output);

    print_ds(ds);

    snprintf(hold_str, 10, "%f", cnv_output);
    ds->output.error = "ok";

    strcpy(ds->output.value, hold_str);

    print_ds(ds);


    return 0;
}


void print_ds(DEFINED_DS *ds)
{
    printf("\nprint_ds\n");
    printf("input: %s\noutput: %s\n", ds->input.value, ds->output.value);
    printf("input error: %s\noutput error: %s\n", ds->input.error, ds->output.error);
}
