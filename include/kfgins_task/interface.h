#ifndef INTERFACE_H_
#define INTERFACE_H_


#define TEMPLATE_ERROR_CODE_PCA_FAILED (1)
#define TEMPLATE_ERROR_CODE_PCA_NOT_ENOUGH_POINTS (2)

typedef struct template_input_t
{
    double point[3];
    bool flag;
}template_input_t;

typedef struct template_output_t
{
    double axis_x[3];
    double axis_y[3];
    bool flag;
}template_output_t;




#endif // INTERFACE_H_