
# 5 任务块 2：扩展交通系统

## 5.1 动机

在本任务块中，将会探讨以下内容：

- 扩展类的层次结构，
- 抽象类和纯虚函数，
- 枚举类，
- 区分和使用 `unique_ptr`、`shared_ptr`、`weak_ptr`，
- 使用和创建模板类，
- 异常处理和自定义异常类，
- 使用外部库，
- 生成均匀分布的随机数。

在这个第二个任务块中，将通过增加一个 `Weg` 类来扩展类的层次结构。由于该类与车辆共享一些属性（例如名称、模拟时间、模拟功能、输出功能等），因此扩展类层次结构并创建一个抽象的基类是有意义的，`Weg` 和 `Fahrzeug` 都从这个基类派生。公共服务功能会被转移到基类中。这在面向对象编程中是常见的情况。

`Weg` 类管理一个车辆列表，并且可以通过模拟该列表中的车辆来进行仿真。

为了计算路线，每当某辆车在一个仿真步骤中返回时，会创建一个新类，来实现某种行为模式。行为模式是设计模式的一个例子。每辆车都有这个类的实例，并且可以在其仿真步骤中使用这个实例来确定其进程。例如，处理异常情况（如停车车辆、行驶车辆到达路线终点）时，会通过异常机制（Exceptions）来处理。为了使仿真更加直观，还将使用带有图形显示功能的库。



---

在复用数据结构和算法时，模板可以用来描述共同的部分。STL 提供了许多预定义的结构，您将使用其中的一些。此外，您还需要为一个特定的列表类型（带有延迟更新的功能）创建一个自定义模板。

为了获得一个全面的了解，请先完整阅读第二个任务块。

### 5.2 复制项目

1. 创建一个名为 "Aufgabenblock_2" 的新空项目。将所有源文件（只包括 `.h` 和 `.cpp` 文件）从 "Aufgabenblock_1" 复制到该项目，并按照第 3.2.3 节的说明将这些文件导入新项目。

2. 将项目的 C++ 方言更改为 C++17。右键点击项目并选择 "Properties"。然后选择 "C/C++ Build → Settings"。在右侧的面板中选择 "Tool Settings"。接着打开 "GCC C++ Compiler → Dialect"，在右侧找到 "Language standard" 并将其设置为 "ISO C++ 17 (-std=c++17)"。

### 5.3 仿真对象与路径

1. 首先创建一个抽象基类 "Simulationsobjekt"，用于结合 `Fahrzeug` 和新的 `Weg` 类的共同属性。车辆和路径都是仿真对象，它们都有名称、ID 和本地时间。它们可以被仿真和输出。将 `Fahrzeug` 集成到这个新的类层次结构中，并将名称、ID 和仿真时间变量，以及 `Fahrzeug` 和 `Weg` 共有的功能，转移到 `Simulationsobjekt` 类中。同时，将析构函数的输出移到新类中，以确保对象可以被正确删除。删除 `Fahrzeug` 中现在多余的变量和函数。

请注意，`Fahrzeug` 中的变量和方法需要被调整或删除。`Simulationsobjekt` 是一个抽象类，至少包含一个纯虚方法。仔细考虑哪些函数应该是虚函数。哪些方法/变量需要声明为 `private`、`protected` 或 `public`？是否有必要禁止复制构造函数以防止错误复制？您是否需要调整赋值运算符？实现一个比较操作符（`operator==()`），确保当两个对象的 ID 相同时返回 `true`。

---

为了避免代码重复，应在输出时复用父类的 `vAusgeben` 方法。例如，在 `Fahrzeug` 中调用 `vAusgeben` 方法时，首先应调用 `Fahrzeug` 的方法，然后再调用 `Simulationsobjekt` 的方法。`Simulationsobjekt::vAusgeben` 只应输出对象的 ID 和名称。由于这种结构的原因，输出操作符（`operator<<`）不应在 `Simulationsobjekt` 类中定义，而应在派生类中定义。此原则同样适用于构造函数：构造函数应调用父类的构造函数，以初始化父类的变量。父类构造函数的调用应在初始化列表中进行。

