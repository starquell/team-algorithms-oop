---
[![Build Status](https://travis-ci.org/starquell/team-algorithms-oop.svg?branch=master)](https://travis-ci.org/starquell/team-algorithms-oop) 

***Implemented :***
  - Red-Black Tree
  - Splay Tree
  - Undoable Tree (Template that expands tree by undo/redo operations)
  - AnyTree (Stores any instance of any class with Tree interface)
  - TreeDatabase (Saves and loads any tree object with begin(), end())
  ___
  
***Used design patterns (lab requirements):***
  - Iterator (Iterator for BSTs)
  - Prototype (operator= in trees perform cloning)
  - Visitor (std::visit in AnyTree implementation)
  - Singleton (TreeDatabase class)
  - Template method (SplayTree and RBTree inheriting from BSTBase)
  - Memento (UndoableTree stores info about underlying tree operations)
  - Decorator (Undoable tree expands (decorates) underlying class by undo/redo operations)
  - Strategy (AnyTree can use different BST implementations (strategies))
  
  ___
  
   **Perfomance comparing with std::set :**
   
  
| Single insert operation   | Time    |
|--------------|---------|
| SplayTree    | 1766 ns |
| RedBlackTree | 1519 ns |
| std::set     | 1695 ns |

| Single erase operation      	| Time   	|
|--------------	|--------	|
| SplayTree    	| 784 ns 	|
| RedBlackTree 	| 787 ns 	|
| std::set     	| 783 ns 	|
  
  | Iterating all container  	| Time     	| Size of container 	|
  |--------------	            |----------	|-------------------	|
  | SplayTree    	            | 0.006 ns 	| 100000            	|
  | RedBlackTree 	            | 0.006 ns 	| 100000            	|
  | std::set     	            | 0.398 ns 	| 100000            	|
  
  ___
  
***Requirements :***
  - Compiler with full C++17 language and standard library support
  
     **Attention :**
     Usage of TreeDatabase requires linking sqlite3
  ___
  Generated documentation located in `doc/`
  
  **All include headers are in `include/`**
  
 
  ___
  
  Part of the lab - GUI could be built using qmake (using .pro file) 
  ___
  
***Running tests using CMake:***
```
git clone --recursive https://github.com/starquell/team-algorithms-oop.git
cd team-algorithms-oop
mkdir build && cd build
cmake ../
cmake .
ctest
```
Last step can be replaced on 
```
cd bin
./tests
```
___
**Usage examples**
``` C++
using namespace lab;

    {
        forest::SplayTree tree{"2", "aaa", "asd", "439", "haha"};

        tree.insert("ff");
        tree.erase("haha");

        /// Iterating in increasing order
        for (const auto &i : tree) {
            std::cout << i << ' ';
        }

        auto it = tree.search("nope");
        assert (it == tree.end());

        const auto size = tree.size();
    }

    {
        constexpr std::array a = {"2", "aaa", "asd"};

        /// Using other comparator, constructing from iter
        forest::RedBlackTree<std::string, std::greater<>> tree (a.begin(), a.end());

        /// Iterating in decreasing order
        for (const auto &i : tree) {
            std::cout << i << ' ';
        }
    }

    {
        forest::UndoableTree tree (forest::RedBlackTree <std::string> {"aaa", "bbb"});

        tree.insert("s");

        while (true) {      /// he could, but don`t do like this
            tree.undo();
            tree.redo();
        }
    }

    {
        forest::AnyTree <SupportedValueType<double>,
                         SupportedComparators<std::less<>, std::greater<>>> any;

        any = forest::SplayTree<double> {};

        any.insert(34.5);

        any = forest::RedBlackTree<double, std::greater<>>{};
        
        any = forest::UndoableTree <forest::SplayTree<double>>{};
    }

```





