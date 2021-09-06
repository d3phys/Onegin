/**
 * input/output
 * \author d3phys
 * \date 05.09.2021
*/
#ifndef IO_H_
#define IO_H_

#include <stdio.h>

/*!
 * \brief ASCII colors enum
*/
enum color {
    RED = 1,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
};

/*!
 * \brief Sets console text color
 *
 * Function sets ASCII text console color
 *
 * \param  text Text color
 *
 * \return 
 * The same as printf() function
*/
int set_text_color(color text);

/*!
 * \brief Sets console background color
 *
 * Function sets ASCII background console color
 *
 * \param  background Background color
 *
 * \return 
 * Negative value in case of error 
*/
int set_back_color(color background);

/*!
 * \brief Resets console color settings
 *
 * \warning Function resets both background and text color settings
 *
 * \return 
 * Negative value in case of error 
*/
int reset_color(); 


#endif // IO_H_
