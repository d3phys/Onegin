/**
 * \file 
 * \brief  Error types
 * \author d3phys
 * \date   03.09.2021
 */
#ifndef _ERROR_T_H_
#define _ERROR_T_H_

/**
 * \brief Error codes 
 */
enum error_t {
    SUCCESS = 0, /**< Succes                  */
    FOPEN   = 1, /**< Opening file error      */
    FCLOSE  = 2, /**< Closing file error      */
    ALLOC   = 3, /**< Allocation memory error */
};

#endif // _ERROR_T_H_
