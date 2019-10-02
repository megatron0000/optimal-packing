#pragma once
#include <memory>
#include <vector>

/**
 * When used for edge set of undirected graph, must contain all entries (i <->
 * j) even though they are simmetrical.
 */
template <class T>
using Matrix = std::vector<std::vector<T>>;

template <class T>
using Vector = std::vector<T>;

template <class T>
using uptr = std::unique_ptr<T>;

template <class T>
using sptr = std::shared_ptr<T>;

template <class T>
struct PairOf {
  T x;
  T y;
};

template <typename... T>
using Tuple = std::tuple<T...>;

template <typename T>
using Pair = std::pair<T, T>;

enum class AdditionTo { E_PLUS, E_MINUS, NONE };

typedef int Dimension;

typedef Pair<int> Edge;

typedef bool EdgeQ;

typedef bool NodeQ;

typedef Tuple<Edge, AdditionTo, Dimension> Augmentation;

enum class Status { EXIT, OK, FIX, BRANCH };

class SearchNode {
 public:
  Vector<Matrix<bool>> positive_sets;
  Vector<Matrix<bool>> negative_sets;
  Augmentation next_aug;
  SearchNode(Vector<Matrix<bool>> positive_sets,
             Vector<Matrix<bool>> negative_sets, Augmentation next_aug)
      : positive_sets(positive_sets),
        negative_sets(negative_sets),
        next_aug(next_aug) {}
  SearchNode(SearchNode&& other) {
    positive_sets = std::move(other.positive_sets);
    negative_sets = std::move(other.negative_sets);
    next_aug = other.next_aug;
  }
};