2. 将 `Weg` 类设为 `Simulationsobjekt` 的子类。路径应具有以下属性：长度（`p_dLaenge`）、车辆列表（`p_pFahrzeuge`，存储当前在路径上的车辆），以及允许的最大速度（`p_eTempolimit`）。车辆列表应使用智能指针 `unique_ptr`，并用 STL 的 `list` 容器来实现列表。

路径应分为不同的类别（市内道路、乡间道路和高速公路），它们的速度限制分别为 50km/h、100km/h 和无限制。对于高速公路速度限制，可以使用常量 `std::numeric_limits<double>::max()`。定义一个名为 `getTempolimit` 的转换函数，该函数返回 `p_eTempolimit` 代表的速度限制值，并以 `double` 类型返回。

`Weg` 应具有一个默认构造函数，以及一个带有名称、长度和可选速度限制（默认值为“无限制”）的构造函数。此外，还应实现 `vSimulieren()` 方法，该方法会模拟路径上的车辆。通过基于范围的循环遍历 `list` 列表来模拟所有车辆。

**注意**：当两个类都包含对方的变量作为成员时（例如，一个 `Weg` 包含 `Fahrzeug` 类的实例），不能在两个头文件中互相包含对方的头文件，否则会导致递归包含。解决此问题的常用方法是只在一个头文件中包含类的声明，而不是定义。例如，在 `Fahrzeug` 的头文件中包含 `class Weg;` 声明即可。同样，在 `Weg` 的头文件中包含 `class Fahrzeug;`。在 `.cpp` 文件中才应包含完整的头文件。为了避免头文件中的循环依赖问题，可以遵循这个常见的经验法则：只有当一个类需要使用另一个类的完整定义时，才需要在头文件中包含它。否则，只需要前向声明即可。在 `.cpp` 文件中，需要包含所有使用到的头文件，以提供函数接口。

为 `Weg` 实现一个 `vAusgeben` 方法，以支持重载输出操作符。

---



---

输出操作符可以用来调用 `Simulationsobjekt` 的实现，以显示 ID 和名称。函数还应显示路径的长度，并以括号的形式输出在该路径上的车辆名称。

定义一个名为 `vKopf()` 的类函数，用于输出路径的标题，格式如下：

```
ID | Name       | Länge  | Fahrzeuge
---------------------------------------
0  | weg        : 100    | ()
```

3. 测试您的旧主程序。它应当保持原样工作。在 `vAufgabe_4()` 中额外测试新类 `Weg`，通过创建一个 `Weg` 对象并使用 `<<` 操作符输出标准显示格式。

### 5.4 停车和行驶的车辆

1. 为了让车辆具备不同的行为模式，`Fahrzeug` 类将扩展一个成员变量 `p_pVerhalten`，该变量保存指向一个即将实现的 `Verhalten` 类的实例。通过更改该对象，可以改变车辆的行为，而无需创建新车辆实例。`p_pVerhalten` 应使用智能指针来管理。

在此，“行为”指的是车辆在行驶和停车之间的不同模式。

由于行为取决于所行驶的路径，`Verhalten` 类应有一个构造函数，该构造函数接受一个 `Weg` 的引用并保存它。同时，还应提供一个函数 `double dStrecke(Fahrzeug& aFzg, double dZeitIntervall)`，用来计算车辆在给定时间间隔内能够行驶的距离，而不超过路径的终点。当前在 `Fahrzeug::vSimulieren` 中的部分距离计算将被 `dStrecke` 替代。为了能读取 `Weg` 和 `Fahrzeug` 的私有变量，可能需要编写新的 Getter 函数。

注意：`dStrecke` 在每个仿真步骤中只能调用一次，且中间结果应被暂时存储。

