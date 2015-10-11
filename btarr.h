/*
** This file is part of libbtarr.
**
** libbtarr is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** libbtarr is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with libbtarr.  If not, see <http://www.gnu.org/licenses/>.
**
*/

#ifndef BTARR_H_
# define BTARR_H_

typedef struct	s_btarr
{
  unsigned int	node_size;
  unsigned int	nb_leafs;
  unsigned char	*root;
}		t_btarr;

int		btarr_init(t_btarr *btarr,
			   unsigned int node_size, unsigned int nb_leafs, unsigned char *root);
t_btarr		*btarr_make(size_t node_size, unsigned int nb_leafs, unsigned char *root);
unsigned int	btarr_get_nb_nodes(t_btarr *btarr);

int		btarr_has_left(t_btarr *btarr, unsigned int index);
int		btarr_has_right(t_btarr *btarr, unsigned int index);
int		btarr_has_parent(t_btarr *btarr, unsigned int index);
int		btarr_is_root(t_btarr *btarr, unsigned int index);

unsigned int	btarr_get_height(t_btarr *btarr, unsigned int index);
unsigned int	btarr_get_depth(t_btarr *btarr, unsigned int index);

unsigned int	btarr_get_left_idx(t_btarr *btarr, unsigned int index);
unsigned int	btarr_get_right_idx(t_btarr *btarr, unsigned int index);
unsigned int	btarr_get_parent_idx(t_btarr *btarr, unsigned int index);
unsigned int	btarr_get_most_left_leaf_idx(t_btarr *btarr, unsigned int index);
unsigned int	btarr_get_most_right_leaf_idx(t_btarr *btarr, unsigned int index);

unsigned char	*btarr_get(t_btarr *btarr, unsigned int index);
unsigned char	*btarr_get_left(t_btarr *btarr, unsigned int index);
unsigned char	*btarr_get_right(t_btarr *btarr, unsigned int index);
unsigned char	*btarr_get_parent(t_btarr *btarr, unsigned int index);
unsigned char	*btarr_get_most_left_leaf(t_btarr *btarr, unsigned int index);
unsigned char	*btarr_get_most_right_leaf(t_btarr *btarr, unsigned int index);

#endif
