/*
 *  eratosthene-suite - client
 *
 *      Nils Hamel - nils.hamel@bluewin.ch
 *      Copyright (c) 2016-2018 DHLAB, EPFL
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

    /*! \file   eratosthene-client-times.h
     *  \author Nils Hamel <nils.hamel@bluewin.ch>
     *
     *  eratosthene-suite - client - times
     */

/*
    header - inclusion guard
 */

    # ifndef __ER_CLIENT_TIMES__
    # define __ER_CLIENT_TIMES__

/*
    header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    header - internal includes
 */

    # include "eratosthene-client-common.h"
    # include "eratosthene-client-font.h"
    # include "eratosthene-client-view.h"

/*
    header - external includes
 */

/*
    header - preprocessor definitions
 */

    /* define pseudo-constructor */
    # define ER_TIMES_C      { 0, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, ER_FONT_ERATOSTHENE, _LE_FALSE }

    /* define string justification */
    # define ER_TIMES_LEFT   ( 0 )
    # define ER_TIMES_RIGHT  ( 1 )
    # define ER_TIMES_CENTER ( 2 )

    /* define interface string */
    # define ER_TIMES_MODES  { ( le_char_t * ) "\177", ( le_char_t * ) "ONLY", ( le_char_t * ) "ONLY", ( le_char_t * ) "OR", ( le_char_t * ) "AND", ( le_char_t * ) "XOR" }

/*
    header - preprocessor macros
 */

/*
    header - type definition
 */

/*
    header - structures
 */

    /*! \struct er_times_struct
     *  \brief Times structure
     *
     *  This structure holds the required information for the display of the
     *  temporal navigation slider. The temporal slider is used by the user to
     *  drive the display of Earth model according to time.
     *
     *  Through this slider, the user can move two separated time values to
     *  tell the graphical client what to display. In addition, the slider
     *  allows the user to change the times comparison mode.
     *
     *  The structure contains fields storing configuration of the slider
     *  display buffer shown on top of the Earth model. This includes slider
     *  buffer size and display position along with the buffer actual bytes.
     *
     *  The structure also contains fields storing pre-computed vertical and
     *  horizontal positions that are used to display slider texts.
     *
     *  \var er_times_struct::tm_width
     *  Width of the slider buffer, in pixels
     *  \var er_times_struct::tm_height
     *  Height of the slider buffer, in pixels
     *  \var er_times_struct::tm_length
     *  Size, in bytes, of the slider buffer
     *  \var er_times_struct::tm_offset
     *  Vertical position of the slider buffer - OpenGL screen position
     *  \var er_times_struct::tm_buffer
     *  Slider buffer bytes
     *  \var er_times_struct::tm_sh1
     *  Slider texts vertical position - Buffer position
     *  \var er_times_struct::tm_sh2
     *  Slider texts vertical position - Buffer position
     *  \var er_times_struct::tm_sh3
     *  Slider texts vertical position - Buffer position
     *  \var er_times_struct::tm_bh1
     *  Slider slider vertical position - Buffer position
     *  \var er_times_struct::tm_bh2
     *  Slider slider vertical position - Buffer position
     *  \var er_times_struct::tm_middle
     *  Slider horizontal middle position - Buffer & OpenGL screen position
     *  \var er_times_struct::tm_font
     *  Slider font structure - Text rendering
     *  \var er_times_struct::_status
     *  Standard status field
     */

    typedef struct er_times_struct {

        le_size_t   tm_width;
        le_size_t   tm_height;
        le_size_t   tm_length;
        le_size_t   tm_offset;

        le_byte_t * tm_buffer;

        le_size_t   tm_sh1;
        le_size_t   tm_sh2;
        le_size_t   tm_sh3;
        le_size_t   tm_bh1;
        le_size_t   tm_bh2;
        le_size_t   tm_middle;

        er_font_t   tm_font;

    le_enum_t _status; } er_times_t;

