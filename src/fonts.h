/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */


/* 
 * File:   fonts.h
 * Author: Djordje
 *
 * Created on March 31, 2023, 10:20 AM
 */

#ifndef FONTS_H
#define	FONTS_H

#include <stdint.h>

typedef struct{
    uint8_t width;
    uint8_t height;
    const uint8_t* font;
}font_t;

extern const uint8_t font_lucida_sans_7x12[];
extern const uint8_t font_lucida_sans_10x19[];
extern const uint8_t font_lucida_sans_14x24[];
extern const uint8_t font_lucida_sans_17x32[];
extern const uint8_t font_lucida_sans_20x38[];

#endif	/* FONTS_H */

