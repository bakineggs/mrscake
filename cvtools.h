#ifndef __CVTOOLS_H__
#define __CVTOOLS_H__

#include "ml.hpp"
#include "lib/core_c.h"
#include "model.h"
#include "dataset.h"
#include "lib/internal.hpp"

/* FIXME- these should come from opencv's include files */
CVAPI(CvMat*) cvCreateMat( int rows, int cols, int type );
CVAPI(void) cvSet(void* arr, CvScalar value, const void* maskarr);
CvMat* cv_preprocess_categories( const CvMat* responses,
    const CvMat* sample_idx, int sample_all,
    CvMat** out_response_map, CvMat** class_counts );

class CvMLDataFromExamples: public CvMLData
{
    public:
    CvMLDataFromExamples(sanitized_dataset_t*dataset);
    ~CvMLDataFromExamples();
};

CvMat*cvmat_from_row(row_t*row, bool add_one);

void cvmSetI(CvMat*m, int y, int x, int v);
void cvmSetF(CvMat*m, int y, int x, float f);
int cvmGetI(const CvMat*m, int y, int x);
float cvmGetF(const CvMat*m, int y, int x);

#endif // __CVTOOLS_H__
