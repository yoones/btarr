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

#include <stdlib.h>
#include "btarr.h"

/*
** source: http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
*/
static int _is_power_of_two(unsigned int x)
{
  return ((x != 0) && !(x & (x - 1)));
}

int		btarr_init(t_btarr *btarr,
			   unsigned int node_size, unsigned int nb_leafs, unsigned char *root)
{
  if (!_is_power_of_two(nb_leafs))
    return (-1);
  btarr->nb_leafs = nb_leafs;
  btarr->root = root;
  btarr->node_size = node_size;
  return (0);
}

t_btarr		*btarr_make(size_t node_size, unsigned int nb_leafs, unsigned char *root)
{
  t_btarr	*btarr;
  int		ret;

  if (!_is_power_of_two(nb_leafs))
    return (NULL);
  btarr = malloc(node_size * nb_leafs);
  if (!btarr)
    return (NULL);
  if (root)
    {
      ret = btarr_init(btarr, node_size, nb_leafs, root);
      if (ret)
	{
	  free(btarr);
	  return (NULL);
	}
      return (btarr);
    }
  root = malloc(node_size * ((nb_leafs * 2) - 1));
  if (!root)
    {
      free(btarr);
      return (NULL);
    }
  ret = btarr_init(btarr, node_size, nb_leafs, root);
  if (ret)
    {
      free(root);
      free(btarr);
      return (NULL);
    }
  return (btarr);
}

unsigned int	btarr_get_nb_nodes(t_btarr *btarr)
{
  return ((2 * btarr->nb_leafs) - 1);
}

int		btarr_has_left(t_btarr *btarr, unsigned int index)
{
  return (index <= (btarr_get_nb_nodes(btarr) - btarr->nb_leafs));
}

int		btarr_has_right(t_btarr *btarr, unsigned int index)
{
  return (btarr_has_left(btarr, index));
}

int		btarr_has_parent(__attribute__((__unused__)) t_btarr *btarr,
				 unsigned int index)
{
  return (index > 1);
}

int		btarr_is_root(__attribute__((__unused__)) t_btarr *btarr,
			      unsigned int index)
{
  return (index == 1);
}

static unsigned int	_2_log_n(unsigned int n)
{
  unsigned int		i, j, k;

  i = 0;
  j = 1;
  k = 1;
  while (!(j <= n && k >= n))
    {
      i++;
      j = k;
      k *= 2;
      if (k < j)
	return (0);		/* overflow */
    }
  return (i);
}

unsigned int	btarr_get_height(t_btarr *btarr, unsigned int index)
{
  return (_2_log_n(btarr->nb_leafs) - btarr_get_depth(btarr, index));
}

unsigned int	btarr_get_depth(__attribute__((__unused__)) t_btarr *btarr,
				unsigned int index)
{
  unsigned int	i;

  for (i = 1; i <= index; i *= 2)
    ;
  index = i / 2;
  return (_2_log_n(index));
}

unsigned int	btarr_get_left_idx(t_btarr *btarr, unsigned int index)
{
  if (index >= btarr->nb_leafs)
    return (0);
  return (index * 2);
}

unsigned int	btarr_get_right_idx(t_btarr *btarr, unsigned int index)
{
  if (index >= btarr->nb_leafs)
    return (0);
  return (btarr_get_left_idx(btarr, index) + 1);
}

unsigned int	btarr_get_parent_idx(__attribute__((__unused__)) t_btarr *btarr,
				     unsigned int index)
{
  index -= (index % 2);
  return (index / 2);
}

unsigned int	btarr_get_most_left_leaf_idx(t_btarr *btarr, unsigned int index)
{
  while (index < btarr->nb_leafs)
    index = index * 2;
  return (index);
}

unsigned int	btarr_get_most_right_leaf_idx(t_btarr *btarr, unsigned int index)
{
  while (index < btarr->nb_leafs)
    index = (index * 2) + 1;
  return (index);
}

unsigned char	*btarr_get(t_btarr *btarr, unsigned int index)
{
  return (btarr->root + ((index - 1) * btarr->node_size));
}

unsigned char	*btarr_get_left(t_btarr *btarr, unsigned int index)
{
  return (btarr_get(btarr, btarr_get_left_idx(btarr, index)));
}

unsigned char	*btarr_get_right(t_btarr *btarr, unsigned int index)
{
  return (btarr_get(btarr, btarr_get_right_idx(btarr, index)));
}

unsigned char	*btarr_get_parent(t_btarr *btarr, unsigned int index)
{
  return (btarr_get(btarr, btarr_get_parent_idx(btarr, index)));
}

unsigned char	*btarr_get_most_left_leaf(t_btarr *btarr, unsigned int index)
{
  return (btarr_get(btarr, btarr_get_most_left_leaf_idx(btarr, index)));
}

unsigned char	*btarr_get_most_right_leaf(t_btarr *btarr, unsigned int index)
{
  return (btarr_get(btarr, btarr_get_most_right_leaf_idx(btarr, index)));
}
