/* transform.h
   Dataset transformations

   Part of the mrscake data prediction package.
   
   Copyright (c) 2010-2012 Matthias Kramm <kramm@quiss.org> 
 
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

#ifndef __transform_h__
#define __transform_h__

#include <stdbool.h>
#include "dataset.h"
#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

/* transformations */
dataset_t* expand_categorical_columns(dataset_t*old_dataset);

dataset_t* reverse_transformation(dataset_t*dataset, node_t**code);
dataset_t* reverse_transformations(dataset_t*dataset, node_t**code);

#ifdef __cplusplus
}
#endif
#endif