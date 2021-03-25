Greetings, my excellent friends!

This is the implemention of a function that visualize a tree in php, it prints every php array in shape of tree.
Works fine with `int` , `float/double` . `string` and `bool` values. 

Result:
```
behrad@TadavomnisT:~/Desktop$ php visualize_tree.php 
.
├── 0
│   ├── item_id -> 6
│   ├── price -> 2311.00
│   ├── qty -> 12
│   └── discount -> 0
├── 1
│   ├── item_id -> 7
│   ├── price -> 1231.00
│   ├── qty -> 1
│   └── discount -> 12
└── 2
    ├── item_id -> 8
    ├── price -> 123896.00
    ├── qty -> 0
    └── discount -> 24

------------------------------
.
└── 0
    ├── name -> John
    ├── lastname -> Doe
    ├── country -> Japan
    ├── nationality -> Japanese
    ├── job -> web developer
    └── hobbies
        ├── sports -> soccer
        └── others
            └── freetime -> watching Tv

------------------------------
.
└── root
    ├── first_depth_node1
    │   ├── 0 -> second_depth_node1
    │   ├── second_depth_node2
    │   │   ├── 0 -> third_depth_node1
    │   │   ├── 1 -> third_depth_node2
    │   │   └── third_depth_node3
    │   │       ├── 0 -> fourth_depth_node1
    │   │       └── 1 -> fourth_depth_node2
    │   └── 1 -> second_depth_node3
    └── first_depth_node2
        └── second_depth_node4
            └── third_depth_node3
                └── 0 -> 1

------------------------------
.

------------------------------
.
└── 0 -> 1

------------------------------
.
├── 0 -> T
├── 1 -> Ta
├── 2 -> Tad
├── 3 -> Tada
├── 4 -> Tadav
├── 5 -> Tadavo
├── 6 -> Tadavom
├── 7 -> Tadavomn
├── 8 -> Tadavomni
├── 9 -> Tadavomnis
└── 10 -> TadavomnisT

```
