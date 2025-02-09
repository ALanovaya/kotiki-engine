## Описание системы

Система моделирует поведение группы котов на прямоугольной карте, где каждый кот начинает движение в случайном направлении с определенного момента времени. На карте отображаются их перемещения и взаимодействия друг с другом, зависящие от расстояния между котами. Если коты находятся очень близко друг к другу, они начинают драться. Если расстояние между ними больше, но всё ещё в пределах определенного радиуса, они шипят друг на друга с вероятностью обратно пропорциональной расстонию между ними. Когда рядом никого нет, коты спокойно гуляют.
Система позволяет не только наблюдать за поведением котов, но и настраивать параметры симуляции. Пользователь может изменять размер карты, количество котов и их начальные координаты, а также радиусы взаимодействия, влияющие на вероятность драк и шипения.

## Требования

- Приложение должно представлять из себя графический интерфейс, визуализирующий симуляцию поведения котов.
- Приложение должно иметь виджет с настройками размеров поля (длины, ширины), количеством котов, выбором метрики, радиусов взаимодействия котов, времени обновления $\tau$, способа перемещения и кнопкой для включения логирования.
- Наличие счетчика FPS.
- Поддержка количества котов до 50.000 с плавной отрисовкой.
- Для сущностей должны быть созданы спрайты, отобрающие каждый вид состояния.
- Логирование поведения котов в терминале в форме "Cat #N moved to $(x, y)$ and has state `EntityState`". В логах должна отображаться информация о времени суток. В ночное время суток коты менее активны и могут спать, однако все еще могут взаимодействовать между собой.
- Возможность смены дня и ночи с помощью специальной кнопки в виджете.
- Должны быть реализованы следующие метрики: метрика Минковского и её частные случаи: евклидово, манхэттеновское и чебышевское расстояния. Для Чебышевского расстояния в виджете должна быть настройка параметра $p$.
- Должны быть два способа перемещения - случайный и по заданной траектории. Для случайного перемещения в виджете должен быть выбор минимального и максимального шага. Для перемещения по траектории зафиксирована переменная $t$ и должны быть поля для ввода уравнений $x(t)$ и $y(t)$. При вводе некорректной траектории должно появиться соответствующее оповещение.

## Инструменты

### Qt
Фреймворк Qt был выбран в качестве основного инструмента для создания графического интерфейса приложения. Причиной выбора стала простота разработки в сранвении с другими инструментами, кроссплатформенность, крупное сообщество и хорошая документация.

Альтернативы - GTK (обеспечивает хорошую производительность, но менее удобен в использовании и имеет меньшее сообщество в сравнении с Qt), OpenGL (достаточно сложный, низкоуровневый API, который требует значительных усилий для реализации даже базовых сцен).

### Google Test
Для написания и запуска тестов в проекте используется Google Test. Основная причина выбора - Google Test является признаным стандартом, один из самых популярных и гибких фреймворков для тестирования в экосистеме C++. Фреймворк поддерживает тестирование как простых функций, так и сложных классов, предоставляя инструменты для проверки исключений, параметризированных тестов.

### Boost Matheval
Для парсинга уравнений, которые задают траекторию движения используется библиотека Boost Matheval, предосталяющая минимально необходимый набор функциональности для данной задачи.

Альтернативы - ExprTk (легковесный и быстрый, но требует больше усилий для интеграции и настройки), MuParser (более простой, но предоставляет меньше возможностей, чем Boost.Matheval)

