/**
 * \file 
 * \brief  Comparators
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef COMPARE_H_
#define COMPARE_H_

#include <stdio.h>
#include "text.h"

/**
 * \brief  Compares two strings using an alphabet order
 *
 * \return
 * - <0 The element pointed by item1 goes before the element pointed by item2 
 * - 0  The element pointed by item1 is equivalent to the element pointed by item2 
 * - >0 The element pointed by item1 goes after the element pointed by item2 
 */
int compare_alpha(const void *item1, const void *item2);

/**
 * \brief  Compares two strings using a back alphabet order
 *
 * \return
 * - <0 The element pointed by item1 goes before the element pointed by item2 
 * - 0  The element pointed by item1 is equivalent to the element pointed by item2 
 * - >0 The element pointed by item1 goes after the element pointed by item2 
 */
int compare_alpha_rev(const void *item1, const void *item2);

/**
 * \brief  Compares two integers using algebra
 *
 * \return
 * - <0 The element pointed by item1 goes before the element pointed by item2 
 * - 0  The element pointed by item1 is equivalent to the element pointed by item2 
 * - >0 The element pointed by item1 goes after the element pointed by item2 
 */
int compare_int(const void *item1, const void *item2);
#endif // COMPARE_H_
