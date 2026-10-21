# Контрольная работа 3 Вариант 4

Для варианта 4 выполнены три задания из соответствующих разделов методички.

1. `task1_recursive_reverse.cpp` рекурсивно выводит строку в обратном порядке.
2. `task2_file_spaces.cpp` читает `input.txt`, заменяет каждый обычный пробел символом `_` и выводит результат на экран. Переводы строк сохраняются.
3. `task3_reformat_date.cpp` преобразует корректную дату из формата `дд.мм.гггг` в `гггг-мм-дд`. Дополнительно проверяется существование календарной даты, включая високосные годы.

Сборка каждого решения:

```text
g++ -std=c++17 -Wall -Wextra -Werror -pedantic task1_recursive_reverse.cpp -o task1
g++ -std=c++17 -Wall -Wextra -Werror -pedantic task2_file_spaces.cpp -o task2
g++ -std=c++17 -Wall -Wextra -Werror -pedantic task3_reformat_date.cpp -o task3
```

Примеры:

```text
Ввод task1: recursion
Вывод: noisrucer

Содержимое input.txt для task2: hello world
Вывод: hello_world

Ввод task3: 29.02.2024
Вывод: 2024-02-29
```

Автоматическая проверка запускается файлом `run_tests.ps1`.