## Алгоритм
Для определения состояния сущностей в проекте был выбран алгоритм поиска соседей на основе сеточного разбиения (grid-based lookup). Этот подход обеспечивает высокую производительность за счёт разбиения пространства на равномерные ячейки, что позволяет быстро находить ближайших соседей для сущностей. Простота реализации и эффективность сделали этот алгоритм оптимальным выбором для проекта. Реализация алгоритма была взята из [статьи](https://www.gorillasun.de/blog/particle-system-optimization-grid-lookup-spatial-hashing/).

В качестве альтернативы рассматривался алгоритм Форчуна, используемый для построения диаграммы Вороного. Он отличается высокой точностью и подходит для задач, требующих сложной геометрической обработки. Однако его сложность в реализации и избыточность для текущих целей привели к отказу от этого варианта.

## Устройство проекта

Проект разбит на логические модули, каждый из которых описывает и реализует отдельную функциональность.

### Core

Центральный модуль, содержащий основную логику работы программы. Состоит из следующих подмодулей:
- **Algoritms.** Данный модуль реализует алгоритм для получения текущих состояний объектов. `Algoritm` - абстрактный класс, описывающий конструктор, принимающий параметры $R0$, $R1$ и указатель на используемую метрику; функцию `GetStates`, который по коллекции сущности возвращает вектор состояний сущностей.
`GridLookupAlgorithm` - контретная реализация абстрактного класса `Algorithm`, реализующая ранее описанный алгоритм.

- **Metrics.** Данный модуль реализует метрики для расчёта расстояний между объектами. `Metric`-- абстрактный класс для создания пользовательских метрик. Реализованные метрики:
    - `MinkowskiMetric` - обобщённое расстояние Минковского.
    - `ManhattanMetric` - манхэттенское расстояние (частный случай метрики Минковского, при p = 1).
    - `EuclideanMetric` - евклидово расстояние (частный случай метрики Минковского, при p = 2).
    - `ChebyshevMetric` - расстояние Чебышёва (частный случай метрики Минковского, при p -> infinity).

- **Movers.** Данный модуль описывает классы и функции, позволяющие перемещать сущности. Абстрактный класс `Mover`, содержащий функцию `Move`, которая принимает коллекцию сущностей и перемещает их по какому-то правилу. Данное правило реализуется приватным методом в наследниках данного класса. Функция `FixEntityCoordinates` позволяет "чинить" координаты сущностей, которые вылезли за пределы поля.
    - `RandomMover` - реализация `Mover`, которая перемещает сущности случайным образом (есть возможность задать минимальный и максимальный шаг перемещения).
    - `TrajectoryMover` - реализация `Mover`, которая перемещает сущности по заданным параметрическими уравнениями траекториям.

- **Trajectory.**
Данный модуль реализует возможность парсинга параметризованных уравнений движений и предоставления текущих координат объекта в зависимости от параметра. Состоит из единственного класса `Trajectory`, конструктор которого принимает на вход уравнения $x = x(t), \ y = y(t)$, а также имя параметра. Содержит один публичный метод `GetPosition`, который по заданным начальным координатам и значению параметра возвращает текущие координаты объекта.

### Entities
Данный модуль описывает сущности, с которыми происходит работа и другие объекты с их функциями:
- `Entity` - структура, описывающая сущность (в конкретном случае котики). Имеет два поля, предствляющих собой координаты.
- `Field` - структура, описывающее размеры и расположение поля, на котором могут перемещаться сущности.
- `EntityState` - Enum класс, описывающий возможные состояния сущности (Angry, Calm, и так далее).
- `EntitiesCollection` - класс, являющийся некоторой "оберткой" над вектором сущностей. Предоставляет множество вспомогательных функция для получения и изменения информации о сущностях входящих в него.

### Graphics
Модуль Graphics отвечает за визуальное представление сущностей и взаимодействие с пользователем через графический интерфейс. Он включает в себя классы для отображения сущностей на сцене, управления их движением, анимацией и обработкой событий.
- Класс `Cats` наследуется от `QGraphicsPixmapItem` и представляет визуальную модель сущности (котика) на графической сцене.
    - **Инициализация.** Конструктор позволяет задать изображение и начальные координаты объекта.
    - **Движение.** Метод `MoveTo` задаёт цель перемещения и флаг телепортации.
    - **Обновление позиции.** Метод `UpdatePosition` реализует плавное перемещение объекта к целевой позиции с разделением движения на 30 шагов. Если включён режим телепортации, объект мгновенно перемещается в заданную точку.
    - **Обновление изображения.** Метод `UpdatePixmap` позволяет сменить текущее изображение объекта.
- Класс `MainWindow` управляет сценой, графическими объектами и настройками приложения. Он наследуется от QMainWindow и включает методы для создания, обновления и настройки графической сцены и её содержимого.
    - **Инициализация.** `InitializeScene` создаёт и настраивает графическую сцену, `InitializeEntities` инициализирует сущности (котиков) на сцене, `InitializeWidgets` создаёт пользовательские интерфейсы для управления настройками, `InitializeTimers` настраивает таймеры для обновления графики и логики.
    - **Обновления.** `UpdateSceneRect` обновляет размер сцены при изменении параметров, `UpdateCats` Обрабатывает перемещение и состояния котиков.
    - **Таймеры.** `OnUpdateTimer` обрабатывает обновления графического интерфейса, включая анимацию и перемещение котиков, `OnPointTimer` обновляет логику приложения, включая изменения состояний и перемещение сущностей.
- Класс `SettingsWidget` предназначен для настройки параметров симуляции и является виджетом на основе QDockWidget. Конструктор класса принимает параметры конфигурации симуляции, такие как количество котиков, размеры сцены и радиусы взаимодействия, позволяя создавать и инициализировать виджет. Сигналы, такие как `NumberOfCatsChanged`, `MetricChanged` и прочие, уведомляют другие компоненты приложения об изменении соответствующих параметров.
- Класс `ResizableGraphicsView` расширяет возможности `QGraphicsView`, добавляя интерактивное управление и поддержку ночного фильтра. Конструктор инициализирует вид с заданной сценой и родительским виджетом. Метод `ShowNightFilter` позволяет включать или отключать наложение ночного фильтра.
- Класс `FPSCounter` предназначен для подсчета и обновления количества кадров в секунду (FPS) в приложении. 
    - `FrameRendered` - метод, который вызывается каждый раз, когда новый кадр был отрендерен, и увеличивает счетчик кадров.
    - `GetCurrentFps` - метод, который возвращает текущее количество кадров в секунду.


### Utils
Данный модуль содержит в себе вспомогательные функции для генерации случайных чисел с плавающей точкой в диапазоне от 0.0 до 1.0, а также описывает тип `coord_t` для представления координат.


## Тестирование

- Для проверки корректности работы алгоритма, муверов и расстояний использовались юнит-тесты.
- Для оценки качества пользовательского интерфейса было проведено ручное тестирование командой в роли пользователей приложения.
- Для оценки производительности были проведены замеры FPS для 50.000 сущностей на следующем оборудовании
    - Процессор `11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz`
    - Видеокарта `Nvidia GeForce RTX 3050 Ti 4 Гб`

    При этом FPS стабильно держался на уровне 2-4 кадров в секунду.