当每辆车从一条路径出发时，将为其创建一个 `Verhalten` 实例，并将其保存在 `Fahrzeug` 中。这最好通过一个新的成员函数 `Fahrzeug::vNeueStrecke(Weg&)` 实现，该函数创建适当的 `Verhalten` 对象，并将其存储在 `p_pVerhalten` 中。那么，当车辆被设置到新的路径时，旧的 `Verhalten` 实例会发生什么呢？

当车辆在不同路径之间行驶时，应为 `Fahrzeug` 增加一个新的成员变量 `p_dAbschnittStrecke`，该变量始终存储车辆在当前路径上行驶的总距离。

---



---

将 `Verhalten` 类扩展为一个类层次结构，其中 `Fahren` 和 `Parken` 作为 `Verhalten` 的子类。

`Verhalten` 应实现为抽象基类。`Fahren` 的功能与以前的 `Verhalten` 相同，因此请直接继承，而无需重复代码。`Parken` 类有一个构造函数，它除了接收路径之外，还接收车辆的开始时间。`Parken::dStrecke()` 在到达开始时间之前返回 0.0，当开始时间到达时，程序应首先输出一条相应的消息。

在一条路径上既可以有停车的车辆，也可以有行驶的车辆。为了区分两者，`vAnnahme(unique_ptr<Fahrzeug>)` 函数应重载为另一个版本 `vAnnahme(unique_ptr<Fahrzeug>, double)`。当只传递一个指向 `Fahrzeug` 的指针时，它应像之前一样处理行驶的车辆。但如果还传递了一个时间，则该车辆应被视为停车车辆。所有车辆将存储在现有列表中。

在 `Fahrzeug::vNeueStrecke` 函数中添加相应的代码，将停车车辆和行驶车辆添加到列表中。停车车辆的属性稍后可能会被忽略。

5. 修改 `vAufgabe_5`，使得程序在启动或到达终点时输出相应的消息。您也可以使用调试器进行测试。

### 5.5 开车、到达终点（异常处理）

1. 目前，程序在两处仅输出“开车”和“到达终点”的消息。相反，每当发生这种情况时，应该抛出（`throw`）一个异常（`Exception`），然后可以在路径的仿真方法中捕获（`catch`）并处理该异常。由于有几种不同类型的异常，建议为这些异常创建一个类层次结构。

从抽象类 `Fahrzeugausnahme` 派生出两个类：`Losfahren` 和 `Streckenende`。此外，`Fahrzeugausnahme` 类应继承自 C++ 标准库中的 `exception` 类，以便获得其优势。`Fahrzeugausnahme` 类应包含对 `Fahrzeug` 和 `Weg` 的引用作为成员变量。这些引用存储引发异常时的车辆和路径，并实现相应的构造函数来设置这两个引用。此外，类应具有一个虚函数 `vBearbeiten()`。暂时只为车辆、路径和异常的类型提供处理方法。

---

---

当异常发生时（之前的输出），现在应该抛出相应的对象，并在路径的仿真例程中捕获。捕获到异常对象后，只需调用其处理函数 `vBearbeiten()` 即可。

**注意**：使用一个 `catch` 块捕获这两种异常。为什么这是可能的？

2. 通过 `Verhalten` 类，车辆和派生类能够了解当前行驶的路径。考虑到路径的最大速度限制（`Weg::p_eTempolimit`），该限制仅适用于轿车（`PKW`）。通过实现 `PKW::dGeschwindigkeit()`，让其适应当前路径的速度限制。为带有速度限制的路径定义一个测试。

3. 使用 `vAufgabe_6` 中实现的异常处理和速度限制进行测试。创建两个路径（至少一个带有速度限制），并设置行驶和停车的车辆在这些路径上。启动仿真并完成测试。

**注意**：当车辆到达路径终点或达到开始时间时，异常 `Streckenende` 和 `Losfahren` 会在每个仿真步骤中重新抛出，因此消息可能会多次出现。由于尚未从列表中删除或移动车辆，这种行为不是错误。

