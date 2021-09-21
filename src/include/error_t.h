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
    SUCCESS      =  0, /**< Succes                  */
    FOPEN        = -1, /**< Opening file error      */
    FERROR       = -2, /**< Closing file error      */
    BAD_ALLOC    = -3, /**< Allocation memory error */
    INCORR_INPUT = -4, /**< Incorrect input error   */
    BAD_FORMAT   = -5, /**< Badly formatted text    */
};

#endif // _ERROR_T_H_
