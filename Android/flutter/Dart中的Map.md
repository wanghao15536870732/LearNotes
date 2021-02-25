# Dart中的Map

`以下是一些创建 Map 的方式：`

```dart
var map1 = {};
map1['first'] = 'partridge';
map1['second'] = 'turtledoves';
map1['fifth'] = 'golden rings';

var map2 = Map();
map2[2] = 'helium';
map2[10] = 'neon';
map2[18] = 'argon';

var map3 = {
  // Key:    Value
  'first': 'partridge',
  'second': 'turtledoves',
  'fifth': 'golden rings'
};

var map4 = {
  2: 'helium',
  10: 'neon',
  18: 'argon',
};
```

`创建一个编译时的常量 map:`

```dart
final constantMap = const {
  2: 'helium',
  10: 'neon',
  18: 'argon',
};
```

`当然，你不能再对它有任何修改了。`