4. **使用调试器的任务**：使用调试器检查车辆是否在正确的时间点起步。让车辆在时间点 3.0 起步。分别在全局时间为 0.25 和 0.3 时检查起点是否正确。如果需要，调整代码以确保车辆能在时间点 3.0 起步。

### 5.6 图形输出

1. 为了让仿真更加直观，应提供图形显示功能。为此，已开发了一个客户端/服务器模型，服务器通过 TCP/IP 接收命令，并将其转化为图形显示。

图形接口由 `SimuClient` 和 `SimuClientSocket` 类提供。图形服务器通过 Java 文件 `SimuServer.jar` 启动。要使用图形界面，首先将以下必需的文件复制到您的项目目录（文件夹包含 `.cpp` 和 `.h` 文件，例如 `Aufgabenblock_3`）中：

- `SimuClient.h`
- `Simuclient.cpp`
- `SimuClientSocket.h`
- `SimuClientSocket.cpp`
- `SimuServer.jar`

这些文件可以在 Moodle 上的模板文件部分找到。

---



---

### 图形接口

图形库的函数只处理传递的值，并不了解您项目中的其他数据。在调用时，会对值进行语法和语义合理性检查。这意味着：

a) 数值必须在一个合理的范围内。

b) 名称只能包含字母、数字和下划线，尤其不能包含空格。

c) 车辆只能绘制在通过两条路径定义的道路上。

图形接口提供以下函数：

- `bInitialisiereGrafik(int GroesseX, int GroesseY);`

  通过此函数，您可以与图形服务器建立连接，并初始化窗口的大小。变量 `GroesseX` 和 `GroesseY` 决定了图形显示的大小。例如，使用以下值：
  
  ```cpp
  GroesseX = 800;
  GroesseY = 500;
  ```

  示例调用：

  ```cpp
  bInitialisiereGrafik(800, 500);
  ```

- `vSetzeZeit(double Zeit);`

  使用此函数，您可以在输出窗口的标题栏中显示全局时间。

- `bZeichneStrasse(string NameHin, string NameRueck, int Laenge, int AnzahlKoord, int[] Koordinaten);`

  此函数绘制一条由名称标识的道路，该道路由一系列坐标组成。道路的路径由至少两个点（直线）定义，坐标通过数组 `Koordinaten` 提供。数组包含 `AnzahlKoord` 个 X/Y 坐标对。对于一条直线道路，坐标值示例为：

  ```cpp
  { 700, 250, 100, 250 };
  ```

  **注意**：
  
  a) 确保 X/Y 坐标值在通过 `bInitialisiereGrafik()` 定义的边界内。

  b) 数组必须包含正好 `2 * AnzahlKoord` 个 `int` 元素。

  c) 每条道路只能调用此函数一次。

- `bZeichnePKW(string PKWName, string WegName, double RelPosition, double KmH, double Tank);`

---



---

当车辆到达终点时，它会立即从列表中删除。为此，编写一个函数 `unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug&)`。在该函数中，您需要在存储的列表 `list<unique_ptr<Fahrzeug>>` 中查找传递的车辆。使用 `operator==` 来比较车辆，并注意空指针的特殊情况。当找到车辆时，将 `unique_ptr` 移动（`move`）到局部变量，并从列表中删除该车辆。然后，您可以返回之前本地存储的指针。通过 `Weg::pAbgabe` 和 `Weg::vAnnahme` 函数，您现在可以调整 `Losfahren` 的处理函数。

- **车辆到达终点**：修改 `Streckenende` 的处理函数，使到达终点的车辆从列表中删除。

测试这些功能：再次运行 `vAufgabe_6`。实现后，仿真不应再出现错误。当车辆到达路径终点时，迭代器应正确地更新列表，避免在删除后继续引用已不存在的车辆。同样，仿真不应在删除或转移车辆后出现未定义行为。

