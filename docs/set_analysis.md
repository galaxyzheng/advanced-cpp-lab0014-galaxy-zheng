# Set Analysis Laboratory

## Core goal
Students must implement a set abstraction over integer values and reason carefully about correctness and complexity.

## Required operations
Students should implement and analyze:

- `insert(value)`
- `contains(value)`
- `erase(value)`
- `clear()`
- `size()`
- `empty()`
- `toVector()`
- `equals(other)`
- `isSubsetOf(other)`
- `unionWith(other)`
- `intersectionWith(other)`
- `difference(other)`

## Analysis expectations
Students should explain:

- average and worst-case complexity of insert, contains, erase, and union operations;
- why duplicate prevention matters for set semantics;
- the difference between a set and a multiset;
- the cost of sorting a set’s contents when returning a vector;
- the trade-offs between array-backed and tree-backed sets;
- how hashing or balancing affects performance in practical implementations.

## Big-O focus
Students should discuss:

- insertion cost
- membership testing cost
- deletion cost
- set equality and subset testing
- union and intersection costs for two sets of size $n$ and $m$
- total cost of converting a set to a sorted vector

## Short writing prompt
In a brief paragraph, explain when a set is preferable to a vector or list, and describe how a hash-based set differs from a balanced-tree set in both performance and guarantees.
