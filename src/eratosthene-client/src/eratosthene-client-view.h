/*
 *  eratosthene-suite - eratosthene indexation server front-end
 *
 *      Nils Hamel - nils.hamel@bluewin.ch
 *      Copyright (c) 2016 EPFL CDH DHLAB
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

    /*! \file   eratosthene-client-view.h
     *  \author Nils Hamel <n.hamel@bluewin.ch>
     *
     *  Eratosthene client - view module
     */

/*
    header - inclusion guard
 */

    # ifndef __ER_CLIENT_VIEW__
    # define __ER_CLIENT_VIEW__

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

/*
    header - external includes
 */

/*
    header - preprocessor definitions
 */

    /* define pseudo-constructor */
    # define ER_VIEW_C { 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0 }

    /* define pseudo-constructor - default point of view */
    # define ER_VIEW_D { 12.335435, 45.438531, LE_ADDRESS_WGSA * 1.5, 0.0, 0.0, 1, 0, 950486422, 0, 31536000, 31536000 }

/*
    header - preprocessor macros
 */

/*
    header - type definition
 */

/*
    header - structures
 */

    typedef struct er_view_struct {

        le_real_t vw_lon;
        le_real_t vw_lat;
        le_real_t vw_alt;
        le_real_t vw_azm;
        le_real_t vw_gam;

        le_enum_t vw_mod;
        le_enum_t vw_act;
        le_time_t vw_tia;
        le_time_t vw_tib;
        le_time_t vw_zta;
        le_time_t vw_ztb;

    } er_view_t;


/*
    header - function prototypes
 */

    er_view_t er_view_create( le_void_t );

    le_void_t er_view_delete( er_view_t * const er_view );

    le_real_t er_view_get_lon( er_view_t const * const er_view );

    le_real_t er_view_get_lat( er_view_t const * const er_view );

    le_real_t er_view_get_alt( er_view_t const * const er_view );

    le_real_t er_view_get_azm( er_view_t const * const er_view );

    le_real_t er_view_get_gam( er_view_t const * const er_view );

    le_void_t er_view_get_pose( er_view_t const * const er_view, le_real_t * const er_pose );

    le_enum_t er_view_get_mode( er_view_t const * const er_view );

    le_enum_t er_view_get_active( er_view_t const * const er_view );

    le_time_t er_view_get_time( er_view_t const * const er_view, le_enum_t const er_time );

    le_address_t er_view_get_times( er_view_t const * const er_view );

    le_time_t er_view_get_area( er_view_t const * const er_view, le_enum_t const er_time );

    er_view_t er_view_get_inter( er_view_t const * const er_views, le_size_t const er_index, le_real_t const er_param );

    le_void_t er_view_set_plan( er_view_t * const er_view, le_real_t const er_xvalue, le_real_t const er_yvalue );

    le_void_t er_view_set_alt( er_view_t * const er_view, le_real_t const er_value );

    le_void_t er_view_set_azm( er_view_t * const er_view, le_real_t const er_value );

    le_void_t er_view_set_gam( er_view_t * const er_view, le_real_t const er_value );

    le_void_t er_view_set_mode( er_view_t * const er_view, le_enum_t const er_mode );

    le_void_t er_view_set_swap( er_view_t * const er_view );

    le_void_t er_view_set_time( er_view_t * const er_view, le_real_t const er_value );

    le_void_t er_view_set_area( er_view_t * const er_view, le_real_t const er_value );

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