/*
    header - function prototypes
 */

    /*! \brief constructor/destructor methods
     *
     *  This function creates and returns a temporal slider structure. Based on
     *  the screen resolution and font size, the function pre-computes the
     *  interface elements horizontal and vertical positions.
     *
     *  The function also allocate the memory of the slider buffer and
     *  initialises its content. As the elements of the slider are drawn through
     *  the alpha component of the buffer, the initialisation of the RGB
     *  components made by this function stands during the whole execution.
     *
     *  \param er_width  OpenGL screen horizontal resolution, in pixels
     *  \param er_height OpenGL screen vertical resolution, in pixels
     *
     *  \return Returns the constructed time interface structure
     */

    er_times_t er_times_create( le_size_t const er_width, le_size_t const er_height );

    /*! \brief constructor/destructor methods
     *
     *  This function deletes the provided temporal slider structure. It
     *  releases the slider buffer memory allocation and clears the structure
     *  fields using default values.
     *
     *  \param er_times Time structure
     */

    le_void_t er_times_delete( er_times_t * const er_times );

    /*! \brief mutator methods
     *
     *  This function clears the slider buffer before its update. While the
     *  elements of the slider are only drawn through the alpha layer of its
     *  buffer, only the alpha components are reset by the function.
     *
     *  \param er_times Time structure
     */

    le_void_t er_times_set_buffer( er_times_t * const er_times );

    /*! \brief mutator methods
     *
     *  This function draws the elements of the temporal slider graduation scale
     *  in the buffer of the provided time structure.
     *
     *  The slider drawing is constituted of several passes on different
     *  log-scale adapted to the provided time window and centred on the time
     *  position of the point of view. A temporal graduation is displayed along
     *  with dates that correspond to the highest graduation marks.
     *
     *  \param er_times Time structure
     *  \param er_time  Position in time of the point of view
     *  \param er_area  Temporal range of the point of view
     */

    le_void_t er_times_set_slider( er_times_t * const er_times, le_time_t const er_time, le_time_t const er_area );

    /*! \brief display methods
     *
     *  This function is responsible of the temporal slider drawing and display
     *  in the OpenGL buffer. It is also responsible of the display of temporal
     *  slider texts.
     *
     *  The function starts by clearing the alpha layer of the slider buffer
     *  before to draw the graduation scale through the specialised function. It
     *  then displays the view structure times and the times comparison mode.
     *
     *  The temporal slider buffer is then drawn in the OpenGL buffer using the
     *  standard OpenGL routines. As the slider is drawn over the Earth model
     *  scene, this function has to be called after Earth model rendering.
     *
     *  \param er_times Time structure
     *  \param er_view  View structure
     */

    le_void_t er_times_display( er_times_t * const er_times, er_view_t const * const er_view );

    /*! \brief display methods
     *
     *  This function displays the provided date in the temporal slider buffer
     *  using the provided time structure font.
     *
     *  The function starts by converting the provided date in a text string
     *  that is written in the slider buffer using \b er_times_display_text()
     *  function. The date is converted using the libcommon date conversion
     *  function that follows the format : YYYY-MM-DD-hh-mm-ss.
     *
     *  \param er_times   Time structure
     *  \param er_date    Time value to display
     *  \param er_value   Display alpha component
     *  \param er_x       Display x-coordinate
     *  \param er_y       Display y-coordinate
     *  \param er_justify Text justification
     */

    le_void_t er_times_display_date( er_times_t * const er_times, le_time_t const er_date, le_byte_t const er_value, le_size_t er_x, le_size_t er_y, le_enum_t const er_justify );

    /*! \brief display methods
     *
     *  This function displays the provided text in the temporal slider buffer
     *  using the provided time structure font.
     *
     *  As buffers are used through OpenGL rendering, the y-coordinates are
     *  reversed. It follows that the specified x and y coordinates are the
     *  lower-left corner of the area in which the text is displayed.
     *
     *  The justification parameter is used to set text alignment. The three
     *  usual modes are available : \b ER_TIMES_LEFT, \b ER_TIMES_RIGHT and the
     *  \b ER_TIMES_CENTER mode.
     *
     *  \param er_times   Time structure
     *  \param er_text    Text string
     *  \param er_value   Display alpha component
     *  \param er_x       Display x-coordinate
     *  \param er_y       Display y-coordinate
     *  \param er_justify Text justification
     */

    le_void_t er_times_display_text( er_times_t * const er_times, le_char_t const * const er_text, le_byte_t const er_value, le_size_t er_x, le_size_t er_y, le_enum_t const er_justify );

/*
    header - C/C++ compatibility
 */

    # ifdef __cplusplus
    }
    # endif

/*
    header - inclusion guard
 */

    # endif

