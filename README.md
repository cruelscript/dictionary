# English-Russian Dictionary

The implementation of a simple dictionary which works with input data base (contains an english and its translation in russian on a new line).

There are implemented some basic operations:
- ```insert(key, value)``` - a method which adds a new word to the dictionary with its key (english word) and value (russian word)
- ```search(key)``` - a method to find a word with a specified key
- ```delete(key)``` - a method to delete a word with a specified key

The dictionary is a Binary Search Tree, where each Node of the Tree contains:
- key - english word
- value (information part) - list of all translations of this word in russian, sorted alphabetically

||Average Time | Worst Time |
|----------|--------|-------|
|Search|O(n)|O(n)|
|Insert|O(log n)|O(n)|
|Delete|O(log n)|O(n)|

# Англо-русский словарь

Реализация простейшего словаря, который работает с входной базой данных слов (содержит английские слова и их русский перевод на следующей строке).

Реализовать следующие базовые операции: 
- ```insert(key, value)``` - добавление записи с указанным ключом и значением
- ```search(key)``` - поиск записи с указанным ключом
- ```delete(key)``` - удаление записи с указанным ключом

Предусмотрена обработка и инициализация исключительных ситуаций, связанных, например, с проверкой значений полей перед инициализацией и присваиванием.

Словарь реализован с помощью бинарного дерева поиска, где каждый узел дерева содержит: 
- Ключ - английское слово
- Информационная часть - список, содержащий переводы английского слова, отсортированные по алфавиту (переводов слова может быть несколько).


||В среднем | В худшем случае |
|----------|--------|-------|
|Поиск|O(n)|O(n)|
|Вставка|O(log n)|O(n)|
|Удаление|O(log n)|O(n)|
