#include "basedefs.h"

/**
 * Returns a feasible augmentation (i.e. one that avoids an excluded
 * configuration) via `out_augmentation`.
 *
 *
 */
Status find_augmentation(Vector<bool>& nodes,
                         Vector<Matrix<bool>>& positive_sets,
                         Vector<Matrix<bool>>& negative_sets,
                         Augmentation& out_augmentation, Vector<int> node_costs,
                         int allowed_cost);

/**
 * Updates positive/negative set based on `aug`. Then checks the viability of
 * the resulting search space, and returns the result.
 */
Status incorporate_augmentation(Vector<bool>& nodes,
                                Vector<Matrix<bool>>& positive_sets,
                                Vector<Matrix<bool>>& negative_sets,
                                Augmentation& aug, Vector<int>& node_costs,
                                int allowed_cost);

/**
 * Returns the packing class (if one is found)
 */
Vector<Matrix<bool>> solve_opp(Vector<bool>& nodes, Vector<int>& node_costs,
                               int allowed_cost, int dimensions);