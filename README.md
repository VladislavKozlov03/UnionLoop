# Loop Analyzer: Nesting of Reducible and Irreducible Loops


### Реализация алгоритма анализа вложенных циклов из статьи **"Nesting of Reducible and Irreducible Loops"** (Paul Havlak, 1997, ACM Transactions on Programming Languages and Systems).


### Данный проект реализует классический алгоритм `analyze_loops` и вспомогательную процедуру `fix_loops` для построения **дерева вложенности циклов** в произвольном графе потока управления (CFG). Алгоритм способен:

### 1. Обнаруживать **reducible** и **irreducible** циклы
### 2. Строить **дерево вложенности** циклов
### 3. Максимизировать количество reducible циклов через нормализацию графа



# Алгоритм `analyze_loops`:

## Алгоритм адаптирует метод Тарьяна для тестирования reducibility:

### 1. **DFS нумерация** узлов, сохранение `last[v]` — номера последнего потомка
### 2. **Классификация рёбер** на `backPreds` и `nonBackPreds` через `isAncestor(w, v)`
### 3. **Обработка в обратном порядке** DFS номеров (от `N` до `1`)
### 4. **Построение тела цикла** через распространение от источников обратных рёбер
### 5. **Union-Find** для объединения узлов цикла под представителем-заголовком
### 6. **Обнаружение irreducibility** при нахождении входа в цикл не через заголовок

# Процедура `fix_loops`:

### Проблема: в irredicible графах один узел может быть заголовком и reducible, и irreducible цикла.

### Решение: **расщепление** узлов с reducible обратными рёбрами и более чем одним другим входящим ребром:
### - Создаётся новый пустой узел `w'`
### - Все `otherIn` рёбра перенаправляются на `w'`
### - Reducible обратные рёбра остаются напрямую к `w`

### Результат: каждый reducible backedge гарантированно ведёт к уникальному заголовку reducible цикла.


## Архитектура проекта:
```
loop-analyzer/
├── include/
│ ├── analyze_loops.hpp 
│ ├── fix_loops.hpp
│ ├── cfg.hpp
│ ├── dfs.hpp 
│ ├── dom.hpp
│ └── union_find.hpp
├── src/
│ ├── analyze_loops.cpp
│ ├── fix_loops.cpp
│ ├── cfg.cpp
│ └── dfs.cpp
├── test/
│ ├── test_loops.cpp
│ └── test_fixtures.hpp
├── CMakeLists.txt
└── README.md
```