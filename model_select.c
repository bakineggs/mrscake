#include "model.h"
#include "model_select.h"

model_t* model_select(dataset_t*dataset)
{
    //return dtree_model_factory.train(dataset);
    return ann_model_factory.train(dataset);
}
