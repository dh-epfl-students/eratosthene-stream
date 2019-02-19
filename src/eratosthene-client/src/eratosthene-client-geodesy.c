/*
 *  eratosthene-suite - client
 *
 *      Nils Hamel - nils.hamel@bluewin.ch
 *      Copyright (c) 2016-2019 DHLAB, EPFL
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

    # include "eratosthene-client-geodesy.h"

/*
    source - conversion methods
 */

    le_void_t er_geodesy_cartesian( le_real_t * const er_point ) {

        /* angles variable */
        le_real_t er_angle[2] = { er_point[0], er_point[1] };

        /* compute coodinates conversion */
        er_point[2] += LE_ADDRESS_WGS_A;

        /* compute coodinates conversion */
        er_point[1] = er_point[2] * sin( er_angle[1] );
        er_point[2] = er_point[2] * cos( er_angle[1] );
        er_point[0] = er_point[2] * sin( er_angle[0] );
        er_point[2] = er_point[2] * cos( er_angle[0] );

    }

/*
    source - distance methods
 */

    le_real_t er_geodesy_distance( le_address_t const * const er_cell, er_view_t const * const er_view ) {

        /* computation array variables */
        le_real_t er_pose[12] = { 0.0 };

        /* half-cell distance variables */
        le_real_t er_scale = ( le_real_t ) ( 1 << ( le_address_get_size( er_cell ) + 1 ) );

        /* half-cell shift variables */
        le_real_t er_shift = LE_ADDRESS_RAN_L / er_scale;

        /* retrieve address edge */
        le_address_get_pose( er_cell, er_pose + 3 );

        /* retrieve view position */
        er_view_get_pose( er_view, er_pose + 9 );

        /* convert cell position - ellipsoidal to cartesian */
        er_pose[1] = er_pose[ 5] + LE_ADDRESS_WGS_A + ( LE_ADDRESS_WGS_A * LE_2P ) / er_scale;
        er_pose[0] = er_pose[ 1] * cos( er_pose[ 4] += er_shift );
        er_pose[2] = er_pose[ 0] * cos( er_pose[ 3] += er_shift );
        er_pose[0] = er_pose[ 0] * sin( er_pose[ 3] );
        er_pose[1] = er_pose[ 1] * sin( er_pose[ 4] );

        /* convert view position - ellipsoidal to cartesian */
        er_pose[7] = er_pose[11];
        er_pose[6] = er_pose[ 7] * cos( er_pose[10] );
        er_pose[8] = er_pose[ 6] * cos( er_pose[ 9] );
        er_pose[6] = er_pose[ 6] * sin( er_pose[ 9] );
        er_pose[7] = er_pose[ 7] * sin( er_pose[10] );

        /* compute dimensional differences */
        er_pose[2] -= er_pose[8], er_pose[0] -= er_pose[6], er_pose[1] -= er_pose[7];

        /* return computed distance */
        return( sqrt( er_pose[2] * er_pose[2] + er_pose[0] * er_pose[0] + er_pose[1] * er_pose[1] ) );

    }

/*
    source - model methods
 */


    le_real_t er_geodesy_face( le_real_t const er_altitude ) {

        /* computation variables */
        le_real_t er_normal = er_altitude / LE_ADDRESS_WGS_A - 1.0;

        /* return evaluation */
        return( er_altitude * ( 1.0 - 0.75 * exp( - LE_PI * er_normal * er_normal ) ) );

    }

    le_real_t er_geodesy_radius( le_real_t const er_altitude ) {

        /* computation variables */
        le_real_t er_normal = er_altitude / LE_ADDRESS_WGS_A - 1.0;

        /* return evaluation */
        return( er_altitude * ( 1.0 - 0.98 * exp( - LE_2P * 32.0 * er_normal * er_normal ) ) );

    }

    le_enum_t er_geodesy_select( le_real_t const er_distance, er_view_t const * const er_view, le_real_t const er_scfg, le_real_t const er_scale ) {

        /* clamping variables */
        le_real_t er_clamp = er_scfg - er_view_get_span( er_view ) - 2;

        /* computation variables */
        le_real_t er_normal = log( ( LE_ADDRESS_WGS_A / 2.0 ) / ( er_distance * 30.0 ) ) / M_LN2 + 9.5;

        /* check range */
        er_normal = ( er_normal < 5.0 ? 5.0 : ( er_normal > er_clamp ? er_clamp : er_normal ) );

        /* check selection condition */
        return( er_normal - er_scale < 1.0 ? _LE_TRUE : _LE_FALSE );

    }

    le_real_t er_geodesy_scale( le_real_t const er_altitude ) {

        /* computation variables */
        le_real_t er_normal = er_altitude / LE_ADDRESS_WGS_A - 1.0;

        /* Return evaluation */
        return( exp( - LE_PI * er_normal * er_normal ) );

    }

    le_real_t er_geodesy_near( le_real_t const er_altitude ) {

        /* computation variables */
        le_real_t er_normal = pow( fabs( er_altitude - LE_ADDRESS_WGS_A ) / ( LE_ADDRESS_WGS_A * 2.0 ), 4 );

        /* return evaluation */
        return( LE_ADDRESS_WGS_A * er_normal * er_geodesy_scale( er_altitude ) + 1.0 );

    }

    le_real_t er_geodesy_far( le_real_t const er_altitude ) {

        /* computation variables */
        le_real_t er_scale = er_geodesy_scale( er_altitude );

        /* computation vairbales */
        le_real_t er_plane = er_scale * er_geodesy_radius( er_altitude );

        /* computation variables */
        le_real_t er_clamp = er_scale * er_geodesy_face( er_altitude );

        /* return evaluation */
        return( er_plane >= er_clamp ? er_clamp : er_plane );

    }

