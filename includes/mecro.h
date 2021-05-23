/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mecro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:38:03 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 16:54:06 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MECRO_H
# define MECRO_H

# define MAP_CHAR " 012345NSEW"
# define N_TEX 1
# define S_TEX 2
# define W_TEX 3
# define E_TEX 4
# define M_TEX 5
# define SP_TEX 6
# define F_TEX 7
# define CE_TEX 8
# define F_COL 9
# define C_COL 10
# define RESOLUTION 11
# define EMPTY_LINE 12
# define MAP_LINE 13
# define XPM_EXTENSION ".xpm"
# define PLAYER "NSEW"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_AR_L 123
# define KEY_AR_R 124
# define KEY_AR_U 126
# define KEY_AR_D 125

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT  17

# define PI 3.1415926535897
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

#endif