为避免这些问题，应该实现一个通用的模板类 `VListe`，并在命名空间 `vertagt` 中进行实现，该类允许推迟对元素的插入和删除操作，直到调用 `vAktualisieren` 方法为止。为便于理解，已提供模板类的框架文件 `vertagt.liste.h` 和 `vertagt.aktion.h`（可在 Moodle 的模板文件部分找到）。将这些文件添加到您的项目中，并在文件的标记区填入代码。为确保您找到了所有标记区域，可以在 Eclipse 中使用 `Ctrl + F` 搜索。

`VListe` 类包含两个数据成员：

a) 一个保存实际对象的列表 `list<T> p_objekte`，对象属于模板类型 `T`。

b) 一个用于暂存即将执行的操作的列表 `list<unique_ptr<Aktion>> p_aktionen`。

我们区分了读取操作和写入操作：读取操作会立即在实际列表上执行，写入操作则需要暂存为“动作”。 

对于写入操作，建立了一个类层次结构，其中包含一个抽象基类 `VAktion`（见图 5.3），该基类仅包含一个函数 `vAusfuehren()`，以及对要操作列表的引用 `p_pListe`。

---



---

写入操作会派生一个子类自 `VAktion`，例如 `VPushFront`、`VPushBack` 和 `VErase`。在子类的构造函数中，将传递写入操作的参数以及对实际列表的引用，否则无法访问列表。子类中的重载函数 `vAusfuehren()` 将执行实际的操作。

`VListe` 的 `vAktualisieren()` 函数遍历待处理操作的列表，并通过 `vAusfuehren()` 方法处理每个元素。请注意，使用的对象会从操作列表中移除。`VListe` 的功能在图 5.2 中以示意图形式再次展示。

要为延迟列表实现以下功能：

- `iterator begin()`：返回指向第一个元素的迭代器。
- `iterator end()`：返回指向最后一个元素之后的迭代器。
- `bool empty()`：返回对象是否为空。
- `void push_front(T obj)`：在列表开头插入 `obj`。
- `void push_back(T obj)`：在列表末尾插入 `obj`。
- `void erase(iterator it)`：删除迭代器 `it` 位置的元素。
- `void vAktualisieren()`：更新 `p_objekte`。
- `void clear()`：更新列表并清除 `p_objekte` 中的所有元素。

2. 在 `vAufgabe_6a()` 中测试您的新 `VListe`，创建一个延迟列表 `vertagt::VListe`，其中包含 1 到 10 之间的整数随机数。依次在列表上执行以下操作：

- 输出列表。
- 在循环中删除所有大于 5 的元素。
- 再次输出列表（由于 `vAktualisieren()` 尚未执行，因此输出应相同）。
- 调用 `vAktualisieren()` 来更新列表。
- 再次输出列表（此时列表应已更改）。
- 最后，在列表的开头和末尾插入两个随机值，并再次输出列表进行检查。

**提示**：要生成一个 `a` 到 `b` 之间的整数随机数，可以使用以下代码：

```cpp
#include <random>

static std::mt19937 device(seed);
std::uniform_int_distribution<int> dist(a, b);
int zuf = dist(device);
```

---

---

简而言之：我们使用伪随机生成器来生成随机数。在第 1 行中，我们创建一个静态变量 `device`，该变量确定所使用的算法（`mt19937`，即 Mersenne Twister 引擎）和初始值（`seed`）。在第 2 行中，我们创建一个分布（均匀分布的整数）并设置所需的区间 `[a, b]`。在第 3 行中，通过生成器和分布，确定相应的随机数。通过反复调用 `dist(device)` 可以生成多个随机数。有关详细信息，请参阅 `<random>` 库。**注意**：为了获得可复现的结果，我们选择了 `seed` 的固定值（0）。

3. 现在，将 `Weg` 中的车辆列表替换为相应的 `vertagt::VListe`。您应在每次仿真前后更新路径列表。注意，在使用整数模板时，还需要进行所有权转换的调整，因为您使用了 `unique_ptr`。再次测试 `vAufgabe_6()`，不应再出现内存保护错误。检查车辆是否被正确地添加到列表中，并在路径的终点被从列表中删除。确保相应的车辆对象自动删除。

---