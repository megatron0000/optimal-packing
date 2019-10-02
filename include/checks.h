#include "basedefs.h"

/**
 * Detects which dimensions do not contain `aug` in their `positive_sets`.
 *
 * If none, returns EXIT (the search space is empty).
 *
 * If only one, updates `negative_set` of the
 * corresponding dimension, since this edge is guaranteed to be excluded from
 * positive set, since including it there would to lead to physical overlap.
 *
 * Else, does nothing.
 */
Status avoid_overlap(Augmentation& aug, Vector<Matrix<bool>>& positive_sets,
                     Vector<Matrix<bool>>& negative_sets,
                     Vector<Augmentation>& out_aug_list);

/**
 * Detects edges that could lead to a chordless C4 in any `positive_set`, and
 * places these edges either in a `positive_set` or a `negative_set` (of the
 * corresponding dimension) when this is guaranteed to be necessary to avoid the
 * C4.
 */
Status avoid_C4(Vector<bool>& nodes, Augmentation& aug,
                Vector<Matrix<bool>>& positive_sets,
                Vector<Matrix<bool>>& negative_sets,
                Vector<Augmentation>& out_aug_list);

/**
 * Tries to find an unfeasible clique in the aug.dim'th negative set. Returns
 * EXIT if one is found.
 */
Status avoid_infeasible_clique(Vector<bool>& nodes, Augmentation& aug,
                               Vector<Matrix<bool>>& positive_sets,
                               Vector<Matrix<bool>>& negative_sets,
                               Vector<int>& node_costs, int allowed_cost);