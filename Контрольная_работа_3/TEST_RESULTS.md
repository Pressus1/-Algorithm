# Проверка контрольной работы 3

Команда:

```text
powershell -File run_tests.ps1
```

Результат 20 октября 2026 года:

```text
COMPILED task1_recursive_reverse.cpp
COMPILED task2_file_spaces.cpp
COMPILED task3_reformat_date.cpp
PASS task1 normal
PASS task1 empty
PASS task2 spaces
PASS task3 leap day
PASS task3 year boundary
ALL C03 TESTS PASSED
```

Все исходники собраны как C++17 с флагами `-Wall -Wextra -Werror -pedantic`. Скрипт завершился с кодом 0.
