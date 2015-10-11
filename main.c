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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "btarr.h"

#define TEST_NODE_SIZE		20
#define TEST_NB_LEAFS		8
#define TEST_NB_NODES		15
#define TEST_ROOT_HEIGHT	3

void		test_btarr_make(t_btarr **btarr)
{
  *btarr = btarr_make(TEST_NODE_SIZE, TEST_NB_LEAFS, NULL);
  assert(*btarr != NULL);
  assert((*btarr)->node_size == TEST_NODE_SIZE);
  assert((*btarr)->nb_leafs == TEST_NB_LEAFS);
  assert((*btarr)->root != NULL);
  assert(btarr_get_nb_nodes(*btarr) == TEST_NB_NODES);
}

void		test_btarr_has_xxx(t_btarr *btarr)
{
  /* root */
  assert(btarr_has_left(btarr, 1) == 1);
  assert(btarr_has_right(btarr, 1) == 1);
  assert(btarr_has_parent(btarr, 1) == 0);
  assert(btarr_is_root(btarr, 1) == 1);

  /* nodes in the middle */
  assert(btarr_has_left(btarr, 2) == 1);
  assert(btarr_has_right(btarr, 2) == 1);
  assert(btarr_has_parent(btarr, 2) == 1);
  assert(btarr_is_root(btarr, 2) == 0);

  assert(btarr_has_left(btarr, 5) == 1);
  assert(btarr_has_right(btarr, 5) == 1);
  assert(btarr_has_parent(btarr, 5) == 1);
  assert(btarr_is_root(btarr, 5) == 0);

  assert(btarr_has_left(btarr, 7) == 1);
  assert(btarr_has_right(btarr, 7) == 1);
  assert(btarr_has_parent(btarr, 7) == 1);
  assert(btarr_is_root(btarr, 7) == 0);

  /* leafs */
  assert(btarr_has_left(btarr, 8) == 0);
  assert(btarr_has_right(btarr, 8) == 0);
  assert(btarr_has_parent(btarr, 8) == 1);
  assert(btarr_is_root(btarr, 8) == 0);

  assert(btarr_has_left(btarr, 11) == 0);
  assert(btarr_has_right(btarr, 11) == 0);
  assert(btarr_has_parent(btarr, 11) == 1);
  assert(btarr_is_root(btarr, 11) == 0);

  assert(btarr_has_left(btarr, 15) == 0);
  assert(btarr_has_right(btarr, 15) == 0);
  assert(btarr_has_parent(btarr, 15) == 1);
  assert(btarr_is_root(btarr, 15) == 0);
}

void		test_btarr_height_and_depth(t_btarr *btarr)
{
  /* root */
  assert(btarr_get_height(btarr, 1) == TEST_ROOT_HEIGHT);
  assert(btarr_get_depth(btarr, 1) == 0);

  /* nodes in the middle */
  assert(btarr_get_height(btarr, 2) == TEST_ROOT_HEIGHT - 1);
  assert(btarr_get_depth(btarr, 2) == 1);

  assert(btarr_get_height(btarr, 5) == TEST_ROOT_HEIGHT - 2);
  assert(btarr_get_depth(btarr, 5) == 2);

  assert(btarr_get_height(btarr, 7) == TEST_ROOT_HEIGHT - 2);
  assert(btarr_get_depth(btarr, 7) == 2);

  /* leafs */
  assert(btarr_get_height(btarr, 8) == 0);
  assert(btarr_get_depth(btarr, 8) == TEST_ROOT_HEIGHT);

  assert(btarr_get_height(btarr, 11) == 0);
  assert(btarr_get_depth(btarr, 11) == TEST_ROOT_HEIGHT);

  assert(btarr_get_height(btarr, 15) == 0);
  assert(btarr_get_depth(btarr, 15) == TEST_ROOT_HEIGHT);
}

void		test_btarr_get_xxx_idx(t_btarr *btarr)
{
  /* root */
  assert(btarr_get_left_idx(btarr, 1) == 2);
  assert(btarr_get_right_idx(btarr, 1) == 3);
  assert(btarr_get_parent_idx(btarr, 1) == 0);
  assert(btarr_get_most_left_leaf_idx(btarr, 1) == 8);
  assert(btarr_get_most_right_leaf_idx(btarr, 1) == 15);

  /* nodes in the middle */
  assert(btarr_get_left_idx(btarr, 2) == 4);
  assert(btarr_get_right_idx(btarr, 2) == 5);
  assert(btarr_get_parent_idx(btarr, 2) == 1);
  assert(btarr_get_most_left_leaf_idx(btarr, 2) == 8);
  assert(btarr_get_most_right_leaf_idx(btarr, 2) == 11);

  assert(btarr_get_left_idx(btarr, 5) == 10);
  assert(btarr_get_right_idx(btarr, 5) == 11);
  assert(btarr_get_parent_idx(btarr, 5) == 2);
  assert(btarr_get_most_left_leaf_idx(btarr, 5) == 10);
  assert(btarr_get_most_right_leaf_idx(btarr, 5) == 11);

  assert(btarr_get_left_idx(btarr, 7) == 14);
  assert(btarr_get_right_idx(btarr, 7) == 15);
  assert(btarr_get_parent_idx(btarr, 7) == 3);
  assert(btarr_get_most_left_leaf_idx(btarr, 7) == 14);
  assert(btarr_get_most_right_leaf_idx(btarr, 7) == 15);

  /* leafs */
  assert(btarr_get_left_idx(btarr, 8) == 0);
  assert(btarr_get_right_idx(btarr, 8) == 0);
  assert(btarr_get_parent_idx(btarr, 8) == 4);
  assert(btarr_get_most_left_leaf_idx(btarr, 8) == 8);
  assert(btarr_get_most_right_leaf_idx(btarr, 8) == 8);

  assert(btarr_get_left_idx(btarr, 11) == 0);
  assert(btarr_get_right_idx(btarr, 11) == 0);
  assert(btarr_get_parent_idx(btarr, 11) == 5);
  assert(btarr_get_most_left_leaf_idx(btarr, 11) == 11);
  assert(btarr_get_most_right_leaf_idx(btarr, 11) == 11);

  assert(btarr_get_left_idx(btarr, 15) == 0);
  assert(btarr_get_right_idx(btarr, 15) == 0);
  assert(btarr_get_parent_idx(btarr, 15) == 7);
  assert(btarr_get_most_left_leaf_idx(btarr, 15) == 15);
  assert(btarr_get_most_right_leaf_idx(btarr, 15) == 15);
}

int		main()
{
  t_btarr	*btarr;

  test_btarr_make(&btarr);
  test_btarr_has_xxx(btarr);
  test_btarr_height_and_depth(btarr);
  test_btarr_get_xxx_idx(btarr);
  free(btarr->root);
  free(btarr);
  printf("success\n");
  return (0);
}
