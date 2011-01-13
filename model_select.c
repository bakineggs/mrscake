/* model_select.c
   Automatic model selection.

   Part of the data prediction package.
   
   Copyright (c) 2010-2011 Matthias Kramm <kramm@quiss.org> 
 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <limits.h>
#include "model.h"
#include "model_select.h"
#include "ast.h"
#include "io.h"
#include "dataset.h"

#define NUM(l) (sizeof(l)/sizeof((l)[0]))

extern model_factory_t* ann_models[];
extern int num_ann_models;

extern model_factory_t* dtree_models[];
extern int num_dtree_models;

extern model_factory_t* svm_models[];
extern int num_svm_models;

typedef struct _model_collection {
    model_factory_t**models;
    int* num_models;
} model_collection_t;

model_collection_t collections[] = {
    {ann_models, &num_ann_models},
    {dtree_models, &num_dtree_models},
    {svm_models, &num_svm_models},
};

model_t* model_select(dataset_t*dataset)
{
    model_t*best_model = 0;
    model_factory_t*best_factory = 0;
    int best_score = INT_MAX;
    int t;
    int s;
    sanitized_dataset_t*data = dataset_sanitize(dataset);
    printf("%d classes, %d rows of examples\n", data->desired_response->num_classes, data->num_rows);
    for(s=0;s<NUM(collections);s++) {
        model_collection_t*collection = &collections[s];
        for(t=0;t<*collection->num_models;t++) {
            model_factory_t*factory = collection->models[t];
            printf("Trying %s... ", factory->name);fflush(stdout);
            model_t*m = factory->train(factory, dataset);
            if(m) {
                int size = model_size(m);
                printf("model size %d", size);fflush(stdout);
                int errors = model_errors(m, dataset);
                int score = size + errors;
                printf(", %d errors (score: %d)", errors, score);fflush(stdout);
                if(score < best_score) {
                    if(best_model) {
                        model_destroy(best_model);
                    }
                    best_score = score;
                    best_factory = factory;
                    best_model = m;
                } else {
                    model_destroy(m);
                }
            } else {
                printf("failed");
            }
            printf("\n");
        }
    }
    printf("Using %s.\n", best_factory->name);
    return best_model;
}

int model_errors(model_t*m, dataset_t*d)
{
    example_t*e = d->first_example;
    node_t*node = m->code;
    int t;
    int error = 0;

    node_t*code = (node_t*)m->code;
    environment_t*env = environment_new(code, 0);
    while(e) {
        env->row = example_to_row(e);
        constant_t c = node_eval(code, env);
        variable_t prediction = constant_to_variable(&c);

        if(!variable_equals(&prediction, &e->desired_response)) {
            error++;
        }
        row_destroy(env->row);env->row=0;
        e = e->next;
    }
    environment_destroy(env);
    return error;
}

int model_size(model_t*m)
{
    node_t*node = m->code;
    writer_t *w = nullwriter_new();
    node_write(node, w);
    int size = w->pos;
    w->finish(w);
    return size;
}

int model_score(model_t*m, dataset_t*d)
{
    return model_size(m) + model_errors(m, d);
}
